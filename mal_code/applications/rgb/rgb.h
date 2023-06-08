/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-06-07     AFShk       the first version
 */
#ifndef APPLICATIONS_TASKS_RGB_H_

#define APPLICATIONS_TASKS_RGB_H_

#include <rtdef.h>
#include <drv_common.h>

#define LED_B_PIN   GET_PIN(H, 10)
#define LED_G_PIN   GET_PIN(H, 11)
#define LED_R_PIN   GET_PIN(H, 12)

typedef enum
{
    LED_RED = 0,
    LED_GREEN,
    LED_BLUE,
    LED_YELLOW,
    LED_PURPLE,
    LED_CYAN,
    LED_WHITE,
    LED_BLACK
}LED_COLOR;

struct rgb_color_mode
{
    LED_COLOR color;
    uint16_t  blink_time;
};

rt_err_t rgb_set(LED_COLOR color, uint16_t blink_time);

#endif /* APPLICATIONS_TASKS_RGB_H_ */
