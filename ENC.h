#ifndef __LOG_DUAL_C_H
#define __LOG_DUAL_C_H

#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>

typedef __uint128_t uint128;

unsigned int const I = 0b100011011;
unsigned char const G = 0x05;
/*							  {0x01000000,0x02000000,0x04000000,0x08000000,0x10000000,0x20000000,0x40000000,0x80000000,0x1b000000,0x36000000};*/
unsigned int const RCON[10] = {0x00ffffff,0x8cffffff,0x19ffffff,0xa5ffffff,0x32ffffff,0xbeffffff,0x4bffffff,0xd7ffffff,0x64ffffff,0xf0ffffff};

unsigned char const S_log[16][16]={	{0xf9,0x2a,0x54,0x60,0x7b,0x4b,0x45,0xb9,0xe8,0x63,0x37,0x53,0x1d,0x5d,0x05,0x82},
									{0x15,0x69,0xaf,0x3e,0x8c,0x87,0x3f,0xd6,0xcc,0xf6,0x46,0x64,0x7a,0x68,0x0f,0x12},
									{0x72,0x75,0x88,0xec,0x8f,0x06,0x3b,0x55,0xbb,0xc5,0xab,0x6b,0x99,0xc2,0xa2,0x09},
									{0x51,0x4c,0xe7,0x18,0x39,0x9b,0x5c,0xd2,0x36,0x25,0xf7,0x0b,0xc6,0x2b,0x0e,0xa9},
									{0x81,0xd7,0x30,0xa1,0x20,0xda,0xe4,0xcf,0x84,0xac,0xbf,0xe3,0x78,0xbc,0xe9,0x31},
									{0xae,0x80,0xeb,0x10,0x07,0x5b,0x4f,0x76,0x1a,0x27,0x58,0x23,0x3a,0x6c,0x5a,0xa4},
									{0x66,0xfb,0x0d,0x5f,0xdb,0x98,0xc4,0x71,0x9e,0xb6,0xd8,0x1b,0xc3,0x1f,0xfd,0x77},
									{0xca,0x94,0x62,0x44,0x8a,0xfa,0x11,0xa3,0x70,0x59,0x08,0x41,0x4e,0x33,0x6e,0xed},
									{0xf2,0x2f,0x48,0xc0,0x97,0x16,0xc7,0x85,0x86,0xfe,0x74,0x2e,0x65,0x21,0x3d,0x52},
									{0x26,0xb5,0xe6,0x0c,0xbd,0xee,0x24,0x7e,0x17,0x38,0x13,0xf8,0x6d,0x7d,0x50,0xaa},
									{0x89,0x1e,0x49,0xef,0xfc,0xb2,0x90,0xb0,0x34,0x95,0x56,0x42,0x67,0xea,0x29,0x9d},
									{0x7c,0xe5,0x19,0xf3,0x8b,0xb1,0x7f,0x8d,0xa0,0x83,0x1c,0xad,0xb7,0x91,0x43,0x22},
									{0x4a,0x3c,0x9a,0xdc,0xf5,0xdd,0x92,0x28,0xd9,0x35,0x79,0xd0,0x03,0xba,0xa5,0xd4},
									{0xe2,0xde,0xd5,0x6f,0xc8,0xa8,0xb8,0x9f,0xc1,0x14,0x93,0x6a,0x47,0x5e,0x04,0xbe},
									{0xcb,0x40,0xce,0x00,0x0a,0xf1,0xe0,0xcd,0xf4,0xb4,0xc9,0x2c,0x02,0x4d,0x9c,0x96},
									{0x01,0xa6,0x61,0xd1,0xd3,0x8e,0x57,0xb3,0x2d,0x32,0xa7,0xdf,0xf0,0x73,0xff,0xe1}	};

