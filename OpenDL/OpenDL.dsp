# Microsoft Developer Studio Project File - Name="OpenDL" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=OpenDL - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "OpenDL.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "OpenDL.mak" CFG="OpenDL - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "OpenDL - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "OpenDL - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/OpenDL/OpenDL", LWAAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "OpenDL - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\..\Intermediate\OpenDL\Release"
# PROP BASE Intermediate_Dir ".\..\Intermediate\OpenDL\Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\..\Intermediate\OpenDL\Release"
# PROP Intermediate_Dir ".\..\Intermediate\OpenDL\Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /Zi /W3 /D "WIN32" /D "_WINDOWS" /D "NDEBUG" /D "_AFXEXT" /D "_WINDLL" /D "_ODL_" /D "_AFXDLL" /D "_MBCS" /Zp1 /Yu"stdafx.h" /Fp"$(IntDir)/$(TargetName).pch" /Fo".\..\Intermediate\OpenDL\Release/" /Fd".\..\Intermediate\OpenDL\Release/" /c /GX 
# ADD CPP /nologo /MD /Zi /W3 /D "WIN32" /D "_WINDOWS" /D "NDEBUG" /D "_AFXEXT" /D "_WINDLL" /D "_ODL_" /D "_AFXDLL" /D "_MBCS" /Zp1 /Yu"stdafx.h" /Fp"$(IntDir)/$(TargetName).pch" /Fo".\..\Intermediate\OpenDL\Release/" /Fd".\..\Intermediate\OpenDL\Release/" /c /GX 
# ADD BASE MTL /nologo /D"NDEBUG" /tlb".\..\Intermediate\OpenDL\Release\OpenDL.tlb" /win32 
# ADD MTL /nologo /D"NDEBUG" /tlb".\..\Intermediate\OpenDL\Release\OpenDL.tlb" /win32 
# ADD BASE RSC /l 2052 /d "NDEBUG" /i "$(IntDir)" 
# ADD RSC /l 2052 /d "NDEBUG" /i "$(IntDir)" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo 
# ADD BSC32 /nologo 
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /out:".\Output\DLL\OpenDL.dll" /incremental:no /debug /pdb:".\Output\DLL\OpenDL.pdb" /pdbtype:sept /subsystem:windows /opt:ref /opt:icf /implib:"./Output/Lib/OpenDL.lib" 
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /out:".\Output\DLL\OpenDL.dll" /incremental:no /debug /pdb:".\Output\DLL\OpenDL.pdb" /pdbtype:sept /subsystem:windows /opt:ref /opt:icf /implib:"./Output/Lib/OpenDL.lib" 
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=auto_copy.bat
# End Special Build Tool

!ELSEIF  "$(CFG)" == "OpenDL - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\..\Intermediate\OpenDL\Debug"
# PROP BASE Intermediate_Dir ".\..\Intermediate\OpenDL\Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\..\Intermediate\OpenDL\Debug"
# PROP Intermediate_Dir ".\..\Intermediate\OpenDL\Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /ZI /W3 /Od /D "WIN32" /D "_WINDOWS" /D "_DEBUG" /D "_AFXEXT" /D "_WINDLL" /D "_ODL_" /D "_AFXDLL" /D "_MBCS" /Zp1 /Yu"stdafx.h" /Fp".\..\Intermediate\OpenDL\Debug/OpenDL.pch" /Fo".\..\Intermediate\OpenDL\Debug/" /Fd".\..\Intermediate\OpenDL\Debug/" /FR /GZ /c /GX 
# ADD CPP /nologo /MDd /ZI /W3 /Od /D "WIN32" /D "_WINDOWS" /D "_DEBUG" /D "_AFXEXT" /D "_WINDLL" /D "_ODL_" /D "_AFXDLL" /D "_MBCS" /Zp1 /Yu"stdafx.h" /Fp".\..\Intermediate\OpenDL\Debug/OpenDL.pch" /Fo".\..\Intermediate\OpenDL\Debug/" /Fd".\..\Intermediate\OpenDL\Debug/" /FR /GZ /c /GX 
# ADD BASE MTL /nologo /D"_DEBUG" /tlb".\..\Intermediate\OpenDL\Debug\OpenDL.tlb" /win32 
# ADD MTL /nologo /D"_DEBUG" /tlb".\..\Intermediate\OpenDL\Debug\OpenDL.tlb" /win32 
# ADD BASE RSC /l 2052 /d "_DEBUG" /i "$(IntDir)" 
# ADD RSC /l 2052 /d "_DEBUG" /i "$(IntDir)" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo 
# ADD BSC32 /nologo 
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /out:".\Output\DLL\OpenDL_D.dll" /incremental:no /debug /pdb:".\Output\DLL\OpenDL_D.pdb" /pdbtype:sept /subsystem:windows /implib:"./Output/Lib/OpenDL_D.lib" 
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /out:".\Output\DLL\OpenDL_D.dll" /incremental:no /debug /pdb:".\Output\DLL\OpenDL_D.pdb" /pdbtype:sept /subsystem:windows /implib:"./Output/Lib/OpenDL_D.lib" 
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=auto_copy.bat
# End Special Build Tool

