# Microsoft Developer Studio Project File - Name="OpenDL_Demo" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=OpenDL_Demo - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "OpenDL_Demo.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "OpenDL_Demo.mak" CFG="OpenDL_Demo - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "OpenDL_Demo - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "OpenDL_Demo - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName "SAK"
# PROP Scc_LocalPath "SAK"
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "OpenDL_Demo - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\Bin"
# PROP BASE Intermediate_Dir "..\Intermediate\OpenDL_Demo\Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\Bin"
# PROP Intermediate_Dir "..\Intermediate\OpenDL_Demo\Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /Zp1 /MDd /W3 /Gm /GX /ZI /Od /I "../ODL_Publish/Include" /D "WIN32" /D "_WINDOWS" /D "_DEBUG" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /GZ /c
# ADD CPP /nologo /Zp1 /MDd /W3 /Gm /GX /ZI /Od /I "../ODL_Publish/Include" /D "WIN32" /D "_WINDOWS" /D "_DEBUG" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
# ADD BASE RSC /l 0x804 /i "$(IntDir)" /d "_DEBUG"
# ADD RSC /l 0x804 /i "$(IntDir)" /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:IX86 /pdbtype:sept /libpath:"..\ODL_Publish\Lib"
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:IX86 /pdbtype:sept /libpath:"..\ODL_Publish\Lib"
# Begin Special Build Tool
SOURCE="$(InputPath)"
PreLink_Cmds=auto_copy.bat
# End Special Build Tool

!ELSEIF  "$(CFG)" == "OpenDL_Demo - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\Bin"
# PROP BASE Intermediate_Dir "..\Intermediate\OpenDL_Demo\Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\Bin"
# PROP Intermediate_Dir "..\Intermediate\OpenDL_Demo\Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /Zp1 /MD /W3 /GX /Zi /I "../ODL_Publish/Include" /D "WIN32" /D "_WINDOWS" /D "NDEBUG" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /Zp1 /MD /W3 /GX /Zi /I "../ODL_Publish/Include" /D "WIN32" /D "_WINDOWS" /D "NDEBUG" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /c
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
# ADD BASE RSC /l 0x804 /i "$(IntDir)" /d "NDEBUG"
# ADD RSC /l 0x804 /i "$(IntDir)" /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:IX86 /pdbtype:sept /libpath:"..\ODL_Publish\Lib" /opt:ref /opt:icf
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:IX86 /pdbtype:sept /libpath:"..\ODL_Publish\Lib" /opt:ref /opt:icf
# Begin Special Build Tool
SOURCE="$(InputPath)"
PreLink_Cmds=auto_copy.bat
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "OpenDL_Demo - Win32 Debug"
# Name "OpenDL_Demo - Win32 Release"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;def;odl;idl;hpj;bat;asm;asmx"
# Begin Source File

