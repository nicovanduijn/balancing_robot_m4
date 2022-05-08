#pragma once

namespace Common {
namespace Interface {

class Gpio {
   public:
    enum class Function { RUN_LED = 0 };

    Gpio(Function function) {
        (void)function;  // enforce a function is implemented by driver
    };

    virtual ~Gpio() = default;

    virtual void on() = 0;
    virtual void off() = 0;
    virtual void toggle() = 0;
};

}  // namespace Interface
}  // namespace Common