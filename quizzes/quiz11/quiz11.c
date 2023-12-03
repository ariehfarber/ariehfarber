/*******************************************************************************
*Auther: Arieh Farber
*******************************************************************************/
#include <stddef.h> /*size_t*/

#include "quiz11.h"

char *FlipStrOrder(char *str,  size_t str_length)
{
    size_t i = 0, j = 0, start = 0;
    char temp_c = '\0';

    for (i = 0; i < (str_length / 2); i++) 
    {
        temp_c = str[i];
        str[i] = str[str_length - i - 1];
        str[str_length - i - 1] = temp_c;
    }

    for (i = 0; i <= str_length; i++) 
    {
        if (' ' == str[i] || '\0' == str[i]) 
        {
            for (j = start; j < ((start + i) / 2); j++) 
            {
                temp_c = str[j];
                str[j] = str[start + i - j - 1];
                str[start + i - j - 1] = temp_c;
            }
            start = i + 1;
        }
    }
	
	return (str);
}


