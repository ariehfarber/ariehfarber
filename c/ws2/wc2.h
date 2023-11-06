/*header file*/

#ifndef WC2_H
#define WC2_H

#include<stddef.h> /*included for size_t variable type*/

/*functions declarations*/
void IntSwap(int *var1, int *var2);
void CopyArray(int* arry, int* arry_copy, int arry_size);
void TSizeSwap(size_t *var1, size_t *var2);
void PtrSwap(size_t **ptr1, size_t **ptr2);
void PtrSwapCombo(size_t **ptr1, size_t **ptr2);

void TestIntSwap();
void TestCopyArray();
void TestTSizeSwap();
void TestPtrSwap();
void TestPtrSwapCombo();

#endif /* WC2_H */
