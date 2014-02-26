#include "ELF-SectionHeaderParser.hpp"

namespace ELF
{
    SHTParser::SHTParser(const Elf32Ehdr* elfHeader) : elfHeader(elfHeader), sectionHeaderBase(((const char*) elfHeader) + elfHeader->e_shoff)
    {
        shstrtab = (Elf32_Shdr*) (sectionHeaderBase + (elfHeader->e_shentsize * elfHeader->e_shstrndx));
    }
    void SHTParser::print()
    {
        if(elfHeader->e_shnum <= 0)
        {
            printf("[ELF] File has no section headers.\n");
            return;
        }
        printf("Number of section headers: %u\n", elfHeader->e_shnum);
        printf("%-5s%-25s%-14s%-8s\n", "[ #]", "Name", "Type", "Flags");

        const char* sectionHeaderBase = ((const char*) elfHeader) + elfHeader->e_shoff;

        for(int i=0;i<elfHeader->e_shnum;i++)
        {
            unsigned int headerOffset = elfHeader->e_shentsize * i;
            const Elf32_Shdr* sectionHeader = (Elf32_Shdr*) (sectionHeaderBase + headerOffset);

            printf("[%2d]%-1s", i, " ");
            printHeader(sectionHeader);
        }
    }
    void SHTParser::printHeader(const Elf32_Shdr* sectionHeader)
    {
        shtStrings s;
        nameToString(sectionHeader, s.name, SHT_NAME_BUF_MAX);
        printf("%-25s", s.name);

        typeToString(sectionHeader, s.type, SHT_TYPE_BUF_MAX);
        printf("%-14s", s.type);

        flagsToString(sectionHeader, s.flags, SHT_FLAGS_BUF_MAX);
        printf("%-8s\n", s.flags);
    }
    void SHTParser::typeToString(const Elf32_Shdr* sectionHeader, char* buffer, size_t maxlen)
    {
        if(sectionHeader->sh_type >= SHT_LOOS && sectionHeader->sh_type <= SHT_HIOS)
        {
            snprintf(buffer, maxlen, "OS");
        }
        else if(sectionHeader->sh_type >= SHT_LOPROC && sectionHeader->sh_type <= SHT_HIPROC)
        {
            snprintf(buffer, maxlen, "PROC");
        }
        else
        {
            switch(sectionHeader->sh_type)
            {
                case SHT_NULL: snprintf(buffer, maxlen, "%-10s", "NULL"); break;
                case SHT_HASH: snprintf(buffer, maxlen, "%-10s", "HASH"); break;
                case SHT_DYNSYM: snprintf(buffer, maxlen, "%-10s", "DYNSYM"); break;
                case SHT_NOTE: snprintf(buffer, maxlen, "%-10s", "NOTE"); break;
                case SHT_PROGBITS: snprintf(buffer, maxlen, "%-10s", "PROGBITS"); break;
                case SHT_REL: snprintf(buffer, maxlen, "%-10s", "REL"); break;
                case SHT_RELA: snprintf(buffer, maxlen, "%-10s", "RELA"); break;
                case SHT_SHLIB: snprintf(buffer, maxlen, "%-10s", "SHLIB"); break;
                case SHT_STRTAB: snprintf(buffer, maxlen, "%-10s", "STRTAB"); break;
                case SHT_SYMTAB: snprintf(buffer, maxlen, "%-10s", "SYMTAB"); break;
                case SHT_NOBITS: snprintf(buffer, maxlen, "%-10s", "NOBITS"); break;
                case SHT_DYNAMIC: snprintf(buffer, maxlen, "%-10s", "DYNAMIC"); break;
                default: snprintf(buffer, maxlen, "%#08x", sectionHeader->sh_type);
            }
        }
    }
    void SHTParser::nameToString(const Elf32_Shdr* sectionHeader, char* buffer, size_t maxlen)
    {
        snprintf(buffer, maxlen, (char*) elfHeader + shstrtab->sh_offset + sectionHeader->sh_name);
    }
    void SHTParser::flagsToString(const Elf32_Shdr* sectionHeader, char* buffer, size_t maxlen)
    {
        memset(buffer, 0, 4);
        if(sectionHeader->sh_flags & SHF_ALLOC)
        {
            sprintf(buffer, "A");
        }
        if(sectionHeader->sh_flags & SHF_EXECINSTR)
        {
            sprintf(buffer + strlen(buffer), "X");
        }
        if(sectionHeader->sh_flags & SHF_WRITE)
        {
            sprintf(buffer + strlen(buffer), "W");
        }
        if(sectionHeader->sh_flags & SHF_MASKPROC)
        {
            sprintf(buffer + strlen(buffer), "MS");
        }
    }
}
