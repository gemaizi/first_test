
#include "MAVLinkPayload.h"

#define FLT_NAN     0x7fc00000
#define FLT_POSINF  0x7f800000
#define FLT_NEGINF  0xff800000

typedef int8_t            s1;
typedef uint8_t           u1;
  
typedef int16_t           s2;
typedef uint16_t          u2;
  
typedef int32_t           s4;
typedef uint32_t          u4;
 
typedef int64_t           s8;
typedef uint64_t          u8;

typedef void (*functionptr) (void);     /* generic function pointer           */

struct imm {
      s4 i;
      s4 op1_t;
    };


typedef union {
  	 s4 		 i;
 	 s8 		 l;
  	 float		 f;
  	 double 	 d;
  	 void		*a;
  	 functionptr fp;
  	 u1 		 b[8];
   #if defined(ENABLE_SSA)
  	 struct imm  _i;
   #endif
   } imm_union;


void InitMAVLinkPayload(MAVLinkPayload mavLinkPayload)
{
    mavLinkPayload.read_index=0;
	mavLinkPayload.write_index=0;
	memset(mavLinkPayload.payload, 0, MAX_PAYLOAD_SIZE);
	
}

char* getData(MAVLinkPayload mavLinkPayload)
{
	return mavLinkPayload.payload;
}

int sizeofpayload(MAVLinkPayload mavLinkPayload)
{
	//return write_index-read_index;
	return mavLinkPayload.write_index;
}

 void add(char c,MAVLinkPayload mavLinkPayload)
{
	
	mavLinkPayload.payload[mavLinkPayload.write_index]=c;
	mavLinkPayload.write_index=(mavLinkPayload.write_index+1)%MAX_PAYLOAD_SIZE;
}

void resetIndex(MAVLinkPayload mavLinkPayload)
{
	mavLinkPayload.read_index = 0;
}

void reset_writeIndex(MAVLinkPayload mavLinkPayload)
{
	mavLinkPayload.write_index= 0;
}

int floatToIntBits(float value)
{
  	 imm_union val;
 	 int e, f;
   
 	 val.f = value;
  
  	 e = val.i & 0x7f800000;
  	 f = val.i & 0x007fffff;
  
  	 if (e == FLT_POSINF && f != 0)
  		 return FLT_NAN;
     return val.i;
}

float intBitsToFloat(int value)
{
     imm_union val;
     val.i = value;
     return val.f;
}

char getByte(MAVLinkPayload mavLinkPayload)
{
	char result = 0;
	result |= (mavLinkPayload.payload[mavLinkPayload.read_index] & 0xFF);
	mavLinkPayload.read_index=(mavLinkPayload.read_index+1);
	return (char) result;
}

short getShort(MAVLinkPayload mavLinkPayload)
{
	short result = 0;
	result |= (mavLinkPayload.payload[mavLinkPayload.read_index + 1]& 0xFF) << 8;
	result |= (mavLinkPayload.payload[mavLinkPayload.read_index + 0] & 0xFF);
	mavLinkPayload.read_index += 2;
	return (short) result;
}

int getInt(MAVLinkPayload mavLinkPayload)
{
	int result = 0;
	result |= (mavLinkPayload.payload[mavLinkPayload.read_index + 3] & (int) 0xFF) << 24;
	result |= (mavLinkPayload.payload[mavLinkPayload.read_index + 2] & (int) 0xFF) << 16;
	result |= (mavLinkPayload.payload[mavLinkPayload.read_index + 1] & (int) 0xFF) << 8;
	result |= (mavLinkPayload.payload[mavLinkPayload.read_index + 0] & (int) 0xFF);
	mavLinkPayload.read_index += 4;
	return (int) result;
}

long getLong(MAVLinkPayload mavLinkPayload)
{
	long result = 0;
	result |= (mavLinkPayload.payload[mavLinkPayload.read_index + 7] & (long) 0xFF) << 56;
	result |= (mavLinkPayload.payload[mavLinkPayload.read_index + 6] & (long) 0xFF) << 48;
	result |= (mavLinkPayload.payload[mavLinkPayload.read_index + 5] & (long) 0xFF) << 40;
	result |= (mavLinkPayload.payload[mavLinkPayload.read_index + 4] & (long) 0xFF) << 32;
	result |= (mavLinkPayload.payload[mavLinkPayload.read_index + 3] & (long) 0xFF) << 24;
	result |= (mavLinkPayload.payload[mavLinkPayload.read_index + 2] & (long) 0xFF) << 16;
	result |= (mavLinkPayload.payload[mavLinkPayload.read_index + 1] & (long) 0xFF) << 8;
	result |= (mavLinkPayload.payload[mavLinkPayload.read_index + 0] & (long) 0xFF);
	mavLinkPayload.read_index += 8;
	return (long) result;
}

long getLongReverse(MAVLinkPayload mavLinkPayload)
{
	long result = 0;
	result |= (mavLinkPayload.payload[mavLinkPayload.read_index + 0] & (long) 0xFF) << 56;
	result |= (mavLinkPayload.payload[mavLinkPayload.read_index + 1] & (long) 0xFF) << 48;
	result |= (mavLinkPayload.payload[mavLinkPayload.read_index + 2] & (long) 0xFF) << 40;
	result |= (mavLinkPayload.payload[mavLinkPayload.read_index + 3] & (long) 0xFF) << 32;
	result |= (mavLinkPayload.payload[mavLinkPayload.read_index + 4] & (long) 0xFF) << 24;
	result |= (mavLinkPayload.payload[mavLinkPayload.read_index + 5] & (long) 0xFF) << 16;
	result |= (mavLinkPayload.payload[mavLinkPayload.read_index + 6] & (long) 0xFF) << 8;
	result |= (mavLinkPayload.payload[mavLinkPayload.read_index + 7] & (long) 0xFF);
	mavLinkPayload.read_index += 8;
	return (long) result;
}

float getFloat(MAVLinkPayload mavLinkPayload)
{
    int i_data;
	i_data = getInt(mavLinkPayload);
	return intBitsToFloat(i_data);
}

void putByte(char data,MAVLinkPayload mavLinkPayload)
{
	add(data,mavLinkPayload);
}

void putShort(short data,MAVLinkPayload mavLinkPayload)
{
	add((char) (data >> 0),mavLinkPayload);
	add((char) (data >> 8),mavLinkPayload);
}

void putInt(int data,MAVLinkPayload mavLinkPayload)
{
	add((char) (data >> 0),mavLinkPayload);
	add((char) (data >> 8),mavLinkPayload);
	add((char) (data >> 16),mavLinkPayload);
	add((char) (data >> 24),mavLinkPayload);
}

void putLong(long data,MAVLinkPayload mavLinkPayload)
{
	add((char) (data >> 0),mavLinkPayload);
	add((char) (data >> 8),mavLinkPayload);
	add((char) (data >> 16),mavLinkPayload);
	add((char) (data >> 24),mavLinkPayload);
	add((char) (data >> 32),mavLinkPayload);
	add((char) (data >> 40),mavLinkPayload);
	add((char) (data >> 48),mavLinkPayload);
	add((char) (data >> 56),mavLinkPayload);
}

void putFloat(float data,MAVLinkPayload mavLinkPayload)
{
    int i_data;
	i_data = floatToIntBits(data);
	putInt(i_data,mavLinkPayload);
}


