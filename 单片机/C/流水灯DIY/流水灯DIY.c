#include<reg51.h>

unsigned  char code rp[]={0x81,0x82,0x84,0x88,0x90,0xa0,0xc0};//rightplace

void deply(unsigned int x){

	unsigned char q=120;
	while(x--){
		while(q--);	
	}
}

void left(){
	unsigned int i=0;
	for(i=0;i<7;i++){
		P0=~(0x03<<i);
		P1=~(0x02<<i);
		P2=~(0x02<<i);
		deply(200);
	}
}

void right(){
	unsigned int i=0;
	P0=0x3e;
	P1=0x7e;
	P2=0x7c;
	//刚开始的位置
	deply(200);
	//之后的位置
	P0=0x3f;
	
	for(i=0;i<7;i++){
		P1=P2=~rp[i];
		P3=~(0x03<<i);
		deply(200);
	}
}

void xiaochu(unsigned char i){	
	while(i--){
		P0=P1=P2=P3=0x3f;
		deply(200);		
		P0=P1=P2=P3=0xff;
		deply(200);
	}
}

void main(){
	while(1){
		left();
		right();
		xiaochu(3);
	   	deply(500);
	}
}