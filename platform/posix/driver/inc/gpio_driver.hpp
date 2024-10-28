#pragma once

#include "common/interface/inc/drivers.hpp"

namespace Driver {

class Gpio : public Common::Interface::Gpio {
   public:
    Gpio(Common::Interface::Functionality functionality){};

    virtual void toggle() final;
    virtual void on() final;
    virtual void off() final;

   private:
    bool m_state{false};
};

}  // namespace Driver
