#pragma once

#include "extern/rtos/include/FreeRTOS.h"
#include "extern/rtos/include/task.h"

void vApplicationMallocFailedHook(void);

void vApplicationStackOverflowHook(TaskHandle_t pxTask, char *pcTaskName);

void vLoggingPrintf(const char *pcFormat, ...);

void vAssertCalled(const char *const pcFileName, unsigned long ulLine);