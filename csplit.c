// This file will be used in case Linrad is complied on
// a non-INTEL architecture
// Entries should never be called, but just in case...

#include "globdef.h"
#include "uidef.h"
#include "fft1def.h"

void expand_rawdat(void)
{
int i,j,k;
unsigned char m,n;
// Expand 18 bit packed data.
// add 0.5 bits (=bit 19) to correct for the average error
// of 0.5 bits that we introduced by truncating to 187 bits.
// This will remove the spur at frequency=0 that would otherwise
// have been introduced
// Set bits 20 to 31=0, even though correct would be to set them
// to 1 if the sign is negative.
i=timf1p_pa;
j=0;
for(k=0; k<rx_read_bytes; k+=16)
  {
  m=rawsave_tmp[j+8];
  timf1_char[i  ]=0;
  n=m&0xc0;
  n|=0x20;
  timf1_char[i+1]=n;
  m<<=2;
  timf1_char[i+2]=rawsave_tmp[j  ];
  timf1_char[i+3]=rawsave_tmp[j+1];
  n=m&0xc0;
  n|=0x20;
  timf1_char[i+4]=0;
  timf1_char[i+5]=n;
  m<<=2;
  timf1_char[i+6]=rawsave_tmp[j+2];
  timf1_char[i+7]=rawsave_tmp[j+3];
  n=m&0xc0;
  n|=0x20;
  timf1_char[i+8]=0;
  timf1_char[i+9]=n;
  m<<=2;
  timf1_char[i+10]=rawsave_tmp[j+4];
  timf1_char[i+11]=rawsave_tmp[j+5];
  n=m&0xc0;
  n|=0x20;
  timf1_char[i+12]=0;
  timf1_char[i+13]=n;
  timf1_char[i+14]=rawsave_tmp[j+6];
  timf1_char[i+15]=rawsave_tmp[j+7];
  i+=16;
  j+=9;
  }
}


void compress_rawdat_disk(void)
{
int i,j,k;
unsigned char m,n;
i=timf1p_pc_disk;
j=0;
for(k=0; k<rx_read_bytes; k+=16)
  {
  rawsave_tmp_disk[j  ]=timf1_char[i+2];
  rawsave_tmp_disk[j+1]=timf1_char[i+3];
  m=timf1_char[i+1];
  m>>=2;
  rawsave_tmp_disk[j+2]=timf1_char[i+6];
  rawsave_tmp_disk[j+3]=timf1_char[i+7];
  n=timf1_char[i+5];
  n&=0xc0;
  m|=n;
  m>>=2;
  rawsave_tmp_disk[j+4]=timf1_char[i+10];
  rawsave_tmp_disk[j+5]=timf1_char[i+11];
  n=timf1_char[i+9];
  n&=0xc0;
  m|=n;
  m>>=2;
  rawsave_tmp_disk[j+6]=timf1_char[i+14];
  rawsave_tmp_disk[j+7]=timf1_char[i+15];
  n=timf1_char[i+3];
  n&=0xc0;
  m|=n;
  rawsave_tmp_disk[j+8]=m;
  i+=16;
  j+=9;
  }
}
