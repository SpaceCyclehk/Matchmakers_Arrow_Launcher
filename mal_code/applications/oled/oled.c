/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-06-08     AFShk       the first version
 */
#include "oled.h"

#define OLED_I2C_BUS_NAME   "hw_i2c2"
struct rt_device *dev_i2c_oled;

#define OLED_ADDRESS        0x78
#define OLED_CMD_ADDRESS    0x00
#define OLED_DATA_ADDRESS   0x40

static rt_err_t write_reg(struct rt_device *dev, rt_uint8_t reg, rt_uint8_t data)
{
    rt_uint8_t buf[2];
    rt_off_t pos;
    rt_uint16_t addr = OLED_ADDRESS;
    rt_uint16_t flags = RT_I2C_WR;

    buf[0] = reg;
    buf[1] = data;
    pos = (flags << 16) | addr;

    rt_device_write(dev, pos, buf, 2);

    return RT_EOK;
}

static rt_err_t read_regs(struct rt_device *dev, rt_uint8_t len, rt_uint8_t *buf)
{
    rt_off_t pos;
    rt_uint16_t addr = OLED_ADDRESS;
    rt_uint16_t flags = RT_I2C_WR;

    pos = (flags << 16) | addr;

    rt_device_write(dev, pos, buf, 2);

    return RT_EOK;
}

static void oled_write_command(unsigned char data)
{
    write_reg(dev_i2c_oled, OLED_CMD_ADDRESS, data);
}

static void oled_write_data(unsigned char data)
{
    write_reg(dev_i2c_oled, OLED_DATA_ADDRESS, data);
}

void oled_fill(unsigned char fill_data)//È«ÆÁÌî³ä
{
    unsigned char m,n;
    for(m=0;m<8;m++)
    {
        oled_write_command(0xb0+m);
        oled_write_command(0x00);
        oled_write_command(0x10);
        for(n=0;n<128;n++)
        {
            oled_write_data(fill_data);
        }
    }
}

static void oled_set_pos(unsigned char x, unsigned char y)
{
    oled_write_command(0xb0+y);
    oled_write_command(((x&0xf0)>>4)|0x10);
    oled_write_command((x&0x0f)|0x01);
}

int oled_init(void)
{
    dev_i2c_oled = rt_device_find(OLED_I2C_BUS_NAME);
    if(dev_i2c_oled == RT_NULL)
    {
        rt_kprintf("find i2c bus fail!\n");
        return RT_ERROR;
    }
    rt_kprintf("find i2c bus success!\n");

    rt_device_open(dev_i2c_oled, RT_DEVICE_OFLAG_RDWR);

    rt_thread_mdelay(100);
    oled_write_command(0xAE);
    oled_write_command(0x20);
    oled_write_command(0x10);
    oled_write_command(0xb0);
    oled_write_command(0xc8);
    oled_write_command(0x00);
    oled_write_command(0x10);
    oled_write_command(0x40);
    oled_write_command(0x81);
    oled_write_command(0xff);
    oled_write_command(0xa1);
    oled_write_command(0xa6);
    oled_write_command(0xa8);
    oled_write_command(0x3F);
    oled_write_command(0xa4);
    oled_write_command(0xd3);
    oled_write_command(0x00);
    oled_write_command(0xd5);
    oled_write_command(0xf0);
    oled_write_command(0xd9);
    oled_write_command(0x22);
    oled_write_command(0xda);
    oled_write_command(0x12);
    oled_write_command(0xdb);
    oled_write_command(0x20);
    oled_write_command(0x8d);
    oled_write_command(0x14);
    oled_write_command(0xaf);

    rt_thread_mdelay(100);

    oled_set_pos(0, 0);
    for(int i = 0; i < 8; i++) {
        for(int n = 0; n<128; n++) {
            oled_write_data(0x0f);
        }
    }

    return RT_EOK;
}
