#pragma once

#include "common/interface/inc/drivers.hpp"
#include "platform/stm32mp1/generated/CM4/Inc/main.h"

namespace Driver {

Common::Interface::Drivers init_low_level(void);

}  // namespace Driver