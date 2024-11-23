
/*
FILE *fopen(const char *filename,
const char *mode);
r Read
File exists
Beginning of file
r+ Read and write
File exists
Beginning of file
w Write
If file exists, it is truncated to NULL, otherwise new created.
Beginning of file
w+ Write and read
If file exists, it is truncated to NULL, otherwise new created.
Beginning of file
a Append (write at end)
File exists
End of file
a+ Read and append
File exists
End of file
*/

#include<stdio.h>
#include<string.h>

void numberOfLines(const char *filePath){
    FILE *openedFile;
    int number = 0;
    char c;
    openedFile = fopen(filePath,"r");
    if(openedFile == NULL){
        printf("\n");
        printf("Unable to open file");
    }else{
        printf("\n");
        while(c!=EOF){
            c = fgetc(openedFile);
            if(c=='\n'){
                number += 1;
            }
        }
        printf("Lines: %d ",number+1);
    }
}
void displayFile(const char *filePath){
    FILE *openedFile;
    char c;
    openedFile = fopen(filePath,"r");
    if(openedFile == NULL){
        printf("\n");
        printf("Unable to open file");
    }else{
        printf("\n");
        printf("File contents: \n");
        while(c!=EOF){
            c = fgetc(openedFile);
            printf("%c",c);
        }
        printf("\n");
        fclose(openedFile);
    }

}
void writeLine(const char *filePath){
    FILE *openedFile;
    openedFile = fopen(filePath,"a");
    if(openedFile == NULL){
        printf("\n");
        printf("Unable to open file");
    }else{
        fprintf(openedFile,"\n");
        fclose(openedFile);
    }
}

void command(){
    char com[50];
    char f[] = "D:\\Computer systems cwk\\Project\\file.txt";
    printf("\n");
    printf("Enter command: ");
    fgets(com,sizeof(com),stdin);
    // Replaces the newline with a null terminator
    com[strcspn(com,"\n")] = '\0';
    if(strcmp(com,"Quit")!=0){
        if(strcmp(com,"Append Line")==0){
            writeLine(f);
            printf("\n");
            printf("Writing successful");
            displayFile(f);
        }else if(strcmp(com,"Lines")==0){
            numberOfLines(f);
        }else if(strcmp(com,"Show")==0){
            displayFile(f);
        }else{
            printf("\n");
            printf("Invalid command \n");
        }
        command();
    }else{
        printf("Program quit");
    }
}
int main(){
    char com[] = "Commands: \n Append Line: \n Adds new line \n Quit: \n Stops program \n Show: \n Shows file contents \n Lines: \n Number of lines in file \n";
    printf("%s",com);
    char f[] = "D:\\Computer systems cwk\\Project\\file.txt";
    command();
    return 0;

}

