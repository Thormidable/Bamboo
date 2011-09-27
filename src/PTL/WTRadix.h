#ifndef __WTRADIX_H__
#define __WTRADIX_H__
/** 
*\brief This is my Optimised Radix sort for sorting arrays of data.
 * \param lpList This points to the list of data to be sorted.
 * \param lpBucket This points to the array the function can use as a bucket arrray.
 * \param liSize This is the size of the data array the function will sort.
 * Radix sort works by dividing the values into 256 'buckets' which then allows the function to 
 * literally insert the objects into the correct place in the list. This is repeated for each
 * byte from least significant byte to most (I think).
*/
void RadixSort(int *lpList,int *lpBucket,unsigned int liSize);
/// Thisis a radix sort for unsigned integers. See RadixStort(int*,int*,unsigned int).
void RadixSort(unsigned int *lpList,unsigned int *lpBucket,unsigned int liSize);
/// Thisis a radix sort for floats. See RadixStort(int*,int*,unsigned int).
void RadixSort(float *lpfList,float *lpfBucket,unsigned int liSize);

//Note this has not been de bugged and only works for types which are sets-of-4-bytes long
/// A non-debugged general Radixsort. Note only works for types which are 4 byte blocks in size.
template<class cValue> void RadixSort(cValue *lpvList,cValue *lpvBucket,unsigned int liSize);
#endif
