/***********************************************************************************
*Auther: Arieh Farber
*Reviewr: Yarden Shai
*Date: 8/11/2023
***********************************************************************************/

#ifndef __STRING_H__
#define __STRING_H__

size_t StrLen(const char *str);

int StrCmp(const char *string1, const char *string2);

int StrNCmp(const char *string1, const char *string2, size_t iterations);

int StrCaseCmp(const char *string1, const char *string2);

char *StrCpy(char *destination, const char *source);

char *StrNCpy(char *destination, const char *source, size_t iterations);

char *StrChar(const char *str, int sign);

char *StrDup(const char *str);

char *StrCat(char *destination, const char *source);

char *StrNCat(char *destination, const char *source, size_t iterations);

char *StrStr(const char *haystack, const char *needle);

size_t StrSpn(const char *str1, const char *str2);

#endif /* __STRING_H__ */
