// Uvagrep
// Javier Gómez Herrero
// Javier Ramiro de Santos
// Grupo X5-10

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
	if(argc<2){
		printf("UVagrep: searchterm [file ...]\n");
		exit(1);
	}
	if(argc==2){
		char *lineBuf;
	        size_t lineBufSize=0;
	        ssize_t lineSize;
		lineSize=getline(&lineBuf, &lineBufSize, stdin);
	        while(lineSize>=0){
		        if(strstr(lineBuf, argv[1])!=NULL)
			        printf("%s", lineBuf);
		        lineSize=getline(&lineBuf, &lineBufSize, stdin);
	        }
	        free(lineBuf);
	        lineBuf=NULL;
	}
	else
		for(int i=2; i<argc; i++){
			char *lineBuf;
			size_t lineBufSize=0;
			ssize_t lineSize;
			FILE *file=fopen(argv[i], "r");	//Abrimos el archivo en modo de lectura
	                if(file==NULL){
	                        printf("UVagrep: cannot open file\n");
	                        exit(1);
	                }
			lineSize=getline(&lineBuf, &lineBufSize, file);
			while(lineSize>=0){
				if(strstr(lineBuf, argv[1])!=NULL)
					printf("%s", lineBuf);
	                	lineSize=getline(&lineBuf, &lineBufSize, file);
			}
			free(lineBuf);
			lineBuf=NULL;
			fclose(file);
		}
    return 0;
}

