/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-06-07     AFShk       the first version
 */

#include <main.h>
#include <drivers/i2c.h>

#include <drv_hw_i2c.h>

struct rt_i2c_bus_device i2c1_bus;
I2C_HandleTypeDef hi2c1;

struct rt_i2c_bus_device i2c2_bus;
I2C_HandleTypeDef hi2c2;

struct rt_i2c_bus_device i2c3_bus;
I2C_HandleTypeDef hi2c3;

static rt_err_t i2c_hw_init(void)
{
    /* USER CODE END I2C1_Init 1 */
    hi2c1.Instance = I2C1;
    hi2c1.Init.ClockSpeed = 400000;
    hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
    hi2c1.Init.OwnAddress1 = 0;
    hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
    hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
    hi2c1.Init.OwnAddress2 = 0;
    hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
    hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
    if (HAL_I2C_Init(&hi2c1) != HAL_OK)
    {
      Error_Handler();
    }
    /* USER CODE BEGIN I2C1_Init 2 */

    /* USER CODE END I2C2_Init 1 */
    hi2c2.Instance = I2C2;
    hi2c2.Init.ClockSpeed = 400000;
    hi2c2.Init.DutyCycle = I2C_DUTYCYCLE_2;
    hi2c2.Init.OwnAddress1 = 0;
    hi2c2.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
    hi2c2.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
    hi2c2.Init.OwnAddress2 = 0;
    hi2c2.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
    hi2c2.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
    if (HAL_I2C_Init(&hi2c2) != HAL_OK)
    {
      Error_Handler();
    }
    /* USER CODE BEGIN I2C2_Init 2 */

    /* USER CODE END I2C3_Init 1 */
    hi2c3.Instance = I2C3;
    hi2c3.Init.ClockSpeed = 400000;
    hi2c3.Init.DutyCycle = I2C_DUTYCYCLE_2;
    hi2c3.Init.OwnAddress1 = 0;
    hi2c3.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
    hi2c3.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
    hi2c3.Init.OwnAddress2 = 0;
    hi2c3.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
    hi2c3.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
    if (HAL_I2C_Init(&hi2c3) != HAL_OK)
    {
      Error_Handler();
    }
    /* USER CODE BEGIN I2C3_Init 2 */

    return RT_EOK;
}

static rt_size_t master_i2c1_xfer(struct rt_i2c_bus_device *bus, struct rt_i2c_msg msgs[], rt_uint32_t num)
{
    struct rt_i2c_msg *msg;
    rt_int32_t i, ret;

    for(i = 0; i< num; i++)
    {
        msg = &msgs[i];
        if(msg->flags & RT_I2C_RD)
        {
            HAL_I2C_Master_Receive(&hi2c1, msg->addr, msg->buf, msg->len, 100);
        }
        else
        {
            HAL_I2C_Master_Transmit(&hi2c1, msg->addr, msg->buf, msg->len, 100);
        }
    }
    ret = i;
    return ret;
}

static rt_size_t master_i2c2_xfer(struct rt_i2c_bus_device *bus, struct rt_i2c_msg msgs[], rt_uint32_t num)
{
    struct rt_i2c_msg *msg;
    rt_int32_t i, ret;

    for(i = 0; i< num; i++)
    {
        msg = &msgs[i];
        if(msg->flags & RT_I2C_RD)
        {
            HAL_I2C_Master_Receive(&hi2c2, msg->addr, msg->buf, msg->len, 100);
        }
        else
        {
            HAL_I2C_Master_Transmit(&hi2c2, msg->addr, msg->buf, msg->len, 100);
        }
    }
    ret = i;
    return ret;
}

static rt_size_t master_i2c3_xfer(struct rt_i2c_bus_device *bus, struct rt_i2c_msg msgs[], rt_uint32_t num)
{
    struct rt_i2c_msg *msg;
    rt_int32_t i, ret;

    for(i = 0; i< num; i++)
    {
        msg = &msgs[i];
        if(msg->flags & RT_I2C_RD)
        {
            HAL_I2C_Master_Receive(&hi2c3, msg->addr, msg->buf, msg->len, 100);
        }
        else
        {
            HAL_I2C_Master_Transmit(&hi2c3, msg->addr, msg->buf, msg->len, 100);
        }
    }
    ret = i;
    return ret;
}

static const struct rt_i2c_bus_device_ops i2c1_bus_ops =
{
    master_i2c1_xfer,
    RT_NULL,
    RT_NULL
};

static const struct rt_i2c_bus_device_ops i2c2_bus_ops =
{
    master_i2c2_xfer,
    RT_NULL,
    RT_NULL
};

static const struct rt_i2c_bus_device_ops i2c3_bus_ops =
{
    master_i2c3_xfer,
    RT_NULL,
    RT_NULL
};

int rt_i2c_hw_init(void)
{
    i2c_hw_init();

    i2c1_bus.ops = &i2c1_bus_ops;
    rt_i2c_bus_device_register(&i2c1_bus, "hw_i2c1");

    i2c2_bus.ops = &i2c2_bus_ops;
    rt_i2c_bus_device_register(&i2c2_bus, "hw_i2c2");

    i2c3_bus.ops = &i2c3_bus_ops;
    rt_i2c_bus_device_register(&i2c3_bus, "hw_i2c3");

    return RT_EOK;
}
INIT_DEVICE_EXPORT(rt_i2c_hw_init);
