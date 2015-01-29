#include <stdio.h>
#include <stdlib.h>

int main (int argc, char **argv ) {
	int delay = 3;
	int volume_scale = 2;

	FILE *fp_input, *fp_output;

	fp_input = fopen(argv[1], "rb");
	fp_output = fopen(argv[2], "wb");

	// Write header to output, short by short
	short s;
	int i;
	short size;
	for(i = 0; i < 22; i++){
		fread(&s, sizeof(short), 1, fp_input);
		
		if(i == 2 || i == 20){
			size = s + delay * 2;
			fwrite(&size, sizeof(short), 1, fp_output);
		} else {
			fwrite(&s, sizeof(short), 1, fp_output);
		}
		//fwrite(&s, sizeof(short), 1, fp_output);
	}
	
	// Add delay 0 samples to output
	/*short zero = 0;
	for(i = 0; i < delay; i++) {
		fwrite(&zero, sizeof(short), 1, fp_output);
	}

	short *echoSamples = malloc(delay * sizeof(short));
	short new;
	int j = 1;

	i = 0;
	while(j == 1) {
		if(i == delay) {
			i = 0;
		}
		j = fread(&echoSamples[i], sizeof(short), 1, fp_input);
		new = echoSamples[i] / volume_scale;
		fwrite(&new, sizeof(short), 1, fp_output);
		i++;
	}*/

	/*short zero = 0;
	for(i = 0; i < delay; i++){
		fwrite(&zero, sizeof(short), 1, fp_output);
	}*/

	short *echo = malloc(delay * sizeof(short));
	for(i = 0; i < delay; i++){
		fread(&echo[i], sizeof(short), 1, fp_input);
		fwrite(&echo[i], sizeof(short), 1, fp_output);
	}

	short mix, curr;
	fread(&curr, sizeof(short), 1, fp_input);
	printf("%d\n",curr);
	mix = echo[0] / volume_scale + curr;
	printf("%d\n",mix);
	fwrite(&mix, sizeof(short), 1, fp_output);
	
	/*short mix, curr;
	int j = 1;
	i = 0;
	while(j == 1){
		if(i == delay){
			i = 0;
		}
		j = fread(&curr, sizeof(short), 1, fp_input);

		mix = echo[i] * mult + curr;
		fwrite(&mix, sizeof(short), 1, fp_output);
		i++;
	}

	while(i != delay){
		fwrite(&echo[i], sizeof(short), 1, fp_output);
	}*/

	return 0;
}