SOURCE=.\AbsLocateDlg.cpp
DEP_CPP_ABSLO=\
	"..\ODL_Publish\Include\Base\GlobalDefine.h"\
	"..\ODL_Publish\Include\Base\ODL_ListT.h"\
	"..\ODL_Publish\Include\Base\ODL_ObjBase.h"\
	"..\ODL_Publish\Include\Base\ODL_ObjListBase.h"\
	"..\ODL_Publish\Include\Base\ODL_Vector2f.h"\
	"..\ODL_Publish\Include\Canvas\ODL_Canvasbase.h"\
	"..\ODL_Publish\Include\Canvas\ODL_GDICanvas.h"\
	"..\ODL_Publish\Include\Elements\ODL_ElementBase.h"\
	"..\ODL_Publish\Include\Elements\ODL_OverlayElementBase.h"\
	"..\ODL_Publish\Include\Elements\ODLEx_Element_Button.h"\
	"..\ODL_Publish\Include\Elements\ODLEx_Element_CheckButton.h"\
	"..\ODL_Publish\Include\Elements\ODLEx_Element_Coordinate.h"\
	"..\ODL_Publish\Include\Elements\ODLEx_Element_CrossLine.h"\
	"..\ODL_Publish\Include\Elements\ODLEx_Element_CurveBase.h"\
	"..\ODL_Publish\Include\Elements\ODLEx_Element_DefaultToolbar.h"\
	"..\ODL_Publish\Include\Elements\ODLEx_Element_Histogram.h"\
	"..\ODL_Publish\Include\Elements\ODLEx_Element_Label.h"\
	"..\ODL_Publish\Include\Elements\ODLEx_Element_TextArea.h"\
	"..\ODL_Publish\Include\Elements\ODLEx_Element_Toolbar.h"\
	"..\ODL_Publish\Include\Elements\ODLEx_Element_ZoomFrame.h"\
	"..\ODL_Publish\Include\ODL_Include.h"\
	"..\ODL_Publish\Include\OpenDL.h"\
	"..\ODL_Publish\Include\Painter\ODL_Painter.h"\
	"..\ODL_Publish\Include\Resource\ODL_Brush.h"\
	"..\ODL_Publish\Include\Resource\ODL_Font.h"\
	"..\ODL_Publish\Include\Resource\ODL_Pen.h"\
	"..\ODL_Publish\Include\Resource\ODL_ResourceManager.h"\
	"..\ODL_Publish\Include\Tools\ODL_Tools.h"\
	"..\ODL_Publish\Include\View\ODL_View.h"\
	"..\ODL_Publish\Include\View\ODL_ViewBase.h"\
	".\AbsLocateDlg.h"\
	".\OpenDL_Demo.h"\
	".\stdafx.h"\
	
# End Source File
# Begin Source File

