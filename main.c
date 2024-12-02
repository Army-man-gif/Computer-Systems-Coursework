#include<stdio.h>
#include<string.h>
#include <stdlib.h>
#include <unistd.h>


char f[100]="";
char *convert(char *filePath){
    int count = 0;
    while(filePath[count]!='\0'){
        if(filePath[count]=='\\'){
            filePath[count] = '/';
        }
        count++;
    }
    return filePath;

}
int numberOfLines(){
    FILE *openedFile;
    int number = 0;
    char c;
    int numberOfCharacters = 0;
    openedFile = fopen(f,"r");
    if(openedFile == NULL){
        printf("\n");
        printf("Unable to open file \n");
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
    printf("%s",f);
    openedFile = fopen(f,"r");
    if(openedFile == NULL){
        printf("\n");
        printf("Unable to open file \n");
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
            printf("Couldn't open file");
            fclose(openedFile);
        }else{
            fprintf(openedFile,"\n%s",value);
            fclose(openedFile);
            printf("\n Writing successful \n");
        }
    }else{
        printf("Invalid entry");
    }
}
void insertLine(int Line,const char *value){
    int currentLine = 0;
    FILE *openedFile = fopen(f,"r");
    char c = '0';
    int count = 0;
    char before_insert_buffer[300];
    if(fgetc(openedFile)=='\0'){
        printf("Y");
        memcpy(before_insert_buffer, value, strlen(value));
        before_insert_buffer[count] = '\n';
    }else{
        while ((c = fgetc(openedFile)) != EOF){
            if(currentLine==Line && c == '\n'){
                count += strlen(value);
                memcpy(before_insert_buffer + count, value, strlen(value));
                before_insert_buffer[count] = '\n';
                count++;
            }
            c = fgetc(openedFile);
            before_insert_buffer[count]=c;
            count++;
            if(c == '\n'){
                currentLine++;
            }
        }
    }
    before_insert_buffer[count] = '\0';   
    printf("%s\n",before_insert_buffer);
    fclose(openedFile);
    strcpy(&before_insert_buffer[count], value);
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

void createFile(char fileName[]){
    char *currentDir = getcwd(NULL,0);
    strcpy(f,currentDir);
    strcat(f,"/");
    strcat(f,fileName);
    strcat(f,".txt");
    strcpy(f,convert(f));
    printf("\n %s",f);
    FILE* file = fopen(f,"a");
    printf("\n File %s successfully Created \n",fileName);
    fclose(file);
}

void deleteFile(char fileName[]){
    strcpy(f,convert(fileName));
    int deleteStatus;
    deleteStatus = remove(f);
    if (deleteStatus == 0){
        printf("%s Successfully Deleted\n",f);
    }
    else{
        printf("File not found\n");
    }
}

void copyFile(char fileName[]){
    int currentCharacter;
    printf("%s",fileName);
    FILE* fileCopyFrom = fopen(f,"r");
    if (fileCopyFrom != NULL){
        char newFileName[100];
        printf("\n Enter New File Name: \n");
        fgets(newFileName,100,stdin);
        newFileName[strcspn(newFileName, "\n")] = '\0';
        char *currentDir = getcwd(NULL,0);
        strcpy(newFileName,currentDir);
        strcat(newFileName,"/");
        strcat(newFileName,fileName);
        strcat(newFileName,".txt");
        strcpy(newFileName,convert(newFileName));
        printf("%s",newFileName);
        FILE* fileCopyTo = fopen(newFileName,"w");
        if (fileCopyTo == NULL){
            perror("Error opening file \n");
            printf("Unable to Create New File\n");
        }
        while((currentCharacter = fgetc(fileCopyFrom))!=EOF){
            //printf("%c",currentCharacter);
            //currentCharacter = fgetc(fileCopyFrom);
            //sprintf(fileText,"%s%d",fileText,currentCharacter);
            //strncat(fileText,currentCharacter,1);
            //fprintf(fileCopyTo,"%c",currentCharacter);
            fputc(currentCharacter,fileCopyTo);
        }
        //printf(fileText);
        //fprintf(fileCopyTo,fileText);
        printf("File Copied Successfully\n");
        fclose(fileCopyTo);
    }
    else{
        printf("File not found\n");
    }
    fclose(fileCopyFrom);
}

void renameFile(char fileName[]){
    char newFileName[100];
    printf("\n Enter New File Name:\n");
    rename(fileName,strcat(newFileName,".txt"));
    printf("File Successfully Renamed\n");
}

int checkValidFile(char com[50]){
    FILE *openedFile;
    openedFile = fopen(f,"r");
    if(com[0]!='\0'){
        if(openedFile==NULL){
            perror("\n Error opening file \n");
            fclose(openedFile);
            printf("File not found. \n");
            if(!(strcmp(com,"Delete File") || strcmp(com,"Copy File") || strcmp(com,"Rename File") || strcmp(com,"Show File"))){
                char createFileYesOrNo[6];
                printf("Do you want to create a new file with this name? Type CREATE to make it or NO to not make it \n");
                fgets(createFileYesOrNo,sizeof(createFileYesOrNo),stdin);
                createFileYesOrNo[strcspn(createFileYesOrNo, "\n")] = '\0';
                if(strcmp(createFileYesOrNo,"CREATE")==0){
                    createFile(f);
                    return 1;
                }else{
                    return 0;
                }
            }
        }else{
            return 1;
        }
    }else{
        fclose(openedFile);
        return 0;
    }
    return 0;
}

void command(char **log,int size){
    char com[50];
    char value[100];
    char insertPhrase[100];
    char logText[50] = "";
    int con;
    printf("Enter command: ");
    fgets(com,sizeof(com),stdin);
    // Replaces the newline with a null terminator
    com[strcspn(com,"\n")] = '\0';
    strcmp(f,convert(f));
    if(strcmp(com,"Quit")!=0){
        if(strcmp(com,"Append Line")==0 ){
            if(checkValidFile(com)){
                printf("Enter phrase to be appended: \n");
                fgets(value,sizeof(value),stdin);
                value[strcspn(value, "\n")] = '\0';
                writeLine(value);
                sprintf(logText,"Appended Line to %s\n",f);
                log = AddToLog(log,size,logText);
                size++;
            }
        }else if(strcmp(com,"Lines")==0){
            if(checkValidFile(com)){
                printf("Current number of lines: %d",numberOfLines());
                printf("\n");
                sprintf(logText,"Showed number of lines of %s\n",f);
                log = AddToLog(log,size,logText);
                size++;
            }
        }else if(strcmp(com,"Show File")==0){
            if(checkValidFile(com)){
                displayFile();
                sprintf(logText,"Showed file %s\n",f);
                log = AddToLog(log,size,logText);
                size++;
            }
        }else if(strcmp(com,"Delete Line")==0){
            if(checkValidFile(com)){
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
                sprintf(logText,"Deleted line from %s\n",f);
                log = AddToLog(log,size,logText);
                size++;
            }

        }else if(strcmp(com,"Show Line")==0){
            if(checkValidFile(com)){
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
                sprintf(logText,"Showed line from %s\n",f);
                log = AddToLog(log,size,logText);
                size++;
            }
        }else if(strcmp(com,"Insert Line")==0){
            if(checkValidFile(com)){
                int line = 0;
                con = 0;
                do{
                    line = 0;
                    printf("Enter the line you want to insert at: \n");
                    scanf("%d",&line);
                    getchar();
                    if(line>numberOfLines() || line<1){
                        con = 1;
                        printf("Line number out of range \n");
                    }else{
                        con = 0;
                    }

                }while(con==1);
                printf("Enter phrase to be inserted: \n");
                fgets(insertPhrase,sizeof(insertPhrase),stdin);
                insertPhrase[strcspn(insertPhrase, "\n")] = '\0';
                insertLine(line,insertPhrase);
                sprintf(logText,"Inserted line to %s\n",f);
                log = AddToLog(log,size,logText);
                size++;
            }

        }else if(strcmp(com,"Show Change Log")==0){
            log = AddToLog(log,size,"Showed change log \n ");
            size++;
            showChangeLog(log,size);
        }else if(strcmp(com,"Copy File")==0){
            printf("Enter the exact filepath of File to be Copied:\n");
            fgets(f,sizeof(f),stdin);
            f[strcspn(f, "\n")] = '\0';
            strcpy(f,convert(f));
            copyFile(f);
            sprintf(logText,"Copied File %s\n",f);
            log = AddToLog(log,size,logText);
            size++;
        }
        else if(strcmp(com,"Delete File")==0){
            char deleteFileName[100];
            printf("Enter the exact filepath of File to be Deleted:\n");
            fgets(deleteFileName,sizeof(deleteFileName),stdin);
            deleteFileName[strcspn(deleteFileName, "\n")] = '\0';
            deleteFile(deleteFileName);
            sprintf(logText,"Deleted File %s\n",deleteFileName);
            log = AddToLog(log,size,logText);
            size++;
        }
        else if(strcmp(com,"Create File")==0){
            char createFileName[100];
            printf("Enter New File Name: \n");
            fgets(createFileName,sizeof(createFileName),stdin);
            createFileName[strcspn(createFileName, "\n")] = '\0';
            createFile(createFileName);
            sprintf(logText,"Created File %s\n",createFileName);
            log = AddToLog(log,size,logText);
            size++;
        }
        else if(strcmp(com,"Rename File")==0){
            if (checkValidFile(com)){
                renameFile(f);
                sprintf(logText,"Renamed File %s\n",f);
                log = AddToLog(log,size,logText);
                size++;
            }
        }
        else{
            printf("\n");
            printf("Invalid command \n");
        }

        command(log,size);

    }else{
        printf("Program quit");
    }
}

int main(){
    printf("Enter filename: ");
    fgets(f,sizeof(f),stdin);
    f[strcspn(f, "\n")] = '\0';
    strcpy(f,convert(f));
    char **strings = NULL;
    int size = 0;
    strings = (char**)malloc(size * sizeof(char*));
    AddToLog(strings,size,"Original unchanged file");
    showChangeLog(strings,size);
    char com[] = "Commands:  \n Create File \n It creates a file \n Copy file \n  Copies a file \n Delete file \n Deletes a file \n Show file \n Shows a file \n Insert Line \n Insert line of specific content at speocific line \n Show Change Log \n Shows change log \n Show Line: \n Show content on specified line \n Append Line: \n Adds new line \n Quit: \n Stops program \n Show: \n Shows file contents \n Delete Line \n Deletes a line that you will get to specify after this command \n Lines: \n Shows number of lines in file \n";
    printf("%s",com);
    //move("C:/Users/khait/Downloads/file.txt",f);
    command(strings,size);
    return 0;
}

