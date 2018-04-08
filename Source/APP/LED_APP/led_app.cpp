#include "led_app.h"
#include "../../MCAL/PWM_DRIVER/pwm_drv.h"

static PwmDriver pwm;

LedApp::LedApp(void)
{
    pwm.Configure();

    flag = false;

}

void LedApp::Run(void)
{
    static unsigned duty = 0;

    if (flag)
    {
        if (duty < 100)
        {
            duty += 10;
        }
        else
        {
            flag = false;
        }
    }
    else
    {
        if (duty > 10)
        {
            duty -= 10;
        }
        else
        {
            flag = true;
        }
    }

    pwm.DutyCycle(duty);

}
