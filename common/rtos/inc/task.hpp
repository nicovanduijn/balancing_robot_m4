#pragma once

#include <string>

#include "common/rtos/inc/freertos_hooks.hpp"
#include "extern/rtos/include/FreeRTOS.h"

namespace Common {
namespace Rtos {

class Task {
   public:
    Task(const std::string& taskName, uint32_t stack_size,
         uint32_t task_priority)
        : m_taskName{taskName} {
        xTaskCreate(threadForwarder, m_taskName.c_str(), stack_size, this,
                    task_priority, &m_taskHandle);
    }

    Task(const Task& other) = delete;
    Task(const Task&& other) = delete;
    virtual ~Task() { vTaskDelete(m_taskHandle); };
    Task& operator=(Task&& other) = delete;
    Task& operator=(const Task& other) = delete;

    virtual void threadFunction(void) = 0;

   private:
    const std::string m_taskName;
    TaskHandle_t m_taskHandle{nullptr};

    static void threadForwarder(void* thisPointer) {
        auto thread = reinterpret_cast<Task*>(thisPointer);
        thread->threadFunction();
    }
};

}  // namespace Rtos
}  // namespace Common
