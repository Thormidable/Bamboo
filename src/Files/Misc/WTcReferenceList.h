#ifndef __WTCREFERENCELIST_H__
#define __WTCREFERENCELIST_H__

/**
*\brief This will Load from an IMF and store a list of string type references.
*This will load a list of string type references from an IMF filestream.
*The References can be accessed as if they were an array.
*/
class cReferenceList 
{
///This stores the number of references stored in this cReferenceList() Object.
uint32 miLength;
///This is a pointer to an array of pointers pointing to the Reference strings.
 char **mpReferenceList;
public:
 ///This is a public constructor and will initialise the function.
 cReferenceList(){mpReferenceList=0;};
 ///This is a public deconstructor and will delete the all the references and mpReferenceList.
 ~cReferenceList();
 ///This will load a Reference List from an IMF file. FileStream should have just reached the start of a Reference List.
 void LoadIMF(ifstream &FileStream);
 ///This will return a pointer to the Reference at position liID in the array mpReferenceList.
 int8 *Reference(uint32 liID);
 ///This will return the number of references stored by this reference list.
 uint32 Size();
};

#endif
