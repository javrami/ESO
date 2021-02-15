// Uvazip
// Javier Gómez Herrero
// Javier Ramiro de Santos
// Grupo X5-10


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
	if(argc==1){
		printf("UVazip: file1 [file2 ...]\n");
		exit(1);
	}
	FILE *archivo;
	char c, d;
	int cont=1;
	for(int i=1; i<argc; i++){
		archivo=fopen(argv[i], "r");
		if(archivo==NULL){
			printf("UVazip: unable to open file\n");
			exit(1);
		}
		c=fgetc(archivo);
		if(i==1){
			d=c;
		}else{
			if(c==d){
				cont++;
			}else{
				if(c!=EOF){
		            fwrite(&cont, sizeof(int), 1, stdout);
                    printf("%c", d);
         	        cont=1;
					d=c;
                        	}
			}
		}
		while(c!=EOF){
			c=fgetc(archivo);
			if(c==d)
				cont++;
			else{
				if(i+1==argc){
					fwrite(&cont, sizeof(int), 1, stdout);
					printf("%c", d);
					cont=1;
					d=c;
				}
			}
		}
		fclose(archivo);
				
	}
}
