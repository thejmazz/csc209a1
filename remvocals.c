#include <stdio.h>

int main (int argc, char **argv ) {

	// Print number of command line arguments
	printf("%d command line argument(s). They are: \n", argc);
	// Print value of command line arguments
	int i;
	for(i = 0; i < argc; i++) {
		printf("%d: %s\n",i,argv[i]);
	}

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

	short n;
	fread(&n, sizeof(short), 1, fp_love);
	//printf("my first short: %d\n", *n);

	// Pointer to output file
	FILE *fp_output;

	// Open the output file in 'write binary' mode
	fp_output = fopen(argv[2], "wb");

	// Write to output file
	fwrite(&n, sizeof(n), 1, fp_output);

	return 0;
}