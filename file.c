#include "file.h"
#include <stdio.h>
#define _BSD_SOURCE             /* See feature_test_macros(7) */
#include <endian.h>
#include <assert.h>

size_t get_next_bin_msg(FILE *fptr, uint8_t *buff, size_t buff_len){
	size_t ret = 0; // next message size
	uint16_t len;
	assert(fptr);
	fread(&len, sizeof(len),1, fptr);
	len = be16toh(len);// convert from big endian to whatever we are using
	if ( len <= buff_len ){
		ret = fread(buff, sizeof(uint8_t), len, fptr);
	}
	#ifdef DEBUG
	printf("raw data :\n");
	for(int i=(int)len-1; i >-1; i--){
		printf("byte %d %#x\n",i, ((char*)buff)[i]);
	}
	printf("\n");
	#endif // DEBUG
	return ret; 
}

void write_bin_msg(FILE *fptr, uint8_t *buff, size_t buff_len){
	uint16_t len_be;
	
	assert(fptr);
	assert(buff);
	
	// write len in big endian
	len_be = htobe16( (uint16_t)buff_len ); 
	fwrite(&len_be, sizeof(uint16_t), 1, fptr); 	
	fwrite(buff, sizeof(uint8_t) * buff_len, 1, fptr);	
}
