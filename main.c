#include<stdio.h>
#include<string.h>

int numberOfLines(const char *filePath){
    FILE *openedFile;
    int number = 0;
    char c;
    int numberOfCharacters = 0;
    openedFile = fopen(filePath,"r");
    if(openedFile == NULL){
        printf("\n");
        printf("Unable to open file");
        return -1;
    }else{
        printf("\n");
        while(c!=EOF){
            c = fgetc(openedFile);
            numberOfCharacters+=1;
            if(c=='\n'){
                number += 1;
            }
        }
        if(numberOfCharacters>0){
            number += 1;
        }
        return number;

    }
}

int NumberOfCharactersTillSpecificLine(const char *filePath,int Line){
    FILE *openedFile;
    char c = '0';
    openedFile = fopen(filePath,"r");
    if(openedFile == NULL){
        printf("\n");
        printf("Unable to open file");
        return -1;
    }else{
        int numberOfCharacters = 0;
        int currentLine = 1;
        printf("\n");
        while(c!=EOF){
            if(currentLine == Line){
                fclose(openedFile);
                return numberOfCharacters;
            }else{
                c = fgetc(openedFile);
                numberOfCharacters++;
                if(c=='\n'){
                    currentLine ++;
                    numberOfCharacters++;
                }
            }
        }
        fclose(openedFile);
        return -1;


    }
}
typedef struct {
    int start;
    int end;
} CharacterRange;
CharacterRange characterRange(const char *filePath,int Line){
    CharacterRange range = {0,0};
    int startCharacterNumber = NumberOfCharactersTillSpecificLine(filePath,Line);
    int endCharacterNumber = startCharacterNumber;
    FILE *openedFile = fopen(filePath,"r");
    char current = '\0';
    fseek(openedFile, startCharacterNumber, SEEK_SET);
    while(current != EOF){
        current = fgetc(openedFile);
        if(current!='\n'){
            endCharacterNumber++;
        }else{
            break;
        }
    }
    range.start = startCharacterNumber;
    range.end = endCharacterNumber;
    return range;

}
void deleteLine(const char *filePath, int Line) {
    CharacterRange range = characterRange(filePath,Line);
    printf("%d",range.start);
    printf("%d",range.end);
    /*
    FILE *openedFile;
    //char *buffer[]="";
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
            buffer += c;
        }
        printf(buffer);
        fclose(openedFile);
    }
    */
}   

void showLine(const char *filePath,int Line){
    FILE *openedFile = fopen(filePath,"r");
    fseek(openedFile,NumberOfCharactersTillSpecificLine(filePath,Line),SEEK_SET);
    char c = fgetc(openedFile);
    if(c==EOF){
        printf("Line %d is an empty line so there's nothing to show",Line);
    }
    fseek(openedFile,NumberOfCharactersTillSpecificLine(filePath,Line),SEEK_SET);
    while (c != EOF && c != '\n') {
        c = fgetc(openedFile);
        printf("%c",c);
    }
    printf("\n");
    fclose(openedFile);
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

void command(const char *value){
    char com[50];
    int con;
    //char f[] = "D:\\Computer systems cwk\\Project\\file.txt";
    printf("Enter command: ");
    fgets(com,sizeof(com),stdin);
    // Replaces the newline with a null terminator
    com[strcspn(com,"\n")] = '\0';
    if(strcmp(com,"Quit")!=0){
        if(strcmp(com,"Append Line")==0){
            writeLine(value);
            printf("\n");
            printf("Writing successful");
        }else if(strcmp(com,"Lines")==0){
            printf("%d",numberOfLines(value));
        }else if(strcmp(com,"Show")==0){
            displayFile(value);
        }else if(strcmp(com,"Delete Line")==0){
            int line = 0;
            con = 0;
            do{
                printf("Enter the line you want to delete: \n");
                scanf("%d",&line);
                if(line>numberOfLines(value) || line<1){
                    con = 1;
                    printf("Line number out of range \n"); 
                }

            }while(con==1);
            deleteLine(value,line);
            fflush(stdin);
        }else if(strcmp(com,"Show Line")==0){
            int line = 0;
            con = 0;
            do{
                printf("Enter the line you want to see: \n");
                scanf("%d",&line);
                if(line>numberOfLines(value) || line<1){
                    con = 1;
                    printf("Line number out of range \n");
                }

            }while(con==1);
            showLine(value,line);
            fflush(stdin);
        }else{
            printf("\n");
            printf("Invalid command \n");
        }
        command(value);
    }else{
        printf("Program quit");
    }
}
int main(){
    char com[] = "Commands:  \n Show Line: \n Show content on specified line \n Append Line: \n Adds new line \n Quit: \n Stops program \n Show: \n Shows file contents \n Delete Line \n Deletes a line that you will get to specify after this command \n Lines: \n Number of lines in file \n";
    printf("%s",com);
    char f[] = "D:/Computer systems cwk/Project/file.txt";
    command(f);
    return 0;

}

