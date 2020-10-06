void SERIAL_PORT_INITIALIZATION ()
{
	 cli();
	 UBRR0 = 0;
	 UCSR0A = 0;
	 UCSR0B = 0X98;
	 UCSR0C = 6;
	 sei();
} 

void USART_Transmit( char *DataT )
{
	while (*DataT)
	{
		UDR0 = *DataT;
		DataT++;
		_delay_ms(1);
	}
	
}

void USART_Transmit( char DataT )
{
		UDR0 = DataT;
		_delay_ms(1);	

}
void I2C_INITIALIZATION()
{
	TWBR0=1;
}

void I2C_WRITE_BYTE (char address_w, char register_address, char *data, int Number_of_Bytes)
{
	TWCR0 = (1<<TWEN)|(1<<TWSTA)|(1<<TWINT);
	while (checkbit(TWCR0,TWINT,0));
	if(TWSR0 != 0x08)
	{
		USART_Transmit("1");
	}
	TWDR0 = address_w;
	
	TWCR0 = (1<<TWEN)|(1<<TWINT);
	while (checkbit(TWCR0,TWINT,0));
	if (TWSR0 != 0x18)
	{
		USART_Transmit("2");
	}
	TWDR0 = register_address;
	
	TWCR0 = (1<<TWEN)|(1<<TWINT);
	while (checkbit(TWCR0,TWINT,0));
	if (TWSR0 != 0x28)
	{
		USART_Transmit("3");
	}
	for(int i=0; i < Number_of_Bytes; i++)
	{
		
		TWDR0 = *(data+i);
		TWCR0 = (1<<TWEN)|(1<<TWINT);
		while (checkbit(TWCR0,TWINT,0));
		if (TWSR0 != 0x28)
		{
			USART_Transmit("4");
		}
	}
	TWCR0 = (1<<TWEN)|(1<<TWINT)|(1<<TWSTO);
}

void I2C_WRITE_BYTE (char address_w, char register_address, char data)
{
	TWCR0 = (1<<TWEN)|(1<<TWSTA)|(1<<TWINT);
	while (checkbit(TWCR0,TWINT,0));
	if(TWSR0 != 0x08)
	{
		USART_Transmit("5");
	}
	TWDR0 = address_w;
	
	TWCR0 = (1<<TWEN)|(1<<TWINT);
	while (checkbit(TWCR0,TWINT,0));
	if (TWSR0 != 0x18)
	{
		USART_Transmit("6");
	}
	TWDR0 = register_address;
	
	TWCR0 = (1<<TWEN)|(1<<TWINT);
	while (checkbit(TWCR0,TWINT,0));
	if (TWSR0 != 0x28)
	{
		USART_Transmit("7");
	}
		TWDR0 = data;
		TWCR0 = (1<<TWEN)|(1<<TWINT);
		while (checkbit(TWCR0,TWINT,0));
		if (TWSR0 != 0x28)
		{
			USART_Transmit("8");
		}
	TWCR0 = (1<<TWEN)|(1<<TWINT)|(1<<TWSTO);
}

char* I2C_READ_BYTE (char address_w, char address_r, char register_address,char number_of_bytes)
{
	char bytes_received[number_of_bytes]={0};
	TWCR0 = (1<<TWEN)|(1<<TWSTA)|(1<<TWINT);
	while (checkbit(TWCR0,TWINT,0));
	if(TWSR0 != 0x08)
	{
		USART_Transmit("9");
	}
	TWDR0 = address_w;
	
	TWCR0 = (1<<TWEN)|(1<<TWINT);
	while (checkbit(TWCR0,TWINT,0));
	if (TWSR0 != 0x18)
	{
		USART_Transmit("A");
	}
	TWDR0 = register_address;
	
	TWCR0 = (1<<TWEN)|(1<<TWINT);
	while (checkbit(TWCR0,TWINT,0));
	if (TWSR0 != 0x28)
	{
		USART_Transmit("B");
	}
	
	TWCR0 = (1<<TWEN)|(1<<TWINT)|(1<<TWSTA);
	while (checkbit(TWCR0,TWINT,0));
	if (TWSR0 != 0x10)
	{
		USART_Transmit("C");
	}	
	TWDR0 = address_r;
	
	TWCR0 = (1<<TWEN)|(1<<TWINT);
	while (checkbit(TWCR0,TWINT,0));
	if (TWSR0 != 0x40)
	{
		USART_Transmit("D");
	}
	
	for(int i=0;i<number_of_bytes;i++)
	{
		if((number_of_bytes-i) == 1)
		TWCR0 = (1<<TWEN)|(1<<TWINT);
		else
		TWCR0 = (1<<TWEN)|(1<<TWINT)|(1<<TWEA);
		while (checkbit(TWCR0,TWINT,0));
		if (TWSR0 != 0x58 && TWSR0 !=0X50)
		{
			USART_Transmit("E");
		}
		bytes_received[i]=TWDR0;
	}
	char *return_pointer = bytes_received;
	TWCR0 = (1<<TWEN)|(1<<TWINT)|(1<<TWSTO);
	return return_pointer;
}

