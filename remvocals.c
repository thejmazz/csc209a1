#include <stdio.h>

int main (int argc, char **argv ) {

	// Check for proper number of command line arguments
	if (argc != 3){
		fprintf(stderr, "Usage: %s <sourcewav> <destwav> \n", argv[0]);
		return 1;
	}

	// Pointer to input and output files
	FILE *fp_love, *fp_output;

	// Open the input audio file in 'read binary' mode
	fp_love = fopen(argv[1], "rb");
	
	// Exit if invalid file path
	if(fp_love == NULL) {
		perror(argv[1]);
		return 1;
	}

	// Open the output file in 'write binary' mode
	fp_output = fopen(argv[2], "wb");

	// Write header to output, short by short
	short s;
	int i;
	for(i = 0; i < 22; i++){
		fread(&s, sizeof(short), 1, fp_love);
		fwrite(&s, sizeof(short), 1, fp_output);
	}

	// Remove vocals and write to file
	int j = 1;
	short left, right, combined;
	while (j == 1){
		// Read in a pair of shorts
		fread(&left, sizeof(short), 1, fp_love);
		j = fread(&right, sizeof(short), 1, fp_love);
		
		// Compute sample with no vocals
		combined = (left - right) / 2;

		// Write pair of shorts
		fwrite(&combined, sizeof(short), 1, fp_output);
		fwrite(&combined, sizeof(short), 1, fp_output);
	}

	return 0;
}