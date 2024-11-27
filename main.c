#include<stdio.h>
#include<string.h>
#include <stdlib.h>

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

    FILE *openedFile;
    char c='0';
    openedFile = fopen(filePath,"r");
    if(openedFile == NULL){
        printf("\n");
        printf("Unable to open file");
    }else{
        int totalcharacters = NumberOfCharactersTillSpecificLine(filePath,numberOfLines(filePath));
        char buffer[totalcharacters+1];
        int index = 0;
        int count = 1;
        printf("\n");
        while(c!=EOF){
            c = fgetc(openedFile);
            if(count!=Line){
                buffer[index] = c;
            }
            if(c=='\n'){
                count++;
            }
            index++;
        }
        buffer[index]='\0';
        printf("Buffer: \n");
        for(int i=0;i<index+1;i++){
            printf("%c",buffer[i]);
        }
        fclose(openedFile);
        openedFile = fopen(filePath,"w");
        fprintf(openedFile,buffer);
        fclose(openedFile);
    }
} 
void showLine(const char *filePath,int Line){
    FILE *openedFile = fopen(filePath,"r");
    fseek(openedFile,NumberOfCharactersTillSpecificLine(filePath,Line),SEEK_SET);
    char c = fgetc(openedFile);
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
char **AddToLog(char **strings,int original_size,const char *addedLog){
    (original_size)++;
    strings  = realloc(strings,(original_size)*sizeof(char*));
    strings[(original_size)-1] = (char*)malloc((strlen(addedLog)+1)*sizeof(char));
    if (strings[original_size - 1] == NULL) {
        fprintf(stderr, "Memory allocation failed for log entry\n");
        exit(EXIT_FAILURE);
    }
    strcpy(strings[(original_size) - 1], addedLog);
    return strings;
}
void showChangeLog(char **strings,int size){
    printf("Change log: \n");
    for(int i=0;i<size;i++){
        printf("%s\n", strings[i]);
    }
}
void command(const char *value,char **log,int size){
    char com[50];
    int con;
    printf("Enter command: ");
    fgets(com,sizeof(com),stdin);
    // Replaces the newline with a null terminator
    com[strcspn(com,"\n")] = '\0';
    if(strcmp(com,"Quit")!=0){
        if(strcmp(com,"Append Line")==0){
            writeLine(value);
            printf("\n");
            printf("Writing successful");
            printf("\n");
            log = AddToLog(log,size,"Appended Line \n");
            size++;
        }else if(strcmp(com,"Lines")==0){
            printf("Current number of lines: %d",numberOfLines(value));
            printf("\n");
            log = AddToLog(log,size,"Showed number of lines \n");
            size++;
        }else if(strcmp(com,"Show")==0){
            displayFile(value);
            log = AddToLog(log,size,"Showed file \n");
            size++;
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
            printf("\n");
            fflush(stdin);
            log = AddToLog(log,size,"Deleted line \n ");
            size++;
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
            log = AddToLog(log,size,"Showed line \n");
            size++;
        }else if(strcmp(com,"Show Change Log")==0){
            log = AddToLog(log,size,"Showed change log \n ");
            size++;
            showChangeLog(log,size);
        }else{
            printf("\n");
            printf("Invalid command \n");
        }

        command(value,log,size);

    }else{
        printf("Program quit");
    }
}

int main(){
    printf("Hi");
    char **strings = NULL;
    int size = 0;
    strings = (char**)malloc(size * sizeof(char*));
    AddToLog(strings,size,"Original unchanged file");
    showChangeLog(strings,size);
    char com[] = "Commands:  \nShow Change Log \n Shows change log \n Show Line: \n Show content on specified line \n Append Line: \n Adds new line \n Quit: \n Stops program \n Show: \n Shows file contents \n Delete Line \n Deletes a line that you will get to specify after this command \n Lines: \n Number of lines in file \n";
    printf("%s",com);
    char f[] = "D:/Computer systems cwk/Project/file.txt";
    command(f,strings,size);
    return 0;

}

