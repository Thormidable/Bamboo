#ifndef __WTMATH_H__
#define __WTMATH_H__

class cRGB;
class cRGBA;

/// This function takes an angle in Degrees and will return it in radians.
float DegreestoRadians(float lfAngle);
/// This function takes an angle in radians and will return it in Degrees.
float RadianstoDegrees(float lfAngle);

template<class tType> tType ClampValue(tType lfValue,tType lfClamp)
{
    if(lfValue>lfClamp) return lfClamp;
    if(lfValue<-lfClamp) return -lfClamp;
    return lfValue;
};

template<class tType> tType ClampValueRange(tType lfValue,tType lfLow, tType lfHigh)
{
    if(lfValue>lfHigh) return lfHigh;
    if(lfValue<lfLow) return lfLow;
    return lfValue;
};

template<class tType> tType ClampValueOut(tType lfValue,tType lfClamp)
{
    if(lfValue<lfClamp) return lfClamp;
    if(lfValue>-lfClamp) return -lfClamp;
    return lfValue;
};

template<class tType> tType CyclicValue(tType lfValue,tType lfCycle)
{
  while(lfValue>lfCycle){lfValue-=lfCycle;}
  while(lfValue<0.0f){lfValue+=lfCycle;}
  return lfValue;
};

template<class tType> tType LoopingValue(tType lfValue,tType lfCycle)
{
  while(lfValue>lfCycle){lfValue-=2*lfCycle;}
  while(lfValue<-lfCycle){lfValue+=2*lfCycle;}
  return lfValue;
};












// BUBBLE SORT
template<class tType> void BubbleSort(tType *arr, uint32 max,bool (*Comparison)(tType*,tType*))
{
tType tmp;
for(uint32 i=0;i<max;i++)
{
 for(uint32 x=0; x<max-1-i; x++)
 {
  if(Comparison(&arr[x],&arr[x+1]))
    {
    //r.push_back(rnd);
   tmp = arr[x];
   arr[x] = arr[x+1];
   arr[x+1] = tmp;
  }
 }

}

};
// SELECTION SORT
template<class tType> void SelectionSort(tType *arr, uint32 max,bool (*Comparison)(tType*,tType*))
{
tType tmp;
uint32 min;
for(long i=0;i<max;i++)
{
min = i;
   for(uint32 x=i; x<max; x++)
   {
    if(Comparison(&arr[x],&arr[min]))
     {
  min = x;
    }
   }
  tmp = arr[i];
  arr[i] = arr[min];
  arr[min] = tmp;
 }
};

// INSERTION SORT
template<class tType> void InsertionSort(tType *arr, uint32 max,bool (*Comparison)(tType*,tType*))
{
uint32 i, j;
tType index;
for(i=1; i < max;i++)
{
    index  = arr[i];
    j = i;
    while((j > 0) && (Comparison(&arr[j-1],&index)))
       {
        arr[j] = arr[j-1];
        j = j-1;
       }
   arr[j] = index;
}

};

template<class tType> void ShellSort(tType *arr, long max,bool (*Comparison)(tType*,tType*))
{

uint32 i, j;
tType index;
for(i=1; i < max;i++)
{
    index  = arr[i];
    j = i;
    while((j > 0) && (Comparison(&arr[j-1],&index)))
       {
        arr[j] = arr[j-1];
        j = j-1;

      }
   arr[j] = index;
}
};











// BUBBLE SORT
template<class tType> void BubbleSort(tType *arr, uint32 max)
{
tType tmp;
for(uint32 i=0;i<max;i++)
{
 for(uint32 x=0; x<max-1-i; x++)
 {
  if(arr[x] > arr[x+1])
    {
    //r.push_back(rnd);
   tmp = arr[x];
   arr[x] = arr[x+1];
   arr[x+1] = tmp;
  }
 }

}

}
// SELECTION SORT
template<class tType> void SelectionSort(tType *arr, uint32 max)
{
tType tmp;
uint32 min;
for(long i=0;i<max;i++)
{
min = i;
   for(uint32 x=i; x<max; x++)
   {
    if(arr[x] < arr[min])
     {
  min = x;
    }
   }
  tmp = arr[i];
  arr[i] = arr[min];
  arr[min] = tmp;
 }
}

