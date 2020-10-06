ISR(USART0_RX_vect)
{
	A[Data] = UDR0;
	Data = ((Data + 1) % 200);
}


ISR(TIMER0_OVF_vect)
{
	TIMER_STOP();
	TEMPERATURE_TIME--;PPG_SAMPLE_TIME--;OLED_TIME--;ACC_TIME--;HR_TIME--;
	if(TEMPERATURE_TIME == 0)
	{
		TEMPERATURE_TIME=temperature_interval;
		UPDATE_TEMPERATURE();
	}
	if(PPG_SAMPLE_TIME == 0)
	{
		PPG_SAMPLE_TIME=ppg_sample_interval;
		READ_PPG_SAMPLE();
	}
	if(OLED_TIME == 0)
	{
		OLED_TIME=oled_interval;
		for (int i=0;i<8;i++)
			if(checkbit(OLED_NEW_DATA_FLAGS,i,1))
			{
				OLED_PLACE_LINE(i,oled_line[i]);
				clearbit(OLED_NEW_DATA_FLAGS,i);
			}
	}
	if(ACC_TIME == 0)
	{
		ACC_TIME=acc_interval;
		UPDATE_FREEFALL_STATUS();
	}
	if(HR_TIME == 0)
	{
		HR_TIME=hr_interval;
		UPDATE_HR();
	}
	TIMER_RESET();
	TIMER_START();
}