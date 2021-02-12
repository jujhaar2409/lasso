#include "utils.h"

// This function helps in putting the value of an input char[] inp in to the target char[]
void Utils::assign_char_array(char target[], char inp[])
{
    int i = 0;
    while (inp[i] != '\0')
    {
        target[i] = inp[i];
        i++;
    }
}