unsigned char const SBOX[16][16]={	{0x63,0x7c,0x77,0x7b,0xf2,0x6b,0x6f,0xc5,0x30,0x01,0x67,0x2b,0xfe,0xd7,0xab,0x76 },
									{0xca,0x82,0xc9,0x7d,0xfa,0x59,0x47,0xf0,0xad,0xd4,0xa2,0xaf,0x9c,0xa4,0x72,0xc0 },
									{0xb7,0xfd,0x93,0x26,0x36,0x3f,0xf7,0xcc,0x34,0xa5,0xe5,0xf1,0x71,0xd8,0x31,0x15 },
									{0x04,0xc7,0x23,0xc3,0x18,0x96,0x05,0x9a,0x07,0x12,0x80,0xe2,0xeb,0x27,0xb2,0x75 },
									{0x09,0x83,0x2c,0x1a,0x1b,0x6e,0x5a,0xa0,0x52,0x3b,0xd6,0xb3,0x29,0xe3,0x2f,0x84 },
									{0x53,0xd1,0x00,0xed,0x20,0xfc,0xb1,0x5b,0x6a,0xcb,0xbe,0x39,0x4a,0x4c,0x58,0xcf },
									{0xd0,0xef,0xaa,0xfb,0x43,0x4d,0x33,0x85,0x45,0xf9,0x02,0x7f,0x50,0x3c,0x9f,0xa8 },
									{0x51,0xa3,0x40,0x8f,0x92,0x9d,0x38,0xf5,0xbc,0xb6,0xda,0x21,0x10,0xff,0xf3,0xd2 },
									{0xcd,0x0c,0x13,0xec,0x5f,0x97,0x44,0x17,0xc4,0xa7,0x7e,0x3d,0x64,0x5d,0x19,0x73 },
									{0x60,0x81,0x4f,0xdc,0x22,0x2a,0x90,0x88,0x46,0xee,0xb8,0x14,0xde,0x5e,0x0b,0xdb },
									{0xe0,0x32,0x3a,0x0a,0x49,0x06,0x24,0x5c,0xc2,0xd3,0xac,0x62,0x91,0x95,0xe4,0x79 },
									{0xe7,0xc8,0x37,0x6d,0x8d,0xd5,0x4e,0xa9,0x6c,0x56,0xf4,0xea,0x65,0x7a,0xae,0x08 },
									{0xba,0x78,0x25,0x2e,0x1c,0xa6,0xb4,0xc6,0xe8,0xdd,0x74,0x1f,0x4b,0xbd,0x8b,0x8a },
									{0x70,0x3e,0xb5,0x66,0x48,0x03,0xf6,0x0e,0x61,0x35,0x57,0xb9,0x86,0xc1,0x1d,0x9e },
									{0xe1,0xf8,0x98,0x11,0x69,0xd9,0x8e,0x94,0x9b,0x1e,0x87,0xe9,0xce,0x55,0x28,0xdf },
									{0x8c,0xa1,0x89,0x0d,0xbf,0xe6,0x42,0x68,0x41,0x99,0x2d,0x0f,0xb0,0x54,0xbb,0x16 }	};

