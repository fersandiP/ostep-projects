#include <stdio.h>
#include <string.h>

bool is_match(char *term, char *line, ssize_t length){
	int term_length = strlen(term);
	if (term_length == 1 && term[0] == ' '){
		return false;
	}

//	printf("Checking this line: %s", line);
	for (int i = 0; i < length; i++){
		if (term[0] == line[i]){
			//Enter substring search
			int tracking = i+1;
			bool match = true;
//			printf("MATCHED in position %d\n", i);
			for (int j = 1; j < term_length; j++){
				if (tracking >= length || 
					term[j] != line[tracking]){
					match = false;
					break;
				}
				tracking++;
			}

			if (match){
				return match;
			}
		}
	}

	return false;
}

int process_file(char *term, char *filename) {
	FILE *fp;

	if (filename == NULL){
		fp = stdin;
	} else {
		fp = fopen(filename, "r");
	}

	if (fp == NULL){
		printf("wgrep: cannot open file\n");
		return 1;
	}

	char *line_buffer;
	ssize_t size;
	size_t n = 0;
	while(true){
		size = getline(&line_buffer, &n, fp);
		if (size == -1){
			break;
		}

		bool match = is_match(term, line_buffer, size);
		if (match){
			printf("%s", line_buffer);
		}
	}
	return 0;
}

int main(int argc, char *argv[]){
	if (argc < 2){
		printf("wgrep: searchterm [file ...]\n");
		return 1;	
	}

	char *term = argv[1];

	// Reading from stdin
	if (argc == 2){
		process_file(term, NULL);	
	}

	for (int i = 2; i < argc; i++){
		int err = process_file(term, argv[i]);
		if (err > 0){
			return err;
		}
	}

	return 0;
}
