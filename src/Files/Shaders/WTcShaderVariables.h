#ifndef __WTCSHADERVARIABLES_H__
#define __WTCSHADERVARIABLES_H__

class cShaderVariables
{
   uint32 miUniforms;
   int32 *mpUniforms;
   string *mpUniformText;

   uint32 miAttributes;
   int32 *mpAttributes;
   string *mpAttributeText;

   friend class cShaderProgram;
	friend class cVariableStore;
	friend class cUniformStore;
	friend class cAttributeStore;

	void GetUniformLocations(uint32 liProgramID,cShader **lpShader,uint32 liShaders);
	void GetAttributeLocations(uint32 liProgramID,cShader **lpShader,uint32 liShaders);

public:

	uint32 Uniforms(){return miUniforms;};
	uint32 Attributes(){return miAttributes;};
	
	int32 GetUniformID(uint32 liVariableNumber);
	int32 GetAttributeID(uint32 liVariableNumber);

	uint32 GetUniformPosition(string Name);
	uint32 GetAttributePosition(string Name);

	
	cShaderVariables();
	~cShaderVariables();
	void SetUniform1(uint32 liUniform,float *Value,uint16 liItems=1);
	void SetUniform2(uint32 liUniform,float *Value,uint16 liItems=1);
	void SetUniform3(uint32 liUniform,float *Value,uint16 liItems=1);
	void SetUniform4(uint32 liUniform,float *Value,uint16 liItems=1);

	void SetUniform(uint32 liUniform,float Value0);
	void SetUniform(uint32 liUniform,float Value0,float Value1);
	void SetUniform(uint32 liUniform,float Value0,float Value1,float Value2);
	void SetUniform(uint32 liUniform,float Value0,float Value1,float Value2,float Value3);

	void SetMatrix2(uint32 liUniform,float *Value);
	void SetMatrix3(uint32 liUniform,float *Value);
	void SetMatrix4(uint32 liUniform,float *Value);
	void SetMatrix(uint32 liUniform,cMatrix4 *lpMatrix,uint32 liMatricesInArray=1);

	/*
inline	void SetAttribute1(uint32 liAttribute,float *Value);
inline	void SetAttribute2(uint32 liAttribute,float *Value);
inline	void SetAttribute3(uint32 liAttribute,float *Value);
inline	void SetAttribute4(uint32 liAttribute,float *Value);

inline	void SetAttribute(uint32 liAttribute,float Value);
inline	void SetAttribute(uint32 liAttribute,float Value,float Value1);
inline	void SetAttribute(uint32 liAttribute,float Value,float Value1,float Value2);
inline	void SetAttribute(uint32 liAttribute,float Value,float Value1,float Value2,float Value3);
*/
 void SetAttribute(uint32 liAttribute,uint8 Size,uint16 liStride,float *lpData);
 void SetAttribute(uint32 liAttribute,uint8 Size,uint16 liStride,uint64 *lpData);
 void SetAttribute(uint32 liAttribute,uint8 Size,uint16 liStride,uint32 *lpData);
 void SetAttribute(uint32 liAttribute,uint8 Size,uint16 liStride,uint16 *lpData);
 void SetAttribute(uint32 liAttribute,uint8 Size,uint16 liStride,uint8 *lpData);
 void SetAttribute(uint32 liAttribute,uint8 Size,uint16 liStride,int64 *lpData);
 void SetAttribute(uint32 liAttribute,uint8 Size,uint16 liStride,int32 *lpData);
 void SetAttribute(uint32 liAttribute,uint8 Size,uint16 liStride,int16 *lpData);
 void SetAttribute(uint32 liAttribute,uint8 Size,uint16 liStride,int8 *lpData);


	void BindAttributes(uint32 liProgramID);

 
};

#endif
