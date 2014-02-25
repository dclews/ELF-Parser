#include "ELF-SectionHeaderParser.hpp"

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
    printName(sectionHeader);
    printType(sectionHeader);
    printFlags(sectionHeader);
    printf("\n");
}
void SHTParser::printType(const Elf32_Shdr* sectionHeader)
{
    char buffer[20];
    memset(buffer, 0, sizeof(char) * 20);

    if(sectionHeader->sh_type >= SHT_LOOS && sectionHeader->sh_type <= SHT_HIOS)
    {
        sprintf(buffer, "OS");
    }
    else if(sectionHeader->sh_type >= SHT_LOPROC && sectionHeader->sh_type <= SHT_HIPROC)
    {
        sprintf(buffer, "PROC");
    }
    else
    {
        switch(sectionHeader->sh_type)
        {
            case SHT_NULL: sprintf(buffer, "%-10s", "NULL"); break;
            case SHT_HASH: sprintf(buffer, "%-10s", "HASH"); break;
            case SHT_DYNSYM: sprintf(buffer, "%-10s", "DYNSYM"); break;
            case SHT_NOTE: sprintf(buffer, "%-10s", "NOTE"); break;
            case SHT_PROGBITS: sprintf(buffer, "%-10s", "PROGBITS"); break;
            case SHT_REL: sprintf(buffer, "%-10s", "REL"); break;
            case SHT_RELA: sprintf(buffer, "%-10s", "RELA"); break;
            case SHT_SHLIB: sprintf(buffer, "%-10s", "SHLIB"); break;
            case SHT_STRTAB: sprintf(buffer, "%-10s", "STRTAB"); break;
            case SHT_SYMTAB: sprintf(buffer, "%-10s", "SYMTAB"); break;
            case SHT_NOBITS: sprintf(buffer, "%-10s", "NOBITS"); break;
            case SHT_DYNAMIC: sprintf(buffer, "%-10s", "DYNAMIC"); break;
            default: sprintf(buffer, "%#08x", sectionHeader->sh_type);
        }
    }

    printf("%-14s", buffer);
}
void SHTParser::printName(const Elf32_Shdr* sectionHeader)
{
    printf("%-25s", (char*) elfHeader + shstrtab->sh_offset + sectionHeader->sh_name);
}
void SHTParser::printFlags(const Elf32_Shdr* sectionHeader)
{
    char flagStr[5];
    memset(flagStr, 0, sizeof(char));

    if(sectionHeader->sh_flags & SHF_ALLOC)
    {
        sprintf(flagStr, "A");
    }
    if(sectionHeader->sh_flags & SHF_EXECINSTR)
    {
        sprintf(flagStr + strlen(flagStr), "X");
    }
    if(sectionHeader->sh_flags & SHF_WRITE)
    {
        sprintf(flagStr + strlen(flagStr), "W");
    }
    if(sectionHeader->sh_flags & SHF_MASKPROC)
    {
        sprintf(flagStr + strlen(flagStr), "MS");
    }
    printf("%-8s", flagStr);
}
