#include "ELF-ProgramHeaderParser.hpp"

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
        printf("Type\tOffset\tVirtAddr\tPhysAddr\tFileSize\tMemSize\t\tFlag\t\tAlign\n");

        const char* progHeaderBase = ((const char*) (elfHeader)) + elfHeader->e_phoff;
//        printf("Prog Header base: %p\n", progHeaderBase);
//        printf("Program header size: %#08x\n", elfHeader->e_phentsize);

        for(int i=0;i<elfHeader->e_phnum;i++)
        {
            unsigned int headerOffset = elfHeader->e_phentsize * i;
            //printf("Program header offset: %#08x\n", headerOffset);

            const Elf32_Phdr* progHeader = (Elf32_Phdr*) (progHeaderBase + headerOffset);
            printHeader(progHeader);
        }
    }

    void PHTParser::printHeader(const Elf32_Phdr* progHeader)
    {
        if((progHeader->p_type == PT_NULL || progHeader->p_type > PT_PHDR) && !((progHeader->p_type >= PT_LOPROC) && progHeader->p_type <= PT_HIPROC))
        {
            return;
        }
        printType(progHeader);
        printf("\t%p", progHeader->p_offset);
        printf("\t%p", progHeader->p_vaddr);
        printf("\t\t%p", progHeader->p_paddr);
        printf("\t\t%#08x", progHeader->p_filesz);
        printf("\t%#08x", progHeader->p_memsz);
        printf("\t%#08x", progHeader->p_flags);
        printf("\t%#08x", progHeader->p_align);

        printf("\n");
    }
    void PHTParser::printType(const Elf32_Phdr* progHeader)
    {
        //printf("[ELF::PH] Type is ");
        switch(progHeader->p_type)
        {
            case PT_NULL: printf("UNDEF"); break;
            case PT_LOAD: printf("LOAD"); break;
            case PT_DYNAMIC: printf("DYNAMIC"); break;
            case PT_INTERP: printf("INTERP"); break;
            case PT_NOTE: printf("NOTE"); break;
            case PT_SHLIB: printf("SHLIB (ABI BREAK!)"); break;
            default: printf("%#08x", progHeader->p_type);
        }
        //printf(".\n");
    }
}
