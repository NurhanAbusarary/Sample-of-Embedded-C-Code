#define setbit(x,y) x |= (1 << y)
#define clearbit(x,y) x &= ~(1 << y)
#define togglebit(x,y) x ^= (1 << y)
#define checkbit(a,b,c) c == (1 & (a >> b))
#define F_CPU 8000000UL

#define ACCELEROMETER_ADD_W		  	0X3E
#define ACCELEROMETER_ADD_R		  	0X3F
#define ACCELEROMETER_WHOAMI	  	0X0A
#define ACCELEROMETER_OUT_XL	  	0X06
#define ACCELEROMETER_OUT_XH	  	0X07
#define ACCELEROMETER_OUT_YL	  	0X08
#define ACCELEROMETER_OUT_YH	  	0X09
#define ACCELEROMETER_OUT_ZL		  0X0A
#define ACCELEROMETER_OUT_ZH		  0X0B
#define ACCELEROMETER_CNTL1			  0x18
#define ACCELEROMETER_CNTL2			  0x19
#define ACCELEROMETER_CNTL3			  0x1A
#define ACCELEROMETER_ODCNTL	   	0x1B

#define ACCELEROMETER_CNTL1_val		0xC0
#define ACCELEROMETER_CNTL2_val		0x00
#define ACCELEROMETER_CNTL3_val		0xFF
#define ACCELEROMETER_ODCNTL_val	0x07

#define TEMPERATURE_ADD_W			0X94
#define TEMPERATURE_ADD_R			0X95

#define PPG_SAMPLES_REDUCED_LENGTH	50

#define FREEFALL_FLAG				0
#define temperature_interval		500 // 50 times 2 msec
#define oled_interval				250
#define ppg_sample_interval			25
#define acc_interval				1
#define hr_interval					1000

#define OLED_ADDRESS_W				0x78
#define OLED_ADDRESS_R				0X79

#define OLED_COMMAND				0x80
#define OLED_DATA					0X40

#define SLA_SPO2_W					0XBC
#define SLA_SPO2_R					0XBD
#define FIFO_C1						0X09 
#define FIFO_C2						0X0A 
#define SYS_CONTROL					0x0D 
#define LED_IR_MA					0X11
#define LED_RED_MA					0X12
#define LED_RGE_MA					0X14
#define LED_PILOT_MA				0X15
#define PPG_CONFIG					0X0E 
#define PPG_CONFIG_2				0X0F 
#define INT_enable					0x02


#define FIFO_WR_PTR					0
#define OVF_COUNTER					1
#define FIFO_RD_PTR					2
#define FIFO_DATA					0x07

#define LINE_1						0
#define LINE_2						1
#define LINE_3						2
#define LINE_4						3
#define LINE_5						4
#define LINE_6						5
#define LINE_7						6
#define LINE_8						7
