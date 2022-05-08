#include "common/rtos/inc/freertos_hooks.hpp"

#include <cstdio>

#include "semphr.h"
#include "stdarg.h"

static SemaphoreHandle_t xLoggingSemaphore = NULL;
static BaseType_t xLoggingEnter(void);
static void vLoggingExit(void);

void vApplicationMallocFailedHook(void) {
    /* vApplicationMallocFailedHook() will only be called if
     * configUSE_MALLOC_FAILED_HOOK is set to 1 in FreeRTOSConfig.h.  It is a
     * hook function that will get called if a call to pvPortMalloc() fails.
     * pvPortMalloc() is called internally by the kernel whenever a task, queue,
     * timer or semaphore is created.  It is also called by various parts of the
     * demo application.  If heap_1.c, heap_2.c or heap_4.c is being used, then
     * the size of the    heap available to pvPortMalloc() is defined by
     * configTOTAL_HEAP_SIZE in FreeRTOSConfig.h, and the xPortGetFreeHeapSize()
     * API function can be used to query the size of free heap space that
     * remains (although it does not provide information on how the remaining
     * heap might be fragmented).  See http://www.freertos.org/a00111.html for
     * more information. */
    vAssertCalled(__FILE__, __LINE__);
}

/*-----------------------------------------------------------*/

void vApplicationStackOverflowHook(TaskHandle_t pxTask, char *pcTaskName) {
    (void)pcTaskName;
    (void)pxTask;

    /* Run time stack overflow checking is performed if
     * configCHECK_FOR_STACK_OVERFLOW is defined to 1 or 2.  This hook
     * function is called if a stack overflow is detected.  This function is
     * provided as an example only as stack overflow checking does not function
     * when running the FreeRTOS POSIX port. */
    vAssertCalled(__FILE__, __LINE__);
}

/*-----------------------------------------------------------*/

static BaseType_t xLoggingEnter(void) {
    BaseType_t xResult;

    if (xTaskGetSchedulerState() == taskSCHEDULER_NOT_STARTED) {
        xResult = pdFALSE;
    } else {
        if (xLoggingSemaphore == NULL) {
            /* Create a mutex. */
            xLoggingSemaphore = xSemaphoreCreateMutex();
        }

        if (xLoggingSemaphore != NULL) {
            /* Never wait longer than e.g. 100 ms. */
            TickType_t xTicksToWait = pdMS_TO_TICKS(100);

            xResult = xSemaphoreTake(xLoggingSemaphore, xTicksToWait);
        } else {
            xResult = pdFALSE;
        }
    }
    return xResult;
}

static void vLoggingExit(void) {
    /* Code below has confirmed that the semaphore has been
    created and that it has been taken by vLoggingPrintf().
    Now release it. */
    xSemaphoreGive(xLoggingSemaphore);
}

void vLoggingPrintf(const char *pcFormat, ...) {
    if (xLoggingEnter() != pdFALSE) {
        va_list xArgs;

        va_start(xArgs, pcFormat);
        vprintf(pcFormat, xArgs);
        va_end(xArgs);

        vLoggingExit();
    }
}

/*-----------------------------------------------------------*/

void vAssertCalled(const char *const pcFileName, unsigned long ulLine) {
    static BaseType_t xPrinted = pdFALSE;
    volatile uint32_t ulSetToNonZeroInDebuggerToContinue = 0;

    /* Called if an assertion passed to configASSERT() fails.  See
     * https://www.FreeRTOS.org/a00110.html#configASSERT for more information.
     */

    /* Parameters are not used. */
    (void)ulLine;
    (void)pcFileName;

    taskENTER_CRITICAL();
    {
        /* Stop the trace recording. */
        if (xPrinted == pdFALSE) {
            xPrinted = pdTRUE;
        }

        /* You can step out of this function to debug the assertion by using
         * the debugger to set ulSetToNonZeroInDebuggerToContinue to a non-zero
         * value. */
        while (ulSetToNonZeroInDebuggerToContinue == 0) {
            __asm volatile("NOP");
            __asm volatile("NOP");
        }
    }
    taskEXIT_CRITICAL();
}