char* I2C_READ_BYTE (char address_r,char number_of_bytes)
{
	char bytes_received[number_of_bytes]={0};
	TWCR0 = (1<<TWEN)|(1<<TWINT)|(1<<TWSTA);
	while (checkbit(TWCR0,TWINT,0));
	if (TWSR0 != 0x08)
	{
		USART_Transmit("F");
	}
	TWDR0 = address_r;
	
	TWCR0 = (1<<TWEN)|(1<<TWINT);
	while (checkbit(TWCR0,TWINT,0));
	if (TWSR0 != 0x40)
	{
		USART_Transmit("G");
	}
	
	for(int i=0;i<number_of_bytes;i++)
	{
		if((number_of_bytes-i) == 1)
		TWCR0 = (1<<TWEN)|(1<<TWINT);
		else
		TWCR0 = (1<<TWEN)|(1<<TWINT)|(1<<TWEA);
		while (checkbit(TWCR0,TWINT,0));
		if (TWSR0 != 0x58 && TWSR0 !=0X50)
		{
			USART_Transmit("H");
		}
		bytes_received[i]=TWDR0;
	}
	char *return_pointer = bytes_received;
	TWCR0 = (1<<TWEN)|(1<<TWINT)|(1<<TWSTO);
	return return_pointer;
}

void WIRELESS_INITIALIZATION()
{
		_delay_ms (8000);
		USART_Transmit ("AT+CIPSTART=\"UDP\",\"192.168.1.10\",1025,2233,0\r\n");
		_delay_ms (1000);
		USART_Transmit ("AT+CIPMODE=1\r\n");
		_delay_ms(1000);
		USART_Transmit("AT+CIPSEND\r\n");
		_delay_ms(1000);
}

void ACCELEROMETER_INITIALIZATION()
{
	I2C_WRITE_BYTE(ACCELEROMETER_ADD_W,ACCELEROMETER_CNTL1,ACCELEROMETER_CNTL1_val);
	I2C_WRITE_BYTE(ACCELEROMETER_ADD_W,ACCELEROMETER_CNTL2,ACCELEROMETER_CNTL2_val);
	I2C_WRITE_BYTE(ACCELEROMETER_ADD_W,ACCELEROMETER_CNTL3,ACCELEROMETER_CNTL3_val);
	I2C_WRITE_BYTE(ACCELEROMETER_ADD_W,ACCELEROMETER_ODCNTL,ACCELEROMETER_ODCNTL_val);
}

void TEMPERATURE_SEN_INITIALIZATION()
{
	I2C_WRITE_BYTE(TEMPERATURE_ADD_W,0X24,0X00);
	_delay_ms(50);
}

void UPDATE_TEMPERATURE()
{
	TEMPERATURE_SEN_INITIALIZATION();
	uint16_t ST=0;
	I2C_REC_POINTER=I2C_READ_BYTE(TEMPERATURE_ADD_R,3);
	temp_high=*I2C_REC_POINTER;
	temp_low=*(I2C_REC_POINTER+1);
	ST=(temp_high<<8)|(temp_low);
	temperature_celsius=(-45.0)+(175.0*(double(ST)/(65535)));
	dtostrf(temperature_celsius,2,2,temperature_string);
}