unsigned char const EXP_of_G[16][16]={	{0x01,0x05,0x11,0x55,0x1a,0x72,0xa1,0x13,0x5f,0x38,0xd8,0x95,0xf7,0x06,0x1e,0x66},
									{0xe5,0x5c,0x37,0xeb,0x6a,0xd9,0x90,0xe6,0x53,0x04,0x14,0x44,0x4f,0x68,0xd3,0xb2},
									{0x4c,0x67,0xe0,0x4d,0x62,0xf1,0x18,0x78,0x83,0xb9,0x6b,0xdc,0x81,0xb3,0x49,0x76},
									{0xb5,0x57,0x10,0x50,0x0b,0x27,0xbb,0x61,0xfe,0x2b,0x87,0xad,0x2f,0x93,0xe9,0x60},
									{0xfb,0x3a,0xd2,0xb7,0x5d,0x32,0xfa,0x3f,0xc3,0xe2,0x47,0x40,0x5b,0x2c,0x9c,0xda},
									{0x9f,0xd5,0xac,0x2a,0x82,0xbc,0x7a,0x89,0x9b,0xc1,0xe8,0x65,0xea,0x6f,0xc8,0xc5},
									{0xfc,0x21,0xa5,0x07,0x1b,0x77,0xb0,0x46,0x45,0x4a,0x79,0x86,0xa8,0x3e,0xc6,0xf3},
									{0x12,0x5a,0x29,0x8d,0x8f,0x85,0xa7,0x0d,0x39,0xdd,0x84,0xa2,0x1c,0x6c,0xc7,0xf6},
									{0x03,0x0f,0x33,0xff,0x2e,0x96,0xf8,0x35,0xe1,0x48,0x73,0xa4,0x02,0x0a,0x22,0xaa},
									{0x34,0xe4,0x59,0x26,0xbe,0x70,0xab,0x31,0xf5,0x0c,0x3c,0xcc,0xd1,0xb8,0x6e,0xcd},
									{0xd4,0xa9,0x3b,0xd7,0xa6,0x08,0x28,0x88,0x9e,0xd0,0xbd,0x7f,0x98,0xce,0xdb,0x9a},
									{0xc4,0xf9,0x30,0xf0,0x1d,0x69,0xd6,0xa3,0x19,0x7d,0x92,0xec,0x71,0xae,0x20,0xa0},
									{0x16,0x4e,0x6d,0xc2,0xe7,0x56,0x15,0x41,0x5e,0x3d,0xc9,0xc0,0xed,0x74,0xbf,0x75},
									{0xba,0x64,0xef,0x7e,0x9d,0xdf,0x8e,0x80,0xb6,0x58,0x23,0xaf,0x25,0xb1,0x43,0x54},
									{0x1f,0x63,0xf4,0x09,0x2d,0x99,0xcb,0xca,0xcf,0xde,0x8b,0x91,0xe3,0x42,0x51,0x0e},
									{0x36,0xee,0x7b,0x8c,0x8a,0x94,0xf2,0x17,0x4b,0x7c,0x97,0xfd,0x24,0xb4,0x52,0x00}	};

unsigned char const LOG_base_G[16][16]={	{0xff,0x00,0x8c,0x80,0x19,0x01,0x0d,0x63,0xa5,0xe3,0x8d,0x34,0x99,0x77,0xef,0x81},
									{0x32,0x02,0x70,0x07,0x1a,0xc6,0xc0,0xf7,0x26,0xb8,0x04,0x64,0x7c,0xb4,0x0e,0xe0},
									{0xbe,0x61,0x8e,0xda,0xfc,0xdc,0x93,0x35,0xa6,0x72,0x53,0x39,0x4d,0xe4,0x84,0x3c},
									{0xb2,0x97,0x45,0x82,0x90,0x87,0xf0,0x12,0x09,0x78,0x41,0xa2,0x9a,0xc9,0x6d,0x47},
									{0x4b,0xc7,0xed,0xde,0x1b,0x68,0x67,0x4a,0x89,0x2e,0x69,0xf8,0x20,0x23,0xc1,0x1c},
									{0x33,0xee,0xfe,0x18,0xdf,0x03,0xc5,0x31,0xd9,0x92,0x71,0x4c,0x11,0x44,0xc8,0x08},
									{0x3f,0x37,0x24,0xe1,0xd1,0x5b,0x0f,0x21,0x1d,0xb5,0x14,0x2a,0x7d,0xc2,0x9e,0x5d},
									{0x95,0xbc,0x05,0x8a,0xcd,0xcf,0x2f,0x65,0x27,0x6a,0x56,0xf2,0xf9,0xb9,0xd3,0xab},
									{0xd7,0x2c,0x54,0x28,0x7a,0x75,0x6b,0x3a,0xa7,0x57,0xf4,0xea,0xf3,0x73,0xd6,0x74},
									{0x16,0xeb,0xba,0x3d,0xf5,0x0b,0x85,0xfa,0xac,0xe5,0xaf,0x58,0x4e,0xd4,0xa8,0x50},
									{0xbf,0x06,0x7b,0xb7,0x8b,0x62,0xa4,0x76,0x6c,0xa1,0x8f,0x96,0x52,0x3b,0xbd,0xdb},
									{0x66,0xdd,0x1f,0x2d,0xfd,0x30,0xd8,0x43,0x9d,0x29,0xd0,0x36,0x55,0xaa,0x94,0xce},
									{0xcb,0x59,0xc3,0x48,0xb0,0x5f,0x6e,0x7e,0x5e,0xca,0xe7,0xe6,0x9b,0x9f,0xad,0xe8},
									{0xa9,0x9c,0x42,0x1e,0xa0,0x51,0xb6,0xa3,0x0a,0x15,0x4f,0xae,0x2b,0x79,0xe9,0xd5},
									{0x22,0x88,0x49,0xec,0x91,0x10,0x17,0xc4,0x5a,0x3e,0x5c,0x13,0xbb,0xcc,0xf1,0xd2},
									{0xb3,0x25,0xf6,0x6f,0xe2,0x98,0x7f,0x0c,0x86,0xb1,0x46,0x40,0x60,0xfb,0x38,0x83}	};