SOURCE=.\CurveDlg.cpp
DEP_CPP_CURVE=\
	"..\ODL_Publish\Include\Base\GlobalDefine.h"\
	"..\ODL_Publish\Include\Base\ODL_ListT.h"\
	"..\ODL_Publish\Include\Base\ODL_ObjBase.h"\
	"..\ODL_Publish\Include\Base\ODL_ObjListBase.h"\
	"..\ODL_Publish\Include\Base\ODL_Vector2f.h"\
	"..\ODL_Publish\Include\Canvas\ODL_Canvasbase.h"\
	"..\ODL_Publish\Include\Canvas\ODL_GDICanvas.h"\
	"..\ODL_Publish\Include\Elements\ODL_ElementBase.h"\
	"..\ODL_Publish\Include\Elements\ODL_OverlayElementBase.h"\
	"..\ODL_Publish\Include\Elements\ODLEx_Element_Button.h"\
	"..\ODL_Publish\Include\Elements\ODLEx_Element_CheckButton.h"\
	"..\ODL_Publish\Include\Elements\ODLEx_Element_Coordinate.h"\
	"..\ODL_Publish\Include\Elements\ODLEx_Element_CrossLine.h"\
	"..\ODL_Publish\Include\Elements\ODLEx_Element_CurveBase.h"\
	"..\ODL_Publish\Include\Elements\ODLEx_Element_DefaultToolbar.h"\
	"..\ODL_Publish\Include\Elements\ODLEx_Element_Histogram.h"\
	"..\ODL_Publish\Include\Elements\ODLEx_Element_Label.h"\
	"..\ODL_Publish\Include\Elements\ODLEx_Element_TextArea.h"\
	"..\ODL_Publish\Include\Elements\ODLEx_Element_Toolbar.h"\
	"..\ODL_Publish\Include\Elements\ODLEx_Element_ZoomFrame.h"\
	"..\ODL_Publish\Include\ODL_Include.h"\
	"..\ODL_Publish\Include\OpenDL.h"\
	"..\ODL_Publish\Include\Painter\ODL_Painter.h"\
	"..\ODL_Publish\Include\Resource\ODL_Brush.h"\
	"..\ODL_Publish\Include\Resource\ODL_Font.h"\
	"..\ODL_Publish\Include\Resource\ODL_Pen.h"\
	"..\ODL_Publish\Include\Resource\ODL_ResourceManager.h"\
	"..\ODL_Publish\Include\Tools\ODL_Tools.h"\
	"..\ODL_Publish\Include\View\ODL_View.h"\
	"..\ODL_Publish\Include\View\ODL_ViewBase.h"\
	".\CurveDlg.h"\
	".\OpenDL_Demo.h"\
	".\stdafx.h"\
	
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
DEP_CPP_MAINF=\
	"..\ODL_Publish\Include\Base\GlobalDefine.h"\
	"..\ODL_Publish\Include\Base\ODL_ListT.h"\
	"..\ODL_Publish\Include\Base\ODL_ObjBase.h"\
	"..\ODL_Publish\Include\Base\ODL_ObjListBase.h"\
	"..\ODL_Publish\Include\Base\ODL_Vector2f.h"\
	"..\ODL_Publish\Include\Canvas\ODL_Canvasbase.h"\
	"..\ODL_Publish\Include\Canvas\ODL_GDICanvas.h"\
	"..\ODL_Publish\Include\Elements\ODL_ElementBase.h"\
	"..\ODL_Publish\Include\Elements\ODL_OverlayElementBase.h"\
	"..\ODL_Publish\Include\Elements\ODLEx_Element_Button.h"\
	"..\ODL_Publish\Include\Elements\ODLEx_Element_CheckButton.h"\
	"..\ODL_Publish\Include\Elements\ODLEx_Element_Coordinate.h"\
	"..\ODL_Publish\Include\Elements\ODLEx_Element_CrossLine.h"\
	"..\ODL_Publish\Include\Elements\ODLEx_Element_CurveBase.h"\
	"..\ODL_Publish\Include\Elements\ODLEx_Element_DefaultToolbar.h"\
	"..\ODL_Publish\Include\Elements\ODLEx_Element_Histogram.h"\
	"..\ODL_Publish\Include\Elements\ODLEx_Element_Label.h"\
	"..\ODL_Publish\Include\Elements\ODLEx_Element_TextArea.h"\
	"..\ODL_Publish\Include\Elements\ODLEx_Element_Toolbar.h"\
	"..\ODL_Publish\Include\Elements\ODLEx_Element_ZoomFrame.h"\
	"..\ODL_Publish\Include\ODL_Include.h"\
	"..\ODL_Publish\Include\OpenDL.h"\
	"..\ODL_Publish\Include\Painter\ODL_Painter.h"\
	"..\ODL_Publish\Include\Resource\ODL_Brush.h"\
	"..\ODL_Publish\Include\Resource\ODL_Font.h"\
	"..\ODL_Publish\Include\Resource\ODL_Pen.h"\
	"..\ODL_Publish\Include\Resource\ODL_ResourceManager.h"\
	"..\ODL_Publish\Include\Tools\ODL_Tools.h"\
	"..\ODL_Publish\Include\View\ODL_View.h"\
	"..\ODL_Publish\Include\View\ODL_ViewBase.h"\
	".\MainFrm.h"\
	".\OpenDL_Demo.h"\
	".\stdafx.h"\
	
# End Source File
# Begin Source File

