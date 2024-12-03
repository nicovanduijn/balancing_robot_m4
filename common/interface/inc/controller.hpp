#pragma once
#include <extern/eigen/Eigen/Dense>

namespace Common {
namespace Interface {

class Controller {
   public:
    virtual ~Controller() = default;

    virtual void setCurrentState(const Eigen::Vector4f& state) = 0;
    virtual void setDesiredState(const Eigen::Vector4f& state) = 0;
    virtual float getControl() = 0;
};

}  // namespace Interface
}  // namespace Common