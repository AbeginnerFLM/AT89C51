#include<reg51.h>

sbit sw=P2^1;
unsigned char code seg[]={0xb0,0xa4,0xf9,0xc0};  
	
void reply(unsigned int x){
	unsigned char i=115;
	while(x--){
		while(i--);
	}
}

void begin(){
	P2=0x87;
}

void car_red(){
	char i=0;
	char m=0;
	for(i=0;i<3;i++){
		P2=0x47;
		reply(250);
		P2=0x07;
		reply(250);	
	}
	P2=0x33;	
	for(m=0;m<4;m++){
		P1=seg[m];
		reply(500);
	}
	P1=0xff;
}

void car_green(){
	char i=0;
	for(i=0;i<3;i++){
		P2=0x2b;
		reply(250);
		P2=0x23;
		reply(250);	
	}
}


void main(){
	while(1){
		begin();
		if(sw==0){
			reply(10);
			if(sw==0){
				car_red();
				car_green();	
			}
		}	

	
	}

}