#ifndef __WTCSHADERVARIABLES_H__
#define __WTCSHADERVARIABLES_H__

/*
 * brief cShaderVariableSet will store the bindings for User defined variables for each cShaderProgram.
 * This will automatically extract the user definable variables for a shader program (As identified in the IMF).
 * This allows the system to access all the User defined Variables.
 *
 */

class cShaderVariableSet
{
   uint32 miVariables;
   cShaderVariable *mpVariables;

    friend class cShaderProgram;
	friend class cVariableStore;
	friend class cUniformStore;
	friend class cAttributeStore;

	void GetVariableLocations(uint32 liProgramID,cShader **lpShader,uint32 liShaders);

public:

	uint32 Variables(){return miVariables;};

	int32 GetID(uint32 liVariableNumber);

	uint32 GetVariablePosition(string Name);
	uint32 GetUniformPosition(string Name);
	uint32 GetAttributePosition(string Name);

	cShaderVariableSet();
	~cShaderVariableSet();

    void BindAttributes(uint32 liProgramID);

};




#endif
