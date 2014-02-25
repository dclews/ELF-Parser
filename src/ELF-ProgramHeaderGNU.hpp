#ifndef ELFPROGRAMHEADERGNU_HPP
#define ELFPROGRAMHEADERGNU_HPP

//Figured these out myself.
enum pt_gnu_types
{
    PT_GNU_EH_FRAME    = 0x6474e550,
    PT_GNU_STACK       = 0x6474e551,
    PT_GNU_RELRO       = 0x6474e552
};

#endif // ELFPROGRAMHEADERGNU_HPP
