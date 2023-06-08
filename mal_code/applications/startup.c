/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-06-06     AFShk       the first version
 */

#include <rthw.h>
#include <rtthread.h>
#include <board.h>

#include "stm32f4xx.h"

extern int  mal_application_init(void);

void mal_show_version(void)
{
    // Clear terminal
    rt_kprintf("\x1b[2J\x1b[H");

    // Show Matchmaker's Arrow Launcher program version
    rt_kprintf("-------------------------------------------\n");
    rt_kprintf("----    Matchmaker's Arrow Launcher    ----\n");
    rt_kprintf("----    Version  0.1.1                 ----\n");
    rt_kprintf("----    By AFShk 2023-06-06            ----\n");
    rt_kprintf("----    Base RT-Thread 4.0.3           ----\n");
    rt_kprintf("-------------------------------------------\n");
}

int main(void)
{
    // Show Matchmaker's Arrow Launcher program version
    mal_show_version();

    // Initializes the application thread
    mal_application_init();

    return RT_EOK;
}
