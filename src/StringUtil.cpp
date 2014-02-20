#include "StringUtil.hpp"

void printConditional(const char* string, const char* conditional, bool condition)
{
    printf("%s is ", string);
    if(!condition)
    {
        printf("not ");
    }
    printf("%s.\n", conditional);
}
