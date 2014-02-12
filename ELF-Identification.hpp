#ifndef ELFIDENTIFICATION_HPP
#define ELFIDENTIFICATION_HPP

enum e_ident_magic //e_ident[0-3] ELF Magic number bytes at the start of e_ident.
{
    ELF_MAG0    = 0x7f,
    ELF_MAG1    = 'E',
    ELF_MAG2    = 'L',
    ELF_MAG3    = 'F'
};
enum e_ident_classes
{
    ELFCLASSNONE    = 0, //Invalid class.
    ELFCLASS32      = 1, //32-bit object.
    ELFCLASS64      = 2, //64 bit object.
};
enum e_ident_data_enc
{
    ELFDATANONE     = 0, //Invalid character encoding.
    ELFDATA2LSB     = 1, //Least significant byte occupies lowest address. Little endian.
    ELFDATA2MSB     = 2, //Most significant byte occupies lowest address. Big endian.
};

enum e_ident_offsets //ELF Identifcation bytes. Array offsets.
{
    EI_MAG0     = 0, //File identification. (ELF Magic)
    EI_MAG1     = 1, //File identification. (ELF Magic)
    EI_MAG2     = 2, //File identification. (ELF Magic)
    EI_MAG3     = 3, //File identification. (ELF Magic)
    EI_CLASS    = 4, //File class/capacity.
    E_DATA      = 5, //Data encoding. ?
    EI_VERSION  = 6, //ELF Header version.
    EI_PAD      = 7, //Start of padding bytes.
    EI_NIDENT   = 16 //Size of e_ident
};

#endif // ELFIDENTIFICATION_HPP
