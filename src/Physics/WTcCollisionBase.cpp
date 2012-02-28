#include "../WTBamboo.h"

void cCollisionBase::SetType(cSphereCollision *lpSphere){ OnFile(lpSphere);};

void cCollisionBase::OnFile(vCollisionData *lpPoint){ClearProcedural();  mpObject=lpPoint; mbAwake=true; mbAlive=true; ProceduralObj=false;}
void cCollisionBase::OnProcedural(){ClearProcedural(); mbAwake=true; mbAlive=true; ProceduralObj=true; }

cSphereCollision *cCollisionBase::SetType(float lfSize)
{

	OnProcedural();
	mpObject=new cSphereCollision;
	mpObject->SetSize(lfSize);

	return Sphere();

};



void cCollisionBase::ClearProcedural()
{


	if(Procedural() && mpObject) delete mpObject;

	mpObject=0;
	mbAwake=false;

}

cSphereCollision *cCollisionBase::SetTypeSphere(float lfRadius)
{
	return SetType(lfRadius);
};


vCollisionData *cCollisionBase::CollisionData(){return mpObject;};

bool cCollisionBase::Procedural(){return ProceduralObj;};

bool cCollisionBase::Loaded(){return (!ProceduralObj);};

cSphereCollision *cCollisionBase::Sphere(){return mpObject->Sphere();};


cCollisionBase::cCollisionBase()
{
	mpObject=0;
    ProceduralObj=false;
    #warning comment Test Removing this.
    ClearProcedural();
}

cCollisionBase::~cCollisionBase()
{
    ClearProcedural();
}

void cCollisionBase::Signal(SIGNAL liFlags)
{

	if(liFlags&WT_SIGNAL_VALUE_WAKE && Asleep())
	{
		if(mpObject) mbAwake=true;
		else SetType(1.0f);
	}
	if(liFlags&WT_SIGNAL_VALUE_SLEEP)
	{
		if(Awake())
		{
			mbAwake=false;
		}
	}

	if(liFlags&WT_SIGNAL_VALUE_KILL) {delete this;}

}

float cCollisionBase::GetCollisionSize()
{
return Sphere()->CollisionSize();
}

bool cCollisionBase::SphereSphere(cSphereCollision* lpFirst, cMatrix4 &lmFirstMatrix,cSphereCollision* lpSecond, cMatrix4 &lmSecondMatrix)
{

	float lfSize=(lpFirst->CollisionSize()+lpSecond->CollisionSize());
	lfSize*=lfSize;

  if(lmFirstMatrix.DistanceSq(lmSecondMatrix)<lfSize) return 1;
  return 0;
}

uint8 cCollisionBase::Type()
{
	if(mpObject) return mpObject->Type();
    return WT_COLLISION_NO_TYPE;
}


#if WT_FULL_VERSION_BAMBOO


cMeshCollision *cCollisionBase::SetTypeBox(float *lfRadius)
{
	return SetType(lfRadius);
};
cMeshCollision *cCollisionBase::SetTypeBox(float lfmX,float lfpX,float lfmY, float lfpY,float lfmZ,float lfpZ)
{
	float lpTemp[6];
	lpTemp[0]=lfmX;
	lpTemp[1]=lfpX;
	lpTemp[2]=lfmY;
	lpTemp[3]=lfpY;
	lpTemp[4]=lfmZ;
	lpTemp[5]=lfpZ;

	return SetType(lpTemp);
};
void cCollisionBase::SetTypeMesh(string lcReference)
{
	SetType(_GET_COLLISION_MESH_FILE(lcReference.c_str()));
};
void cCollisionBase::SetTypeMesh(cMeshCollision *lpMesh)
{
	SetType(lpMesh);
};

void cCollisionBase::SetTypeCompound(cCompoundCollision *lpData)
{
	SetType(lpData);
};

cBeamCollision *cCollisionBase::SetType(cBeamMesh *lpBeam)
{

	OnProcedural();
	mpObject=new cBeamCollision;
	Beam()->BuildObject(lpBeam->Length(),lpBeam->Radius());
	return Beam();

};

void cCollisionBase::SetType(cCompoundCollision *lpCompound)
{
    OnProcedural();
    mpObject=lpCompound;
};

cCompoundCollision *cCollisionBase::SetType()
{
 OnProcedural();
 mpObject=new cCompoundCollision(5);
 return Compound();
};

cCompoundCollision *cCollisionBase::SetTypeCompound(){return SetType();};

