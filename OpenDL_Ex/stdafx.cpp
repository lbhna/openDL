// stdafx.cpp : source file that includes just the standard includes
// OpenDL_Ex.pch will be the pre-compiled header
// stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"

VOID	StringSet(LPSTR& IN OUT pDst,LPCSTR IN pStr)
{
	if(pStr == NULL)return;
	ODL_SafeDeleteArray(pDst);
	size_t len =strlen(pStr);
	pDst =new CHAR[len+1];
	strcpy(pDst,pStr);
	pDst[len]=0;
}
