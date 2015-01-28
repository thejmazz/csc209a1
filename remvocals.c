#include <stdio.h>

int main (int argc, char **argv ) {

	// Check for proper number of command line arguments
	if (argc != 3){
		fprintf(stderr, "Usage: %s <sourcewav> <destwav> \n", argv[0]);
		return 1;
	}

	// Pointer to input file
	FILE *fp_love;

	// Open the input audio file in 'read binary' mode
	fp_love = fopen(argv[1], "rb");
	
	// Exit if invalid file path
	if(fp_love == NULL) {
		perror(argv[1]);
		return 1;
	}

	// Pointer to output file
	FILE *fp_output;

	// Open the output file in 'write binary' mode
	fp_output = fopen(argv[2], "wb");


	short *n;
	int i;
	for(i = 0; i < 22; i++){
		fread(&n, sizeof(short), 1, fp_love);
		fwrite(&n, sizeof(short), 1, fp_output);
	}

	return 0;
}