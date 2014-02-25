#ifndef ELFSECTIONHEADER_HPP
#define ELFSECTIONHEADER_HPP

#include "ELF-Types.hpp"

enum e_shent_reserved_indexes
{
    SHN_UNDEF       = 0, //!< Undefined/irrelevant.
    SHN_LORESERVE   = 1, //!< This value specifies the lower bound of the range of reserved indexes.
    SHN_LOPROC      = 2, //!< Values between LOPROC and HIPROC (inclusively) are reserved for processor specific semantics.
    SHN_HIPROC      = 3, //!< See LOPROC.
    SHN_ABS         = 4, /*!< This value specifies absolute values for the corresponding reference. For example,
                                symbols defined relative to section number SHN_ABS have absolute values and are
                                not affected by relocation. */

    SHN_COMMON      = 5, /*!< Symbols defined relative to this section are common symbols, such as FORTRAN
                                COMMON or unallocated C external variables. */

    SHN_HIRESERVE   = 6 //!< Upper bound of the range of reserved indexes.

    /*!< Although index 0 is reserved as the undefined value, the section header table contains an entry for
       index 0. That is, if the e_shnum member of the ELF header says a file has 6 entries in the section
       header table, they have the indexes 0 through 5. The contents of the initial entry are specified later in
       this section */
};

enum e_shent_reserved_index_value
{
    SHN_UNDEF_VAL       = 0,
    SHN_LORESERVE_VAL   = 0xFF00,
    SHN_LOPROC_VAL      = 0xFF00,
    SHN_HIPROC_VAL      = 0xFF1F,
    SHN_ABS_VAL         = 0xFFF1,
    SHN_COMMON_VAL      = 0xfff2,
    SHN_HIRESERVE_VAL   = 0xffff
};

typedef struct {
    Elf32_Word sh_name;     //!< An index into the String Header Table, giving the location of a null terminated string describing the name of this section.
    Elf32_Word sh_type;
    Elf32_Word sh_flags;    //!< Bitmap of section flags describing section attributes.

    Elf32_Addr sh_addr;     /*!< If the section will appear in the memory image of a process, this member gives the
                              address at which the section’s first byte should reside. Otherwise, the member con-
                              tains 0. */

    Elf32_Off  sh_offset;   /*!< This member’s value gives the byte offset from the beginning of the file to the first
                              byte in the section. One section type, SHT_NOBITS described below, occupies no
                              space in the file, and its sh_offset member locates the conceptual placement in the
                              file. */

    Elf32_Word sh_size;     /*!< This member gives the section’s size in bytes. Unless the section type is
                              SHT_NOBITS, the section occupies sh_size bytes in the file. A section of type
                              SHT_NOBITS may have a non-zero size, but it occupies no space in the file. */

    Elf32_Word sh_link;     //!< Holds a section header table index link, whose interpretation depends on the section type.
    Elf32_Word sh_info;     //!< Holds extra information, whose interpretation depends on the section type.

    Elf32_Word sh_addralign; /*!< Some sections have address alignment constraints. For example, if a section holds a
                               doubleword, the system must ensure doubleword alignment for the entire section.
                               That is, the value of sh_addr must be congruent to 0, modulo the value of
                               sh_addralign. Currently, only 0 and positive integral powers of two are allowed.
                               Values 0 and 1 mean the section has no alignment constraint */

    Elf32_Word sh_endsize;   /*!< Some sections hold a table of fixed-size entries, such as a symbol table. For such a sec-
                               tion, this member gives the size in bytes of each entry. The member contains 0 if the
                               section does not hold a table of fixed-size entries.*/
} Elf32_Shdr ;
enum sh_types
{
    SHT_NULL        = 0, //!< Marks the section header as inactive; it does not have an associated section.
    SHT_PROGBITS    = 1, //!< Holds information defined by the program, whose format and meaning are determined solely by the program.
    SHT_SYMTAB      = 2, //!< See "Symbol tables" below.
    SHT_STRTAB      = 3, //!< The section holds a string table. An object file may have multiple string table sections.

    SHT_RELA        = 4, /*!< The section holds relocation entries with explicit addends, such as type Elf32_Rela for the 32-bit class of object files.
                           An object file may have multiple relocation sections. */

    SHT_HASH        = 5, /*!< The section holds a symbol hash table. All objects participating in dynamic linking
                            must contain a symbol hash table. Currently, an object file may have only one hash
                            table, but this restriction may be relaxed in the future. */

    SHT_DYNAMIC     = 6, /*!< The section holds information for dynamic linking. Currently, an object file may have
                           only one dynamic section, but this restriction may be relaxed in the future. */

    SHT_NOTE        = 7, //!< The section holds information that marks the file in some way.
    SHT_NOBITS      = 8, /*!< A section of this type occupies no space in the file but otherwise resembles
                           SHT_PROGBITS. Although this section contains no bytes, the sh_offset member
                           contains the conceptual file offset. */

    SHT_REL         = 9, /*!< The section holds relocation entries without explicit addends, such as type
                           Elf32_Rel for the 32-bit class of object files. An object file may have multiple reloca-
                           tion sections. See ‘‘Relocation’’ below for details.*/

    SHT_SHLIB       = 10, //!< This section type is reserved but has unspecified semantics. Programs that contain a section of this type do not conform to the ABI.
    SHT_DYNSYM      = 11, //!< See Symbol tables below.
    SHT_LOOS        = 0x60000000, //!< Values inclusively between LOOS and HIOS are reserved for environment specific semantics.
    SHT_HIOS        = 0x6FFFFFFF, //!< Values inclusively between LOOS and HIOS are reserved for environment specific semantics.
    SHT_LOPROC      = 0x70000000, //!< Values between LOPROC and HIPROC (inclusively) are reserved for processor specific semantics.
    SHT_HIPROC      = 0x7fffffff, //!< Values between LOPROC and HIPROC (inclusively) are reserved for processor specific semantics.

    /*Section types between SHT_LOUSER and SHT_HIUSER may be used by
      the application, without conflicting with current or future system-defined section
      types. */
    SHT_LOUSER      = 0x80000000,
    SHT_HIUSER      = 0xffffffff
};
/* Symbol tables
 * These sections hold a symbol table. Currently, an object file may have only one sec-
 * tion of each type, but this restriction may be relaxed in the future. Typically,
 * SHT_SYMTAB provides symbols for link editing, though it may also be used for
 * dynamic linking. As a complete symbol table, it may contain many symbols unneces-
 * sary for dynamic linking. Consequently, an object file may also contain a
 * SHT_DYNSYM section, which holds a minimal set of dynamic linking symbols, to save
 * space. See ‘‘Symbol Table’’ below for details */

//! Index zero of the Section Header table.
enum sht_zero
{
    sh_zero_name    = 0,
    sh_zero_type    = SHT_NULL,
    sh_zero_flags   = 0,
    sht_zero_addr   = 0,
    sht_zero_offset = 0,
    sht_zero_size   = 0,
    sht_zero_link   = SHN_UNDEF_VAL,
    sht_zero_info   = 0,
    sht_zero_addralign = 0,
    sht_zero_entsize   = 0
};

enum sh_flags
{
    SHF_WRITE       = 0x1, //!< This section's data should be writable.
    SHF_ALLOC       = 0x2, //!< This section occupies memory during process execution.
    SHF_EXECINSTR   = 0x4, //!< This section contains exectuable machine instructions.
    SHF_MASKPROC    = 0xf0000000 //!< Processor specific.
};

#endif // ELFSECTIONHEADER_HPP
