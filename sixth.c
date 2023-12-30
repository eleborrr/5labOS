#include <stdio.h>
#include <ftw.h>
#include <time.h>
#include <stdlib.h>

long N1;
long N2;
int M1d;
int M1m;
int M1y;
int M2d;
int M2m;
int M2y;


static int callback(const char *fpath, const struct stat *sb, int tFlag){
	struct tm dateIn = {0};
	struct tm date1 = {0};
	struct tm date2 = {0};
	
	struct tm *tm = gmtime(&sb->st_ctime);

	dateIn.tm_year = tm->tm_year + 1900;
	dateIn.tm_mon = tm->tm_mon;
	dateIn.tm_mday = tm->tm_mday;

	date1.tm_year = M1y;
	date1.tm_mon = M1m - 1;
	date1.tm_mday = M1d;
	date2.tm_year = M2y;
	date2.tm_mon = M2m - 1;
	date2.tm_mday = M2d;


	time_t t1 = mktime(&date1);
	time_t t2 = mktime(&date2);
	time_t tInput = mktime(&dateIn);
	
	if(tInput < t1 || tInput > t2)
	{return 0;}


	if (sb->st_size > N1 && sb->st_size < N2)
	{
		printf("File: %s, Size: %ld\n, Created: %s", fpath, sb->st_size, ctime(&sb-> st_ctime));			
	}

	return 0;
}

int main(int argc, char *argv[]){
	N1 = atol(argv[2]);
	N2 = atol(argv[3]);
	M1d = atoi(argv[4]);
	M1m = atoi(argv[5]);
	M1y = atoi(argv[6]);
	M2d = atoi(argv[7]);
	M2m = atoi(argv[8]);
	M2y = atoi(argv[9]);
	
	if(ftw(argv[1], callback, 10) != 0){
		printf("ftw error");
		return -1;
	}
	return 0;
}