!ENDIF

# Begin Target

# Name "OpenDL - Win32 Release"
# Name "OpenDL - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;def;odl;idl;hpj;bat;asm;asmx"
# Begin Source File

SOURCE=Support\MemoryPool.cpp

!IF  "$(CFG)" == "OpenDL - Win32 Debug"

# ADD CPP /nologo /Od /Yu"stdafx.h" /FR /GZ /GX 
!ENDIF

# End Source File
# Begin Source File

SOURCE=Resource\ODL_Brush.cpp

!IF  "$(CFG)" == "OpenDL - Win32 Debug"

# ADD CPP /nologo /Od /Yu"stdafx.h" /FR /GZ /GX 
!ENDIF

# End Source File
# Begin Source File

SOURCE=Canvas\ODL_CanvasBase.cpp

!IF  "$(CFG)" == "OpenDL - Win32 Debug"

# ADD CPP /nologo /Od /Yu"stdafx.h" /FR /GZ /GX 
!ENDIF

# End Source File
# Begin Source File

SOURCE=Elements\ODL_ElementBase.cpp

!IF  "$(CFG)" == "OpenDL - Win32 Debug"

# ADD CPP /nologo /Od /Yu"stdafx.h" /FR /GZ /GX 
!ENDIF

# End Source File
# Begin Source File

SOURCE=Resource\ODL_Font.cpp

!IF  "$(CFG)" == "OpenDL - Win32 Debug"

# ADD CPP /nologo /Od /Yu"stdafx.h" /FR /GZ /GX 
!ENDIF

# End Source File
# Begin Source File

SOURCE=Canvas\ODL_GDICanvas.cpp

!IF  "$(CFG)" == "OpenDL - Win32 Debug"

# ADD CPP /nologo /Od /Yu"stdafx.h" /FR /GZ /GX 
!ENDIF

# End Source File
# Begin Source File

SOURCE=Painter\ODL_GDIPainter.cpp

!IF  "$(CFG)" == "OpenDL - Win32 Debug"

# ADD CPP /nologo /Od /Yu"stdafx.h" /FR /GZ /GX 
!ENDIF

# End Source File
# Begin Source File

SOURCE=Base\ODL_ObjBase.cpp

!IF  "$(CFG)" == "OpenDL - Win32 Debug"

# ADD CPP /nologo /Od /Yu"stdafx.h" /FR /GZ /GX 
!ENDIF

# End Source File
# Begin Source File

SOURCE=Base\ODL_ObjListBase.cpp

!IF  "$(CFG)" == "OpenDL - Win32 Debug"

# ADD CPP /nologo /Od /Yu"stdafx.h" /FR /GZ /GX 
!ENDIF

# End Source File
# Begin Source File

SOURCE=Elements\ODL_OverlayElementBase.cpp

!IF  "$(CFG)" == "OpenDL - Win32 Debug"

# ADD CPP /nologo /Od /Yu"stdafx.h" /FR /GZ /GX 
!ENDIF

# End Source File
# Begin Source File

SOURCE=Painter\ODL_Painter.cpp

!IF  "$(CFG)" == "OpenDL - Win32 Debug"

# ADD CPP /nologo /Od /Yu"stdafx.h" /FR /GZ /GX 
!ENDIF

# End Source File
# Begin Source File

SOURCE=Resource\ODL_Pen.cpp

!IF  "$(CFG)" == "OpenDL - Win32 Debug"

# ADD CPP /nologo /Od /Yu"stdafx.h" /FR /GZ /GX 
!ENDIF

# End Source File
# Begin Source File

SOURCE=Resource\ODL_ResourceManager.cpp

