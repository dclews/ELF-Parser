#ifndef ELFPROGRAMHEADER_HPP
#define ELFPROGRAMHEADER_HPP

#include "ELF-Types.hpp"

typedef struct {
    Elf32_Word p_type;
    Elf32_Off p_offset; //!< The offset from the beginning of the file at which the first byte of the segment resides.
    Elf32_Addr p_vaddr; //!< The virtual address at which the first byte of the segment resides in memory.
    Elf32_Addr p_paddr; //!< The physical address at which the first byte of the segment resides in memory. Optional.
    Elf32_Word p_filesz; //!< The number of bytes in the file image of the segment; it may be zero.
    Elf32_Word p_memsz; //!< This member gives the number of bytes in the memory image of the segment; it may be zero.
    Elf32_Word p_flags; //!< The number of bytes in the file image of the segment; it may be zero.

    Elf32_Word p_align; /*!< Loadable process segments must have congruent values for p_vaddr and p_offset, modulo the page size. This member
                             gives the value to which the segments are aligned in memory and in the file. Values 0
                             and 1 mean no alignment is required. Otherwise, p_align should be a positive, integral
                             power of 2, and p_vaddr should equal p_offset, modulo p_align. */
} Elf32_Phdr;

enum p_type
{
    PT_NULL     = 0,

    PT_LOAD     = 1, /*!< The array element specifies a loadable segment, described by p_filesz and p_memsz.
                          The bytes from the file are mapped to the beginning of the memory segment. If the
                          segment’s memory size (p_memsz) is larger than the file size (p_filesz), the ‘‘extra’’
                          bytes are defined to hold the value 0 and to follow the segment’s initialized area. The file
                          size may not be larger than the memory size. Loadable segment entries in the program
                          header table appear in ascending order, sorted on the p_vaddr member. */

    PT_DYNAMIC  = 2, //!< The array element specifies dynamic linking information.
    PT_INTERP   = 3, //!< The array element specifies the location and size of a null-terminated path name to invoke as an interpreter.
    PT_NOTE     = 4, //!< The array element specifies the location and size of auxiliary information.
    PT_SHLIB    = 5, //!< Reserved.

    PT_PHDR     = 6, /*!< The array element, if present, specifies the location and size of the program header table
                          itself, both in the file and in the memory image of the program. This segment type may
                          not occur more than once in a file. Moreover, it may occur only if the program header
                          table is part of the memory image of the program. If it is present, it must precede any
                          loadable segment entry. */

    PT_LOPROC   = 0x70000000, //!< Values inclusively between LOPROC and HIPROC are reserved for processor-specific semantics.
    PT_HIPROC   = 0x7fffffff  //!< Values inclusively between LOPROC and HIPROC are reserved for processor-specific semantics.
};

#endif // ELFPROGRAMHEADER_HPP
