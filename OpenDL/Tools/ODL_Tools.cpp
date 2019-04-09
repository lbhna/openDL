#include "StdAfx.h"
#include ".\odl_tools.h"

CODL_Tools::CODL_Tools(void)
{
}

CODL_Tools::~CODL_Tools(void)
{
}



LONG	CODL_Tools::PointInLine(LINE IN *pLine,POINT IN *pPoint)//返回0 ，point在线段上，-1在左，1在右
{
	LONG	a=pPoint->x*(pLine->end.y-pLine->start.y);
	LONG	b=pPoint->y*(pLine->start.x-pLine->end.x);
	LONG	c=(pLine->end.x*pLine->start.y)-(pLine->start.x*pLine->end.y);
	LONG	ret=a+b+c;
	if(ret<0)
		return -1;
	if(ret>0)
		return 1;
	return 0;
}
BOOL	CODL_Tools::IsIntersectRect(LINE IN *pLine,RECT IN *pRect)//判断线是否与矩形相交
{
	POINT	pt1;
	POINT	pt2;
	POINT	pt3;
	POINT	pt4;

	pt1.x=pRect->left;
	pt1.y=pRect->top;
	pt2.x=pRect->right;
	pt2.y=pRect->top;
	pt3.x=pRect->right;
	pt3.y=pRect->bottom;
	pt4.x=pRect->left;
	pt4.y=pRect->bottom;

	LONG	ret1=PointInLine(pLine,&pt1);
	LONG	ret2=PointInLine(pLine,&pt2);
	if(ret1!=ret2)
		return FALSE;

	LONG	ret3=PointInLine(pLine,&pt3);
	if(ret1!=ret3)
		return FALSE;

	LONG	ret4=PointInLine(pLine,&pt4);
	if(ret3!=ret4)
		return FALSE;

	return TRUE;
}

#define AT_LEFT		1
#define AT_RIGHT	2
#define AT_BOTTOM	4
#define AT_TOP		8
inline LONG make_code(RECT IN *pCutRect,ODL_POINT IN *pPoint)
{//编码函数
	LONG	code = 0;

	if(pPoint->x < pCutRect->left)
	{
		code |=AT_LEFT;
	}
	else if(pPoint->x > pCutRect->right)
	{
		code |=AT_RIGHT;
	}

	if(pPoint->y > pCutRect->bottom)
	{
		code |=AT_BOTTOM;
	}
	else if(pPoint->y < pCutRect->top)
	{
		code |=AT_TOP;
	}
	return code;
}
BOOL	CODL_Tools::GetLineIntersectRect(LINE IN OUT *pLine,RECT IN *pCutRect)
{//求出相交后的线段

	POINT	pt1,pt2;
	pt1.x	=pLine->start.x;
	pt1.y	=pLine->start.y;
	pt2.x	=pLine->end.x;
	pt2.y	=pLine->end.y;

	if(PtInRect(pCutRect,pt1)&&PtInRect(pCutRect,pt2))//2个点都在矩形区域内
		return TRUE;

	LONG	code1	=make_code(pCutRect,&pLine->start);
	LONG	code2	=make_code(pCutRect,&pLine->end);
	LONG	code	=0;
	ODL_POINT	pt;

	while(code1!=0||code2!=0)
	{
		if((code1&code2)!=0)//线段在矩形外
			return FALSE;

		code = code1;
		if(code == 0)
			code = code2;

		if((code&AT_LEFT)!=0)
		{//交左边界
			pt.x = pCutRect->left;
			pt.y = pLine->start.y + (int)(float(pLine->end.y - pLine->start.y)*float(pCutRect->left-pLine->start.x)/float(pLine->end.x - pLine->start.x));
		}
		else if((code&AT_RIGHT)!=0)
		{//右边界相交
			pt.x = pCutRect->right;
			pt.y = pLine->start.y + int(float(pLine->end.y - pLine->start.y)*float(pCutRect->right - pLine->start.x)/float(pLine->end.x - pLine->start.x));
		}
		else if((code&AT_BOTTOM) != 0)
		{//与下边界相交
			pt.y = pCutRect->bottom;
			pt.x = pLine->start.x + int(float(pLine->end.x - pLine->start.x) * float(pCutRect->bottom - pLine->start.y)/float(pLine->end.y - pLine->start.y));
		}
		else if((code&AT_TOP)!=0)
		{//与上边界相交
			pt.y = pCutRect->top;
			pt.x = pLine->start.x + int(float(pLine->end.x - pLine->start.x) * float(pCutRect->top - pLine->start.y)/float(pLine->end.y - pLine->start.y));
		}

		if(code == code1)
		{
			pLine->start.x = pt.x;
			pLine->start.y = pt.y;
			code1 = make_code(pCutRect,&pt);
		}
		else
		{
			pLine->end.x = pt.x;
			pLine->end.y = pt.y;
			code2 = make_code(pCutRect,&pt);
		}
	}
	return TRUE;
}
void	CODL_Tools::InsertCutRectPoint(RECT IN *pCutRect,LINE IN *pLine,POINT IN *pPoint,LONG IN OUT &result_count)
{
	if(pLine->start.x==pCutRect->left)
	{
		if(pLine->end.y==pCutRect->top)
		{//矩形左上角
			pPoint[result_count].x=pCutRect->left;
			pPoint[result_count].y=pCutRect->top;
			result_count++;
		}
		else if(pLine->end.y==pCutRect->bottom)
		{
			pPoint[result_count].x=pCutRect->left;
			pPoint[result_count].y=pCutRect->bottom;
			result_count++;
		}
	}
	else if(pLine->start.x==pCutRect->right)
	{
		if(pLine->end.y==pCutRect->top)
		{//矩形左右上角
			pPoint[result_count].x=pCutRect->right;
			pPoint[result_count].y=pCutRect->top;
			result_count++;
		}
		else if(pLine->end.y==pCutRect->bottom)
		{
			pPoint[result_count].x=pCutRect->right;
			pPoint[result_count].y=pCutRect->bottom;
			result_count++;
		}
	}
}
/****************************************************************\
pCutRect 剪裁矩形
pPointArray 线上的点数组，
lPointCount 点个数
pResultPoint 剪裁后的点数组
返回值为 裁剪后点的个数

\****************************************************************/
DWORD	CODL_Tools::RectCutPolyLine(RECT IN *pCutRect,ODL_POINT IN *pPointArray,LONG IN lPointCount,ODL_POINT IN OUT **pResultPoint)
{
	if(pCutRect==NULL||pPointArray==NULL||lPointCount<=1||pResultPoint==NULL)
		return 0;

	LINE		line;
	LONG		result_count	=0;
	ODL_POINT	*pPoint			=new ODL_POINT[lPointCount*2];//交点数量最多为原始点的2倍
	BOOL		bHaveSeperatorPoint =FALSE;
	LONG		start_index			=-1;
	LONG		end_index			=-1;
	*pResultPoint				=pPoint;

	for(LONG i=1;i<lPointCount;i++)
	{
		line.start	=pPointArray[i-1];
		line.end	=pPointArray[i];

		if(!GetLineIntersectRect(&line,pCutRect))//线段与矩形无交点
		{
			bHaveSeperatorPoint =TRUE;
			if(start_index==-1)
				start_index=i-1;
			continue;
		}
		if(bHaveSeperatorPoint)
		{

		}

		bHaveSeperatorPoint =FALSE;
		start_index			=-1;
		pPoint[result_count]=line.start;
		result_count++;
		pPoint[result_count]=line.end;
		result_count++;
	}
	if(start_index!=-1)
	{

	}
	return result_count;
}