void cCollisionBase::SetType(cMeshCollision *lpMesh){OnFile(lpMesh); };
void cCollisionBase::SetType(cBeamCollision *lpBeam){OnFile(lpBeam); };
//void cCollisionBase::SetType(string lcMeshReference){SetType(_GET_COLLISION_MESH_FILE(lcMeshReference.c_str()));};

cBeamCollision *cCollisionBase::SetType(float lfLength,float lfRadius){OnProcedural(); mpObject=new cBeamCollision; Beam()->BuildObject(lfLength,lfRadius); return Beam();};

cMeshCollision *cCollisionBase::SetType(float *lpBounds)
{

	OnProcedural();
	mpObject=new cMeshCollision;
	mpObject->Mesh()->BuildObject(lpBounds);

	return mpObject->Mesh();

};

cMeshCollision *cCollisionBase::SetType(float lfXP,float lfXN,float lfYP,float lfYN,float lfZP,float lfZN)
{
    float lpTemp[6];
    lpTemp[0]=lfXP;
    lpTemp[1]=lfXN;
    lpTemp[2]=lfYP;
    lpTemp[3]=lfYN;
    lpTemp[4]=lfZP;
    lpTemp[5]=lfZN;

    return SetType(lpTemp);
}


cMeshCollision *cCollisionBase::Mesh(){return mpObject->Mesh();};

cRayCollision *cCollisionBase::Ray(){return mpObject->Ray();};

cBeamCollision *cCollisionBase::Beam(){return mpObject->Beam();};

cCompoundCollision *cCollisionBase::Compound(){return mpObject->Compound();};


cSphereCollision *cCollisionBase::GetCollisionData()
	{
		if(Type()==WT_COLLISION_RADIUS) return Sphere();
		if(Type()==WT_COLLISION_MODEL) return Mesh();
		if(Type()==WT_COLLISION_RAY) return Ray();
		if(Type()==WT_COLLISION_BEAM) return Beam();
		if(Type()==WT_COLLISION_COMPOUND) return Compound();
	return 0;
	};

bool cCollisionBase::ModelModel(cMeshCollision* lpFirst, cMatrix4 &lmFirstMatrix,cMeshCollision* lpSecond, cMatrix4 &lmSecondMatrix)
{

	// Objects get assigned to pointers so code is consistent and each object type is known.
	cMeshCollision *lpPlanes;
	cMeshCollision *lpVerteces;

	// Matrix showing the relative positions of the objects.
	cMatrix4 lmRelative;


	//Determine which object is model and which is sphere
	if(lpFirst->Verteces()<lpSecond->Verteces())
	{
	    lpVerteces=lpFirst;
		lpPlanes=lpSecond;
		//Invert the Matrix of the object NOT moving
		lmRelative=lmSecondMatrix.InvertRotationMatrix()*lmFirstMatrix;
	}
	else
	{
		lpVerteces=lpSecond;
		lpPlanes=lpFirst;
		lmRelative=lmFirstMatrix.InvertRotationMatrix()*lmSecondMatrix;
	}

	uint32 liVertex;
	for(liVertex=0;liVertex<lpVerteces->Verteces();++liVertex)
	{
		float lpPos[3];
		double lfValue;
		float *lpPlane;

		float *lpVertex;
		lpVertex=lpVerteces->Vertex(liVertex);

		uint32 liPlane;
		for(liPlane=0;liPlane<lpPlanes->Planes();++liPlane)
		{
			lpPos[0]=lpVertex[0]*lmRelative[0]+lpVertex[1]*lmRelative[1]+lpVertex[2]*lmRelative[2]+lmRelative[12];
			lpPos[1]=lpVertex[0]*lmRelative[4]+lpVertex[1]*lmRelative[5]+lpVertex[2]*lmRelative[6]+lmRelative[13];
			lpPos[2]=lpVertex[0]*lmRelative[8]+lpVertex[1]*lmRelative[9]+lpVertex[2]*lmRelative[10]+lmRelative[14];

			lpPlane=lpPlanes->Plane(liPlane);

			lfValue=lpPos[0]*lpPlane[0]+lpPos[1]*lpPlane[1]+lpPos[2]*lpPlane[2];

			if(lfValue>lpPlane[3]) {liPlane=0;break;}
		}
		if(liPlane==lpPlanes->Planes()) return 1;
	}
	return 0;

}

