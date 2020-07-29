/*
*	设备：ATC-1000WF	
*	默认数据格式：
*	模块的ID号为：01
*	传输波特率：4800bps
*	格式为：8，N，1
*	发送数据：01 03 00 48 00 06 45 DE （读0048 开始的6 个寄存器）
*	接收数据：01 03 0C 57 E4 09 D9 02 2D 00 00 03 40 03 D6 3F 17
 */



unsigned int calccrc(unsigned char crcbuf,unsigned int crc)
{
	unsigned char i;
	unsigned char chk;
	crc=crc ^ crcbuf;
	for(i=0;i<8;i++)
	{
		chk=( unsigned char)(crc&1);
		crc=crc>>1;
		crc=crc&0x7fff;
		if (chk==1)
		crc=crc^0xa001;
		crc=crc&0xffff;
	}
	return crc;
}

unsigned int chkcrc(unsigned char *buf,unsigned char len)
{
	unsigned char hi,lo;
	unsigned int i;
	unsigned int crc;
	crc=0xFFFF;
	for(i=0;i<len;i++)
	{
		crc=calccrc(*buf,crc);
		buf++;
	}
	hi=( unsigned char)(crc%256);
	lo=( unsigned char)(crc/256);
	crc=(((unsigned int)(hi))<<8)|lo;
	return crc;
}

void read_data(void)
{
	union crcdata
	{
		unsigned int word16;
		unsigned char byte[2];
	}crcnow;
	if((Clock.Second%2)==1) //2 秒读一次
	{
		Tx_Buffer[0]=Read_ID; //抄读模块的ID 号
		Tx_Buffer[1]=0x03;
		Tx_Buffer[2]=0x00;
		Tx_Buffer[3]=0x48;
		Tx_Buffer[4]=0x00;
		Tx_Buffer[5]=0x06;
		crcnow.word16=chkcrc(Tx_Buffer,6);
		Tx_Buffer[6]=crcnow.byte[1]; //CRC 效验低字节在前
		Tx_Buffer[7]=crcnow.byte[0];
		Send_data(8); //发送8 个数据，请根据单片机类型自己编程
	}
}


void Analysis_data(void)
{
	unsigned char i;
	union crcdata
	{
		unsigned int word16;
		unsigned char byte[2];
	}crcnow;
	if(Comm[1].Status==2) //接收完成
	{
		if(RX_Buffer[0]==Read_ID) //确认ID 正确
		{
		crcnow.word16=chkcrc(RX_Buffer,Comm[1].nRx-2); //Comm[1].nRx 是接收数据长度
		if((crcnow.byte[0]==RX_Buffer[Comm[1].nRx-1])&&(crcnow.byte[1]==RX_Buffer[Comm[1].nRx-2])) //CRC
		效验
		{
			Voltage_data=(((unsigned int)(RX_Buffer[3]))<<8)|RX_Buffer[4]; //Voltage_data 为unsigned int 型
			Current_data=(((unsigned int)(RX_Buffer[5]))<<8)|RX_Buffer[6]; //Current_data 为unsigned int 型
			Power_data=(((unsigned int)(RX_Buffer[7]))<<8)|RX_Buffer[8]; //Power_data 为unsigned int 型
			Energy_data=(((unsigned long)(RX_Buffer[9]))<<24)|(((unsigned long)(RX_Buffer[10]))<<16)|(((unsigned
			long)(RX_Buffer[11]))<<8)|RX_Buffer[12]; ////Energy_data 为unsigned long 型
			Pf_data=(((unsigned int)(RX_Buffer[13]))<<8)|RX_Buffer[14]; //Pf_data 为unsigned int 型
		}
	}
	Comm[1].Status=0; //切换回接收数据状态
	}
}

//说明：例子中的变量请自己根据习惯定义，Voltage_data~Pf_data 等数据除以对应的倍率，就得到实际的值