unsigned char const TransForm[16][16]={	{0xff,0x19,0x32,0xdf,0x64,0x8a,0xbf,0x70,0xc8,0x78,0x15,0xf5,0x7f,0x63,0xe0,0x21},
									{0x91,0x44,0xf0,0x5c,0x2a,0x0a,0xeb,0xc4,0xfe,0x01,0xc6,0x68,0xc1,0xb5,0x42,0x2d},
									{0x23,0x0f,0x88,0x20,0xe1,0xb3,0xb8,0x6a,0x54,0x9d,0x14,0x79,0xd7,0x1f,0x89,0x65},
									{0xfd,0xc5,0x02,0xee,0x8d,0x93,0xd0,0x3f,0x83,0x53,0x6b,0x52,0x84,0xba,0x5a,0x37},
									{0x46,0xa2,0x1e,0xd8,0x11,0x82,0x40,0x6d,0xc3,0xec,0x67,0xc7,0x71,0xe4,0xd4,0xae},
									{0xa8,0xa0,0x3b,0x39,0x28,0xaa,0xf2,0xa7,0xaf,0xcb,0x3e,0xd1,0x13,0x9e,0xca,0xb0},
									{0xfb,0xbe,0x8b,0x0d,0x04,0x2f,0xdd,0x4a,0x1b,0xf8,0x27,0x3a,0xa1,0x47,0x7e,0xf6},
									{0x07,0x4c,0xa6,0xf3,0xd6,0x7a,0xa4,0x99,0x09,0x2b,0x75,0xb7,0xb4,0xc2,0x6e,0x0c},
									{0x8c,0xef,0x45,0x38,0x3c,0xfa,0xb1,0x90,0x22,0x2e,0x05,0x62,0x80,0x34,0xda,0x96},
									{0x87,0x10,0xd9,0x35,0xce,0xbc,0x8f,0xb2,0xe2,0x77,0xc9,0x9f,0xa9,0x29,0x5d,0x9b},
									{0x51,0x6c,0x41,0xb6,0x76,0xe3,0x72,0x57,0x50,0x9c,0x55,0xd3,0xe5,0xe8,0x4f,0x58},
									{0x5f,0x86,0x97,0x25,0x7c,0x1d,0xa3,0x7b,0x26,0xf9,0x3d,0xcc,0x95,0xdb,0x61,0x06},
									{0xf7,0x1c,0x7d,0x48,0x17,0x31,0x1a,0x4b,0x08,0x9a,0x5e,0x59,0xbb,0xcf,0x94,0xcd},
									{0x36,0x5b,0xf1,0xab,0x4e,0xe9,0x74,0x2c,0x43,0x92,0x8e,0xbd,0xfc,0x66,0xed,0x03},
									{0x0e,0x24,0x98,0xa5,0x4d,0xac,0xe7,0xe6,0xad,0xd5,0xf4,0x16,0x49,0xde,0x33,0x81},
									{0x12,0xd2,0x56,0x73,0xea,0x0b,0x6f,0xc0,0x69,0xb9,0x85,0x60,0xdc,0x30,0x18,0x00}	};


#define T(x) (TransForm[((x)>>4)&0xf][(x)&0xf])
#define exp_g(e) (EXP_of_G[((e)>>4)&0xf][(e)&0xf])
#define log_g(x) (LOG_base_G[((x)>>4)&0xf][(x)&0xf])
#define subByte(a) (SBOX[((a)>>4)&0xf][a&0xf])
#define subByte_g(a) (S_log[((a)>>4)&0xf][(a)&0xf])

