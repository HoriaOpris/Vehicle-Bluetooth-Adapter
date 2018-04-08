#include "led_app.h"
#include "../../MCAL/GPT_DRV/gpt_drv.h"

int x = 0;

LedApp::LedApp(void)
{
    GptDriver timer;
    timer.Configure();

    flag = false;

}

void LedApp::Run(void)
{
    if (flag)
    {
        if (x < 100)
        {
            x += 10;
        }
        else
        {
            flag = false;
        }
    }
    else
    {
        if (x > 10)
        {
            x -= 10;
        }
        else
        {
            flag = true;
        }
    }
}
