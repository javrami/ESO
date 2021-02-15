#include <sys/types.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char *argv[]){

    char *archivo = argv[1];

    struct stat sb;

    if(stat(archivo, &sb) != -1){
        printf("%s ocupa %lld bytes.\n", archivo, sb.st_size);
        printf("%s Tipo de archivo. %u\n", archivo, sb.st_mode);
        //printf("La ultima modificacion se realizo: %s\n", sb.st_mtim);
        printf("Numero de bloques de 512B asignados en %s: %lld.\n", archivo, sb.st_blocks);
        printf("%s ocupa %lld bytes.\n", archivo, sb.st_size);
    }


}