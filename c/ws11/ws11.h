#ifndef _WS11_
#define _WS11_

#include <stddef.h> /* size_t*/

/*place macro here*/

int Atoi(const char *str);

int AtoiAnyBase(const char *str, int base);

char* Itoa(int num, char* buffer);

char* ItoaAnyBase(int num, char* buffer, int base);

void PrintArrOfChars(char *str1, char *str2 ,char *str3, size_t size1, size_t size2, size_t size3);

int IsLittleEndian(void);


#endif /*_WS11_*/