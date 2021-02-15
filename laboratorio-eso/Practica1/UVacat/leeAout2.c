/*#include <sys/types.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>*/

#include <sys/stat.h>
#include <sys/dir.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/dir.h>



int main(int argc, char *argv[]){


    struct exec { /* a.out header */
    unsigned char a_magic[2]; /* magic number */
    unsigned char a_flags; /* flags, see below */
    unsigned char a_cpu; /* cpu id */
    unsigned char a_hdrlen; /* length of header */
    unsigned char a_unused; /* reserved for future use */
    unsigned short a_version; /* version stamp (not used at present) */
    long a_text; /* size of text segement in bytes */
    long a_data; /* size of data segment in bytes */
    long a_bss; /* size of bss segment in bytes */
    long a_entry; /* entry point */
    long a_total; /* total memory allocated */
    long a_syms; /* size of symbol table */
 /* SHORT FORM ENDS HERE */
    long a_trsize; /* text relocation size */
    long a_drsize; /* data relocation size */
    long a_tbase; /* text relocation base */
    long a_dbase; /* data relocation base */
};

    

        char *archivo = argv[1];

        struct exec prueba;

        printf("%s ocupa %ld bytes.\n", argv[1], prueba.a_text);
        printf("%s Tipo de archivo. %u\n", argv[1], prueba.a_cpu);                //printf("La ultima modificacion se realizo: %s\n", sb.st_mtim);
        //printf("Numero de bloques de 512B asignados en %s: %lld.\n", archivo, sb.st_blocks);
        //printf("%s ocupa %lld bytes.\n", archivo, sb.st_size);
    

}


