#pragma once
/*====================================================================\
		#创建日期:	2015/06/02
		#文件名  :	ODLEx_Element_ShapeBase
		#作者    :	LBHNA   
		#说明    :	矢量基类
\====================================================================*/

typedef ODLEX_EXPORT enum
{
	ODLSC_SCREEN			=0,
	ODLSC_COORDINATE		,

	ODLSC_FORCE_DWORD		=0x7fffffff,
}ODL_SHAPE_COORD;

class ODLEX_EXPORT CODLEx_Element_ShapeBase:
	public CODL_OverlayElementBase
{
protected:
	ODL_SHAPE_COORD					m_Coordinate;		//是屏幕坐标空间
	
	BOOL							m_bStroke;			//是否描边
	CODL_Pen*						m_pStrokePen;		//描边画笔
	BOOL							m_bFill;			//是否填充
	CODL_Brush*						m_pFillBrush;		//填充画刷
protected:
	POINT							m_ptDragOffset;
	BOOL							m_bEnableDrag;
	BOOL							m_bDraging;
	BOOL							m_bEnableAdjustSize;
	BOOL							m_bAdjustSizeing;

public:
	CODLEx_Element_ShapeBase(CODL_CanvasBase* IN pCanvas);
	virtual ~CODLEx_Element_ShapeBase();

public:

	ODL_SHAPE_COORD		GetShapeCoordinate();

	BOOL				IsEnableStroke();
	VOID				EnableStroke(BOOL IN bEnable);

	BOOL				IsEnableFill();
	VOID				EnableFill(BOOL IN bEnable);

	VOID				SetStokePen(LOGPEN* IN lp);
	VOID				SetFillBrush(LOGBRUSH* IN lb);
public:
	virtual VOID		SetShapeCoordinate(ODL_SHAPE_COORD IN coord)=0;
	virtual BOOL		PtInAdjustSizeButton(POINT* IN pt);
	virtual VOID		EnableAdjustSize(BOOL IN bEnable);
	virtual BOOL		IsEnableAdjustSize();
	virtual VOID		EnableDrag(BOOL IN bEnable);

};
