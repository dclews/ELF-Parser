#include "ELFFile.hpp"
#include <stdio.h>
#include <stdlib.h>

using namespace std;

int main(int argc, char** argv)
{
    //FILE *f = fopen("/usr/lib32/libpng.so", "rb");
    //FILE *f = fopen("/home/dan/ELF-Files/bash", "rb");

    const char* file = (argc > 1) ? argv[1] : "bash";

    FILE *f = fopen(file, "rb");

    fseek(f, 0, SEEK_END);
    long fsize = ftell(f);
    fseek(f, 0, SEEK_SET);

    char* elfBuffer = (char*) malloc(fsize + 1);
    fread(elfBuffer, fsize, 1, f);

    fclose(f);
    elfBuffer[fsize] = 0;

    ELFFile elf(elfBuffer);
    elf.Print();


    return 0;
}

