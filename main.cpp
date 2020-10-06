#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include "definitions.h"
#include "variables.h"
#include "functions.h"
#include "interrupts.h"


int main(void)
{		
	_delay_ms(10);
	SERIAL_PORT_INITIALIZATION();
	I2C_INITIALIZATION();
	WIRELESS_INITIALIZATION();
	ADC_INITIALIZATION();
	ACCELEROMETER_INITIALIZATION();
	HEARTRATE_INITIALIZATION();
	OLED_INITIALIZATION();
	TIMER_INITIALIZATION();
	
	uint64_t x = 0, y = 112;
	int i;
	
	while(1)
	{
		//_delay_ms(20);
		battery_percentage = GET_BATTERY();
		DRAW_BATTERY(battery_percentage);
		setbit(OLED_NEW_DATA_FLAGS, LINE_1);
		itoa(HR, itoa_result, 10);
		for (i = 11; itoa_result[i-11] != 0; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				oled_line[6][(i * 8) +j] = nums[itoa_result[i - 11] - '0'][j];
			}
			
		}
			oled_line[6][(i * 8)]     = 0X00;
			oled_line[6][(i * 8) + 1] = 0xC3;
			oled_line[6][(i * 8) + 2] = 0XC3;
			oled_line[6][(i * 8) + 3] = 0XC3;
			oled_line[6][(i * 8) + 4] = 0XFF;
			oled_line[6][(i * 8) + 5] = 0XFF;
			oled_line[6][(i * 8) + 6] = 0X00;
			oled_line[6][(i * 8) + 7] = 0X00;
			i++;
			for (; i < 16; i++)
			{
				for (int j = 0; j < 8; j++)
				oled_line[6][(i * 8) + j] = 0;
			}
		setbit(OLED_NEW_DATA_FLAGS, LINE_7);
	}
	while (1)
	{	
		USART_Transmit("temp reading IS: ");
		if(checkbit(FLAGS, FREEFALL_FLAG, 1))
		{
			clearbit(FLAGS, FREEFALL_FLAG);
		}
		USART_Transmit(temperature_string);
		USART_Transmit("DEGREES CELSIUS");
		USART_Transmit("\r\n");
		_delay_ms(10);
	}
}
