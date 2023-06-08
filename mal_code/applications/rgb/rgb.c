/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-06-07     AFShk       the first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <drivers/pin.h>

#include <rgb/rgb.h>

static struct rgb_color_mode rgb;

static void rgb_init(void)
{
    rt_pin_mode(LED_R_PIN, PIN_MODE_OUTPUT);
    rt_pin_mode(LED_G_PIN, PIN_MODE_OUTPUT);
    rt_pin_mode(LED_B_PIN, PIN_MODE_OUTPUT);

    rgb.color = LED_YELLOW;
    rgb.blink_time = 500;
}

INIT_DEVICE_EXPORT(rgb_init);

static void rgb_color_set(struct rgb_color_mode rgb)
{
    switch(rgb.color) {
    case LED_RED:
        rt_pin_write(LED_R_PIN, PIN_HIGH);
        rt_pin_write(LED_G_PIN, PIN_LOW);
        rt_pin_write(LED_B_PIN, PIN_LOW);
        break;
    case LED_GREEN:
        rt_pin_write(LED_R_PIN, PIN_LOW);
        rt_pin_write(LED_G_PIN, PIN_HIGH);
        rt_pin_write(LED_B_PIN, PIN_LOW);
        break;
    case LED_BLUE:
        rt_pin_write(LED_R_PIN, PIN_LOW);
        rt_pin_write(LED_G_PIN, PIN_LOW);
        rt_pin_write(LED_B_PIN, PIN_HIGH);
        break;
    case LED_YELLOW:
        rt_pin_write(LED_R_PIN, PIN_HIGH);
        rt_pin_write(LED_G_PIN, PIN_HIGH);
        rt_pin_write(LED_B_PIN, PIN_LOW);
        break;
    case LED_PURPLE:
        rt_pin_write(LED_R_PIN, PIN_HIGH);
        rt_pin_write(LED_G_PIN, PIN_LOW);
        rt_pin_write(LED_B_PIN, PIN_HIGH);
        break;
    case LED_CYAN:
        rt_pin_write(LED_R_PIN, PIN_LOW);
        rt_pin_write(LED_G_PIN, PIN_HIGH);
        rt_pin_write(LED_B_PIN, PIN_HIGH);
        break;
    case LED_WHITE:
        rt_pin_write(LED_R_PIN, PIN_HIGH);
        rt_pin_write(LED_G_PIN, PIN_HIGH);
        rt_pin_write(LED_B_PIN, PIN_HIGH);
        break;
    case LED_BLACK:
        rt_pin_write(LED_R_PIN, PIN_LOW);
        rt_pin_write(LED_G_PIN, PIN_LOW);
        rt_pin_write(LED_B_PIN, PIN_LOW);
        break;
    default:
        rt_kprintf("\nIt doesn't have this color.");
        rt_pin_write(LED_R_PIN, PIN_LOW);
        rt_pin_write(LED_G_PIN, PIN_LOW);
        rt_pin_write(LED_B_PIN, PIN_LOW);
        break;
    }
}

rt_err_t rgb_set(LED_COLOR color, uint16_t blink_time)
{
    rgb.color = color;
    rgb.blink_time = blink_time;

    return RT_EOK;
}

void rgb_entry(void *parameter)
{
    struct rgb_color_mode black;
    black.color = LED_BLACK;
    black.blink_time = 0;

    while(1) {
        rgb_color_set(rgb);
        if(rgb.blink_time != 0) {
            rt_thread_mdelay(rgb.blink_time);
            rgb_color_set(black);
            rt_thread_mdelay(rgb.blink_time);
        } else {
            rt_thread_mdelay(100);
        }
    }

}