bool cCollisionBase::RayRay(cBeamCollision* lpOne, cMatrix4 &lmFirstMatrix,cBeamCollision* lpTwo, cMatrix4 &lmSecondMatrix)
{
	float lfDist[3];

	lfDist[0]=lmFirstMatrix[12]-(lmSecondMatrix[12]);
	lfDist[1]=lmFirstMatrix[13]-(lmSecondMatrix[13]);
	lfDist[2]=lmFirstMatrix[14]-(lmSecondMatrix[14]);


	float Ray1[3],Ray2[3];
	Ray1[0]=lpOne->RayVector(0)*lpOne->Length();
	Ray1[1]=lpOne->RayVector(1)*lpOne->Length();
	Ray1[2]=lpOne->RayVector(2)*lpOne->Length();

	Ray2[0]=lpTwo->RayVector(0)*lpTwo->Length();
	Ray2[1]=lpTwo->RayVector(1)*lpTwo->Length();
	Ray2[2]=lpTwo->RayVector(2)*lpTwo->Length();

	double a,b,c,d,e,f;

	a=Ray1[0]*Ray1[0]+Ray1[1]*Ray1[1]+Ray1[2]*Ray1[2];
	b=-Ray1[0]*Ray2[0]-Ray1[1]*Ray2[1]-Ray1[2]*Ray2[2];
	c=Ray2[0]*Ray2[0]+Ray2[1]*Ray2[1]+Ray2[2]*Ray2[2];
	d=Ray1[0]*lfDist[0]+Ray1[1]*lfDist[1]+Ray1[2]*lfDist[2];
	e=-Ray2[0]*lfDist[0]-Ray2[1]*lfDist[1]-Ray2[2]*lfDist[2];
	f=lfDist[0]*lfDist[0]+lfDist[1]*lfDist[1]+lfDist[2]*lfDist[2];

	double det,s,t;
	s=0.0;
	det=a*c-b*b;

	//Non Parrallel.
	if(det>0)
	{

		s=b*e-c*d;
		t=b*d-a*e;
		if(s >=0.0f)
		{
			if(s<=det)
			{
				if(t>=0.0f)
				{
					if(t<=det)
					{

						//Region 0;
						double invDet=1.0f/det;
						s*=invDet;
						t*=invDet;
					}
					else
					{
						//Region 3
						// F(s) = Q(s,1)
						//Q(s; t)	= as2 + 2bst + ct2 + 2ds + 2et + f
						//Q(s,1)= as2 + 2bs + c2 + 2ds + 2e + f
						// F'(s) = 2*((b+d)+a*s)
						// F'(S) = 0 when S = -(b+d)/a
						double tmp;
						t = 1;
						tmp = b+d;
						if ( tmp > 0 ) s = 0;
						else 	if ( -tmp > a ) s = 1;
						else s = -tmp/a;
					}
				}
				else
				{
					//Region 7
					// F(t) = Q(s,0)
					//Q(s; t)	= as2 + 2bst + ct2 + 2ds + 2et + f
					//Q(s,0) =  as2+2ds
					// F'(t) = 2*a*s+2*d
					// F'(t) = 0 when T = -(2*d)/2*a
					double tmp;
					t = 0;
					tmp = d;
					if ( tmp > 0 ) s = 0;
					else 	if ( -tmp > a ) s = 1;
						else s = -tmp/a;
				}
			}
			else
			{
				if(t>=0.0f)
				{
					if(t<=det)
					{
						double tmp;
						//Region 1;
						s = 1;
						tmp = b+e;
						if ( tmp > 0 ) t = 0;
						else 	if ( -tmp > c ) t = 1;
							else t = -tmp/c;
					}
					else
					{
						//Region 2
						//Q(s; t)	= as2 + 2bst + ct2 + 2ds + 2et + f
						// Q_s(1,1)/2 = a+b+d, Q_t(1,1)/2 = b+c+e
						double tmp;
						tmp = b+d;
						if ( -tmp < a ) // Q_s(1,1) > 0
						{
						// F(s) = Q(s,1) = (c+2*e+f)+2*(b+d)*s+(a)*s^2
						// F'(s) = 2*((b+d)+a*s), F'(S) = 0 when S = -(b+d)/a < 1
						t = 1;
						if ( tmp > 0 ) // S < 0, so minimum at s = 0
							s = 0;
							else // 0 <= S < 1, so minimum at s = S
							s = -tmp/a;
							}
							else // Q_s(1,1) <= 0
							{
								s = 1;
								tmp = b+e;
								if ( -tmp < c ) // Q_t(1,1) > 0
							{
								// F(t) = Q(1,t) = (a+2*d+f)+2*(b+e)*t+(c)*t^2
								// F'(t) = 2*((b+e)+c*t), F'(T) = 0 when T = -(b+e)/c < 1
								if ( tmp > 0 ) // T < 0, so minimum at t = 0
							t = 0;
							else // 0 <= T < 1, so minimum at t = T
							t = -tmp/c;
							}
							else // Q_t(1,1) <= 0, gradient points to region 2, so minimum at t = 1
							t = 1;
							}
					}
				}
				else
				{
					//Region 8
					//Q(s; t)	= as2 + 2bst + ct2 + 2ds + 2et + f
					// Q_s(1,0)/2 = a+d, Q_t(1,0)/2 = b+c+e
					double tmp;
					tmp = d;
					if ( -tmp < a ) // Q_s(1,0) > 0
						{
							// F(s) = Q(s,0) = as^2+2ds+f
							// F'(s) = 2*(d+a*s), F'(S) = 0 when S = -(d)/a < 1
							t = 1;
							if ( tmp > 0 ) // S < 0, so minimum at s = 0
							s = 0;
							else // 0 <= S < 1, so minimum at s = S
							s = -tmp/a;
						}
						else // Q_s(1,1) <= 0
							{
								s = 1;
								tmp = b+e;
								if ( -tmp < c ) // Q_t(1,0) > 0
							{
								// F(t) = Q(1,t) = (a+2*d+f)+2*(b+e)*t+(c)*t^2
								// F'(t) = 2*((b+e)+c*t), F'(T) = 0 when T = -(b+e)/c < 1
								if ( tmp > 0 ) // T < 0, so minimum at t = 0
							t = 0;
							else // 0 <= T < 1, so minimum at t = T
							t = -tmp/c;
							}
							else // Q_t(1,1) <= 0, gradient points to region 2, so minimum at t = 1
							t = 1;
							}
				}
			}
		}
		else
		{
			if(t>=0.0f)
			{
				if(t<=det)
				{
					//Region 5;
					// F(t) = Q(0,t)
					//Q(s; t)	= as2 + 2bst + ct2 + 2ds + 2et + f
					//Q(0,t) =  ct2+2et+f
					// F'(t) = 2*ct+2*e
					// F'(t) = 0 when T = -(e)/c
					double tmp;
					s = 0;
					tmp = e;
					if ( tmp > 0 ) t = 0;
					else 	if ( -tmp > c ) t = 1;
					else t = -tmp/(c);

				}
				else
				{
					//Region 4
					//Q(s; t)	= as2 + 2bst + ct2 + 2ds + 2et + f
					//Q(0; t)	=  2et + ct2 +f
					// Q_s(0,1)/2 = b+d, Q_t(0,1)/2 = c+e
					double tmp;
					tmp = b+d;
					if ( -tmp < a ) // Q_s(1,1) > 0
						{
							// F(s) = Q(s,1) = as^2+2bs+c+2ds+2e+f
							// F'(s) = 2*(b+d+a*s), F'(S) = 0 when S = -(b+d)/a < 1
							t = 1;
							if ( tmp > 0 ) // S < 0, so minimum at s = 0
							s = 0;
							else // 0 <= S < 1, so minimum at s = S
							s = -tmp/a;
						}
						else // Q_s(1,1) <= 0
							{
								s = 1;
								tmp = e;
								if ( -tmp < c ) // Q_t(1,1) > 0
							{
								// F(t) = Q(0,t) = c*t^2+2et+f
								// F'(t) = 2*(c*t+e), F'(T) = 0 when T = -(e)/c < 1
								if ( tmp > 0 ) // T < 0, so minimum at t = 0
							t = 0;
							else // 0 <= T < 1, so minimum at t = T
							t = -tmp/c;
							}
							else // Q_t(1,1) <= 0, gradient points to region 2, so minimum at t = 1
							t = 1;
							}

				}
			}
			else
			{
				//Region 6
				//Q(s; t)	= as2 + 2bst + ct2 + 2ds + 2et + f
				//Q_s(0,0)/2 = d. Q_t(0,0)/2 = e
				double tmp;
				tmp = d;
				if ( -tmp > a) // Q_s(0,0) > 0
				{
					// F(s) = Q(s,0) = (a)*s^2+2ds+f
					// F'(s) = 2as+2d, F'(S) = 0 when S = -d/a < 1
					t = 1;
					if ( tmp > 0 ) // S < 0, so minimum at s = 0
						s = 0;
					else // 0 <= S < 1, so minimum at s = S
						s = -tmp/a;
				}
				else // Q_s(1,1) <= 0
				{
					s = 1;
					tmp = e;
					if ( -tmp < c ) // Q_t(0,0) > 0
					{
						// F(t) = Q(0,t) = ct2+2et+f
						// F'(t) = 2*(e+c*t), F'(T) = 0 when T = -(e)/c < 1
						if ( tmp > 0 ) // T < 0, so minimum at t = 0
							t = 0;
						else // 0 <= T < 1, so minimum at t = T
							t = -tmp/c;
					}
					else // Q_t(1,1) <= 0, gradient points to region 2, so minimum at t = 1
						t = 1;
				}
			}

		}
	}
	else
	{
		//Parrallel
		if ( b > 0 )
		{
			// compare intervals [-(b+d)/a,-d/a] to [0,1]
			if ( d >= 0 )
			{	// -d/a <= 0, so minimum is at s = 0, t = 0
				s=0;
				t=0;
			}
			else 	if ( -d <= a )
				{	// 0 < -d/a <= 1, so minimum is at s = -d/a, t = 0
					s=-d/a;
					t=0;
				}
			else
			{	// minimum occurs at s = 1, need to determine t (see below)
				double tmp;
				tmp = a+d;
				if ( -tmp >= b ) t = 1; else t = -tmp/b;
			}
		}
		else
		{
			// compare intervals [-d/a,-(b+d)/a] to [0,1]
			if ( -d >= a )
			{
				// 1 <= -d/a, so minimum is at s = 1, t = 0
				s=1;
				t=0;
			}
			else if ( d <= 0 )
			{
				// 0 <= -d/a < 1, so minimum is at s = -d/a, t = 0
				s=-d/a;
				t=0;
			}
			else
				// minimum occurs at s = 0, need to determine t (see below)
				if ( d >= -b ) t = 1; else t = -d/b;

		}


	}

/*
Collision is at point lfDist from this
//Find dist between closest points
lfDist[0]=lfDist[0]+s*Ray1[0]-t*Ray2[0];
lfDist[1]=lfDist[1]+s*Ray1[1]-t*Ray2[1];
lfDist[2]=lfDist[2]+s*Ray1[2]-t*Ray2[2];

det=lfDist[0]*lfDist[0]+lfDist[1]*lfDist[1]+lfDist[2]*lfDist[2];
*/


 	det=a*s*s+2*b*s*t+c*t*t+2*d*s+2*e*t+f;
if(det<lpOne->CollisionSize()+lpTwo->CollisionSize()) {return true;}
return 0;

}

