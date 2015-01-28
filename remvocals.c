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

	// Declare pointers to shorts
	short *s1, *s2;

	// Write header to output, short by short
	int i;
	for(i = 0; i < 22; i++){
		fread(&s1, sizeof(short), 1, fp_love);
		fwrite(&s1, sizeof(short), 1, fp_output);
	}

	//short new;
	for(i = 0; i < 2; i++) {
		fread(&s1, sizeof(short), 1, fp_love);
		fread(&s2, sizeof(short), 1, fp_love);
	}

	int j = 1;
	while (j == 1){
		// Read in a pair of shorts
		j = fread(&s1, sizeof(short), 1, fp_love);
		j = fread(&s2, sizeof(short), 1, fp_love);
		
		// Write pair of shorts
		fwrite(&s1, sizeof(short), 1, fp_output);
		fwrite(&s2, sizeof(short), 1, fp_output);
	}

	return 0;
}