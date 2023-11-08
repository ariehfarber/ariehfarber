/***********************************************************************************
*Auther: Arieh Farber
*Reviewr: Omer Bruker
*Date: 7/11/2023
***********************************************************************************/

#ifndef __STRING_H__
#define __STRING_H__

size_t StrLen(const char *str);

int StrCmp(const char *string1, const char *string2);

char *StrCpy(char *destination, const char *source);

char *StrNCpy(char *destination, const char *source, size_t iterations);

int StrNCmp(const char *string1, const char *string2, size_t iterations);

#endif /* __STRING_H__ */
