#include<reg51.h>

sbit P1_0=P1^0;
unsigned char fasong=0,jieshou=0,i=0,kaiguan=0;
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
	
	TMOD=0x20;
	TH1=TL1=256-11059200/12/32/9600;
	TR1=1;
	IT1=1;
	
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
		
		if(jieshou=='1'){
			for(i=0;i<8;i++){
				P2=~(0x80>>i);
				delay(150);
			}
			P2=0xFF;
			jieshou=0;
		}
	}
	
}

void MCU_left ()interrupt 4{
	if(RI==1){
		RI=0;
		jieshou=SBUF;
	}
}

void switch_fuck ()interrupt 2{
	kaiguan=1;
}