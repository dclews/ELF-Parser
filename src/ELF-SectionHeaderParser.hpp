#ifndef ELFSECTIONHEADERPARSER_HPP
#define ELFSECTIONHEADERPARSER_HPP

#include "ELF.hpp"
#include "StringUtil.hpp"
#include <string.h>

#define SHT_TYPE_BUF_MAX 20
#define SHT_NAME_BUF_MAX 20
#define SHT_FLAGS_BUF_MAX 4

namespace ELF
{
    typedef struct
    {
        char name[SHT_NAME_BUF_MAX];
        char type[SHT_TYPE_BUF_MAX];
        char flags[SHT_FLAGS_BUF_MAX];
    } shtStrings;

    class SHTParser
    {
    private:
        const Elf32Ehdr* elfHeader;
        Elf32_Shdr* shstrtab;
        const char* sectionHeaderBase;
        void printHeader(const Elf32_Shdr* sectionHeader);
        void typeToString(const Elf32_Shdr* sectionHeader, char* buffer, size_t maxlen);
        void nameToString(const Elf32_Shdr* sectionHeader, char* buffer, size_t maxlen);
        void flagsToString(const Elf32_Shdr* sectionHeader, char* buffer, size_t maxlen);
    public:
        SHTParser(const Elf32Ehdr* elfHeader);
        void print();
    };
}


#endif // ELFSECTIONHEADERPARSER_HPP
