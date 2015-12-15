#ifndef __WTCSINGLETON_H__
#define __WTCSINGLETON_H__

template <class cX> class cSingleton
{
protected:
  static cX *mpInstance;
  cSingleton(){};
public:
  static cX *Instance()
  {
    if(!mpInstance)
    {
        mpInstance=new cX;
    }
    return mpInstance;
  };
  ~cSingleton()
  {
      mpInstance=0;
  }
};

template <class cX> cX *cSingleton<cX>::mpInstance=0;

#endif
