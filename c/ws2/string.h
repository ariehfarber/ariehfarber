/***********************************************************************************
*Author: Arieh Farber
*Reviewer: Yarden Shai
*Date: 9/11/2023
***********************************************************************************/

#ifndef __STRING_H__
#define __STRING_H__

size_t StrLen(const char *str);

int StrCmp(const char *string1, const char *string2);

int StrNCmp(const char *string1, const char *string2, size_t n);

int StrCaseCmp(const char *string1, const char *string2);

char *StrCpy(char *destination, const char *source);

char *StrNCpy(char *destination, const char *source, size_t n);

char *StrChr(const char *str, int sign);

/*when using StrDup the user is responsible for freeing the memory*/
char *StrDup(const char *str); 

char *StrCat(char *destination, const char *source);

char *StrNCat(char *destination, const char *source, size_t n);

char *StrStr(const char *haystack, const char *needle);

size_t StrSpn(const char *s, const char *accept);

#endif /* __STRING_H__ */
