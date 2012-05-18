#ifndef __WTCMOUSECOLLISION_H__
#define __WTCMOUSECOLLISION_H__

	#if WT_FULL_VERSION_BAMBOO

class cMouseCollisionObject;

class cMouseCollision : public cBeamCollision
{
    friend class cMouseCollisionObject;
    cMatrix4 mpMatrix;
    bool mbNormalised;
  public:

    void PrepForCollision();
    cMouseCollision();

    cMouseCollision *Mouse();

};


	#endif

#endif
