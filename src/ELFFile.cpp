#include "ELFFile.hpp"

using namespace ELF;

ELFFile::ELFFile(const char* elfFile) : elfFile(elfFile)
{
    elfHeader = (Elf32Ehdr*) elfFile;
}

void ELFFile::Print()
{
    printIdentificationBytes();
    printf("[ELF] Entry Point Address: %#08x\n", elfHeader->e_entry);
    printf("\n");

    phtStrings p;
    PHTParser phtParser(elfHeader);
    phtParser.print();
    printf("\n");

    SHTParser shtParser(elfHeader);
    shtParser.print();
}
bool ELFFile::validMagic()
{
    if(elfHeader->e_ident[EI_MAG0] != ELF_MAG0) return false;
    if(elfHeader->e_ident[EI_MAG1] != ELF_MAG1) return false;
    if(elfHeader->e_ident[EI_MAG2] != ELF_MAG2) return false;
    if(elfHeader->e_ident[EI_MAG3] != ELF_MAG3) return false;

    printMachine();
    printType();

    return true;
}
void ELFFile::printIdentificationBytes()
{
    printConditional("[ELF] Magic", "valid", validMagic());
    printClass();
    printDataEncoding();
    printConditional("[ELF] Header Version", "current", elfHeader->e_version == EV_CURRENT);
    printOSABI();
}

void ELFFile::printMachine()
{
    printf("[ELF] Target machine is ");
    switch(elfHeader->e_machine)
    {
        case EM_68K: printf("68K"); break;
        case EM_860: printf("Intel 860"); break;
        case EM_86K: printf("86K"); break;
        case EM_386: printf("Intel 80386"); break;
        case EM_M32: printf("M32"); break;
        case EM_MIPS: printf("MIPS"); break;
        case EM_SPARC: printf("SPARC"); break;
        case EM_NONE: printf("not specified."); break;
        case EM_PPC: printf("PowerPC"); break;
        case EM_ARM: printf("ARM"); break;
        case EM_IA64: printf("IA64 (Itanium)"); break;
        case EM_x86_64: printf("x86_64"); break;
        case EM_AARCH64: printf("AArch64 (ARM)"); break;
        default: printf("unknown: %#08x", elfHeader->e_machine);
    }
    printf("\n");
}
void ELFFile::printType()
{
    printf("[ELF] Type is ");
    switch(elfHeader->e_type)
    {
        case ET_CORE:printf("CORE"); break;
        case ET_DYN: printf("Shared Object"); break;
        case ET_REL: printf("Relocatable"); break;
        case ET_EXEC: printf("Exectutable"); break;
        default: printf("unknown: %#08x", elfHeader->e_type);
    }
    printf(".\n");
}
void ELFFile::printClass()
{
    printf("[ELF] Class is ");
    switch(elfHeader->e_ident[EI_CLASS])
    {
        case ELFCLASS32: printf("32 bit"); break;
        case ELFCLASS64: printf("64 bit"); break;
        case ELFCLASSNONE: printf("invalid"); break;
        default: printf("unkown: %#08x", elfHeader->e_ident[EI_CLASS]);
    }
    printf(".\n");
}
void ELFFile::printDataEncoding()
{
    printf("[ELF] Encoding is ");
    switch(elfHeader->e_ident[E_DATA])
    {
        case ELFDATA2LSB: printf("LSB (little endian)"); break;
        case ELFDATA2MSB: printf("MSB (big endian)"); break;
        case ELFDATANONE: printf("not specified."); break;
        default: printf("unkown: %#08x", elfHeader->e_ident[E_DATA]);
    }
    printf(".\n");
}
void ELFFile::printOSABI()
{
    printf("[ELF] OS/ABI is ");
    switch(elfHeader->e_ident[EI_OSABI])
    {
        case ELFOSABI_AIX: printf("AIX"); break;
        case ELFOSABI_FREEBSD: printf("FreeBSD"); break;
        case ELFOSABI_HPUX: printf("HP-UX"); break;
        case ELFOSABI_IRIX: printf("IRIX"); break;
        case ELFOSABI_LINUX: printf("Linux"); break;
        case ELFOSABI_NETBSD: printf("NetBSD"); break;
        case ELFOSABI_OPENBSD: printf("OpenBSD"); break;
        case ELFOSABI_SOLARIS: printf("Solaris"); break;
        case ELFOSABI_STANDALONE: printf("Embedded/standalone"); break;
        case ELFOSABI_SYSV: printf("UNIX - SystemV"); break;
        default: printf("unkown: %#08x", elfHeader->e_ident[EI_OSABI]);
    }
    printf(" version %d.\n", elfHeader->e_ident[EI_ABIVERSION]);
}
