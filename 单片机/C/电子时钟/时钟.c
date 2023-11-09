#include<reg51.h>

unsigned char times=0,miao=0,fen=0,shi=0;

unsigned char code seg[]={0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90};

sbit P1_0=P1^0;
sbit P1_1=P1^1;
sbit P1_2=P1^2;
sbit P1_3=P1^3;
sbit P1_4=P1^4;
sbit P1_5=P1^5;
sbit P1_6=P1^6;
sbit P1_7=P1^7;

sbit P0_0=P0^0;
sbit P0_1=P0^1;
sbit P0_2=P0^2;
sbit P0_3=P0^3;
sbit P0_4=P0^4;
sbit P0_5=P0^5;

void delay(unsigned int t){
	//unsigned char i=115;
	while(t--){
		//while(i--);
	}
}

void miao_show(){
	P1=0x00;	
	P1_7=1;
	P2=seg[miao%10];
	delay(100);
	P1=0x00;
	P1_6=1;
	P2=seg[miao/10];
	delay(100);
}

void fen_show(){
	P1=0x00;
	P1_4=1;
	P2=seg[fen%10];
	delay(100);
	P1=0x00;
	P1_3=1;
	P2=seg[fen/10];
	delay(100);
}

void shi_show(){
	P1=0x00;
	P1_1=1;
	P2=seg[shi%10];
	delay(100);
	P1=0x00;
	P1_0=1;
	P2=seg[shi/10];
	delay(100);
}

void _show_(){
	P1=0x00;
	P1=0x24;
	P2=0xbf;
	delay(100);
}

void main(){
	TMOD=0x01;
	EA=1;
	ET0=1;
	TR0=1;
	TH0=0x3C;
	TL0=0xB0;
	EX0=1;
	IT0=1;
	EX1=1;
	IT1=1;
	while(1){
		miao_show();
		fen_show();
		shi_show();
		_show_();
	}
}

void clock()interrupt 1{
	times++;
	TH0=0x3C;
	TL0=0xB0;
	if(times==20){
		miao++;
		times=0;
	}
	if(miao==60){
		fen++;
		miao=0;
	}
	if(fen==60){
		shi++;
		fen=0;
	}
	if(shi==24){
		shi=0;
	}

}

void change_up()interrupt 0{
	if(P0_0==0){
		shi++;
	}
	if(P0_1==0){
		fen++;
	}
	if(P0_2==0){
		miao++;
	}
}

void change_down()interrupt 2{
	if(P0_3==0&shi>0){
		shi--;
	}
	if(P0_4==0&fen>0){
		fen--;
	}
	if(P0_5==0&miao>0){
		miao--;
	}
}