!IF  "$(CFG)" == "OpenDL - Win32 Debug"

# ADD CPP /nologo /Od /Yu"stdafx.h" /FR /GZ /GX 
!ENDIF

# End Source File
# Begin Source File

SOURCE=Tools\ODL_Tools.cpp

!IF  "$(CFG)" == "OpenDL - Win32 Debug"

# ADD CPP /nologo /Od /Yu"stdafx.h" /FR /GZ /GX 
!ENDIF

# End Source File
# Begin Source File

SOURCE=Base\ODL_Vector2f.cpp

!IF  "$(CFG)" == "OpenDL - Win32 Debug"

# ADD CPP /nologo /Od /Yu"stdafx.h" /FR /GZ /GX 
!ENDIF

# End Source File
# Begin Source File

SOURCE=View\ODL_View.cpp

!IF  "$(CFG)" == "OpenDL - Win32 Debug"

# ADD CPP /nologo /Od /Yu"stdafx.h" /FR /GZ /GX 
!ENDIF

# End Source File
# Begin Source File

SOURCE=View\ODL_ViewBase.cpp

!IF  "$(CFG)" == "OpenDL - Win32 Debug"

# ADD CPP /nologo /Od /Yu"stdafx.h" /FR /GZ /GX 
!ENDIF

# End Source File
# Begin Source File

SOURCE=OpenDL.cpp

!IF  "$(CFG)" == "OpenDL - Win32 Debug"

# ADD CPP /nologo /Od /Yu"stdafx.h" /FR /GZ /GX 
!ENDIF

# End Source File
# Begin Source File

SOURCE=stdafx.cpp

!IF  "$(CFG)" == "OpenDL - Win32 Release"

# ADD CPP /nologo /Yc"stdafx.h" /GX 
!ELSEIF  "$(CFG)" == "OpenDL - Win32 Debug"

# ADD CPP /nologo /Od /Yc"stdafx.h" /FR /GZ /GX 
!ENDIF

# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;inc;xsd"
# Begin Source File

SOURCE=Base\GlobalDefine.h
# End Source File
# Begin Source File

SOURCE=Support\MemoryPool.h
# End Source File
# Begin Source File

SOURCE=Resource\ODL_Brush.h
# End Source File
# Begin Source File

SOURCE=Canvas\ODL_CanvasBase.h
# End Source File
# Begin Source File

SOURCE=Elements\ODL_ElementBase.h
# End Source File
# Begin Source File

SOURCE=Resource\ODL_Font.h
# End Source File
# Begin Source File

SOURCE=Canvas\ODL_GDICanvas.h
# End Source File
# Begin Source File

SOURCE=Painter\ODL_GDIPainter.h
# End Source File
# Begin Source File

SOURCE=ODL_Include.h
# End Source File
# Begin Source File

SOURCE=Base\ODL_ListT.h
# End Source File
# Begin Source File

SOURCE=Base\ODL_ObjBase.h
# End Source File
# Begin Source File

SOURCE=Base\ODL_ObjListBase.h
# End Source File
# Begin Source File

SOURCE=Elements\ODL_OverlayElementBase.h
# End Source File
# Begin Source File

SOURCE=Painter\ODL_Painter.h
# End Source File
# Begin Source File

SOURCE=Resource\ODL_Pen.h
# End Source File
# Begin Source File

SOURCE=Resource\ODL_ResourceManager.h
# End Source File
# Begin Source File

SOURCE=Tools\ODL_Tools.h
# End Source File
# Begin Source File

SOURCE=Base\ODL_Vector2f.h
# End Source File
# Begin Source File

SOURCE=View\ODL_View.h
# End Source File
# Begin Source File

SOURCE=View\ODL_ViewBase.h
# End Source File
# Begin Source File

SOURCE=Resource.h
# End Source File
# Begin Source File

SOURCE=stdafx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "rc;ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe;resx"
# Begin Source File

SOURCE=OpenDL.rc

!IF  "$(CFG)" == "OpenDL - Win32 Release"

# ADD RSC /l 1033 /d "NDEBUG" 
!ELSEIF  "$(CFG)" == "OpenDL - Win32 Debug"

# ADD RSC /l 1033 /d "_DEBUG" 
!ENDIF

# End Source File
# Begin Source File

SOURCE=res\OpenDL.rc2
# End Source File
# End Group
# Begin Source File

SOURCE=ReadMe.txt
# End Source File
# End Target
# End Project

