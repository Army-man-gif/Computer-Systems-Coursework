#include<stdio.h>
#include<string.h>
#include <stdlib.h>
char f[100] = "D:/Computer systems cwk/Project/file.txt";
int numberOfLines(){
    FILE *openedFile;
    int number = 0;
    char c;
    int numberOfCharacters = 0;
    openedFile = fopen(f,"r");
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
void move(char *originalPath,char *newPath){
    rename(originalPath,newPath);
    strcpy(originalPath,newPath);
}
int NumberOfCharactersTillSpecificLine(int Line){
    FILE *openedFile;
    char c = '0';
    openedFile = fopen(f,"r");
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
void deleteLine(int Line) {
    FILE *openedFile;
    char c='0';
    openedFile = fopen(f,"r");
    if(openedFile == NULL){
        printf("\n");
        printf("Unable to open file");
    }else{
        int totalcharacters = NumberOfCharactersTillSpecificLine(numberOfLines());
        char buffer[totalcharacters+1];
        int index = 0                ;
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
        openedFile = fopen(f,"w");
        fprintf(openedFile,buffer);
        fclose(openedFile);
    }
} 
void showLine(int Line){
    FILE *openedFile = fopen(f,"r");
    fseek(openedFile,NumberOfCharactersTillSpecificLine(Line),SEEK_SET);
    char c = '0';
    while (c != EOF && c != '\n') {
        c = fgetc(openedFile);
        printf("%c",c);
    }
    printf("\n");
    fclose(openedFile);
}
void displayFile(){
    FILE *openedFile;
    char c;
    openedFile = fopen(f,"r");
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
void writeLine(const char *value){
    FILE *openedFile;
    openedFile = fopen(f,"a");
    if(value!=NULL){
        if(openedFile == NULL){
            printf("\n");
            printf("Unable to open file");
        }else{
            fprintf(openedFile,"\n %s",value);
            fclose(openedFile);
        }
    }else{
        fprintf(openedFile,"\n");
        fclose(openedFile);
    }
}
void insertLine(int Line,const char *value){
    FILE *openedFile = fopen(f,"r");
    fseek(openedFile,NumberOfCharactersTillSpecificLine(Line),SEEK_SET);
    char c = '0';
    int count = 0;
    char before_insert_buffer[NumberOfCharactersTillSpecificLine(numberOfLines())+strlen(value)+1];
    for(int i=0;i<Line;i++){
        while(c!=EOF && c!='\n'){
            c = fgetc(openedFile);
            before_insert_buffer[count]=c;
            count++;
        }
        
        before_insert_buffer[count]='\n';
        count++;
    }
    printf("%s",before_insert_buffer);
    strcpy(&before_insert_buffer[count], value);
    count += strlen(value);
    before_insert_buffer[count]='\n';
    count++;
    for(int i=Line;i<numberOfLines();i++){
        while(c!=EOF && c!='\n'){
            c = fgetc(openedFile);
            before_insert_buffer[count]=c;
            count++;
        }
        before_insert_buffer[count]='\n';
        count++;
    }
    fclose(openedFile);
    openedFile = fopen(f,"w");
    fseek(openedFile,0,SEEK_SET);
    fprintf(openedFile,before_insert_buffer);

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
void command(char **log,int size){
    char com[50];
    char value[100];
    char insertPhrase[100];
    int con;
    printf("Enter command: ");
    fgets(com,sizeof(com),stdin);
    // Replaces the newline with a null terminator
    com[strcspn(com,"\n")] = '\0';
    if(strcmp(com,"Quit")!=0){
        if(strcmp(com,"Append Line")==0){
            printf("Enter phrase to be appended: \n");
            fgets(value,sizeof(value),stdin);
            value[strcspn(value, "\n")] = '\0';
            printf("%s",value);
            writeLine(value);
            printf("\n");
            printf("Writing successful");
            printf("\n");
            log = AddToLog(log,size,"Appended Line \n");
            size++;
        }else if(strcmp(com,"Lines")==0){
            printf("Current number of lines: %d",numberOfLines());
            printf("\n");
            log = AddToLog(log,size,"Showed number of lines \n");
            size++;
        }else if(strcmp(com,"Show")==0){
            displayFile();
            log = AddToLog(log,size,"Showed file \n");
            size++;
        }else if(strcmp(com,"Delete Line")==0){
            int line = 0;
            con = 0;
            do{
                printf("Enter the line you want to delete: \n");
                scanf("%d",&line);
                if(line>numberOfLines() || line<1){
                    con = 1;
                    printf("Line number out of range \n"); 
                }

            }while(con==1);
            deleteLine(line);
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
                if(line>numberOfLines() || line<1){
                    con = 1;
                    printf("Line number out of range \n");
                }

            }while(con==1);
            showLine(line);
            fflush(stdin);
            log = AddToLog(log,size,"Showed line \n");
            size++;
        }else if(strcmp(com,"Insert Line")==0){
            int line = 0;
            con = 0;
            do{
                printf("Enter the line you want to insert at: \n");
                scanf("%d",&line);
                if(line>numberOfLines() || line<1){
                    con = 1;
                    printf("Line number out of range \n");
                }

            }while(con==1);
            printf("Enter phrase to be inserted: \n");
            fgets(insertPhrase,sizeof(insertPhrase),stdin);
            value[strcspn(value, "\n")] = '\0';
            insertLine(line,insertPhrase);
            log = AddToLog(log,size,"Inserted line \n");
            size++;
        }else if(strcmp(com,"Show Change Log")==0){
            log = AddToLog(log,size,"Showed change log \n ");
            size++;
            showChangeLog(log,size);
        }else{
            printf("\n");
            printf("Invalid command \n");
        }

        command(log,size);

    }else{
        printf("Program quit");
    }
}
int main(){
    char **strings = NULL;
    int size = 0;
    strings = (char**)malloc(size * sizeof(char*));
    AddToLog(strings,size,"Original unchanged file");
    showChangeLog(strings,size);
    char com[] = "Commands:  \nInsert Line \n Insert line of specific content at speocific line \n Show Change Log \n Shows change log \n Show Line: \n Show content on specified line \n Append Line: \n Adds new line \n Quit: \n Stops program \n Show: \n Shows file contents \n Delete Line \n Deletes a line that you will get to specify after this command \n Lines: \n Number of lines in file \n";
    printf("%s",com);
    //move("C:/Users/khait/Downloads/file.txt",f);
    command(strings,size);
    return 0;
}

