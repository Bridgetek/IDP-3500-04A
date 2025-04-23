/**
 *  @file max31725.c Temperature sensor device driver
 *
 *  @brief
 *   Temperature sensor device driver
 **/

#include <stdio.h>
#include <math.h>
#include "bsp_debug.h"
#include "bsp_hwdefs.h"
#include "max31725.h"

#define REG_TEMPERATURE		  0x00
#define REG_CONFIG			  0x01
#define REG_TEMP_HYSTERESIS	  0x02
#define REG_TEMP_SHUTDOWN	  0x03
#define BIT_TEMP_DATA_MSBBIT  15
#define MASK_TEMP_DATA_MSBBIT (1 << BIT_TEMP_DATA_MSBBIT)

#define MAX31725_ONESHOT	  (1 << 7)
#define MAX31725_TIMEOUTN	  (1 << 6)
#define MAX31725_DATAFORMAT	  (1 << 5)
#define MAX31725_EXTENDED	  MAX31725_DATAFORMAT
#define MAX31725_FAULT_Q1	  (1 << 4)
#define MAX31725_FAULT_Q2	  (1 << 3)
#define MAX31725_IRQ_POLARITY (1 << 2)
#define MAX31725_COMP_OR_IRQ  (1 << 1)
#define MAX31725_SHUTDOWN	  (1 << 0)

/* In extended format, the measured temperature equals the two's
 * complement value plus 64'C, thereby extending the upper
 * temperature data range to 191.99609375'C and allowing
 * temperatures as high as 150'C to be measured.
 */
#define SENSOR_EXTENDED_DATA_FORMAT
#ifdef SENSOR_EXTENDED_DATA_FORMAT
#define TEMP_OFFSET 0x4000 // Adding 64'c to MSB
/* In extended format, offset addition to be handled
 * for positive temperatures above 128'C
 * */
#define POSITIVE_TEMP_CONDITION_1 0x4000
#define POSITIVE_TEMP_CONDITION_2 0x8000
#endif

#define BIT_TEMPSENSOR_DATA_FORMAT					5
#define MASK_TEMPSENSOR_DATA_FORMAT				   (1 << BIT_TEMPSENSOR_DATA_FORMAT)

#if 0
#define WAIT_FOR_CONVERSION() delayms(7)
#endif
#define SWAP_16(a) ((a >> 8) | (a << 8))

static bool is_registered = false;
static bool is_initialized = false;

static int8_t read_temp_sensor_registers(uint8_t addr, uint8_t startReg, uint8_t* regData, int numBytes)
{
	int8_t ret_val = 0;
	ret_val = i2cm_read(addr, startReg, regData, numBytes);
	return ret_val;
}

float max31725_deg_C(void)
{
	uint16_t rxWORD = 0;
	int8_t iRet = 0;

	/* Set the I2C Master pins to channel 0*/
	sys_i2c_swop(0);

	iRet = read_temp_sensor_registers(TEMP_SENSOR_ADDRESS, REG_TEMPERATURE, (uint8_t*)&rxWORD, 2);

	if (!iRet)
	{
		char	intpart = (char)(rxWORD & 0xff);
		uint8_t fract = rxWORD >> 8;
		float	deg_c = (float)intpart + (float)fract / 256.0f;
		return deg_c;
	}
	return 0;
}

int8_t i2c_init(void)
{
	int8_t iRet = 0;

	iRet = sys_disable(sys_device_i2c_master);
	iRet = sys_enable(sys_device_i2c_master);

	/* Set GPIO44 to I2CM_SCL and GPIO45 to I2CM_SDA... */
	gpio_function(TEMP_SENSOR_I2C0_SCL, pad_i2c0_scl);
	gpio_pull(TEMP_SENSOR_I2C0_SCL, pad_pull_none);
	gpio_function(TEMP_SENSOR_I2C0_SDA, pad_i2c0_sda);
	gpio_pull(TEMP_SENSOR_I2C0_SDA, pad_pull_none);

	if (!iRet) i2cm_init(I2CM_NORMAL_SPEED, 10000);

	/* Set the I2C Master pins to channel 0 first */
	sys_i2c_swop(0);

	return iRet;
}

int max31725_init(void)
{
	int8_t iRet = 0;
	uint16_t txWORD = 0;

	if (!is_registered) {
		iRet = i2c_init();
		if (iRet)
			return -1;
		is_registered = true;
	}
	if (!is_initialized) {
		sys_i2c_swop(0);

		iRet = i2cm_write(TEMP_SENSOR_ADDRESS, REG_CONFIG, (uint8_t*)&txWORD, 2);
		if (iRet)
			return -2;
		is_initialized = true;
	}
	return 0;
}