// INSERTION SORT
template<class tType> void InsertionSort(tType *arr, long max)
{
uint32 i, j;
tType index;
for(i=1; i < max;i++)
{
    index  = arr[i];
    j = i;
    while((j > 0) && (arr[j-1] > index))
       {
        arr[j] = arr[j-1];
        j = j-1;
       }
   arr[j] = index;
}

}
template<class tType> void ShellSort(tType *arr, long max)
{

uint32 i, j;
tType index;
for(i=1; i < max;i++)
{
    index  = arr[i];
    j = i;
    while((j > 0) && (arr[j-1] > index))
       {
        arr[j] = arr[j-1];
        j = j-1;

      }
   arr[j] = index;
}
}













































template<class tType> void BubbleSort(tType **arr, long max,bool (*Comparison)(tType*,tType*))
{
tType *tmp;
for(uint32 i=0;i<max;i++)
{
 for(uint32 x=0; x<max-1-i; x++)
 {
  if(Comparison(arr[x],arr[x+1]))
    {
    //r.push_back(rnd);
   tmp = arr[x];
   arr[x] = arr[x+1];
   arr[x+1] = tmp;
  }
 }

}

}
// SELECTION SORT
template<class tType> void SelectionSort(tType **arr, long max,bool (*Comparison)(tType*,tType*))
{
tType *tmp;
int min;
for(int32 i=0;i<max;i++)
{
min = i;
   for(uint32 x=i; x<max; x++)
   {
    if(Comparison(arr[x],arr[min]))
     {
  min = x;
    }
   }
  tmp = arr[i];
  arr[i] = arr[min];
  arr[min] = tmp;
 }
}
// INSERTION SORT
template<class tType> void InsertionSort(tType **arr, uint32 max,bool(*Comparison)(tType*,tType*))
{
int i, j;
tType *index;
for(i=1; i < max;i++)
{
    index  = arr[i];
    j = i;
    while((j > 0) && (Comparison(arr[j-1],index)))
       {
        arr[j] = arr[j-1];
        j = j-1;
       }
   arr[j] = index;
}
}
// SHELL SORT
template<class tType> void ShellSort(tType **arr, long max,bool(*Comparison)(tType*,tType*))
{
int i, j;
tType *index;
for(i=1; i < max;i++)
{
    index  = arr[i];
    j = i;
    while((j > 0) && (Comparison(arr[j-1],index)))
       {
        arr[j] = arr[j-1];
        j = j-1;
      }
   arr[j] = index;
}
}

template<class T> void QuickSort(T *a,const int& leftarg, const int& rightarg)
{
  if (leftarg < rightarg) {

    T pivotvalue = a[leftarg];
    int left = leftarg - 1;
    int right = rightarg + 1;

  for(;;) {

    while (a[--right] > pivotvalue);
    while (a[++left] < pivotvalue);

    if (left >= right) break;

    T temp = a[right];
    a[right] = a[left];
    a[left] = temp;
  }

  int pivot = right;
  QuickSort(a, leftarg, pivot);
  QuickSort(a, pivot + 1, rightarg);
  }
}

/*
template<class T> void QuickSort(T *a, uint32 liItems,bool (*Comparison)(T*,T*))
{
  uint32 liStart=0;
    T *pivotvalue = &a[liStart];
    int left = liStart - 1;
    int right = liItems + 1;

  for(;;) {

    while (Comparison(&a[--right],pivotvalue));
    while (!Comparison(&a[++left],pivotvalue));

    if (left >= right) break;

    T temp = a[right];
    a[right] = a[left];
    a[left] = temp;
  }

  int pivot = right;
  QuickSort(&a[liStart], pivot-liStart,Comparison);
  QuickSort(&a[pivot+1], liItems-pivot-1,Comparison);

}


template<class T> void QuickSort(T **a, uint32 liItems,bool (*Comparison)(T*,T*),bool OtherComparison)
{
  uint32 liStart=0;
    T **pivotvalue = &a[liStart];
    int left = liStart - 1;
    int right = liItems + 1;

  for(;;) {

    while (Comparison(a[--right],pivotvalue[0]));
    while (Comparison(a[++left],pivotvalue[0]));

    if (left >= right) break;

    T temp = a[right];
    a[right] = a[left];
    a[left] = temp;
  }

  int pivot = right;
  QuickSort(&a[liStart], pivot,Comparison);
  QuickSort(&a[pivot+1], liItems,Comparison);

}*/

#endif
