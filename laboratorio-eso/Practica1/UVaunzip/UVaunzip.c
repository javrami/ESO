// Uvaunzip
// Javier Gómez Herrero
// Javier Ramiro de Santos
// Grupo X5-10

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
	if(argc==1){
		printf("UVaunzip: file1 [file2 ...]\n");
		exit(1);
	}
	FILE *archivo;
	int cont, aux;
	char c;
	for(int i=1; i<argc; i++){
		archivo=fopen(argv[i], "r");
		if(archivo==NULL){
			printf("UVaunzip: unable to open file\n");
			exit(1);
		}
		aux=fread(&cont, sizeof(int), 1, archivo);
		while((c=fgetc(archivo))!=EOF){
			for(int j=0; j<cont; j++)
				printf("%c", c);
			aux=fread(&cont, sizeof(int), 1, archivo);
		}
		fclose(archivo);
		printf("%d", aux);
		cont=aux;
	}
}
