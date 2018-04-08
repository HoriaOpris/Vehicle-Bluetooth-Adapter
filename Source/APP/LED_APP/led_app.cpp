#include "led_app.h"

int x = 0;

LedApp::LedApp(void)
{
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
