#ifndef ELFPROGRAMHEADERPARSER_HPP
#define ELFPROGRAMHEADERPARSER_HPP

#include "ELF.hpp"
#include "StringUtil.hpp"

#define PHT_TYPE_BUF_MAX 20
#define PHT_FLAGS_BUF_MAX 4

namespace ELF
{
    typedef struct
    {
        char type[PHT_TYPE_BUF_MAX];
        char flags[PHT_FLAGS_BUF_MAX];
    } phtStrings;

    class PHTParser
    {
    private:
        const Elf32Ehdr* elfHeader;
    public:
        PHTParser(const Elf32Ehdr* elfHeader);
        void print();
        void printHeader(const Elf32_Phdr* progHeader);
        void typeToString(const Elf32_Phdr* progHeader, char* buffer);
        void flagsToString(const Elf32_Phdr* progHeader, char* flagStr);
    };
}


#endif // ELFPROGRAMHEADERPARSER_HPP
