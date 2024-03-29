/*******************************************************************************
*Author: Arieh Farber
*Reviewer: Yarden Shai
*Date: 9/11/2023
*******************************************************************************/
#ifndef __STRING_H__
#define __STRING_H__

#include <stddef.h> /*size_t*/

/*******************************************************************************
*Description: Calculate the length of a string, excluding the NULL terminator.
*Notes: Undefind beahaviour if Parameters are NULL.
*******************************************************************************/
size_t StrLen(const char *str);

/*******************************************************************************
*Description: Compare two strings.
*Retuern values: 0, if string1 and string2 are equal.
*		 A negative value if string1 is less than string2.
*		 A positive value if string1 is greater than string2.
*Notes: Undefind beahaviour if Parameters are NULL.
*******************************************************************************/
int StrCmp(const char *string1, const char *string2);

/*******************************************************************************
*Description: Similar to StrCmp, but compares only the first
*	     (at most) n charecters of string1 and string2.
*Parameters: The 2 strings and the n amount of charecters to compare.
*Retuern values: See StrCmp.
*Notes: Undefind beahaviour if Parameters are NULL.
*******************************************************************************/
int StrNCmp(const char *string1, const char *string2, size_t n);

/*******************************************************************************
*Description: Compare two strings while ignoring upper and lower case.
*Retuern values: See StrCmp.
*Notes: Undefind beahaviour if Parameters are NULL.
*******************************************************************************/
int StrCaseCmp(const char *string1, const char *string2);

/*******************************************************************************
*Description: Copy a string.
*Retuern values: A pointer to the dest string.
*Notes: The dest string must be large enough to receive the copy.
*		Undefind beahaviour if Parameters are NULL.
*******************************************************************************/
char *StrCpy(char *dest, const char *src);

/*******************************************************************************
*Description: Similar to StrCpy, but copied only the first
*	     	  (at most) n charecters of src into dest.
*Parameters: The 2 strings and the n amount of charecters to copy.
*Retuern values: A pointer to the dest string.
*Notes: If dest is bigger than n, the rest of the memmory will be padded
*		with null-terminaters.
*		The user is responsible for allocating the memory.
*		The strings must not overlap.
*		Warning! If there is no null byte among the first n bytes of src, 
*		the string placed in dest will not be null-terminated.
*		Undefind beahaviour if Parameters are NULL.
*******************************************************************************/
char *StrNCpy(char *dest, const char *src, size_t n);

/*******************************************************************************
*Description: Locate character in string.
*Retuern values: A pointer to the matched character or NULL if
*				 the character is not found.
*Notes: Undefind beahaviour if Parameters are NULL.
*******************************************************************************/
char *StrChr(const char *str, int c);

/*******************************************************************************
*Description: Duplicate a string.
*Retuern values: A pointer to a new duplicated string.
*Notes: If the function fails NULL will be returnd.
		Warning! The user is responsible for freeing the memory.
*		Undefind beahaviour if Parameters are NULL.	
*******************************************************************************/
char *StrDup(const char *str); 

/*******************************************************************************
*Description: Concatenate two strings.
*Retuern values: A pointer to the dest string.
*Notes: The strings must not overlap.
*		The dest string must be large enough to receive the result.
*		Undefind beahaviour if Parameters are NULL.
*******************************************************************************/
char *StrCat(char *dest, const char *src);

/*******************************************************************************
*Description: Similar to StrCat, but it concatenate only the
*	     	  first n charecters of src into dest.
*Parameters: The 2 strings and the n amount of charecters to be concatenated.
*Retuern values: See StrCat.
*Notes: See StrCat.
*		Undefind beahaviour if Parameters are NULL.
*******************************************************************************/
char *StrNCat(char *dest, const char *src, size_t n);

/*******************************************************************************
*Description: Locate a substring
*Retuern values: A pointer to the beginning of the located substring
*Notes: Undefind beahaviour if Parameters are NULL.
*******************************************************************************/
char *StrStr(const char *haystack, const char *needle);

/*******************************************************************************
*Description: Get length of a prefix substring
*Retuern values: The number of bytes in the initial segment of str which consist
*				 only of bytes from accept.
*Notes: Undefind beahaviour if Parameters are NULL.
*******************************************************************************/
size_t StrSpn(const char *str, const char *accept);

#endif /* __STRING_H__ */
