#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main (int argc, char **argv ) {
	int delay = 8000;
	int volume_scale = 4;
	int file_num = 1;

	int option = 0;
	while ((option = getopt(argc, argv,"d:v:")) != -1) {
		switch (option) {
			 case 'd' : {
				delay = (int)atoi(optarg);
				file_num = file_num + 2;
				break;
			 }
			 case 'v' : {
				volume_scale = (int)atoi(optarg);
				file_num = file_num + 2;
				break;	
			 }
			 default: break;
		}
	}

	if ( (file_num == 1 && argc != 3) ||
		 (file_num == 3 && argc != 5) ||
		 (file_num == 5 && argc != 7) ) {
		fprintf(stderr, "Usage: %s [-d delay] [-v volume_scale] sourcewav destwav  \n", argv[0]);
		return 1;
	}

	FILE *fp_input, *fp_output;

	fp_input = fopen(argv[file_num], "rb");
	fp_output = fopen(argv[file_num+1], "wb");

	#define HEADER_SIZE 22
	int i;
	int j;
	short header[HEADER_SIZE];
	for(i = 0; i < HEADER_SIZE; i++) {
		j = fread(&header[i], sizeof(short), 1, fp_input);
		if(j != 1){
			printf("premptively reache end of file, exiting\n");
			return 1;
		}
	}

	int size;
	unsigned int * sizepointer;
	for(i = 0; i < HEADER_SIZE; i++){
		if(i == 2 || i == 20){
			sizepointer = (unsigned int *)(header + i);
			size = *sizepointer + delay * 2;
			fwrite(&size, sizeof(int), 1, fp_output);
			i++;
		} else {
			fwrite(&header[i], sizeof(short), 1, fp_output);
		}
	}

	short *echo = malloc(delay * sizeof(short));
	if (echo == NULL) {
		fprintf(stderr, "failed to allocate memory.\n");
		return 1;
	}
	
	for(i = 0; i < delay; i++){
		j = fread(&echo[i], sizeof(short), 1, fp_input);
		if(j != 1){
			printf("premptively reache end of file, exiting\n");
			return 1;
		}
		fwrite(&echo[i], sizeof(short), 1, fp_output);
	}

	short mix, curr;
	i = 0;
	j = 1;
	while(j == 1){
		if(i == delay){
			i = 0;
		}

		j = fread(&curr, sizeof(short), 1, fp_input);
		mix = echo[i] / volume_scale + curr;
		echo[i] = curr;

		if(j == 1){
			fwrite(&mix, sizeof(short), 1, fp_output);
			i++;
		}
	}

	for(i = 0; i < delay; i++){
		echo[i] = echo[i] / volume_scale;
		fwrite(&echo[i], sizeof(short), 1, fp_output);
	}

	return 0;
}