#ifndef ELF_HPP
#define ELF_HPP

#include "ELF-Identification.hpp"
#include "ELF-SectionHeader.hpp"
#include "ELF-ProgramHeader.hpp"
#include "ELF-Architectures.hpp"

//Source: http://www.skyfree.org/linux/references/ELF_Format.pdf

enum e_types
{
    ET_NONE     = 0, /*!< No file type. */
    ET_REL      = 1, /*!< Relocatable file. */
    ET_EXEC     = 2, /*!< Executable file. */
    ET_DYN      = 3, /*!< Shared object file. */
    ET_CORE     = 4, /*!< Core File. ? */
    ET_LOPROC   = 0xFF00, /*!< Processor specific. */
    ET_HIGHPROC = 0xFFFF  /*!< Processor specific. */
};
enum e_machines
{
    EM_NONE     = 0, /*!< No machine. */
    EM_M32      = 1, /*!< AT&T WE 32100 */
    EM_SPARC    = 2, /*!< SPARC */
    EM_386      = 3, /*!< Intel 80386 */
    EM_68K      = 4, /*!< Motorolla 68000 */
    EM_86K      = 5, /*!< Motorolla 88000 */
    EM_860      = 7, /*!< Intel 80860 */
    EM_MIPS     = 8  /*!< MIPS RS3000 */
};
enum e_versions
{
    EV_NONE     = 0, /*!< Invalid version. */
    EV_CURRENT  = 1  /*!< Current version. At the time of writing this is ELF version 1. */
};

//! ELF Header.
typedef struct {
    unsigned char e_ident[EI_NIDENT]; /*!< ELF identification bytes.*/
    Elf32_Half  e_type;         /*!< ELF Object type.*/
    Elf32_Half  e_machine;      /*!< Target archictecture.*/
    Elf32_Word  e_version;      /*!< ELF Object version.*/
    Elf32_Addr  e_entry;        /*!< Virtual entry point. If not specified this equals zero.*/
    Elf32_Off   e_phoff;        /*!< Program header table's offset in bytes. If the file does not have a PH table this equals zero.*/
    Elf32_Off   e_shoff;        /*!< Section header table's offset in bytes. If the file does not have a SH table this equals zero.*/
    Elf32_Word  e_flags;        /*!< This member holds processor-specific flags associated with the file. Flag names take the form EF_machine_flag.*/
    Elf32_Half  e_ehsize;       /*!< ELF header's size in bytes.*/
    Elf32_Half  e_phentsize;    /*!< Member entry size in PH table.*/
    Elf32_Half  e_phnum;        /*!< Number of entries in the PH table.*/
    Elf32_Half  e_shentsize;    /*!< Member entry size in SH table.*/
    Elf32_Half  e_shnum;        /*!< Number of entries in the SH table.*/
    Elf32_Half  e_shstrndx;     /*!< This member holds the section header table index of the entry associated with the section name string table.
                                  If the file has no section name string table, this member holds
                                  the value SHN_UNDEF.*/
} Elf32Ehdr;

#endif //ELF_HPP
