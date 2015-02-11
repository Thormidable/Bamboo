
#include "../../WTBamboo.h"
//
//#if WT_FULL_VERSION_BAMBOO
//
//void cText::AddFont(string lsFontSlot,string lcFont)
//{
// AddFont(lsFontSlot,_GET_FONT_FILE(lcFont.c_str()));
//}
//
//void cText::AddFont(string lsFontSlot,cFont *lpFont)
//{
// uint32 liPos=mpShader->ShaderVariableSet()->GetUniformPosition(lsFontSlot);
// if(liPos)
// {
//		AddTexture(liPos-1,lpFont);
// 	//	miCharSize=lpFont->Height();
// }
//}
//
//void cText::AddFont(cFont *lpFont)
//{
//
// int32 liSlot=ReturnFreeSlot();
// if(liSlot>=0)
// {
// 		string lsTextureSlot="Font";
// 		std::stringstream out;
// 		out << liSlot;
//		lsTextureSlot.append(out.str());
//		uint32 liPos=mpShader->ShaderVariableSet()->GetUniformPosition(lsTextureSlot);
//	 	if(liPos)
//		{
//			AddTexture(liPos-1,lpFont);
//			//miCharSize=lpFont->Height();
//		}
// }
//}
//
//void cText::AddFont(string lcFont)
//{
// AddFont(_GET_FONT_FILE(lcFont.c_str()));
//}
//
//uint16 cText::Length()
//{
//	return mpString.length();
//}
//
//void cText::Length(uint16 liLength)
//{
//	mpString.resize(liLength);
//};
//
//
//void cText::RenderPainter()
//{
//
//cFont *lpFont=static_cast<cFont*>(mpTextures[0].mpTexture);
// if(Textures() && lpFont)
// {
//  SetShaderVariables();
//
// float lfHeight=mfHeight*0.5f;
// uint32 liCount;
// float lfXRange,lfYRange;
//
//
//
// lfXRange=lpFont->CharacterX();
// lfYRange=lpFont->CharacterY();
//
// glBegin(GL_QUADS);
// glNormal3f(0.0f,0.0f,1.0f);
//
//  for(liCount=0;liCount<mpString.length();++liCount)
//  {
//
//     if(mpString[liCount]!=32)
//     {
//	uint8 liCharacter=cFont::Character(mpString[liCount]);
//	  float lfX=lpFont->CharacterX(liCharacter);
//	  float lfY=lpFont->CharacterY(liCharacter);
//          glMultiTexCoord2f(GL_TEXTURE0,lfX,lfY+lfYRange);   		glVertex3f(-mfHeight*(liCount-0.5f),lfHeight,1.0f);
//          glMultiTexCoord2f(GL_TEXTURE0,lfX,lfY);            		glVertex3f(-mfHeight*(liCount-0.5f),-lfHeight,1.0f);
//          glMultiTexCoord2f(GL_TEXTURE0,lfX+lfXRange,lfY);            	glVertex3f(-mfHeight*(liCount+0.5f),-lfHeight,1.0f);
//          glMultiTexCoord2f(GL_TEXTURE0,lfX+lfXRange,lfY+lfYRange);   	glVertex3f(-mfHeight*(liCount+0.5f),lfHeight,1.0f);
//
//    }
//
//  }
// }
// glEnd();
//}
//
//std::string &cText::Text()
//{
// return mpString;
//}
//
//
//void cText::Text(string lsText)
//{
// mpString=lsText;
//}
//
//cText::cText(const char *lsText)
//{
// mpString=lsText;
//}
//
//cText::cText(string lsText)
//{
// mpString=lsText;
//}
//
//cText::cText(cCamera *lpCamera) : cImage(lpCamera)
//{
//
//}
//
//cText::cText(string lsText,cCamera *lpCamera) : cImage(lpCamera)
//{
//	mpString=lsText;
//}
//
//cText::cText()
//{
//
//
//}


//
//void cTextMessage::Time(float lfTime)
//{
//miFrames=lfTime*_FPS;
//};
//
//void cTextMessage::Frames(uint32 liFrames){miFrames=liFrames;};
//uint32 cTextMessage::Frames(){return miFrames;};
//void cTextMessage::RenderPainter()
//{
//    cText::RenderPainter();
//    --miFrames;
//    if(!miFrames) _KILL_THIS();
//};
//#endif
