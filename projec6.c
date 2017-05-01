#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

int fork (void);
int pipe (int pd[2]);

int  main (int argc, char *argv[] ) {
	int lines = 0;
	int words = 0;
	int chars = 0;
	int blanks = 0;
	int lineSum = 0;
	int wordSum = 0;
	int charSum = 0;
	int options = 0;
	char c;
	int printLine = 0;
	int printChar = 0;
	int printWord = 0;
	int argNum = 0;
	int wordSwitch = 0;
	int pd[2];
	FILE *file;
	int i;

	

	if( (pipe(pd) == -1) ) {
		fprintf(stderr, "pipe failure\n");
		exit(1);
	}

	for( int z = 1; z < argc; z++ ) {

  		

		if( strcmp(argv[z], "-l") == 0 ) 
			printLine = 1;
		
			

		else if( strcmp(argv[z], "-m") == 0 )
			printChar = 1;
		else if( strcmp(argv[z], "-w") == 0 )
			printWord = 1;
		else
			break;
	}
	for(  i = options + 1; i < argc; i++ ) {
		file = fopen(argv[i], "r");
         
		if ( file == 0 ) {
			printf("Unable to open file\n",stderr);
			break;
		}
		else {
			argNum = i;
			

			if ( fork() == 0 ) {
				lines = 0;
				chars = 0;
				words = 0;

				close(pd[0]);

			
			while( (c = fgetc(file)) != EOF  ){
					chars++;
					
				if ( isalpha(c) || isdigit(c) || ispunct(c))
					wordSwitch = 1;
				if ( isspace(c) && wordSwitch ) {
					words++;
					wordSwitch = 0;
				}
				if ( c == '\n')
					lines++;
			}
			fclose(file);
			if( printLine == 1 && printChar == 1 && printWord == 1 )
				printf("%5d %5d %5d %s\n", words, lines,chars,argv[i]);
			else if( printLine == 1 && printChar == 0 && printWord == 1 )
				printf("%5d %5d %s\n", lines, words,argv[i]);
			else if( printLine == 1  && printChar == 0 && printWord == 0 )
				printf("%5d %s\n", lines,argv[i]);
			else if( printLine == 0 && printChar == 1 && printWord == 0 )
				printf("%5d %s\n", chars,argv[i]);
			else if( printLine == 0 && printChar == 0 && printWord == 1 )
				printf("%5d %s\n", words,argv[i]);
			else if( printLine == 1 && printChar == 0 && printWord == 1 )
				printf("%5d %5d %s\n ", lines, words,argv[i]);
			else if( printLine == 0 && printChar == 1 && printWord == 1 )
				printf("%5d %5d %s\n", words, chars,argv[i]);
			else if( printLine == 1 && printChar == 1 && printWord == 0)
               
              printf("The output is");
			  printf("Lines:%d Words:%d Chars:%d %s PID %d",lines,words,chars,argv[i],getpid());
			
			

			 

                         printf("\n");
			if( (write(pd[1], &lines, sizeof(int)) == -1) ||
				(write(pd[1], &words, sizeof(int)) == -1) ||
					(write(pd[1], &chars, sizeof(int)) == -1) )
						printf("write to pipe failed\n");
			return 1;
			}
		}
	}

	for( int x = options + 1; x < argc; x++ ) {
			close(pd[1]);
			if( (read(pd[0], &lines, sizeof(int)) == -1) ||
				(read(pd[0], &words, sizeof(int)) == -1) ||
					(read(pd[0], &chars, sizeof(int)) == -1) ) 
						printf("reading from pipe failed\n");
			else {
				lineSum += lines;
				wordSum += words;
				charSum += chars;
				


			}
			
	}


	 if( printLine == 1 && printChar == 1 && printWord == 1 )
    	printf("hi");

        else if( printLine == 1 && printChar == 0 && printWord == 1 )
                  printf("%5d %5d", lineSum, wordSum);
        else if( printLine == 1  && printChar == 0 && printWord == 0)
                  printf("%5d", lineSum);
       	else if( printLine == 0 && printChar == 1 && printWord == 0 )
                  printf("%5d", charSum);
        else if( printLine == 0 && printChar == 0 && printWord == 1 )
                  printf("%5d", wordSum);
       	else if( printLine == 1 && printChar == 0 && printWord == 1 )
                  printf("%5d %5d", lineSum, wordSum);
       	else if( printLine == 0 && printChar == 1 && printWord == 1 )
                  printf("%5d %5d", wordSum, charSum);
	else if( printLine == 1 && printChar == 1 && printWord == 0 )
		 
	   printf(" child id: %d\n", getpid());
	//getting the total sum of the words in the file

printf("%7d%8d%9d total",lineSum,wordSum,charSum);
}
