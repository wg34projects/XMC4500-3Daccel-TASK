/**
 * @file		3Daccel_out_driver.c
 * @version		v1.0
 * @date		Jan 2018
 * @author		Egermann, Resch
 *
 * @brief		3Daccel out driver
 */

#include "3Daccel_out_driver.h"
#include "3Daccel_out_library.h"

/**
 * @brief	function to init LED output
 * @param	none
 * @return	none
 *
 */
void outputInitXMC(void)
{
    // config LED output

    XMC_GPIO_CONFIG_t config_out;
    config_out.mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL;
    config_out.output_level = XMC_GPIO_OUTPUT_LEVEL_LOW;
    config_out.output_strength = XMC_GPIO_OUTPUT_STRENGTH_WEAK;
    XMC_GPIO_Init(LED1, &config_out);
}

/**
 * @brief	read buttons debounce
 * @param	none
 * @return	none
 *
 */
void readButtonDebounceXMC()
{
    // read both onboard buttons with debounce

    if ((XMC_GPIO_GetInput(BUTTON1) == 0) && (button1pressed == 0))
    {
        button1pressed = 1;
    }
    if ((XMC_GPIO_GetInput(BUTTON1) == 0) && (button1pressed == 1))
    {
        button1pressed = 2;
    }
    if ((XMC_GPIO_GetInput(BUTTON1) == 1) && (button1pressed == 2))
    {
        if (circularAdd(BUTTON1INT) == 1)
        {
            button1pressed = 0;
        }
    }

    if ((XMC_GPIO_GetInput(BUTTON2) == 0) && (button2pressed == 0))
    {
        button2pressed = 1;
    }
    if ((XMC_GPIO_GetInput(BUTTON2) == 0) && (button2pressed == 1))
    {
        button2pressed = 2;
    }
    if ((XMC_GPIO_GetInput(BUTTON2) == 1) && (button2pressed == 2))
    {
        if (circularAdd(BUTTON2INT) == 1)
        {
            button2pressed = 0;
        }
    }
}

/**
 * @brief	function to set LED
 * @param	LED state <br>
 *			0 for LED off <br>
 *			1 for LED on <br>
 *			other for LED toggle <br>
 * @return	none
 *
 */
void ledSettingXMC(uint8_t ledState)
{
    // LED settings

    if (ledState == 0)
    {
        XMC_GPIO_SetOutputLow(XMC_GPIO_PORT1, 0);
    }
    else if (ledState == 1)
    {
        XMC_GPIO_SetOutputHigh(XMC_GPIO_PORT1, 0);
    }
    else
    {
        XMC_GPIO_ToggleOutput(LED1);
    }
}

/**
 * @brief	intialize input GPIOs
 * @param	none
 * @return	none
 *
 */
void inputInitXMC()
{
    // init onboard buttons

    XMC_GPIO_CONFIG_t config_in;
    config_in.mode = XMC_GPIO_MODE_INPUT_INVERTED_PULL_UP;
    XMC_GPIO_Init(BUTTON1, &config_in);
    XMC_GPIO_Init(BUTTON2, &config_in);
}

/** EOF **/
