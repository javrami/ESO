// Uvacat
// Javier Gómez Herrero
// Javier Ramiro de Santos
// Grupo X5-10

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
	FILE *archivo;
	char c;
	for(int i=1; i<argc; i++){
		archivo=fopen(argv[i], "r");	//Abrimos el archivo en modo de lectura
		if(archivo==NULL){
			printf("UVacat: no puedo abrir fichero\n");
			exit(1);
		}
		c=fgetc(archivo);
		while(c!=EOF){
			printf("%c", c);
			c=fgetc(archivo);
		}
		fclose(archivo);
	}
	return 0;
}
