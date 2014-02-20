#ifndef ELFFILE_HPP
#define ELFFILE_HPP

#include <stdio.h>

#include "ELF.hpp"
#include "StringUtil.hpp"
#include "ELF-ProgramHeaderParser.hpp"
#include "ELF-SectionHeaderParser.hpp"

class ELFFile
{
private:
    const char* elfFile;
    const Elf32Ehdr* elfHeader;

    bool validMagic();
    void printMachine();
    void printType();
    void printClass();
    void printIdentificationBytes();
    void printDataEncoding();
public:
    ELFFile(const char* elfFile);
    void Print();
};

#endif // ELFFILE_HPP
