#ifndef ELFSECTIONHEADERPARSER_HPP
#define ELFSECTIONHEADERPARSER_HPP

#include "ELF.hpp"
#include "StringUtil.hpp"
#include <string.h>

class SHTParser
{
private:
    const Elf32Ehdr* elfHeader;
    Elf32_Shdr* shstrtab;
    const char* sectionHeaderBase;
    void printHeaders();
    void printHeader(const Elf32_Shdr* sectionHeader);
    void printType(const Elf32_Shdr* sectionHeader);
    void printName(const Elf32_Shdr* sectionHeader);
    void printFlags(const Elf32_Shdr* sectionHeader);
public:
    SHTParser(const Elf32Ehdr* elfHeader);
    void print();
};

#endif // ELFSECTIONHEADERPARSER_HPP