bool cCollisionBase::SphereModel(cSphereCollision* lpSphere, cMatrix4 &lmSphereMatrix,cMeshCollision* lpModel, cMatrix4 &lmModelMatrix)
{

// Matrix showing the relative positions of the objects.
cMatrix4 lmRelative;
lmRelative=lmModelMatrix.InvertRotationMatrix()*lmSphereMatrix;

uint32 liLoop;
 for(liLoop=0;liLoop<lpModel->Verteces();++liLoop)
 {
		float lpPos[3];
		double lfValue;
		float *lpVertex;
		lpVertex=lpModel->Vertex(liLoop);

		lpPos[0]=lpVertex[0]*lmRelative[0]+lpVertex[1]*lmRelative[1]+lpVertex[2]*lmRelative[2]+lmRelative[12];
		lpPos[1]=lpVertex[0]*lmRelative[4]+lpVertex[1]*lmRelative[5]+lpVertex[2]*lmRelative[6]+lmRelative[13];
		lpPos[2]=lpVertex[0]*lmRelative[8]+lpVertex[1]*lmRelative[9]+lpVertex[2]*lmRelative[10]+lmRelative[14];

		lfValue=lpPos[0]*lpPos[0]+lpPos[1]*lpPos[1]+lpPos[2]*lpPos[2];

		if(lfValue<lpSphere->CollisionSize()) return 1;
 }

 return 0;

}

