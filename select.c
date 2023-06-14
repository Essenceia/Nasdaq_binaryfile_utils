#include <stdio.h>
#include "file.h"
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <assert.h>

#define RAND_GAP     40000
#define MAX_MSG_CNT  10000

#define RAND_SEED    10

int main (int argc, char **argv)
{
  	uint32_t n = MAX_MSG_CNT;
  	uint32_t g = RAND_GAP;
  	uint32_t wn = 0;// written to file cnt
  	uint32_t gd = 0;// gap decount until the next 
	char *fpath = NULL;// input file path
	char *opath = NULL;// output file path 
 	int c;
	int err;
	FILE *ifptr;
	FILE *ofptr;
	char   buff[ITCH_MSG_MAX_LEN];
	size_t buff_len;
	


	while ((c = getopt (argc, argv, "n:g:f:o:")) != -1)
	{
		switch (c)
 		{
 		case 'n':
			n = (uint32_t)atoi(optarg);
			break;
 		case 'g':
			g = (uint32_t)atoi(optarg);
			break;
		case 'f':
			fpath = optarg;
 			break;	
 		case 'o':
			opath = optarg;
 			break;
		case '?':
			if (isprint (optopt))fprintf (stderr, "Unknown option `-%c'.\n", optopt);
			else fprintf (stderr,"Unknown option character `\\x%x'.\n",optopt);
				return 1;
		default: abort ();
 		}
	}

	if ( fpath == NULL ){
		fprintf(stderr, "Missing input file path, option -f\n");
		return 1;
	}
	if ( opath == NULL ){
		fprintf(stderr, "Missing output file path, option -o\n");
		return 1;
	}
	// open file
	ifptr = fopen(fpath,"rb");
	ofptr = fopen(opath,"wb");
	if ( ifptr != NULL && ofptr != NULL ){
		//err = read_bin_file(ifptr, n);
		//init rand
		srand(RAND_SEED);
		gd = rand() % g;
		while( wn < n && !feof(ifptr)){
			// read next bin msg
			buff_len = get_next_bin_msg(ifptr, &buff,ITCH_MSG_MAX_LEN);
			assert(buff_len);
			if( gd > 0 ) gd--;
			else{
				// reset gap decount and write to file
				gd = rand()% g;
				wn++;
				write_bin_msg(ofptr, &buff, buff_len);	
			}
		}
		fclose(ifptr);
		fclose(ofptr);
	}else {
		if ( ifptr == NULL ) fprintf(stderr,"Input file open failed\n");
		else fclose(ifptr);
		if ( ofptr == NULL ) fprintf(stderr,"Output file open failed\n");
		else fclose(ofptr);	
		return 1;
	}
	return err;
}

