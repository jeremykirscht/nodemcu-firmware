#ifndef _CPU_ESP32_H_
#define _CPU_ESP32_H_

#include <stdint.h>
#include <stdbool.h>
#include "user_config.h"
#include <spi_flash.h>
#include <eagle_soc.h>
#include <gpio.h>
#include <gpio/io_mux_reg.h>
#include <gpio/gpio_reg.h>
#include "flash_api.h"
#include "pin_map.h"

/* FIXME: real numbers here! */
#define NUM_GPIO              GPIO_PIN_NUM
#define NUM_SPI               2
#define NUM_UART              1
#define NUM_PWM               GPIO_PIN_NUM
#define NUM_ADC               1
#define NUM_CAN               0
#define NUM_I2C               1
#define NUM_OW                GPIO_PIN_NUM
#define NUM_TMR               7

#if defined(FLASH_512K)
# define FLASH_SEC_NUM 	0x80 	// 4MByte: 0x400, 2MByte: 0x200, 1MByte: 0x100, 512KByte: 0x80
#elif defined(FLASH_1M)
# define FLASH_SEC_NUM 	0x100
#elif defined(FLASH_2M)
# define FLASH_SEC_NUM 	0x200
#elif defined(FLASH_4M)
# define FLASH_SEC_NUM 	0x400
#elif defined(FLASH_8M)
# define FLASH_SEC_NUM 	0x800
#elif defined(FLASH_16M)
# define FLASH_SEC_NUM 	0x1000
#elif defined(FLASH_AUTOSIZE)
# if defined(FLASH_SAFE_API)
#  define FLASH_SEC_NUM 	(flash_safe_get_sec_num())
# else
#  define FLASH_SEC_NUM 	(flash_rom_get_sec_num())
# endif // defined(FLASH_SAFE_API)
#else
# define FLASH_SEC_NUM 	0x80
#endif

#define SYS_PARAM_SEC_NUM 4
#define SYS_PARAM_SEC_START (FLASH_SEC_NUM - SYS_PARAM_SEC_NUM)

#define INTERNAL_FLASH_SECTOR_SIZE      SPI_FLASH_SEC_SIZE
// #define INTERNAL_FLASH_SECTOR_ARRAY     { 0x4000, 0x4000, 0x4000, 0x4000, 0x10000, 0x20000, 0x20000, 0x20000, 0x20000, 0x20000 }
#define INTERNAL_FLASH_WRITE_UNIT_SIZE  4
#define INTERNAL_FLASH_READ_UNIT_SIZE	4

#define INTERNAL_FLASH_SIZE             ( (SYS_PARAM_SEC_START) * INTERNAL_FLASH_SECTOR_SIZE )

// TODO: double-check flash mapped address
#define INTERNAL_FLASH_MAPPED_ADDRESS    0x40084000

#if defined(FLASH_SAFE_API)
#define flash_write flash_safe_write
#define flash_erase flash_safe_erase_sector
#define flash_read flash_safe_read
#else
#define flash_write spi_flash_write
#define flash_erase spi_flash_erase_sector
#define flash_read spi_flash_read
#endif // defined(FLASH_SAFE_API)



#endif