bool cCollisionBase::SphereRay(cSphereCollision* lpSphere, cMatrix4 &lmSphereMatrix,cBeamCollision* lpBeam, cMatrix4 &lmBeamMatrix)
{
   double lfEq[2];


float lpStart[3];
lpStart[0]=lmSphereMatrix[12]-lmBeamMatrix[12];
lpStart[1]=lmSphereMatrix[13]-lmBeamMatrix[13];
lpStart[2]=lmSphereMatrix[14]-lmBeamMatrix[14];

float lpRV[3];
lpRV[0]=lpBeam->RayVector(0);
lpRV[1]=lpBeam->RayVector(1);
lpRV[2]=lpBeam->RayVector(2);


//Find the number of Ray vectors to reach the sphere.
lfEq[0]=(lpStart[0]*lpRV[0]+
		lpStart[1]*lpRV[1]+
		lpStart[2]*lpRV[2]);

if(lfEq[0]>lpBeam->Length())
{
		lpRV[0]=lpRV[0]*lpBeam->Length();
		lpRV[1]=lpRV[1]*lpBeam->Length();
		lpRV[2]=lpRV[2]*lpBeam->Length();

		lfEq[1]=0.0f;
		lfEq[1]+=(lpStart[0]-lpRV[0])*(lpStart[0]-lpRV[0]);
		lfEq[1]+=(lpStart[1]-lpRV[1])*(lpStart[1]-lpRV[1]);
		lfEq[1]+=(lpStart[2]-lpRV[2])*(lpStart[2]-lpRV[2]);
}
else
{
	if(lfEq[0]<0.0f)
	{
		lfEq[1]=lpStart[0]*lpStart[0]+lpStart[1]*lpStart[1]+lpStart[2]*lpStart[2];
	}
	else
	{
		lpRV[0]=lpRV[0]*lfEq[0];
		lpRV[1]=lpRV[1]*lfEq[0];
		lpRV[2]=lpRV[2]*lfEq[0];

		lfEq[1]=0.0f;
		lfEq[1]+=(lpStart[0]-lpRV[0])*(lpStart[0]-lpRV[0]);
		lfEq[1]+=(lpStart[1]-lpRV[1])*(lpStart[1]-lpRV[1]);
		lfEq[1]+=(lpStart[2]-lpRV[2])*(lpStart[2]-lpRV[2]);
	}
}

	float lfSize=lpSphere->CollisionSize()+lpBeam->CollisionSize();
	lfSize*=lfSize;
	if(lfEq[1]<lfSize) return 1;

return 0;


}

