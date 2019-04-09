#pragma once

/********************************************************************\
	filename: 	ODLEx_Element_Ship.h
	created:	2014/10/24
	author:		LB
	purpose:	靶船类
\*********************************************************************/

#include "ODLEx_Element_ShapeBase.h"

class ODLEX_EXPORT CODLEx_Element_Ship :
	public CODL_ElementBase
{
protected:
	CODL_Pen*				m_pBorderPen;		//
	SIZE					m_BodySize;			//船身大小
	LONG					m_lHeaderLength;	//船头长
	ODL_SHAPE_COORD			m_CoordType;
public:
	CODLEx_Element_Ship(CODL_CanvasBase* IN pCanvas);
	virtual ~CODLEx_Element_Ship();
public:
	ODL_SHAPE_COORD		GetCoordinateType();
	VOID				SetCoordinateType(ODL_SHAPE_COORD IN coord);

	SIZE*				GetBodySize(){return &m_BodySize;}
	VOID				SetBodySize(LONG width,LONG length);
	LONG				GetHeaderLength(){return m_lHeaderLength;}
	VOID				SetHeaderLength(LONG IN lLength);	
	VOID				SetBorderPen(LOGPEN* IN lp);

public:
	virtual BOOL		OnDraw(HDC IN hDC,RECT* IN pPaintRect);
};