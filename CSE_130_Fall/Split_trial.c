//CSE 130: program for the split character upon reading a file

/*
Files needed: 
1. split.c
2. Makefile
3. README.md
*/
//cannot use fopen function
//has to be in c
//look at manpage for open and read of a file descriptor

/*
Let the program read the file first:
1. So that means take the user argument in the form of ./split [txtfile] [character to split]
2. Make use of the "-" to split the filename as input from the character
3. Split should work for any number of files into input
4. 
*/


/*
Thought Process:
1. If user enters no file txt then return null or error message, "No file to read from"
2. 
*/

//LIBRARY
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>


int buf=2048;

//create a character based function that takes in the filename and dissects it.
void *split(char *filename){
    int buffer[buf];
    int file=open(filename, ,);
    if(file==NULL){
        eterr(1,"\nusage", argv[0]);
    }
    int r=read(file, buf, 2048);

}

int main(int argc, char **argv){

    if(argc <3){
        warn();
    }

    FILE *pToFile=fopen("text_p.txt", 'r');
    int line =0;
    char input[512];
    while(fgets(input, 512, pToFile)){
        line++;
        printf("Line: %d -> %s", line, input);
    }
    printf("\n\n End of Program");
    fclose(pToFile);
    return 0;
}


/*char *split_char(char *filename){
    //read the file using open() syscall
    //declare a int type.
    int file=open(filename, O_RDONLY);
    //cant read from the file we havent opened
    if(file==NULL) return NULL;
    //trying to understand how many characters are in the file
    //this will tell us how much space to allocate on the heap for character array
    //fseek() moves the file pointer to the end of file with an offset of 0
    fseek(file, 0, SEEK_END);
    //ftell() returns the current value of position indicator
    int length= ftell(file);
    //move the file pointer back to the beginning of the file
    fseek(file, 0, SEEK_SET);
    //dynamically allocate space for char array taht stores the string
    char *string=malloc(sizeof(char)* (length+1));



}
*/