void UPDATE_FREEFALL_STATUS()
{
	acc_temp=I2C_READ_BYTE(ACCELEROMETER_ADD_W,ACCELEROMETER_ADD_R,ACCELEROMETER_OUT_XL,6);
	ACC_X=((*(acc_temp+1))<<8)|(*(acc_temp));
	ACC_Y=((*(acc_temp+3))<<8)|(*(acc_temp+2));
	ACC_Z=((*(acc_temp+5))<<8)|(*(acc_temp+4));
	ACC_X_MSEC=ACC_X*0.00059814453125;
	ACC_Y_MSEC=ACC_Y*0.00059814453125;
	ACC_Z_MSEC=ACC_Z*0.00059814453125;
	normal=sqrt((ACC_X_MSEC*ACC_X_MSEC)+(ACC_Y_MSEC*ACC_Y_MSEC)+(ACC_Z_MSEC*ACC_Z_MSEC));
	if((abs(normal-9.8) >7))
	{
		setbit(FLAGS,FREEFALL_FLAG);
	}
}

void TIMER_RESET()
{
	TCNT0=256-250;
}

void TIMER_START()
{
	TCCR0B=3;
}

void TIMER_INITIALIZATION()
{
	cli();
	TCCR0A=0;
	TIMSK0=1;
	TIMER_RESET();
	TIMER_START();
	sei();
}

void TIMER_STOP()
{
	TCCR0B=0;
}

void OLED_RESET()
{
	for (int j=0;j<8;j++)
	{
		for (int i=0;i<128;i++)
		{
			I2C_WRITE_BYTE(OLED_ADDRESS_W,OLED_DATA,0);
		}
		I2C_WRITE_BYTE(OLED_ADDRESS_W,OLED_COMMAND,0xB0+j);
	}
	I2C_WRITE_BYTE(OLED_ADDRESS_W,OLED_COMMAND,0XB0);
	I2C_WRITE_BYTE(OLED_ADDRESS_W,OLED_COMMAND,0x00);
	I2C_WRITE_BYTE(OLED_ADDRESS_W,OLED_COMMAND,0x10);
}

void OLED_PLACE_LINE(int line,char *payload)
{
	I2C_WRITE_BYTE(OLED_ADDRESS_W,OLED_COMMAND,0XB7-line);
// 			for (int i=0;i<128;i++)
// 			{
// 				I2C_WRITE_BYTE(OLED_ADDRESS_W,OLED_DATA,0);
// 			}
			for (int i=127;i>=0;i--)
			{
				I2C_WRITE_BYTE(OLED_ADDRESS_W,OLED_DATA,*(payload+i));
			}
}

