#include "ELFFile.hpp"
#include <stdio.h>

#if defined(__sun) && defined(__SVR4)
typedef long id_t;
typedef id_t ctid_t;
typedef id_t zoneid_t;
#endif

#include <stdlib.h>

using namespace std;

int main(int argc, char** argv)
{
    //FILE *f = fopen("/usr/lib32/libpng.so", "rb");
    //FILE *f = fopen("/home/dan/ELF-Files/bash", "rb");

    const char* file = (argc > 1) ? argv[1] : "bash";

    printf("Parsing file: %s\n", file);
    FILE* f = fopen(file, "rbw");

    if(f!=NULL)
    {
        fseek(f, 0, SEEK_END);
        long fsize = ftell(f);
        fseek(f, 0, SEEK_SET);

        char* elfBuffer = (char*) malloc(fsize + 1);
        fread(elfBuffer, fsize, 1, f);

        ELFFile elf(elfBuffer);
        elf.Print();

        fclose(f);
        elfBuffer[fsize] = 0;
    }
    else
    {
        printf("Failed to open file %s\n", file);
        return 1;
    }

    return 0;
}