#define Word(a,i) (((a)>>((3-(i))<<5))&0xffffffff)
#define Byte(b,i) (((b)>>((3-(i))<<3))&0xff)
#define rotWord(W) ((Byte(W,1)<<24)|(Byte(W,2)<<16)|(Byte(W,3)<<8)|Byte(W,0))
#define subWord(W) ((unsigned int)(subByte_g(Byte(W,0))<<24)|(unsigned int)(subByte_g(Byte(W,1))<<16)|(unsigned int)(subByte_g(Byte(W,2))<<8)|(unsigned int)subByte_g(Byte(W,3)))
#define putAt(t,i,j) (((t)<<((3-(i))<<5))<<((3-(j))<<3))
#define xor_word(a,b) ((((unsigned int)f_xor(Byte(a,0),Byte(b,0)))<<24)|(((unsigned int)f_xor(Byte(a,1),Byte(b,1)))<<16)|(((unsigned int)f_xor(Byte(a,2),Byte(b,2)))<<8)|((unsigned int)f_xor(Byte(a,3),Byte(b,3))))

unsigned int bits(unsigned int a);
unsigned char mult(unsigned int a,unsigned int b);
unsigned char F(unsigned int a);
unsigned char expo(unsigned char g,unsigned char e);
unsigned char f_xor(unsigned short i,unsigned short j);
unsigned char f_mult(unsigned short a,unsigned short b);
unsigned char f_pow(unsigned short g,unsigned short e);
unsigned char f_subByte(unsigned char a);
uint128  shiftRows(uint128 a);
uint128  mixColumn(uint128 a);
unsigned char multVector(unsigned int a,unsigned int b);
uint128 *keyExpansion(uint128 k);
uint128 xor_state(uint128 a,uint128 b);
unsigned char *logDual(const unsigned char *str,const unsigned char *key);

unsigned int bits(unsigned int a)
{
	unsigned int count=0;
	while(a!=0)
	{
		a>>=1;
		count++;
	}
	return count;
}

unsigned char mult(unsigned int a,unsigned int b)
{
	int i,j;
	unsigned int x = 0;
	unsigned int p,q;
	for(i=0;i<8;i++)
		for(j=0;j<8;j++)
		{
			p = (a>>i)&1;
			q = (b>>j)&1;
			if(p&q)
				x^=(1<<(i+j));
		}
	return F(x);
}

unsigned char F(unsigned int a)
{
	if(bits(a)<9)
		return a;
	unsigned int p,k;
	unsigned int x,y,q=0;
	x=a;
	while(bits(x)>=9)
	{
		p=bits(x);
		k=p-9;
		y=I<<k;
		x^=y;
	}
	
	return (unsigned char)x;
}

unsigned char expo(unsigned char g,unsigned char e)
{
	unsigned int b=bits(e);
	unsigned char s=1;
	while(b!=0)
	{
		b--;
		s=mult(s,s);
		if(((e>>b)&1)==1)
		{
			s=mult(s,g);
		}
	}
	
	return s;
}

unsigned char f_xor(unsigned short i,unsigned short j)
{
	unsigned int k;
	if(i==j)
		return 0xff;

	else if(i==0xff)
		return (unsigned char)(j%0xff);

	else if(j==0xff)
		return (unsigned char)(i%0xff);

	if(i<j)
		i^=j^=i^=j;

	k=j+T(i-j);
	return (unsigned char)(k%0xff);

}

unsigned char f_mult(unsigned short a,unsigned short b)
{
	unsigned int k;
	if(a==0xff || b==0xff)
		return 0xff;
	k=(a+b);
	return (unsigned char)(k%0xff);
}

unsigned char f_pow(unsigned short g,unsigned short e)
{
	if(g == 0xff)
		return 0xff;
	return (unsigned char)((g*e)%0xff);
}

unsigned char f_subByte(unsigned char a)
{
	unsigned int k;
	unsigned char s = exp_g(a);
	s = subByte(s);
	k=log_g(s);
	return (unsigned char)k;
}





/*main subroutines starts here */


