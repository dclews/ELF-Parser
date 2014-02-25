#include "ELF-ProgramHeaderParser.hpp"
#include <string.h>

namespace ELF
{
    PHTParser::PHTParser(const Elf32Ehdr* elfHeader) : elfHeader(elfHeader)
    {

    }
    void PHTParser::print()
    {
        if(elfHeader->e_phnum <= 0)
        {
            printf("[ELF] File has no program headers.\n");
            return;
        }

        printf("Number of program headers: %u\n", elfHeader->e_phnum);
        printf("%-5s%-14s%-14s%-14s%-14s%-14s%-14s%-8s%-14s\n", "[ #]", "Type", "Offset", "Virt Addr", "Phys Addr", "File Size", "Mem Size","Flags","Align");

        const char* progHeaderBase = ((const char*) (elfHeader)) + elfHeader->e_phoff;

        for(int i=0;i<elfHeader->e_phnum;i++)
        {
            unsigned int headerOffset = elfHeader->e_phentsize * i;

            printf("[%2d]%-1s", i, " ");

            const Elf32_Phdr* progHeader = (Elf32_Phdr*) (progHeaderBase + headerOffset);
            printHeader(progHeader);

            printf("\n");
        }
    }

    void PHTParser::printHeader(const Elf32_Phdr* progHeader)
    {
        phtStrings phtStr;
        typeToString(progHeader, phtStr.type);
        flagsToString(progHeader, phtStr.flags);

        printf("%-14s", phtStr.type);
        printf("%-14p", progHeader->p_offset);
        printf("%-14p", progHeader->p_vaddr);
        printf("%-14p", progHeader->p_paddr);
        printf("%-14x", progHeader->p_filesz);
        printf("%-14x", progHeader->p_memsz);
        printf("%-8s", phtStr.flags);
        printf("%-14x", progHeader->p_align);
        if(progHeader->p_type == PT_INTERP)
        {
            printf("\n     [%s]", (char*) elfHeader + progHeader->p_offset);
        }
    }
    void PHTParser::typeToString(const Elf32_Phdr* progHeader, char* buffer)
    {
        if(progHeader->p_type >= PT_LOOS && progHeader->p_type <= PT_HIOS)
        {
            switch(progHeader->p_type)
            {
                case PT_GNU_EH_FRAME: snprintf(buffer, PHT_TYPE_BUF_MAX, "GNU_EH_FRAME"); break;
                case PT_GNU_STACK: snprintf(buffer, PHT_TYPE_BUF_MAX, "GNU_STACK"); break;
                case PT_GNU_RELRO: snprintf(buffer, PHT_TYPE_BUF_MAX, "GNU_RELRO"); break;
                default: snprintf(buffer, PHT_TYPE_BUF_MAX, "OS %#08x", progHeader->p_type);
            }
        }
        else if(progHeader->p_type >= PT_LOPROC && progHeader->p_type <= PT_HIPROC)
        {
            snprintf(buffer, PHT_TYPE_BUF_MAX, "PROC");
        }
        else
        {
            switch(progHeader->p_type)
            {
                case PT_NULL: snprintf(buffer, PHT_TYPE_BUF_MAX, "UNDEF"); break;
                case PT_LOAD: snprintf(buffer, PHT_TYPE_BUF_MAX, "LOAD"); break;
                case PT_PHDR: snprintf(buffer, PHT_TYPE_BUF_MAX, "PHDR"); break;
                case PT_DYNAMIC: snprintf(buffer, PHT_TYPE_BUF_MAX, "DYNAMIC"); break;
                case PT_INTERP: snprintf(buffer, PHT_TYPE_BUF_MAX, "INTERP"); break;
                case PT_NOTE: snprintf(buffer, PHT_TYPE_BUF_MAX, "NOTE"); break;
                case PT_SHLIB: snprintf(buffer, PHT_TYPE_BUF_MAX, "SHLIB (ABI BREAK!)"); break;
                default: snprintf(buffer, PHT_TYPE_BUF_MAX, "%#08x", progHeader->p_type);
            }
        }
    }
    void PHTParser::flagsToString(const Elf32_Phdr* progHeader, char* flagStr)
    {
        if(progHeader->p_flags & PF_R)
        {
            sprintf(flagStr, "R");
        }
        if(progHeader->p_flags & PF_W)
        {
            sprintf(flagStr + strlen(flagStr), "W");
        }
        if(progHeader->p_flags & PF_X)
        {
            sprintf(flagStr + strlen(flagStr), "X");
        }
    }
}
