#pragma once

namespace Common {
namespace Interface {

class Motor {
   public:
    virtual ~Motor() = default;

    virtual void setMotorSpeed(float speed_normalized) = 0;
};

}  // namespace Interface
}  // namespace Common