#include<reg51.h>

sbit P1_0=P1^0;

unsigned char code ms[]={0x01,0x03,0x02,0x06,0x04,0x0c,0x08,0x09};
unsigned char fasong=0,jieshou=0,i=0,kaiguan=0,kaiguann=0,fasongg=0,m=0;
char n=7;
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
		if(kaiguan==1){
			fasong='1';
			SBUF=fasong;
			while(!TI);
			TI=0;

			kaiguan=0;
			fasong=0;
		}
		
		if(kaiguann==1){
			fasongg='2';
			SBUF=fasongg;
			while(!TI);
			TI=0;

			kaiguann=0;
			fasongg=0;
		}
		
		if(jieshou=='1'){
			for(i=0;i<8;i++){
				P2=~(0x80>>i);
				delay(150);
			}
			P2=0xFF;
			jieshou=0;
		}
		
		if(jieshou=='a'){
			for(m=0;m<8;m++){
				P1=ms[m];
				delay(175);
			}
		}
		if(jieshou=='b'){
			for(n=7;n>=0;n--){
				P1=ms[n];
				delay(175);
		}
		if(jieshou=='c'){
			P1=0x00;
			jieshou=0;
		}
		
	}
	
}}

void MCU_left ()interrupt 4{
	if(RI==1){
		RI=0;
		jieshou=SBUF;
	}
}

void switch_fuck ()interrupt 2{
	kaiguan=1;
}
void switch_fuckk ()interrupt 0{
	kaiguann=1;
}