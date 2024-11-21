#include<stdio.h>
void openFile(filePath,modeOfOperation){
   FILE *openedFile;
    char c;
    openedFile = fopen(filePath,modeOfOperation);
    if(openedFile == NULL){
        printf("Unable to open file");
    }else{
        while(1){
            c = fgetc(openedFile);
            if(c==EOF){
                break;
            }else{
                printf("%c",c);
            }
        }
        fclose(openedFile);
    }

}
int main(){
    openFile("D:\\Computer systems cwk\\Project\\file.txt","r");
}

