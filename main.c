
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

void displayFile(const char *filePath){
    FILE *openedFile;
    int number = 0;
    char c;
    openedFile = fopen(filePath,"r");
    if(openedFile == NULL){
        printf("Unable to open file");
    }else{
        printf("\n");
        printf("File contents: \n");
        while(1){
            c = fgetc(openedFile);
            if(c==EOF){
                break;
            }else{
                number += 1;
                printf("%c",c);
            }
        }
        printf("\n");
        printf("Number of Line: \n "+number);
        fclose(openedFile);
    }

}
void writeLine(const char *filePath){
    FILE *openedFile;
    openedFile = fopen(filePath,"a");
    if(openedFile == NULL){
        printf("Unable to open file");
    }else{
        fprintf(openedFile,"\n");
        fclose(openedFile);
    }
}

void command(){
    char com[50];
    printf("\n");
    printf("Enter command: ");
    fgets(com,sizeof(com),stdin);
    // Replaces the newline with a null terminator
    com[strcspn(com,"\n")] = '\0';
    if(strcmp(com,"Quit")!=0){
        if(strcmp(com,"Append Line")==0){
            char f[] = "D:\\Computer systems cwk\\Project\\file.txt";
            writeLine(f);
            printf("\n");
            printf("Writing successful");
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
    char com[] = "Commands: \n Append Line: \n Adds new line \n Quit: \n Stops program";
    printf("%s",com);
    char f[] = "D:\\Computer systems cwk\\Project\\file.txt";
    displayFile(f);
    command();
    return 0;

}