bool cCollisionBase::RayModel(cBeamCollision* lpRay, cMatrix4 &lmRayMatrix,cMeshCollision* lpModel, cMatrix4 &lmModelMatrix)
{

 float *lpRayVector;

	lpRayVector=lpRay->RayVector();

	float lpRayTemp[3];
	lpRayTemp[0]=lmModelMatrix[12]-lmRayMatrix[12];
	lpRayTemp[1]=lmModelMatrix[13]-lmRayMatrix[13];
	lpRayTemp[2]=lmModelMatrix[14]-lmRayMatrix[14];

	float lpRayStart[3];
	lpRayStart[0]=lpRayTemp[0]*lmModelMatrix[0]+lpRayTemp[1]*lmModelMatrix[1]+lpRayTemp[2]*lmModelMatrix[2];
	lpRayStart[1]=lpRayTemp[0]*lmModelMatrix[4]+lpRayTemp[1]*lmModelMatrix[5]+lpRayTemp[2]*lmModelMatrix[6];
	lpRayStart[2]=lpRayTemp[0]*lmModelMatrix[8]+lpRayTemp[1]*lmModelMatrix[9]+lpRayTemp[2]*lmModelMatrix[10];


	float lpRV[3];
	lpRV[0]=lpRayVector[0]*lmModelMatrix[0]+lpRayVector[1]*lmModelMatrix[1]+lpRayVector[2]*lmModelMatrix[2];
	lpRV[1]=lpRayVector[0]*lmModelMatrix[4]+lpRayVector[1]*lmModelMatrix[5]+lpRayVector[2]*lmModelMatrix[6];
	lpRV[2]=lpRayVector[0]*lmModelMatrix[8]+lpRayVector[1]*lmModelMatrix[9]+lpRayVector[2]*lmModelMatrix[10];

uint32 liCount;
double lfAngle;
float lpPosition[3];
float *lpPlane;
float Denom;

float lpFinalPos[3];
//For Each Face Do This.
for(liCount=0;liCount<lpModel->Faces();++liCount)
{
    lpPlane=lpModel->FacePlane(liCount);

    //Find Ray / Plane intersection

	//Equation is Plane3 = (RayStart + N * RayVertor)*Plane[0-2]
	//Rearranged to N = (Plane3 - RayStart * Plane[0-2]) / (RayVector * Plane[0-2]);
	//Denom is (RayVector * plane[0-2])
    Denom=lpPlane[0]*lpRV[0]+lpPlane[1]*lpRV[1]+lpPlane[2]*lpRV[2];

    if(Denom)
    {
		//Denom Now becomes N - the number of Ray Vectors to get to the plane
	    Denom=(lpPlane[3]-lpPlane[0]*lpRayStart[0]-lpPlane[1]*lpRayStart[1]-lpPlane[2]*lpRayStart[2])/(Denom);

	    if(Denom<=0.0f && Denom>=-(lpRay->Length()*lpRay->Length()))
	    {
		    //Find the Ray position on the face. This is the vector position of the center of the Beam
		    lpPosition[0]=lpRayStart[0]+lpRV[0]*Denom;
		    lpPosition[1]=lpRayStart[1]+lpRV[1]*Denom;
		    lpPosition[2]=lpRayStart[2]+lpRV[2]*Denom;

		    lpFinalPos[0]=lpModel->mlFaces.mpList[liCount].mlCenter.mpData[0];
		    lpFinalPos[1]=lpModel->mlFaces.mpList[liCount].mlCenter.mpData[1];
		    lpFinalPos[2]=lpModel->mlFaces.mpList[liCount].mlCenter.mpData[2];

			//Find Vector from Center of Collision to Center of Polygon
		    lpFinalPos[0]-=lpPosition[0];
		    lpFinalPos[1]-=lpPosition[1];
		    lpFinalPos[2]-=lpPosition[2];

			//This is the Squared distance to get to the center of the plane
		    double Inv=lpFinalPos[0]*lpFinalPos[0]+lpFinalPos[1]*lpFinalPos[1]+lpFinalPos[2]*lpFinalPos[2];

			//Find the Ratio due to relative angles of Plane, Beam Vector and Plane Center angle.
			float lpCross[3];
			lpCross[0]=lpRV[1]*lpFinalPos[2]-lpRV[2]*lpFinalPos[1];
			lpCross[1]=lpRV[2]*lpFinalPos[0]-lpRV[0]*lpFinalPos[2];
			lpCross[2]=lpRV[0]*lpFinalPos[1]-lpRV[1]*lpFinalPos[0];

			float a,c;
			//Cross product this.
			a = lpCross[0]*lpCross[0]+lpCross[1]*lpCross[1]+lpCross[2]*lpCross[2];
			//Radius^2 * Dotproduct of Beam Vector product this.
			c = lpRay->Radius()*lpRay->Radius()*(lpRV[0]*lpRV[0]+lpRV[1]*lpRV[1]+lpRV[2]*lpRV[2]);

			Inv=sqrt(a*c)/a;

			if(1.0f < Inv) return 1;

			//Find the vector to the point closest to the center
		    lpFinalPos[0]*=Inv;
		    lpFinalPos[1]*=Inv;
		    lpFinalPos[2]*=Inv;
			//printf("Vector Proportion : %f %f %f\n",lpFinalPos[0],lpFinalPos[1],lpFinalPos[2]);

			//Find the global position of the point closest to the center
		    lpFinalPos[0]+=lpPosition[0];
		    lpFinalPos[1]+=lpPosition[1];
		    lpFinalPos[2]+=lpPosition[2];

			//Check if it is within the plane.
		    lfAngle=lpModel->GetAngle(lpFinalPos,liCount);
		    if(lfAngle>WT_RAY_ANGLE_LOWER && lfAngle<WT_RAY_ANGLE_UPPER) return 1;
	    }
    }


}



return 0;

}
/*

bool cCollisionBase::RayModel(cBeamCollision* lpRay, cMatrix4 &lmRayMatrix,cMeshCollision* lpModel, cMatrix4 &lmModelMatrix)
{

//	printf("RayModel");

 float *lpRayVector;
 cMatrix4 lmRelative;

	lpRayVector=lpRay->RayVector();
	 	//Invert the Matrix of the object NOT moving
	//lmRelative=lmModelMatrix.InvertRotationMatrix()*lmRayMatrix;



	float lpRayStart[3];
	lpRayStart[0]=lmModelMatrix[12]-lmRayMatrix[12];
	lpRayStart[1]=lmModelMatrix[13]-lmRayMatrix[13];
	lpRayStart[2]=lmModelMatrix[14]-lmRayMatrix[14];

	float lpRV[3];
	lpRV[0]=lpRayVector[0];
	lpRV[1]=lpRayVector[1];
	lpRV[2]=lpRayVector[2];

printf("RayStart : %f %f %f\n",lpRayStart[0],lpRayStart[1],lpRayStart[2]);
printf("RayVector : %f %f %f\n",lpRV[0],lpRV[1],lpRV[2]);

uint32 liCount;
double lfAngle;
float lpPosition[3];
float *lpPlane;
float Denom;

float lpFinalPos[3];
//For Each Face Do This.
for(liCount=0;liCount<lpModel->Faces();++liCount)
{
	printf("***********************\nProcess Plane : %u\n",liCount);
    lpPlane=lpModel->FacePlane(liCount);

	printf("lpPlane : %f %f %f %f\n",lpPlane[0],lpPlane[1],lpPlane[2],lpPlane[3]);

    //Find Ray / Plane intersection

	//Equation is Plane3 = (RayStart + N * RayVertor)*Plane[0-2]
	//Rearranged to N = (Plane3 - RayStart * Plane[0-2]) / (RayVector * Plane[0-2]);
	//Denom is (RayVector * plane[0-2])
    Denom=lpPlane[0]*lpRV[0]+lpPlane[1]*lpRV[1]+lpPlane[2]*lpRV[2];

    if(Denom)
    {
		//Denom Now becomes N - the number of Ray Vectors to get to the plane
	    Denom=(lpPlane[3]-lpPlane[0]*lpRayStart[0]-lpPlane[1]*lpRayStart[1]-lpPlane[2]*lpRayStart[2])/(Denom);
		printf("N Units along Ray: %f\n",Denom);


	    if(Denom<=0.0f && Denom>=-(lpRay->Length()*lpRay->Length()))
	    {
		    //Find the Ray position on the face. This is the vector position of the center of the Beam
		    lpPosition[0]=lpRayStart[0]+lpRV[0]*Denom;
		    lpPosition[1]=lpRayStart[1]+lpRV[1]*Denom;
		    lpPosition[2]=lpRayStart[2]+lpRV[2]*Denom;

			printf("Collision Center : %f %f %f\n",lpPosition[0],lpPosition[1],lpPosition[2]);

		    lpFinalPos[0]=lpModel->mlFaces.mpList[liCount].mlCenter.mpData[0];
		    lpFinalPos[1]=lpModel->mlFaces.mpList[liCount].mlCenter.mpData[1];
		    lpFinalPos[2]=lpModel->mlFaces.mpList[liCount].mlCenter.mpData[2];

			printf("Center Point : %f %f %f\n",lpFinalPos[0],lpFinalPos[1],lpFinalPos[2]);

			//Find Vector from Center of Collision to Center of Polygon
		    lpFinalPos[0]-=lpPosition[0];
		    lpFinalPos[1]-=lpPosition[1];
		    lpFinalPos[2]-=lpPosition[2];

			printf("Vector Collision -> Plane Center : %f %f %f\n",lpFinalPos[0],lpFinalPos[1],lpFinalPos[2]);

			//This is the distance to get to the center of the plane
		    double Inv=lpFinalPos[0]*lpFinalPos[0]+lpFinalPos[1]*lpFinalPos[1]+lpFinalPos[2]*lpFinalPos[2];

			printf("Distance^2 Collision -> Plane Center : %f\n",Inv);
			printf("RayLength^2 : %f\n",lpRay->Radius()*lpRay->Radius());
			printf("if(Distance<RayLength^2) return 1;\n");
			//If the center of the plane is within the radius of the beam you have collision.
		    if(Inv<lpRay->Radius()*lpRay->Radius()) return 1;

			//If not you need to move the collision point to the point closest to the collision center
		    Inv=(lpRay->Radius()*lpRay->Radius())/Inv;
			//Find the vector to the point closest to the center
		    lpFinalPos[0]*=Inv;
		    lpFinalPos[1]*=Inv;
		    lpFinalPos[2]*=Inv;
			//printf("Vector Proportion : %f %f %f\n",lpFinalPos[0],lpFinalPos[1],lpFinalPos[2]);

			//Find the global position of the point closest to the center
		    lpFinalPos[0]+=lpPosition[0];
		    lpFinalPos[1]+=lpPosition[1];
		    lpFinalPos[2]+=lpPosition[2];
			//printf("Point Closest to center : %f %f %f\n",lpFinalPos[0],lpFinalPos[1],lpFinalPos[2]);
			//Check if it is within the plane.
		    lfAngle=lpModel->GetAngle(lpFinalPos,liCount);
			//printf("lfAngle : %f\n",lfAngle);
//			printf("if(lfAngle>%f && lfAngle<%f) return 1;\n",WT_RAY_ANGLE_LOWER,WT_RAY_ANGLE_UPPER);

		    if(lfAngle>WT_RAY_ANGLE_LOWER && lfAngle<WT_RAY_ANGLE_UPPER) return 1;
	    }
    }


}



return 0;

}
  */



#else

cSphereCollision *cCollisionBase::GetCollisionData()
	{
        return Sphere();
	};

#endif