void OLED_INITIALIZATION()
{
	I2C_WRITE_BYTE(OLED_ADDRESS_W,OLED_COMMAND,0XA8); // SET MUX RATIO
	I2C_WRITE_BYTE(OLED_ADDRESS_W,OLED_COMMAND,0X3F);
	I2C_WRITE_BYTE(OLED_ADDRESS_W,OLED_COMMAND,0XD3);//SET DISPLAY OFFSET
	I2C_WRITE_BYTE(OLED_ADDRESS_W,OLED_COMMAND,0X00);
	I2C_WRITE_BYTE(OLED_ADDRESS_W,OLED_COMMAND,0X40);//SET_DISPLAY_START_LINE
	I2C_WRITE_BYTE(OLED_ADDRESS_W,OLED_COMMAND,0XA0);//SET_SEGMENT_REMAP
	I2C_WRITE_BYTE(OLED_ADDRESS_W,OLED_COMMAND,0XC0);//SET_COM_OUTPUT_SCAN_DIRECTION
	I2C_WRITE_BYTE(OLED_ADDRESS_W,OLED_COMMAND,0XDA);//SET_COM_PINS_HW_CONF
	I2C_WRITE_BYTE(OLED_ADDRESS_W,OLED_COMMAND,0X12);
	I2C_WRITE_BYTE(OLED_ADDRESS_W,OLED_COMMAND,0X81);//SET_CONTRAST_CONTROL
	I2C_WRITE_BYTE(OLED_ADDRESS_W,OLED_COMMAND,0X7F);
	I2C_WRITE_BYTE(OLED_ADDRESS_W,OLED_COMMAND,0XA4);//DISABLE_ENTIRE_DISP_ON
	I2C_WRITE_BYTE(OLED_ADDRESS_W,OLED_COMMAND,0XA6);//SET_NORM_DISPLAY
	I2C_WRITE_BYTE(OLED_ADDRESS_W,OLED_COMMAND,0XD5);//SET_OSC_FREQ
	I2C_WRITE_BYTE(OLED_ADDRESS_W,OLED_COMMAND,0X80);
	I2C_WRITE_BYTE(OLED_ADDRESS_W,OLED_COMMAND,0X8D);//ENABLE_CHARGE_PUMP_REGULATOR
	I2C_WRITE_BYTE(OLED_ADDRESS_W,OLED_COMMAND,0X14);
	I2C_WRITE_BYTE(OLED_ADDRESS_W,OLED_COMMAND,0XAF);//DISPLAY_ON
	I2C_WRITE_BYTE(OLED_ADDRESS_W,OLED_COMMAND,0X22);
	I2C_WRITE_BYTE(OLED_ADDRESS_W,OLED_COMMAND,0);
	I2C_WRITE_BYTE(OLED_ADDRESS_W,OLED_COMMAND,7);
	I2C_WRITE_BYTE(OLED_ADDRESS_W,OLED_COMMAND,0X00);
	I2C_WRITE_BYTE(OLED_ADDRESS_W,OLED_COMMAND,0X10);
	OLED_RESET();
}
void SEND_OLED_CHAR(char x)
{
		for(int i=0; i<128;i++)
		{
			I2C_WRITE_BYTE(OLED_ADDRESS_W,OLED_DATA,x);
		}
}

void HEARTRATE_INITIALIZATION()
{
	I2C_WRITE_BYTE(SLA_SPO2_W,SYS_CONTROL,0X04);
	I2C_WRITE_BYTE(SLA_SPO2_W,LED_RED_MA,0X22);
	I2C_WRITE_BYTE(SLA_SPO2_W,LED_PILOT_MA,0XFF);
	I2C_WRITE_BYTE(SLA_SPO2_W,LED_IR_MA,0X22);
	I2C_WRITE_BYTE(SLA_SPO2_W,PPG_CONFIG,0b11100100);
	I2C_WRITE_BYTE(SLA_SPO2_W,PPG_CONFIG_2,0X05);
	I2C_WRITE_BYTE(SLA_SPO2_W,LED_RGE_MA,0X0F);
	I2C_WRITE_BYTE(SLA_SPO2_W,INT_enable,0XE0);
	I2C_WRITE_BYTE(SLA_SPO2_W,FIFO_C1,0X01);
}

void READ_PPG_SAMPLE()
{
	char *PPG_PAYLOAD=0;
	PPG_PAYLOAD=I2C_READ_BYTE(SLA_SPO2_W,SLA_SPO2_R,FIFO_DATA,3);
	PPG_all=((((*PPG_PAYLOAD)&0x07)<<16))|(((*(PPG_PAYLOAD+1))&0XFF)<<8)|((*(PPG_PAYLOAD+2))&0XFF);
	PPG_SAMPLES_REDUCED[(PPG_SAMPLES_PLACER++)%PPG_SAMPLES_REDUCED_LENGTH]=uint16_t(PPG_all>>3);
	//_delay_ms(20);
}

void ADC_INITIALIZATION()
{
	ADMUX=0X40;
	ADCSRA=0X87;
}

int GET_BATTERY()
{
	volatile float percentage=0.0f;
	setbit(ADCSRA,ADSC);
	while(checkbit(ADCSRA,ADSC,1));
	percentage=(((((ADC/1023.0)*3.3*2)*1.02319587628866)-3.65)/0.55)*100;
	if(percentage >100)
		percentage=100;
	batt_array[(batt_array_counter)%20]=int(percentage);
	batt_reading_now+=((batt_array[(batt_array_counter)%20])-(batt_array[(batt_array_counter+1)%20]));
	batt_array_counter++;
	return int(batt_reading_now/19.0);
}

