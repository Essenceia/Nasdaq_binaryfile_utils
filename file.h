#ifndef FILE_H
#define FILE_H
#include <stdint.h>
#include <stdio.h>

#define ITCH_MSG_MAX_LEN 50 

void write_bin_msg(FILE *fptr, uint8_t *buff, size_t buff_len);


// Read the next binary message in the file into a buffer.
size_t get_next_bin_msg(FILE *fptr, uint8_t *buff, size_t buff_len);
#endif // FILE_H
