#include <stdio.h>

int main (int argc, char **argv ) {

	// Print number of command line arguments
	printf("%d command line arguments. They are: \n", argc);
	// Print value of command line arguments
	int i;
	for(i = 0; i < argc; i++) {
		printf("%d: %s\n",i,argv[i]);
	}

	// Check for proper number of command line arguments
	if (argc != 3){
		printf("Incorrect progam call, exiting...bye...\n");
		return 1;
	}

	return 0;
}