void DRAW_BATTERY(int percentage)
{
	volatile double no_of_blocks=(percentage*0.78);
		for(int u=112;u<125;u++)
		{
			for(int point=1;point<7;point++)
			{
				if(int(no_of_blocks)>0)
					{
						no_of_blocks--;
						setbit(oled_line[LINE_1][u],point);
					}
				else
					{
						clearbit(oled_line[LINE_1][u],point);
					}
			}
			oled_line[LINE_1][u]|=129;
		}
}

void UPDATE_HR()
{
	int i=0;
	volatile char interval_arr[10]={0},interval_arr_counter=0,intervals[10]={0};
	uint16_t MAX=0,MIN=65535;
	for(i=0;i<PPG_SAMPLES_REDUCED_LENGTH;i++)
	{
		if(PPG_SAMPLES_REDUCED[i] !=0)
		{
			if(PPG_SAMPLES_REDUCED[i] >MAX)
				MAX=PPG_SAMPLES_REDUCED[i];
			if(PPG_SAMPLES_REDUCED[i]<MIN)
				MIN=PPG_SAMPLES_REDUCED[i];
		}
	}
	char q=0,sorter[24]={0};
	for(i=0;i<50;i++)
	{
		q=char(double((PPG_SAMPLES_REDUCED[i]-MIN)*(23.0/(MAX-MIN))));
		sorter[q]++;
// 		if(q>16)
// 		{
// 			oled_line[LINE_5][i]=(1<<char(q-16));
// 			oled_line[LINE_6][i]=0;
// 			oled_line[LINE_7][i]=0;
// 		}
// 		else if(q>8)
// 		{
// 			oled_line[LINE_6][i]=(1<<char(q-8));
// 			oled_line[LINE_7][i]=0;
// 			oled_line[LINE_5][i]=0;
// 		}
// 		else
// 		{
// 			oled_line[LINE_7][i]=(1<<char(q));
// 			oled_line[LINE_6][i]=0;
// 			oled_line[LINE_5][i]=0;
// 		}
	}
	int lock=0;
	for(i=0;i<50;i++)
	{
		q=char(double((PPG_SAMPLES_REDUCED[i]-MIN)*(23.0/(MAX-MIN))));
	 		if((q>17)&& (lock==0))
			 {
	 			lock=1;
	 			interval_arr[(interval_arr_counter++)%10]=i;
				 i+=2;
			 }
	 		if(q<6)
				lock=0;
	}
// 	setbit(OLED_NEW_DATA_FLAGS,LINE_5);
// 	setbit(OLED_NEW_DATA_FLAGS,LINE_6);
// 	setbit(OLED_NEW_DATA_FLAGS,LINE_7);
	for(i=0;i<24;i++)
	{
		if(sorter[i] > 10)
		{
			
			HR_not_weared_counter--;
			if(HR_not_weared_counter ==0)
			{
				HR_CUMULATIVE=0;
				for(int t=0;t<20;t++)
					HR_ARRAY[t]=0;
					HR=0;
					first_time=0;
			}
			return;
		}
	}

volatile int k=0; volatile char probe=0,hr_old=HR;
	HR=0;
	for (i=0;(i<9)&&(interval_arr[(i+1)] !=0);i++)
	{
	//	probe=char((interval_arr[i+1]-interval_arr[i])*((30000.0/ppg_sample_interval)));
	probe=char(1100/(interval_arr[i+1]-interval_arr[i]));
		if((probe < 100) && (probe >50))
		{
			intervals[k++]=probe;
			HR_not_weared_counter=5;
		}
	}

	for(int u=0;u<k;u++)
		HR+=char(intervals[u]/k);
	if(HR !=0)
	{
		first_time++;
		if(first_time>10)
			first_time=10;
	HR_ARRAY[(HR_array_counter++)%10]=HR;
	HR_CUMULATIVE+=HR_ARRAY[(HR_array_counter-1)%10]-HR_ARRAY[(HR_array_counter)%10];
	HR=char(HR_CUMULATIVE/first_time);
	}
	else
	{
		HR=hr_old;
	}
	
}