SOURCE=.\OpenDL_Demo.cpp
DEP_CPP_OPEND=\
	"..\ODL_Publish\Include\Base\GlobalDefine.h"\
	"..\ODL_Publish\Include\Base\ODL_ListT.h"\
	"..\ODL_Publish\Include\Base\ODL_ObjBase.h"\
	"..\ODL_Publish\Include\Base\ODL_ObjListBase.h"\
	"..\ODL_Publish\Include\Base\ODL_Vector2f.h"\
	"..\ODL_Publish\Include\Canvas\ODL_Canvasbase.h"\
	"..\ODL_Publish\Include\Canvas\ODL_GDICanvas.h"\
	"..\ODL_Publish\Include\Elements\ODL_ElementBase.h"\
	"..\ODL_Publish\Include\Elements\ODL_OverlayElementBase.h"\
	"..\ODL_Publish\Include\Elements\ODLEx_Element_Button.h"\
	"..\ODL_Publish\Include\Elements\ODLEx_Element_CheckButton.h"\
	"..\ODL_Publish\Include\Elements\ODLEx_Element_Coordinate.h"\
	"..\ODL_Publish\Include\Elements\ODLEx_Element_CrossLine.h"\
	"..\ODL_Publish\Include\Elements\ODLEx_Element_CurveBase.h"\
	"..\ODL_Publish\Include\Elements\ODLEx_Element_DefaultToolbar.h"\
	"..\ODL_Publish\Include\Elements\ODLEx_Element_Histogram.h"\
	"..\ODL_Publish\Include\Elements\ODLEx_Element_Label.h"\
	"..\ODL_Publish\Include\Elements\ODLEx_Element_TextArea.h"\
	"..\ODL_Publish\Include\Elements\ODLEx_Element_Toolbar.h"\
	"..\ODL_Publish\Include\Elements\ODLEx_Element_ZoomFrame.h"\
	"..\ODL_Publish\Include\ODL_Include.h"\
	"..\ODL_Publish\Include\OpenDL.h"\
	"..\ODL_Publish\Include\Painter\ODL_Painter.h"\
	"..\ODL_Publish\Include\Resource\ODL_Brush.h"\
	"..\ODL_Publish\Include\Resource\ODL_Font.h"\
	"..\ODL_Publish\Include\Resource\ODL_Pen.h"\
	"..\ODL_Publish\Include\Resource\ODL_ResourceManager.h"\
	"..\ODL_Publish\Include\Tools\ODL_Tools.h"\
	"..\ODL_Publish\Include\View\ODL_View.h"\
	"..\ODL_Publish\Include\View\ODL_ViewBase.h"\
	".\CurveDlg.h"\
	".\MainFrm.h"\
	".\OpenDL_Demo.h"\
	".\OpenDL_DemoDoc.h"\
	".\OpenDL_DemoView.h"\
	".\stdafx.h"\
	
# End Source File
# Begin Source File

SOURCE=.\OpenDL_DemoDoc.cpp
DEP_CPP_OPENDL=\
	"..\ODL_Publish\Include\Base\GlobalDefine.h"\
	"..\ODL_Publish\Include\Base\ODL_ListT.h"\
	"..\ODL_Publish\Include\Base\ODL_ObjBase.h"\
	"..\ODL_Publish\Include\Base\ODL_ObjListBase.h"\
	"..\ODL_Publish\Include\Base\ODL_Vector2f.h"\
	"..\ODL_Publish\Include\Canvas\ODL_Canvasbase.h"\
	"..\ODL_Publish\Include\Canvas\ODL_GDICanvas.h"\
	"..\ODL_Publish\Include\Elements\ODL_ElementBase.h"\
	"..\ODL_Publish\Include\Elements\ODL_OverlayElementBase.h"\
	"..\ODL_Publish\Include\Elements\ODLEx_Element_Button.h"\
	"..\ODL_Publish\Include\Elements\ODLEx_Element_CheckButton.h"\
	"..\ODL_Publish\Include\Elements\ODLEx_Element_Coordinate.h"\
	"..\ODL_Publish\Include\Elements\ODLEx_Element_CrossLine.h"\
	"..\ODL_Publish\Include\Elements\ODLEx_Element_CurveBase.h"\
	"..\ODL_Publish\Include\Elements\ODLEx_Element_DefaultToolbar.h"\
	"..\ODL_Publish\Include\Elements\ODLEx_Element_Histogram.h"\
	"..\ODL_Publish\Include\Elements\ODLEx_Element_Label.h"\
	"..\ODL_Publish\Include\Elements\ODLEx_Element_TextArea.h"\
	"..\ODL_Publish\Include\Elements\ODLEx_Element_Toolbar.h"\
	"..\ODL_Publish\Include\Elements\ODLEx_Element_ZoomFrame.h"\
	"..\ODL_Publish\Include\ODL_Include.h"\
	"..\ODL_Publish\Include\OpenDL.h"\
	"..\ODL_Publish\Include\Painter\ODL_Painter.h"\
	"..\ODL_Publish\Include\Resource\ODL_Brush.h"\
	"..\ODL_Publish\Include\Resource\ODL_Font.h"\
	"..\ODL_Publish\Include\Resource\ODL_Pen.h"\
	"..\ODL_Publish\Include\Resource\ODL_ResourceManager.h"\
	"..\ODL_Publish\Include\Tools\ODL_Tools.h"\
	"..\ODL_Publish\Include\View\ODL_View.h"\
	"..\ODL_Publish\Include\View\ODL_ViewBase.h"\
	".\OpenDL_Demo.h"\
	".\OpenDL_DemoDoc.h"\
	".\stdafx.h"\
	
