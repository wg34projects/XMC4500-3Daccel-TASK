#include "servo_driver.h"
#include "servo_library.h"

void initServoPWM()
{
    // onboard alternate function 3 at CCU40 slice 2 = CCU40.OUT2 = CCU40.CC42
    P1_1_set_mode(OUTPUT_PP_AF3);
    P1_1_set_driver_strength(STRONG);
    P1_1_reset();

    // setup CC40 unit with shadow transfer
    SCU_RESET->PRSET0 |= (1 << SCU_RESET_PRSET0_CCU40RS_Pos);		// peripheral 0 reset set - CCU40RS - CCU40 timer
    SCU_RESET->PRCLR0 |= (1 << SCU_RESET_PRCLR0_CCU40RS_Pos);		// peripheral 0 reset clear - CCU40RS - CCU40 timer
    SCU_CLK->CLKSET = (1 << SCU_CLK_CLKSET_CCUCEN_Pos); 			// clock enable register CCUCEN - CCU clock enabled
    CCU40->GIDLC |= (1 << CCU4_GIDLC_SPRB_Pos); 					// global idle clear - SPRB - prescaler run bit set
    CCU40_CC42->PSC = 6; 											// prescaler control - 0 - CCU40.OUT2
    CCU40_CC42->TC |= (1 << CCU4_CC4_TC_CLST_Pos); 					// slice timer control - CLST - shadow transfer on clear - CCU40.OUT2
    CCU40->GIDLC |= (1 << CCU4_GIDLC_CS2I_Pos); 					// global idle clear - C2SI - CC43 idle mode clear - CCU40.OUT2
    SCU_GENERAL->CCUCON |= (1 << SCU_GENERAL_CCUCON_GSC40_Pos);		// CCU control register - GSC40 - global start control CCU40
    CCU40_CC42->PRS = 37500; 										// period register - timer shadow period value - CCU40.OUT2
    CCU40_CC42->TCSET = 1;											// slice timer run set - CCU40.OUT2

    // initial output values
    CCU40_CC42->CRS = 37500;										// compare register - timer shadow compare value - CCU40.OUT2
    CCU40->GCSS |= (1 << CCU4_GCSS_S2SE_Pos); 						// global channel set - S3SE slice 2 shadow transfer set enable
}

uint8_t pwmXMC(double dutycycle)
{
    double dcCalc = 0;
    uint32_t intdcCalc = 0;

    if (dutycycle < 0 || dutycycle > 100)
    {
        return 1;
    }

    dcCalc = 37500 - (37500 * dutycycle * 0.01);
    intdcCalc = (uint32_t)dcCalc;
    CCU40_CC42->CRS = intdcCalc;									// compare register . timer shadow compare value - CCU40.OUT2
    CCU40->GCSS |= (1<<CCU4_GCSS_S2SE_Pos); 						// global channel set - S2SE slice 2 shadow transfer set enable

    return 0;
}


