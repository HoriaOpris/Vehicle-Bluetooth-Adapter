#ifndef PWM_DRV_H_
#define PWM_DRV_H_

class PwmDriver
{
public:
    void Configure(void);
    void DutyCycle(unsigned duty);

private:
};

#endif /* PWM_DRV_H_ */
