#pragma once

namespace Common {
namespace Interface {

class Gpio {
   public:
    virtual ~Gpio() = default;

    virtual void on() = 0;
    virtual void off() = 0;
    virtual void toggle() = 0;
};

}  // namespace Interface
}  // namespace Common