#include <stdio.h>

int writeCharacter(int count, int character){
	size_t out = fwrite(&count, sizeof(count), 1, stdout);
	if (out == 0){
		printf("Error happened\n");
	}
	putchar(character);
	return 0;
}

int compress_file(int numOfFiles, char *filenames[]){
	int tracker = -1;
	int current = -1;

	// 4 byte guaranteed
    int count = 1;

	for (int i = 1; i < numOfFiles; i++){
		FILE* f = fopen(filenames[i], "r");
		if (f == NULL) {
			return 1;
		}

		// Loop until EOF
		while((current = fgetc(f)) != EOF){
			if (tracker == -1) {
				tracker = current;
			} else if (tracker == current) {
				count++;
			} else {
				// Output to stdout 5 byte
				writeCharacter(count, tracker);
						
				// Reset the state
				tracker = current;
				count = 1;
			}
		}
		fclose(f);
	}

	writeCharacter(count, tracker);
	return 0;
}

int main(int argc, char *argv[]){
	if (argc < 2) {
		printf("wzip: file1 [file2 ...]\n");
		return 1;
	}

	compress_file(argc, argv);

	return 0;
}
