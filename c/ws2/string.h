/*header file*/

#ifndef STRING_H
#define STRING_H

#include<stddef.h> /*included for size_t variable type*/

/*functions declarations*/
size_t StrLen(const char *str);
int StrCmp(const char *str1, const char *str2);

void TestStrLen();
void TestStrCmp();

#endif /* STRING_H */
