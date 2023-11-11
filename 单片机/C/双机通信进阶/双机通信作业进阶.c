#include<reg51.h>

unsigned char code seg[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};
sbit P1_0=P1^0;
sbit P3_4=P3^4;
sbit P3_5=P3^5;
sbit P3_6=P3^6;
unsigned char segg=0;
unsigned char fasong=0,jieshou=0,i=0,kaiguan=0,kaiguann=0,fasongg=0;
void delay(unsigned int t){
	unsigned char i=125;
	while(t--){
		while(i--);
	}
}

void main(){
	EA=1;
	ES=1;
	EX1=1;
	EX0=1;
	
	TMOD=0x20;
	TH1=TL1=256-11059200/12/32/9600;
	TR1=1;
	IT1=1;
	IT0=1;
	
	SCON=0x50;
	PCON=0;
	
	while(1){
		if(segg==10) segg=0;
		P1=seg[segg];
		
		if(kaiguan==1){
			fasong='1';
			SBUF=fasong;
			while(!TI);
			TI=0;
			
			kaiguan=0;
			fasong=0;
		}
		if(kaiguann==1){
			SBUF=fasongg;
			while(!TI);
			TI=0;
			kaiguann=0;
		}
		
		if(jieshou=='1'){
			for(i=0;i<8;i++){
				P2=~(0x01<<i);
				delay(150);
			}
			P2=0xFF;
			jieshou=0;
		}
		if(jieshou=='2'){
			segg++;
			jieshou=0;
		}
	}
	
}

void MCU_left ()interrupt 4{
	//如果不加if(RI=0),每次发送也会进入此中断函数,使jieshou=SUBF,即发送
	//一个字符后也会"接收"一个同样的字符
	if(RI==1){
		RI=0;
		jieshou=SBUF;
	}
}

void switch_fuck ()interrupt 2{
	kaiguan=1;
}
void switch_fuckk ()interrupt 0{
	if(P3_4==0){
		kaiguann=1;
		fasongg='a';
	}
	if(P3_5==0){
		kaiguann=1;
		fasongg='b';
	}
	if(P3_6==0){
		kaiguann=1;
		fasongg='c';
	}
}