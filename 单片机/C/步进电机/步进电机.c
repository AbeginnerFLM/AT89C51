#include<reg51.h>

//ud为挡位 sw=1顺时针 sw=2逆时针 speed转速
unsigned char sw=0,ud=2;
unsigned int speed=225;
//电机旋转顺序
unsigned char code ms[]={0x01,0x03,0x02,0x06,0x04,0x0c,0x08,0x09};
//数码管顺序
unsigned char code seg[]={0xf9,0xa4,0xb0};
sbit P10=P1^0;
sbit P11=P1^1;
sbit P14=P1^4;
sbit P15=P1^5;
void delay(unsigned int t){
	unsigned char i=115;
	while(t--){
		while(i--);
	}
}

void main(){
	while(1){
		signed char i=0,j=7;
		EA=1;
		EX0=1;
		EX1=1;
		IT0=1;
		IT1=1;
			
//		switch(P1){
//			case 0xfe:
//				sw=1;
//				break;
//			case 0xfb:
//				sw=2;
//				break;
//		}	
		
		if(sw==1){
			//电机正转
			for(i;i<8;i++){
				P2=ms[i];
				P0=seg[ud-1];
				delay(speed);
			}
		}

		if(sw==2){
			//电机反转
			for(j;j>=0;j--){
				P2=ms[j];
				P0=seg[ud-1];
				delay(speed);
			}
		}
		P0=0xff;
		
	}
}

void stopsw() interrupt 0{
	sw=0;
	ud=2;
	speed=225;
}

void shun_ni__up_down() interrupt 2{
	if(P10==0){
		sw=1;
	}
	if(P11==0){
		sw=2;
	}
	
	if(P14==0&ud!=3){
		delay(10);
		if(P14==0){
			speed-=150;
			ud++;
		}
	}
	if(P15==0&ud!=1){
		delay(10);
		if(P15==0){
			speed+=150;
			ud--;
		}
	}
	
}