# End Source File
# Begin Source File

SOURCE=.\OpenDL_DemoView.cpp
DEP_CPP_OPENDL_=\
	"..\ODL_Publish\Include\Base\GlobalDefine.h"\
	"..\ODL_Publish\Include\Base\ODL_ListT.h"\
	"..\ODL_Publish\Include\Base\ODL_ObjBase.h"\
	"..\ODL_Publish\Include\Base\ODL_ObjListBase.h"\
	"..\ODL_Publish\Include\Base\ODL_Vector2f.h"\
	"..\ODL_Publish\Include\Canvas\ODL_Canvasbase.h"\
	"..\ODL_Publish\Include\Canvas\ODL_GDICanvas.h"\
	"..\ODL_Publish\Include\Elements\ODL_ElementBase.h"\
	"..\ODL_Publish\Include\Elements\ODL_OverlayElementBase.h"\
	"..\ODL_Publish\Include\Elements\ODLEx_Element_Button.h"\
	"..\ODL_Publish\Include\Elements\ODLEx_Element_CheckButton.h"\
	"..\ODL_Publish\Include\Elements\ODLEx_Element_Coordinate.h"\
	"..\ODL_Publish\Include\Elements\ODLEx_Element_CrossLine.h"\
	"..\ODL_Publish\Include\Elements\ODLEx_Element_CurveBase.h"\
	"..\ODL_Publish\Include\Elements\ODLEx_Element_DefaultToolbar.h"\
	"..\ODL_Publish\Include\Elements\ODLEx_Element_Histogram.h"\
	"..\ODL_Publish\Include\Elements\ODLEx_Element_Label.h"\
	"..\ODL_Publish\Include\Elements\ODLEx_Element_TextArea.h"\
	"..\ODL_Publish\Include\Elements\ODLEx_Element_Toolbar.h"\
	"..\ODL_Publish\Include\Elements\ODLEx_Element_ZoomFrame.h"\
	"..\ODL_Publish\Include\ODL_Include.h"\
	"..\ODL_Publish\Include\OpenDL.h"\
	"..\ODL_Publish\Include\Painter\ODL_Painter.h"\
	"..\ODL_Publish\Include\Resource\ODL_Brush.h"\
	"..\ODL_Publish\Include\Resource\ODL_Font.h"\
	"..\ODL_Publish\Include\Resource\ODL_Pen.h"\
	"..\ODL_Publish\Include\Resource\ODL_ResourceManager.h"\
	"..\ODL_Publish\Include\Tools\ODL_Tools.h"\
	"..\ODL_Publish\Include\View\ODL_View.h"\
	"..\ODL_Publish\Include\View\ODL_ViewBase.h"\
	".\AbsLocateDlg.h"\
	".\CurveDlg.h"\
	".\OpenDL_Demo.h"\
	".\OpenDL_DemoDoc.h"\
	".\OpenDL_DemoView.h"\
	".\stdafx.h"\
	
