/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011,2012,2013,2014 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#include "config/stm32plus.h"

#if defined(STM32PLUS_F1)

#include "config/exti.h"

using namespace stm32plus;


#if defined(USE_EXTI_RTC_ALARM_INTERRUPT)

extern "C" {

  void __attribute__ ((interrupt("IRQ"))) RTCAlarm_IRQHandler(void) {

    if(EXTI_GetITStatus(EXTI_Line17)!=RESET) {
      ExtiRtcAlarm::_extiInstance->ExtiInterruptEventSender.raiseEvent(17);
      EXTI_ClearITPendingBit(EXTI_Line17);
    }
    __DSB();      // prevent erroneous recall of this handler due to delayed memory write
  }
}

#endif
#endif
