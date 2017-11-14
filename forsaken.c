#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lfu.c"
#include "optimal.c"
#include "lru1.c"
#include "lru8.c"
#include "mfu.c"

#define BUF_SIZE 1024

void usage();
void algo();
void print_results(long long time_of_replacement, int miss);

int str[BUF_SIZE];
int j=0;
int frames = 5;
char *filename;
char *algo_name= "LRU8";
int algo_flag=1;
long long ago=1;//in a galaxy far far away :D
long long time=2;

int main(int argc, char *argv[]) {

	int i;
	for (i=0; i<argc; i++) {
		if(strcmp(argv[i],"-t")==0) {
			ago=atol(argv[i+1]);
			time=atol(argv[i+2]);
		}
		if(strcmp(argv[i],"-f")==0) {
			frames= atoi(argv[i+1]);
		}
		if(strcmp(argv[i],"-r")==0) {
			if(strcmp(argv[i+1],"LFU")==0) {
				algo_name= "LFU";
				algo_flag=2;
			}
			else if(strcmp(argv[i+1],"LRU1")==0) {
				algo_name= "LRU1";
				algo_flag=3;
			}
			else if(strcmp(argv[i+1],"MFU")==0) {
				algo_name= "MFU";
				algo_flag=4;
			}
			else if(strcmp(argv[i+1],"LRU8")==0) {
				algo_name= "LRU8";
				algo_flag=1;
			}
			else if(strcmp(argv[i+1],"OPTIMAL")==0) {
				algo_name= "OPTIMAL";
				algo_flag=5;
			}
			else {
				algo_flag=1;
				algo_name= "LRU8";
			}
		}
		if(strcmp(argv[i],"-i")==0) {
			filename= argv[i+1];
		}
	}
	FILE *fp;
	fp= fopen(filename, "r");
	char s[BUF_SIZE];
	int c,flag;
	int k=0;
	if (fp == NULL) {
		printf("Enter the input string: \n");
		gets(s);
		k=strlen(s);
		k= k+1;
		printf("%d",k);
	}
	else {
		if (fp) {
			while ((s[k] = fgetc(fp)) != EOF) {
						k++;
			}
		}
		s[k]='\0';
		fclose(fp);
	}
	int x=k;
	for(c=0;c<=x;c++) {
		k=0;
		flag=0;
		while(!isspace(s[c])) {
			//printf("c- %d", c);
			k= k*10 + s[c]-'0';
			c++;
			flag=1;
		}
		if(flag==1)
			str[j++]=k;
	}
	j=j-1;
	printf("\n Captured Int array \n");
	int p;
	for(p=0;p<j;p++) {
		printf("%d ",str[p]);
	}
	printf("\n accepted: %d , %d", frames,j);
	algo(algo_flag);
	return 0;
}

void algo(int alg_flag) {
	int algo_flag=alg_flag;
	int miss;
	if (algo_flag == 1) {
		miss= lru8(str,frames,j);
	}else if(algo_flag == 2) {
		miss= lfu(str,frames,j);
	}else if(algo_flag == 3) {
		miss= lru1(str,frames,j);
	} else if(algo_flag == 4) {
		miss= mfu(str,frames,j);
	} else {
		miss= optimal(str,frames,j);
	}
	print_results(time+ago, miss);
}

void print_results(long long time_of_replacement, int miss) {

	printf("\n # of Page Replacements with %s algorithm       :  %d", algo_name, miss);
	printf("\n");
	printf("\n Total time to run %s algorithm      : %ld units", algo_name,time_of_replacement*miss);
	printf("\n");
}

void usage() {
	printf("\n**************************************************************************\n**************************************************************************");
	printf("\n forsaken [-h][-t time1 time2] [-f available-frames] [-r replacement_policy] [-i input_file]");
	printf("\n Give -t then value to find out page fault then value to update it");
	printf("\n Give -f then value to change by default frames value");
	printf("\n Give -r then relacement-policy to change by default value for example -r LRU8");
	printf("\n Give -i and then filename of input file for example: /home/workspace/virtualmem/src/input.txt");
	printf("\n Press Ctrl+c anytime to exit the calculations");
	printf("\n **************************************************************************\n**************************************************************************\n");
	exit(1);
}
