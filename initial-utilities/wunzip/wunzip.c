#include <stdio.h>

int uncompress_file(int numOfFiles, char *filenames[]){

    int count[1];
    int character;
    size_t ret;

	for (int i = 1; i < numOfFiles; i++){
		FILE* f = fopen(filenames[i], "r");
		if (f == NULL) {
			return 1;
		}

        while (1){
            ret = fread(count, sizeof(count), 1, f);
            if (ret == 0){
                // EOF
                break;
            }

            character = fgetc(f);
            for (int num = 0; num < count[0]; num++){
                putchar(character);
            }
        }
		fclose(f);
	}

	return 0;
}

int main(int argc, char *argv[]){
	if (argc < 2) {
		printf("wunzip: file1 [file2 ...]\n");
		return 1;
	}

	uncompress_file(argc, argv);

	return 0;
}
