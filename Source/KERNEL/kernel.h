/*
 * kernel.h
 *
 *  Created on: Apr 2, 2018
 *      Author: horia
 */

#ifndef KERNEL_H_
#define KERNEL_H_

typedef void (*FP)(void);

struct RTOS
{
    unsigned count;
    const unsigned div;
    const FP task;
};

enum taskSymbol
{
    TASK_1_MS,
    TASK_5_MS,
    TASK_10_MS,
    TASK_25_MS,
    TASK_TOTAL
};

class Rtos
{
public:
    void Init(void);
    void Run(void);
    static void Task_1_ms(void);
    static void Task_5_ms(void);
    static void Task_10_ms(void);
    static void Task_25_ms(void);

private:
    void Increment(void);
    static void Timer_A(void);
};

#endif /* KERNEL_H_ */
