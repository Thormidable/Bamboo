#ifndef __WTMATH_H__
#define __WTMATH_H__

class cRGB;
class cRGBA;


class cRandomTausworthe
{
    uint32 s1, s2, s3;
public:
    cRandomTausworthe(uint32 seed1,uint32 seed2,uint32 seed3)
    {
        s1=seed1;
        s2=seed2;
        s3=seed3;
    };

uint32 GetUInt()
{
#define TAUSWORTHE(s,a,b,c,d) ((s&c)<<d) ^ (((s <<a) ^ s)>>b)

    s1 = TAUSWORTHE(s1, 13, 19, 4294967294UL, 12);
    s2 = TAUSWORTHE(s2, 2, 25, 4294967288UL, 4);
    s3 = TAUSWORTHE(s3, 3, 11, 4294967280UL, 17);

    return (s1 ^ s2 ^ s3);
};

float32 GetFloat(){ return static_cast<float32>(static_cast<float64>(GetUInt()) / static_cast<float64>(0xFFFFFFFF)); };
float32 GetZeroed(){ return (GetFloat() - 0.5f)*2.0f; };

};


template<uint32 tiMult=1664525,uint32 tiInc=1013904223> class cRandomLCG
{
    uint32 miState;
public:
    cRandomLCG(uint32 seed1)
    {
        miState=seed1;
    };

uint32 GetUInt(){miState=miState*tiMult+tiInc;return miState;};
float32 GetFloat(){ return static_cast<float32>(static_cast<float64>(GetUInt()) / static_cast<float64>(0xFFFFFFFF)); };
float32 GetZeroed(){return (GetFloat()-0.5f)*2.0f;};

};


/// This function takes an angle in Degrees and will return it in radians.
float DegreestoRadians(float lfAngle);
/// This function takes an angle in radians and will return it in Degrees.
float RadianstoDegrees(float lfAngle);

bool LineLineIntersect(c3DVf p1,c3DVf p2,c3DVf p3,c3DVf p4,c3DVf *pa,c3DVf *pb,double *mua, double *mub);


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

template<class tType, typename tLambda> void ShellSort(tType *arr, long max, tLambda Comparison)
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
template<class tType, typename tLambda> void ShellSort(tType **arr, long max, tLambda Comparison)
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
};

float FastSquareRoot(float number);
float FastSquareRoot(double number);


/*
double inline __declspec (naked) __fastcall FastSquareRoot(double n)
{
	asm("fld qword ptr [esp+4]");
	asm("fsqrt");
	asm("ret 8");
};*/

#endif
