#pragma			once
/********************************************************************\
	filename: 	G:\LIBO\projects\OpenDL\OpenDL\Base\GlobalDefine.h
	created:	2012/02/21
	author:		LB
	purpose:	ȫ�ֶ���
\*********************************************************************/





#define			ODL_SafeDelete(p)			{if(p!=NULL){delete p;p=NULL;}}
#define			ODL_SafeDeleteArray(p)		{if(p!=NULL){delete []p;p=NULL;}}
#define			ODL_SafeRelease(p)			{if(p!=NULL){p->Release();p=NULL;}}
#define			ODL_SafeDeleteGDIObj(p)		{if(p!=NULL){DeleteObject(p);p=NULL;}}
#define			D3DGetAValue(d3dCOLOR)				( (0xFF000000 & (d3dCOLOR))>>24 )
#define			D3DGetColorValue(d3dCOLOR)			(  RGB( (0x00FF0000&(d3dCOLOR))>>16 ,(0x0000FF00&(d3dCOLOR))>>8,(0x000000FF&(d3dCOLOR)) ) )
#define			D3DCOLOR_ACOLOR(alpha,rgbCOLOR)		(D3DCOLOR_ARGB( (alpha),GetRValue(rgbCOLOR),GetGValue(rgbCOLOR),GetBValue(rgbCOLOR) ) )


typedef enum _CANVAS_TYPE
{//��������

	CANVAS_BASE			=0,	//��������
	CANVAS_D3D,				//D3D����
	CANVAS_GDI,				//GDI����

	//--------------------------------
	CANVAS_TYPE_FORCE_DWORD=0x7fffffff,
}CANVAS_TYPE;
typedef enum _VIEW_TYPE
{//������
	VIEW_BASE			=0,	//�ӻ���,
	VIEW_GENERAL,			//ͨ�õ���
	VIEW_H3,
	//----------------------------------
	VIEW_TYPE_FORCE_DWORD=0x7fffffff,
}VIEW_TYPE;

typedef enum _PAINTER_TYPE
{//��������
	PAINTER_BASE		=0,	//���һ���
	PAINTER_GDI,
	PAINTER_D3D,
	//-----------------------------
	PAINTER_TYPE_FORCE_DWORD=0x7fffffff,
}PAINTER_TYPE;


typedef enum _ODL_ELEMENT_TYPE
{//ͼԪ����
	ODL_ELEMENT_BASE		=0,
	ODL_ELEMENT_OVERLAY_BASE,		//��͸�������
	ODL_ELEMENT_LAYER_BASE,			//�ɹ����ӽڵ�Ĳ����

	//--------------------------------------------
	ODL_ELEMENT_COORD		=1000,	//������ͼԪ
	ODL_ELEMENT_CURVE,				//����
	ODL_ELEMENT_CROSSLINE,			//ʮ����
	ODL_ELEMENT_ZOOMFRAME,			//ѡ���
	ODL_ELEMENT_TOOLBAR,			//������
	ODL_ELEMENT_BUTTON,				//��ť
	ODL_ELEMENT_CHECK_BUTTON,		//��check״̬�İ�ť
	ODL_ELEMENT_DEFAULT_TOOLBAR,	//������
	ODL_ELEMENT_HISTROGRAM,			//��״ͼ
	ODL_ELEMENT_TEXTAREA,			//�ı�����
	ODL_ELEMENT_LABEL,				//����
	ODL_ELEMENT_SAFEAREA,			//��ȫ����
	ODL_ELEMENT_DIAGRAMPREVIEW,		//ͼ��
	ODL_ELEMENT_CURVECASE,			//����ͼ��
	ODL_ELEMENT_REPORT,				//����ؼ�
	ODL_ELEMENT_REPORT_ROW,			//����ؼ��е��пؼ�
	ODL_ELEMENT_REPORT_ITEM,		//����ؼ��е���
	ODL_ELEMENT_CHECKBOX,			//��ѡ��
	ODL_ELEMENT_TIPS,				//��������ʾ
	ODL_ELEMENT_CANVASTITLE,		//�����ı���
	ODL_ELEMENT_COMPASS,			//ָ����
	ODL_ELEMENT_PICTURE,			//ͼƬ
	ODL_ELEMENT_PICTURE_BUTTON,		//ͼƬ��ť
	ODL_ELEMENT_SCROLLBAR,			//������
	ODL_ELEMENT_LEDDIGITAL,			//LED���ֿؼ�
	
	ODL_ELEMENT_SHAPEBASE,			//ʸ������
	ODL_ELEMENT_SHAPE_LINE,			//ʸ����
	ODL_ELEMENT_SHAPE_ELLIPSE,		//ʸ��Բ��
	ODL_ELEMENT_SHAPE_RECTANGLE,	//ʸ������
	ODL_ELEMENT_SHAPE_TRIANGLE,		//ʸ��������
	ODL_ELEMENT_SHAPE_REGION,		//ʸ�����������



	//----------------------------------
	ODL_ELEMENT_USER			=0x10000000,	//�û��Զ���ͼԪ������ʼֵ

	ODL_ELEMENT_FORCE_DWORD=0x7fffffff,
}ODL_ELEMENT_TYPE;

typedef VOID (CALLBACK *BTN_CLICKED_CALLBACK) (DWORD IN dwID,DWORD_PTR IN UserData);
typedef VOID (CALLBACK *SCROLL_CALLBACK) (DWORD IN dwID,DWORD IN dwPosition,DWORD IN dwMaxPosition,DWORD IN dwPageSize,DWORD_PTR IN UserData);

typedef enum _ODL_OPERATION_TYPE
{//��������

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




































