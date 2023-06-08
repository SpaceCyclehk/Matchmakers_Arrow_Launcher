/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-06-06     AFShk       the first version
 */
#include <rtdevice.h>
#include <rtthread.h>
#include <board.h>
#include <stdio.h>

static rt_thread_t tid0;

#define LED_THREAD_PRIORITY 10
//#define MOTOR_CONTROL

extern void rgb_entry(void *parameter);
static char thread_led_stack[256];
struct rt_thread thread_led_handle;



void mal_init_thread_entry(void* parameter)
{
    rt_err_t res;
    res = rt_thread_init(&thread_led_handle,
                           "rgb",
                           rgb_entry,
                           RT_NULL,
                           &thread_led_stack[0],
                           sizeof(thread_led_stack),
                           LED_THREAD_PRIORITY,
                           10);
    if (res == RT_EOK)
        rt_thread_startup(&thread_led_handle);

    /* delete itself */
    tid0 = RT_NULL;
}

int mal_application_init()
{
    tid0 = rt_thread_create("init",
                            mal_init_thread_entry,
                            RT_NULL,
                            8192,
                            RT_THREAD_PRIORITY_MAX / 2,
                            20);

    if (tid0 != RT_NULL)
        rt_thread_startup(tid0);

    return 0;
}