uint128 shiftRows(uint128 a)
{	
	uint128 t = 0,k;
	int i,j;
	unsigned int word;
	for(int i=0;i<4;i++)
	{
		word = Word(a,i);
		for(int j=0;j<4;j++)	
		{
			k = Byte(word,j);
			t|=putAt(k,(4-j+i)&3,j);
		}
	}
	return t;
	
}

/*(02 03 01 01) will trasfrom to the logs which is (8c 80 00 00)*/
uint128 mixColumn(uint128 a)
{
	unsigned int ti[4]={0x8c800000,0x008c8000,0x00008c80,0x8000008c},word;
	uint128 u=0,k,t;
	for(int i=0;i<4;i++)
	{
		word = Word(a,i);
		for(int j=0;j<4;j++)	
		{	
			t=multVector(ti[j],word);
			u |= putAt(t,i,j);
		}
	}
	return u;	
}

unsigned char multVector(unsigned int a,unsigned int b)
{
	unsigned char t,k=0xff;
	
	for(int i=0;i<4;i++)
	{
		t= f_mult(Byte(a,i),Byte(b,i));
		k=f_xor(k,t);
	}
	return k;
}

uint128 *keyExpansion(uint128 k)
{
	uint128 *key = (uint128*)malloc(11*sizeof(uint128)),t;
	unsigned int temp,*w = (unsigned int*)malloc(44*sizeof(unsigned int));
	int i;
	
	for(i=0;i<4;i++)
		w[i] = Word(k,i);
	for(i=4;i<44;i++)
	{
		temp = w[i-1];
		if((i&3)==0)
			temp = xor_word((subWord(rotWord(temp))),RCON[(i>>2)-1]);
		w[i] = xor_word(w[i-4],temp);
	}
	for(i=0;i<11;i++)
	{	
		key[i] = 0;
		t = w[i<<2];
		key[i] |= t<<96;
		t = w[(i<<2)+1];
		key[i] |= t<<64;
		t = w[(i<<2)+2];
		key[i] |= t<<32;
		t = w[(i<<2)+3];
		key[i] |= t;
	}
	return key;
}

uint128 xor_state(uint128 a,uint128 b)
{
	uint128 x,y=0;
	int i,j;
	unsigned int word_a,word_b;
	unsigned char byte_a,byte_b;
	for(i=0;i<4;i++)
	{
		word_a = Word(a,i);
		word_b = Word(b,i);
		for(j=0;j<4;j++)
		{
			byte_a = Byte(word_a,j);
			byte_b = Byte(word_b,j);
			x = f_xor(byte_a,byte_b);
			y|=putAt(x,i,j);
		}
	}
	return y;
}

unsigned char *logDual(const unsigned char *str,const unsigned char *k)
{	
	uint128 key = 0,t,*K,x = 0,y;
	unsigned int word;
	unsigned char *res = (unsigned char*)malloc(17);
	for(int i=0;i<4;i++)
		for(int j=0;j<4;j++)	
		{
			t = k[(i<<2)+j];
			key|=putAt(t,i,j);
			t = str[(i<<2)+j];
			x  |=putAt(t,i,j);
		}
	
	K = keyExpansion(key);
	x=xor_state(x,K[0]);
	for(int r=1;r<10;r++)
	{
		y=x;
		x=0;
		for(int i=0;i<4;i++)
		{
			word = Word(y,i);
			for(int j=0;j<4;j++)
			{
				t = subByte_g(Byte(word,j));
				x |= putAt(t,i,j);
			}
			
		}
		x = shiftRows(x);
		x = mixColumn(x);
		x=xor_state(x,K[r]);
	}
	y=x;
	x=0;
	for(int i=0;i<4;i++)
	{
		word = Word(y,i);
		for(int j=0;j<4;j++)
		{
			t = subByte_g(Byte(word,j));
			x |= putAt(t,i,j);
		}
		
	}
	x = shiftRows(x);
	x=xor_state(x,K[10]);
	for(int i=0;i<4;i++)
	{
		word = Word(x,i);
		for(int j=0;j<4;j++)
		{	
			res[(i<<2)+j] = (unsigned char)Byte(word,j);
		}
	}
	res[16] = '\0';
	return res;
}

#endif
