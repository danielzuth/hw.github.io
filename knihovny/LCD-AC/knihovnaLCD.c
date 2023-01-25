///////////// DEFINICE LCD /////////////////////
#define LCD_Data        	PORTA
#define LCD_ControlP	PORTC

#define LCD_DataD		DDRA

#define LCD_ControlPD	DDRC
#define LCD_SetEnable() PORTC |= 16
#define LCD_ClrEnable() PORTC &= ~16
#define LCD_SetData()   PORTC |= 4
#define LCD_SetCommand()PORTC &= ~4
#define LCD_SetRead()   PORTC |= 8;
#define LCD_SetWrite()  PORTC &= ~8;
#define SoundOn()       PORTC |= 32;
#define SoundOff()      PORTC &= ~32;
#define SoundInvert()   PORTC ^= 32;


void LCD_WriteDelay();
void LCD_WriteData(unsigned char co);
void LCD_WriteCommand(unsigned char co);
void LCD_Init();
void LCD_Clear();
void LCD_Position(unsigned char radek, unsigned char sloupec);
void LCD_WriteString(char* retezec);
void LCD_WriteCString(const char* retezec);
void LCD_PrDec(unsigned char co);
void LCD_PrHexByte(unsigned char co);
void LCD_PrHexInt(unsigned int co);

void LCD_WriteDelay()
{
 
_delay_us(45);
 // unsigned char i;
 // for (i = 0; i<250; i++);
}

void LCD_WriteData(unsigned char co)
{
        LCD_SetData();
        LCD_WriteDelay();
        LCD_Data = co;  
        LCD_WriteDelay();
        LCD_SetEnable();
        LCD_WriteDelay();        
        LCD_ClrEnable(); 
        LCD_WriteDelay();        
}

void LCD_WriteCommand(unsigned char co)
{
        LCD_SetCommand();
        LCD_WriteDelay();
        LCD_Data = co;  
        LCD_WriteDelay();
        LCD_SetEnable();
        LCD_WriteDelay();        
        LCD_ClrEnable();        
        LCD_WriteDelay();
}


void LCD_Init()
{               
		LCD_Data =0x00;
		LCD_DataD=0xFF;
		LCD_ControlP=0x00;
		LCD_ControlPD=0x3C;             
        LCD_SetWrite();
        LCD_ClrEnable(); 
        LCD_WriteCommand(59);
        LCD_WriteCommand(12);
		LCD_Clear();	
}

void LCD_Clear()
{  
        unsigned int a;
        LCD_WriteCommand(1);                
        for (a = 0; a<5000; a++); 
}


void LCD_Position(unsigned char radek, unsigned char sloupec)
{
        unsigned char policko = 0;
        switch (radek)
        {
                case 0: policko+=0; break;
                case 1: policko+=0x40; break;
                case 2: policko+=0x10; break;
                case 3: policko+=0x050; break;
        }                                     
        
        policko += sloupec;
        LCD_WriteCommand(128|policko);
}


void LCD_WriteString(char* retezec)
{
	while (*retezec !='\0')
	{
		LCD_WriteData(*retezec);
		retezec +=1;
	}
}

void LCD_WriteCString(const char* retezec)
{
	while (*retezec !='\0')
	{
		LCD_WriteData(*retezec);
		retezec +=1;
	}
}

void LCD_PrDec(unsigned char co)
{
	LCD_WriteData((co / 10)+48);
	LCD_WriteData((co % 10)+48);

}

void LCD_PrHexByte(unsigned char co)
{
	unsigned char znak;
	
	znak = (co / 16);
	if (znak < 10)		
		LCD_WriteData(znak+48);
	else
		LCD_WriteData(znak+7+48);
	
	znak = (co % 16);
	if (znak < 10)		
		LCD_WriteData(znak+48);
	else
		LCD_WriteData(znak+7+48);		

}

void LCD_PrHexInt(unsigned int co)
{
	unsigned char hi_nibble, lo_nibble;
	hi_nibble = (unsigned char)(co >> 8);
	lo_nibble = (unsigned char)co;
	LCD_PrHexByte(hi_nibble);
	LCD_PrHexByte(lo_nibble);
}