VOID	CODL_Tools::AngleToDirect(DOUBLE IN fAngle,CODL_Vector2f& IN OUT vAt,CODL_Vector2f& IN OUT vRight)
{	
	vAt	=CODL_Vector2f(0.0f,1.0f);
	RotateVectorNormal(vAt,fAngle);
	vRight		=vAt;
	RotateVectorNormal(vRight,90.0f);
	vAt			=-vAt;
}
DOUBLE	CODL_Tools::DirectToAngle(CODL_Vector2f IN vAt)
{
	CODL_Vector2f vAxisY(0.0f,1.0f);
	CODL_Vector2f vAxis		=vAt;
	vAxis.Normalize();
	DOUBLE	ret		=acos(vAxis.Dot(vAxisY))/DOUBLE_PI*180.0;
	if(vAxis.x < 0.0f)
		return (360.0f - ret);
	return ret;
}
VOID	CODL_Tools::RotateVectorCoord(CODL_Vector2f& IN OUT vec,DOUBLE IN fAngle)
{
	CODL_Vector2f tmp;
	DOUBLE	v	=fAngle*DOUBLE_PI/180.0;
	tmp.x		=vec.x*cos(v)	+ vec.y*sin(v);
	tmp.y		=-vec.x*sin(v)	+ vec.y*cos(v);
	vec =tmp;
}
VOID	CODL_Tools::RotateVectorNormal(CODL_Vector2f& IN OUT vec,DOUBLE IN fAngle)
{
	RotateVectorCoord(vec,fAngle);
	vec.Normalize();
}


LPWSTR	CODL_Tools::WideChar(LPCSTR IN pStr)
{
	size_t	size		= strlen(pStr);
	int		nLen		= MultiByteToWideChar(_AtlGetConversionACP(), 0, pStr, size,NULL, NULL);
	LPWSTR	bstr		= new WCHAR[nLen+1];
	ZeroMemory(bstr,sizeof(WCHAR)*(nLen+1));
	MultiByteToWideChar(_AtlGetConversionACP(), 0, pStr, strlen(pStr), bstr, nLen);

	return bstr;
}
LPSTR	CODL_Tools::MultiChar(LPCWSTR IN pStr)
{
	size_t	size		= wcslen(pStr);
	int		nLen		= WideCharToMultiByte(_AtlGetConversionACP(), 0, pStr, size,NULL, NULL,NULL,NULL);
	LPSTR	bstr		= new CHAR[nLen+1];
	ZeroMemory(bstr,sizeof(CHAR)*(nLen+1));

	WideCharToMultiByte(_AtlGetConversionACP(), 0, pStr, size, bstr, nLen,NULL,NULL);

	return bstr;
}







