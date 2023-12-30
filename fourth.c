#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[]){
	FILE *srcP, *destP;
	int c, srcMode, destMode;
	struct stat srcStat;

	if(argc != 3) {
		printf("lack of args");
		return -1;
	}

	srcP = fopen(argv[1], "r");
	if(srcP == NULL){
		printf("File opening error");
		return -1;
	}

	destP = fopen(argv[2], "w");
	if (destP == NULL){
		printf("Second file opening error");
		return -1;
	}

	while((c = getc(srcP)) != EOF){
		if(putc(c, destP) == EOF){
			printf("Error writing to dest file");
			return -1;
		}
	}

	if (fclose(srcP) == EOF || fclose(destP) == EOF){
		printf("Error closing files");
		return -1;
	}

	if (stat(argv[1], &srcStat) == -1){
		printf("Error gettins src file status");
		return -1;
	}


	srcMode = srcStat.st_mode;
	if (chmod(argv[2], srcMode) == -1){
		printf("Error setting permissions");
		return -1;
	}


	return 0;

}
