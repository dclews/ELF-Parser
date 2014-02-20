#ifndef ELFPROGRAMHEADERPARSER_HPP
#define ELFPROGRAMHEADERPARSER_HPP

#include "ELF.hpp"
#include "StringUtil.hpp"

namespace ELF
{
    class PHTParser
    {
    private:
        const Elf32Ehdr* elfHeader;
        void printHeaders();
        void printHeader(const Elf32_Phdr* progHeader);
        void printType(const Elf32_Phdr* progHeader);
        void printFlags(const Elf32_Phdr* progHeader);
    public:
        PHTParser(const Elf32Ehdr* elfHeader);
        void print();
    };
}


#endif // ELFPROGRAMHEADERPARSER_HPP
