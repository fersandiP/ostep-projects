#include <stdio.h>

int output_file(char *filename){
	FILE *fp = fopen(filename, "r");
	if (fp == NULL){
		return 1;
	}

	char buffer[100];
	int size = 30;

	while(true){
		char* is_null = fgets(buffer, size, fp);
		if (is_null == NULL){
			break;
		}
		printf("%s", buffer);
	}

	return 0;
}

int main(int argc, char *argv[]){
        for (int i = 1; i < argc; i++){
                int err = output_file(argv[i]);

                if (err > 0) {
                        printf("wcat: cannot open file\n");
			return 1;
                }
        }

        return 0;
}
