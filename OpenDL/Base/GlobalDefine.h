#pragma			once
/********************************************************************\
	filename: 	G:\LIBO\projects\OpenDL\OpenDL\Base\GlobalDefine.h
	created:	2012/02/21
	author:		LB
	purpose:	全局定义
\*********************************************************************/





#define			ODL_SafeDelete(p)			{if(p!=NULL){delete p;p=NULL;}}
#define			ODL_SafeDeleteArray(p)		{if(p!=NULL){delete []p;p=NULL;}}
#define			ODL_SafeRelease(p)			{if(p!=NULL){p->Release();p=NULL;}}
#define			ODL_SafeDeleteGDIObj(p)		{if(p!=NULL){DeleteObject(p);p=NULL;}}
#define			D3DGetAValue(d3dCOLOR)				( (0xFF000000 & (d3dCOLOR))>>24 )
#define			D3DGetColorValue(d3dCOLOR)			(  RGB( (0x00FF0000&(d3dCOLOR))>>16 ,(0x0000FF00&(d3dCOLOR))>>8,(0x000000FF&(d3dCOLOR)) ) )
#define			D3DCOLOR_ACOLOR(alpha,rgbCOLOR)		(D3DCOLOR_ARGB( (alpha),GetRValue(rgbCOLOR),GetGValue(rgbCOLOR),GetBValue(rgbCOLOR) ) )


typedef enum _CANVAS_TYPE
{//画布类型

	CANVAS_BASE			=0,	//画布其类
	CANVAS_D3D,				//D3D画布
	CANVAS_GDI,				//GDI画布

	//--------------------------------
	CANVAS_TYPE_FORCE_DWORD=0x7fffffff,
}CANVAS_TYPE;
typedef enum _VIEW_TYPE
{//视类型
	VIEW_BASE			=0,	//视基类,
	VIEW_GENERAL,			//通用的视
	VIEW_H3,
	//----------------------------------
	VIEW_TYPE_FORCE_DWORD=0x7fffffff,
}VIEW_TYPE;

typedef enum _PAINTER_TYPE
{//画家类型
	PAINTER_BASE		=0,	//画家基类
	PAINTER_GDI,
	PAINTER_D3D,
	//-----------------------------
	PAINTER_TYPE_FORCE_DWORD=0x7fffffff,
}PAINTER_TYPE;


typedef enum _ODL_ELEMENT_TYPE
{//图元类型
	ODL_ELEMENT_BASE		=0,
	ODL_ELEMENT_OVERLAY_BASE,		//可透明层基类
	ODL_ELEMENT_LAYER_BASE,			//可管理子节点的层基类

	//--------------------------------------------
	ODL_ELEMENT_COORD		=1000,	//坐标轴图元
	ODL_ELEMENT_CURVE,				//曲线
	ODL_ELEMENT_CROSSLINE,			//十字线
	ODL_ELEMENT_ZOOMFRAME,			//选择框
	ODL_ELEMENT_TOOLBAR,			//工具条
	ODL_ELEMENT_BUTTON,				//按钮
	ODL_ELEMENT_CHECK_BUTTON,		//有check状态的按钮
	ODL_ELEMENT_DEFAULT_TOOLBAR,	//工具条
	ODL_ELEMENT_HISTROGRAM,			//柱状图
	ODL_ELEMENT_TEXTAREA,			//文本区域
	ODL_ELEMENT_LABEL,				//标牌
	ODL_ELEMENT_SAFEAREA,			//安全区域
	ODL_ELEMENT_DIAGRAMPREVIEW,		//图例
	ODL_ELEMENT_CURVECASE,			//曲线图例
	ODL_ELEMENT_REPORT,				//报表控件
	ODL_ELEMENT_REPORT_ROW,			//报表控件中的行控件
	ODL_ELEMENT_REPORT_ITEM,		//报表控件中的项
	ODL_ELEMENT_CHECKBOX,			//复选框
	ODL_ELEMENT_TIPS,				//工具条提示
	ODL_ELEMENT_CANVASTITLE,		//画布的标题
	ODL_ELEMENT_COMPASS,			//指北针
	ODL_ELEMENT_PICTURE,			//图片
	ODL_ELEMENT_PICTURE_BUTTON,		//图片按钮
	ODL_ELEMENT_SCROLLBAR,			//滚动条
	ODL_ELEMENT_LEDDIGITAL,			//LED数字控件
	
	ODL_ELEMENT_SHAPEBASE,			//矢量基类
	ODL_ELEMENT_SHAPE_LINE,			//矢量线
	ODL_ELEMENT_SHAPE_ELLIPSE,		//矢量圆形
	ODL_ELEMENT_SHAPE_RECTANGLE,	//矢量矩形
	ODL_ELEMENT_SHAPE_TRIANGLE,		//矢量三角形
	ODL_ELEMENT_SHAPE_REGION,		//矢量多边形区域



	//----------------------------------
	ODL_ELEMENT_USER			=0x10000000,	//用户自定义图元类型起始值

	ODL_ELEMENT_FORCE_DWORD=0x7fffffff,
}ODL_ELEMENT_TYPE;

typedef VOID (CALLBACK *BTN_CLICKED_CALLBACK) (DWORD IN dwID,DWORD_PTR IN UserData);
typedef VOID (CALLBACK *SCROLL_CALLBACK) (DWORD IN dwID,DWORD IN dwPosition,DWORD IN dwMaxPosition,DWORD IN dwPageSize,DWORD_PTR IN UserData);

typedef enum _ODL_OPERATION_TYPE
{//操作类型

	ODL_OPER_NONE			=0,

	ODL_OPER_DRAG_AXIS,
	ODL_OPER_DRAG_AXIS_X,
	ODL_OPER_DRAG_AXIS_Y,
	ODL_OPER_DRAG_DIAGRAM,
	ODL_OPER_SCALE_AXIS,
	ODL_OPER_SCALE_AXIS_X,
	ODL_OPER_SCALE_AXIS_Y,

	ODL_OPER_DIAGRAM_MOVELEFT,
	ODL_OPER_DIAGRAM_MOVERIGHT,
	ODL_OPER_DIAGRAM_MOVEUP,
	ODL_OPER_DIAGRAM_MOVEDOWN,
	
	ODL_OPER_ENABLE_AUTOSCROLL,
	ODL_OPER_VIEWSTYLE_CASCADE,

	//----------------------------------
	ODL_OPERATION_TYPE_FORCE_DWORD=0x7fffffff,
}ODL_OPERATION_TYPE;











//-------------------------------------------------------------
#ifdef _ODL_
	#define ODL_EXPORT			__declspec(dllexport)
#else
	#define ODL_EXPORT			__declspec(dllimport)
#endif
//-------------------------------------------------------------

//-------------------------------------------------------------
#ifdef _ODL_EX
#define ODLEX_EXPORT			__declspec(dllexport)
#else
#define ODLEX_EXPORT			__declspec(dllimport)
#endif
//-------------------------------------------------------------




































