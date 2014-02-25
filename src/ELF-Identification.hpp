#ifndef ELFIDENTIFICATION_HPP
#define ELFIDENTIFICATION_HPP

//! e_ident[0-3] ELF Magic number bytes at the start of e_ident.
enum e_ident_magic
{
    ELF_MAG0    = 0x7f,
    ELF_MAG1    = 'E',
    ELF_MAG2    = 'L',
    ELF_MAG3    = 'F'
};
enum e_ident_classes
{
    ELFCLASSNONE    = 0, //!< Invalid class.
    ELFCLASS32      = 1, //!< 32-bit object.
    ELFCLASS64      = 2 //!< 64 bit object.
};
enum e_ident_data_enc
{
    ELFDATANONE     = 0, //!< Invalid character encoding.
    ELFDATA2LSB     = 1, //!< Least significant byte occupies lowest address. Little endian.
    ELFDATA2MSB     = 2 //!< Most significant byte occupies lowest address. Big endian.
};

//! ELF Identifcation bytes. Array offsets.
enum e_ident_offsets
{
    EI_MAG0     = 0, //!< File identification. (ELF Magic)
    EI_MAG1     = 1, //!< File identification. (ELF Magic)
    EI_MAG2     = 2, //!< File identification. (ELF Magic)
    EI_MAG3     = 3, //!< File identification. (ELF Magic)
    EI_CLASS    = 4, //!< File class/capacity.
    E_DATA      = 5, //!< Data encoding. ?
    EI_VERSION  = 6, //!< ELF Header version.
    EI_OSABI    = 7, //!< Identiﬁes the operating system and ABI for which the object is prepared.
    EI_ABIVERSION = 8, //!< OS/ABI version.
    EI_PAD      = 9, //!< Start of padding bytes.
    EI_NIDENT   = 16 //!< Size of e_ident
};

enum e_ident_osabi
{
    ELFOSABI_SYSV       = 0x0, //!< System V ABI
    ELFOSABI_HPUX       = 0x1, //!< HB-UX ABI
    ELFOSABI_NETBSD     = 0x2, //!< NetBSD ABI
    ELFOSABI_LINUX      = 0x3, //!< Linux ABI
    ELFOSABI_SOLARIS    = 0x6, //!< Solaris ABI
    ELFOSABI_AIX        = 0x7, //!< AIX ABI
    ELFOSABI_IRIX       = 0x8, //!< IRIX ABI
    ELFOSABI_FREEBSD    = 0x09,//!< FreeBSD ABI
    ELFOSABI_OPENBSD    = 0x0C,//!< OpenBSD ABI
    ELFOSABI_STANDALONE = 0xFF //!< Standalone/embedded.
};

#endif // ELFIDENTIFICATION_HPP