# End Source File
# Begin Source File

SOURCE=.\stdafx.cpp
DEP_CPP_STDAF=\
	"..\ODL_Publish\Include\Base\GlobalDefine.h"\
	"..\ODL_Publish\Include\Base\ODL_ListT.h"\
	"..\ODL_Publish\Include\Base\ODL_ObjBase.h"\
	"..\ODL_Publish\Include\Base\ODL_ObjListBase.h"\
	"..\ODL_Publish\Include\Base\ODL_Vector2f.h"\
	"..\ODL_Publish\Include\Canvas\ODL_Canvasbase.h"\
	"..\ODL_Publish\Include\Canvas\ODL_GDICanvas.h"\
	"..\ODL_Publish\Include\Elements\ODL_ElementBase.h"\
	"..\ODL_Publish\Include\Elements\ODL_OverlayElementBase.h"\
	"..\ODL_Publish\Include\Elements\ODLEx_Element_Button.h"\
	"..\ODL_Publish\Include\Elements\ODLEx_Element_CheckButton.h"\
	"..\ODL_Publish\Include\Elements\ODLEx_Element_Coordinate.h"\
	"..\ODL_Publish\Include\Elements\ODLEx_Element_CrossLine.h"\
	"..\ODL_Publish\Include\Elements\ODLEx_Element_CurveBase.h"\
	"..\ODL_Publish\Include\Elements\ODLEx_Element_DefaultToolbar.h"\
	"..\ODL_Publish\Include\Elements\ODLEx_Element_Histogram.h"\
	"..\ODL_Publish\Include\Elements\ODLEx_Element_Label.h"\
	"..\ODL_Publish\Include\Elements\ODLEx_Element_TextArea.h"\
	"..\ODL_Publish\Include\Elements\ODLEx_Element_Toolbar.h"\
	"..\ODL_Publish\Include\Elements\ODLEx_Element_ZoomFrame.h"\
	"..\ODL_Publish\Include\ODL_Include.h"\
	"..\ODL_Publish\Include\OpenDL.h"\
	"..\ODL_Publish\Include\Painter\ODL_Painter.h"\
	"..\ODL_Publish\Include\Resource\ODL_Brush.h"\
	"..\ODL_Publish\Include\Resource\ODL_Font.h"\
	"..\ODL_Publish\Include\Resource\ODL_Pen.h"\
	"..\ODL_Publish\Include\Resource\ODL_ResourceManager.h"\
	"..\ODL_Publish\Include\Tools\ODL_Tools.h"\
	"..\ODL_Publish\Include\View\ODL_View.h"\
	"..\ODL_Publish\Include\View\ODL_ViewBase.h"\
	".\stdafx.h"\
	

!IF  "$(CFG)" == "OpenDL_Demo - Win32 Debug"

# ADD CPP /nologo /GX /Yc"stdafx.h" /GZ

!ELSEIF  "$(CFG)" == "OpenDL_Demo - Win32 Release"

# ADD CPP /nologo /GX /Yc"stdafx.h"

!ENDIF 

# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;inc;xsd"
# Begin Source File

SOURCE=.\AbsLocateDlg.h
# End Source File
# Begin Source File

SOURCE=.\CurveDlg.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\OpenDL_Demo.h
# End Source File
# Begin Source File

SOURCE=.\OpenDL_DemoDoc.h
# End Source File
# Begin Source File

SOURCE=.\OpenDL_DemoView.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\stdafx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "rc;ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe;resx"
# Begin Source File

SOURCE=.\res\OpenDL_Demo.ico
# End Source File
# Begin Source File

SOURCE=.\OpenDL_Demo.rc
# End Source File
# Begin Source File

SOURCE=.\res\OpenDL_Demo.rc2
# End Source File
# Begin Source File

SOURCE=.\res\OpenDL_DemoDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\res\OpenDL_Demo.manifest
# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
