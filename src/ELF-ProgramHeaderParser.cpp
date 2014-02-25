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
//        if((progHeader->p_type == PT_NULL || progHeader->p_type > PT_PHDR) && !((progHeader->p_type >= PT_LOPROC) && progHeader->p_type <= PT_HIPROC))
//        {
//            return;
//        }
        printType(progHeader);
        printf("%-14p", progHeader->p_offset);
        printf("%-14p", progHeader->p_vaddr);
        printf("%-14p", progHeader->p_paddr);
        printf("%-14x", progHeader->p_filesz);
        printf("%-14x", progHeader->p_memsz);
        printFlags(progHeader);
        printf("%-14x", progHeader->p_align);
        if(progHeader->p_type == PT_INTERP)
        {
            printf("\n     [%s]", (char*) elfHeader + progHeader->p_offset);
        }
    }
    void PHTParser::printType(const Elf32_Phdr* progHeader)
    {
        char buffer[20];
        memset(buffer, 0, sizeof(char) * 20);

        if(progHeader->p_type >= PT_LOOS && progHeader->p_type <= PT_HIOS)
        {
            switch(progHeader->p_type)
            {
                case PT_GNU_EH_FRAME: sprintf(buffer, "GNU_EH_FRAME"); break;
                case PT_GNU_STACK: sprintf(buffer, "GNU_STACK"); break;
                case PT_GNU_RELRO: sprintf(buffer, "GNU_RELRO"); break;
                default: sprintf(buffer, "OS %#08x", progHeader->p_type);
            }
        }
        else if(progHeader->p_type >= PT_LOPROC && progHeader->p_type <= PT_HIPROC)
        {
            sprintf(buffer, "PROC");
        }
        else
        {
            switch(progHeader->p_type)
            {
                case PT_NULL: sprintf(buffer, "UNDEF"); break;
                case PT_LOAD: sprintf(buffer, "LOAD"); break;
                case PT_PHDR: sprintf(buffer, "PHDR"); break;
                case PT_DYNAMIC: sprintf(buffer, "DYNAMIC"); break;
                case PT_INTERP: sprintf(buffer, "INTERP"); break;
                case PT_NOTE: sprintf(buffer, "NOTE"); break;
                case PT_SHLIB: sprintf(buffer, "SHLIB (ABI BREAK!)"); break;
                default: sprintf(buffer, "%#08x", progHeader->p_type);
            }
        }
        printf("%-14s", buffer);
    }
    void PHTParser::printFlags(const Elf32_Phdr* progHeader)
    {
        char flagStr[4];
        memset(flagStr, 0, sizeof(char));

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
        printf("%-8s", flagStr);
    }
}
