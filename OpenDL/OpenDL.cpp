// OpenDL.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include <afxdllx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

class CGdiPlusInterface
{
protected:
	ULONG_PTR	m_GdiplusToken;

public:

	CGdiPlusInterface(void)
	{
		GdiplusStartupInput gdiplusStartupInput;
		GdiplusStartup(&m_GdiplusToken,&gdiplusStartupInput,NULL);

	}

	~CGdiPlusInterface(void)
	{
		GdiplusShutdown(m_GdiplusToken);
	}

};

CGdiPlusInterface	gm_GdiplusInitializeObject;



static AFX_EXTENSION_MODULE OpenDLDLL = { NULL, NULL };

extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	// Remove this if you use lpReserved
	UNREFERENCED_PARAMETER(lpReserved);

	if (dwReason == DLL_PROCESS_ATTACH)
	{
		TRACE0("OpenDL.DLL Initializing!\n");
		
		// Extension DLL one-time initialization
		if (!AfxInitExtensionModule(OpenDLDLL, hInstance))
			return 0;

		// Insert this DLL into the resource chain
		// NOTE: If this Extension DLL is being implicitly linked to by
		//  an MFC Regular DLL (such as an ActiveX Control)
		//  instead of an MFC application, then you will want to
		//  remove this line from DllMain and put it in a separate
		//  function exported from this Extension DLL.  The Regular DLL
		//  that uses this Extension DLL should then explicitly call that
		//  function to initialize this Extension DLL.  Otherwise,
		//  the CDynLinkLibrary object will not be attached to the
		//  Regular DLL's resource chain, and serious problems will
		//  result.

		new CDynLinkLibrary(OpenDLDLL);


		CoInitialize(NULL);

	
	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		TRACE0("OpenDL.DLL Terminating!\n");

		CoUninitialize();

		// Terminate the library before destructors are called
		AfxTermExtensionModule(OpenDLDLL);
	}
	return 1;   // ok
}



BOOL			SaveDCToBmpFile(HDC IN hDC,HBITMAP IN hBitmap,DWORD IN width,DWORD height,LPCSTR IN pFileName)
{
	if(pFileName == NULL)
		return FALSE;
	BITMAPINFO			bmpInfo;
	BITMAPFILEHEADER	bmpHeader;
	ZeroMemory(&bmpHeader,sizeof(bmpHeader));
	ZeroMemory(&bmpInfo,sizeof(bmpInfo));

	bmpInfo.bmiHeader.biSize =sizeof(bmpInfo.bmiHeader);

	if(0==GetDIBits(hDC,hBitmap,0,1,NULL,&bmpInfo,DIB_RGB_COLORS))
		return FALSE;

	DWORD	lineBytes	=((width*bmpInfo.bmiHeader.biBitCount+31)>>5)<<2; 

	bmpHeader.bfType	=19778;
	bmpHeader.bfOffBits	=sizeof(bmpHeader)+bmpInfo.bmiHeader.biSize + bmpInfo.bmiHeader.biClrUsed * sizeof (RGBQUAD); 
	bmpHeader.bfSize	=lineBytes * height + bmpHeader.bfOffBits;


	BYTE*	pBmpData=(BYTE*)LB_ALLOC(bmpHeader.bfSize);
	BOOL	bRet	=FALSE;

	PBITMAPINFO		pBitmapInfo		=(PBITMAPINFO)(pBmpData+sizeof(bmpHeader));
	*pBitmapInfo	=bmpInfo;
	PBITMAPFILEHEADER pBitmapHeader	=(PBITMAPFILEHEADER)pBmpData;
	*pBitmapHeader	=bmpHeader;

	int		size	=GetDIBits(hDC,hBitmap,0,height,pBmpData + bmpHeader.bfOffBits,pBitmapInfo,DIB_RGB_COLORS);
	if(size > 0)
	{
		pBitmapInfo->bmiHeader.biCompression	=	BI_RGB;

		CFile	 bmpFile;
		if(bmpFile.Open(pFileName,CFile::modeCreate|CFile::modeNoInherit|CFile::modeReadWrite|CFile::shareDenyNone))
		{
			bmpFile.SeekToBegin();
			bmpFile.Write(pBmpData  , bmpHeader.bfSize);
			bmpFile.Close();
			bRet =TRUE;
		}
	}

	LB_FREE(pBmpData);
	return bRet;
}
BOOL			SaveDCToClipboard(HDC IN hDC,HBITMAP IN hBitmap,DWORD IN width,DWORD height)
{
	BITMAPINFO			bmpInfo;
	BITMAPFILEHEADER	bmpHeader;
	ZeroMemory(&bmpHeader,sizeof(bmpHeader));
	ZeroMemory(&bmpInfo,sizeof(bmpInfo));

	bmpInfo.bmiHeader.biSize =sizeof(bmpInfo.bmiHeader);

	if(0==GetDIBits(hDC,hBitmap,0,1,NULL,&bmpInfo,DIB_RGB_COLORS))
		return FALSE;

	DWORD	lineBytes	=((width*bmpInfo.bmiHeader.biBitCount+31)>>5)<<2; 

	bmpHeader.bfType	=19778;
	bmpHeader.bfOffBits	=sizeof(bmpHeader)+bmpInfo.bmiHeader.biSize + bmpInfo.bmiHeader.biClrUsed * sizeof (RGBQUAD); 
	bmpHeader.bfSize	=lineBytes * height + bmpHeader.bfOffBits;


	BYTE*	pBmpData=(BYTE*)LB_ALLOC(bmpHeader.bfSize);
	BOOL	bRet	=FALSE;

	PBITMAPINFO		pBitmapInfo		=(PBITMAPINFO)(pBmpData+sizeof(bmpHeader));
	*pBitmapInfo	=bmpInfo;
	PBITMAPFILEHEADER pBitmapHeader	=(PBITMAPFILEHEADER)pBmpData;
	*pBitmapHeader	=bmpHeader;

	int		size	=GetDIBits(hDC,hBitmap,0,height,pBmpData + bmpHeader.bfOffBits,pBitmapInfo,DIB_RGB_COLORS);
	if(size > 0)
	{
		pBitmapInfo->bmiHeader.biCompression	=	BI_RGB;

		if (OpenClipboard(NULL)) 
		{
			EmptyClipboard();
			HGLOBAL		hMem=GlobalAlloc(GHND,bmpHeader.bfSize-sizeof(bmpHeader)); 
			if (hMem != NULL) 
			{ 
				LPVOID pMem = GlobalLock(hMem); 
				memcpy(pMem , pBmpData+sizeof(bmpHeader) , bmpHeader.bfSize-sizeof(bmpHeader) ); 
				GlobalUnlock(hMem); 
				SetClipboardData(CF_DIB, pMem); 
				CloseClipboard(); 
				bRet =TRUE;
			} 
		}
	}

	LB_FREE(pBmpData);
	return bRet;
}


