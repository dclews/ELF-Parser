#ifndef ELFX86_HPP
#define ELFX86_HPP

#include "ELF-Identification.hpp"

enum e_ident_x86
{
    EI_x86_CLASS = ELFCLASS32,
    EI_x86_DATA  = ELFDATA2LSB
};

#endif // ELFX86_HPP
