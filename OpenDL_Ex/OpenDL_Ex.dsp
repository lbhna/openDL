# Microsoft Developer Studio Project File - Name="OpenDL_Ex" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=OpenDL_Ex - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "OpenDL_Ex.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "OpenDL_Ex.mak" CFG="OpenDL_Ex - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "OpenDL_Ex - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "OpenDL_Ex - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/OpenDL/OpenDL_Ex", BBBAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "OpenDL_Ex - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\..\Intermediate\OpenDL_Ex\Debug"
# PROP BASE Intermediate_Dir ".\..\Intermediate\OpenDL_Ex\Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\..\Intermediate\OpenDL_Ex\Debug"
# PROP Intermediate_Dir ".\..\Intermediate\OpenDL_Ex\Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /I "..\OpenDL\Output\Include" /ZI /W3 /Od /D "WIN32" /D "_WINDOWS" /D "_DEBUG" /D "_AFXEXT" /D "_WINDLL" /D "_ODL_EX" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /Fp".\..\Intermediate\OpenDL_Ex\Debug/OpenDL_Ex.pch" /Fo".\..\Intermediate\OpenDL_Ex\Debug/" /Fd".\..\Intermediate\OpenDL_Ex\Debug/" /GZ /c /GX 
# ADD CPP /nologo /MDd /I "..\OpenDL\Output\Include" /ZI /W3 /Od /D "WIN32" /D "_WINDOWS" /D "_DEBUG" /D "_AFXEXT" /D "_WINDLL" /D "_ODL_EX" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /Fp".\..\Intermediate\OpenDL_Ex\Debug/OpenDL_Ex.pch" /Fo".\..\Intermediate\OpenDL_Ex\Debug/" /Fd".\..\Intermediate\OpenDL_Ex\Debug/" /GZ /c /GX 
# ADD BASE MTL /nologo /D"_DEBUG" /tlb".\..\Intermediate\OpenDL_Ex\Debug\OpenDL_Ex.tlb" /win32 
# ADD MTL /nologo /D"_DEBUG" /tlb".\..\Intermediate\OpenDL_Ex\Debug\OpenDL_Ex.tlb" /win32 
# ADD BASE RSC /l 2052 /d "_DEBUG" /i "$(IntDir)" 
# ADD RSC /l 2052 /d "_DEBUG" /i "$(IntDir)" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo 
# ADD BSC32 /nologo 
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /out:".\Output\DLL\OpenDL_Ex_d.dll" /incremental:no /libpath:"../OpenDL/Output/lib" /debug /pdb:".\..\Intermediate\OpenDL_Ex\Debug\OpenDL_Ex_d.pdb" /pdbtype:sept /subsystem:windows /implib:"./Output/Lib/OpenDL_Ex_d.lib" 
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /out:".\Output\DLL\OpenDL_Ex_d.dll" /incremental:no /libpath:"../OpenDL/Output/lib" /debug /pdb:".\..\Intermediate\OpenDL_Ex\Debug\OpenDL_Ex_d.pdb" /pdbtype:sept /subsystem:windows /implib:"./Output/Lib/OpenDL_Ex_d.lib" 
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=auto_copy.bat
# End Special Build Tool

!ELSEIF  "$(CFG)" == "OpenDL_Ex - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\..\Intermediate\OpenDL_Ex\Release"
# PROP BASE Intermediate_Dir ".\..\Intermediate\OpenDL_Ex\Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\..\Intermediate\OpenDL_Ex\Release"
# PROP Intermediate_Dir ".\..\Intermediate\OpenDL_Ex\Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /I "..\OpenDL\Output\Include" /Zi /W3 /D "WIN32" /D "_WINDOWS" /D "NDEBUG" /D "_AFXEXT" /D "_WINDLL" /D "_ODL_EX" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /Fp".\..\Intermediate\OpenDL_Ex\Release/OpenDL_Ex.pch" /Fo".\..\Intermediate\OpenDL_Ex\Release/" /Fd".\..\Intermediate\OpenDL_Ex\Release/" /FR /c /GX 
# ADD CPP /nologo /MD /I "..\OpenDL\Output\Include" /Zi /W3 /D "WIN32" /D "_WINDOWS" /D "NDEBUG" /D "_AFXEXT" /D "_WINDLL" /D "_ODL_EX" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /Fp".\..\Intermediate\OpenDL_Ex\Release/OpenDL_Ex.pch" /Fo".\..\Intermediate\OpenDL_Ex\Release/" /Fd".\..\Intermediate\OpenDL_Ex\Release/" /FR /c /GX 
# ADD BASE MTL /nologo /D"NDEBUG" /tlb".\..\Intermediate\OpenDL_Ex\Release\OpenDL_Ex.tlb" /win32 
# ADD MTL /nologo /D"NDEBUG" /tlb".\..\Intermediate\OpenDL_Ex\Release\OpenDL_Ex.tlb" /win32 
# ADD BASE RSC /l 2052 /d "NDEBUG" /i "$(IntDir)" 
# ADD RSC /l 2052 /d "NDEBUG" /i "$(IntDir)" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo 
# ADD BSC32 /nologo 
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /out:".\Output\DLL\OpenDL_Ex.dll" /incremental:no /libpath:"../OpenDL/Output/lib" /debug /pdb:".\..\Intermediate\OpenDL_Ex\Release\OpenDL_Ex.pdb" /pdbtype:sept /subsystem:windows /opt:ref /opt:icf /implib:"./Output/Lib/OpenDL_Ex.lib" 
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /out:".\Output\DLL\OpenDL_Ex.dll" /incremental:no /libpath:"../OpenDL/Output/lib" /debug /pdb:".\..\Intermediate\OpenDL_Ex\Release\OpenDL_Ex.pdb" /pdbtype:sept /subsystem:windows /opt:ref /opt:icf /implib:"./Output/Lib/OpenDL_Ex.lib" 
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=auto_copy.bat
# End Special Build Tool

!ENDIF

# Begin Target

# Name "OpenDL_Ex - Win32 Debug"
# Name "OpenDL_Ex - Win32 Release"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;def;odl;idl;hpj;bat;asm;asmx"
# Begin Source File

SOURCE=Elements\ODLEx_Element_Button.cpp

!IF  "$(CFG)" == "OpenDL_Ex - Win32 Debug"

# ADD CPP /nologo /Od /Yu"stdafx.h" /GZ /GX 
!ELSEIF  "$(CFG)" == "OpenDL_Ex - Win32 Release"

# ADD CPP /nologo /Yu"stdafx.h" /FR /GX 
!ENDIF

# End Source File
# Begin Source File

SOURCE=.\Elements\ODLEx_Element_CanvasTitle.cpp
# End Source File
# Begin Source File

SOURCE=.\Elements\ODLEx_Element_CheckBox.cpp
# End Source File
# Begin Source File

SOURCE=Elements\ODLEx_Element_CheckButton.cpp

!IF  "$(CFG)" == "OpenDL_Ex - Win32 Debug"

# ADD CPP /nologo /Od /Yu"stdafx.h" /GZ /GX 
!ELSEIF  "$(CFG)" == "OpenDL_Ex - Win32 Release"

# ADD CPP /nologo /Yu"stdafx.h" /FR /GX 
!ENDIF

# End Source File
# Begin Source File

SOURCE=Elements\ODLEx_Element_Coordinate.cpp

!IF  "$(CFG)" == "OpenDL_Ex - Win32 Debug"

# ADD CPP /nologo /Od /Yu"stdafx.h" /GZ /GX 
!ELSEIF  "$(CFG)" == "OpenDL_Ex - Win32 Release"

# ADD CPP /nologo /Yu"stdafx.h" /FR /GX 
!ENDIF

# End Source File
# Begin Source File

SOURCE=Elements\ODLEx_Element_CrossLine.cpp

!IF  "$(CFG)" == "OpenDL_Ex - Win32 Debug"

# ADD CPP /nologo /Od /Yu"stdafx.h" /GZ /GX 
!ELSEIF  "$(CFG)" == "OpenDL_Ex - Win32 Release"

# ADD CPP /nologo /Yu"stdafx.h" /FR /GX 
!ENDIF

# End Source File
# Begin Source File

SOURCE=Elements\ODLEx_Element_CurveBase.cpp

!IF  "$(CFG)" == "OpenDL_Ex - Win32 Debug"

# ADD CPP /nologo /Od /Yu"stdafx.h" /GZ /GX 
!ELSEIF  "$(CFG)" == "OpenDL_Ex - Win32 Release"

# ADD CPP /nologo /Yu"stdafx.h" /FR /GX 
!ENDIF

# End Source File
# Begin Source File

SOURCE=.\Elements\ODLEx_Element_CurveCase.cpp
# End Source File
# Begin Source File

SOURCE=Elements\ODLEx_Element_DefaultToolbar.cpp

!IF  "$(CFG)" == "OpenDL_Ex - Win32 Debug"

# ADD CPP /nologo /Od /Yu"stdafx.h" /GZ /GX 
!ELSEIF  "$(CFG)" == "OpenDL_Ex - Win32 Release"

# ADD CPP /nologo /Yu"stdafx.h" /FR /GX 
!ENDIF

# End Source File
# Begin Source File

SOURCE=Elements\ODLEx_Element_DiagramPreview.cpp

!IF  "$(CFG)" == "OpenDL_Ex - Win32 Debug"

# ADD CPP /nologo /Od /Yu"stdafx.h" /GZ /GX 
!ELSEIF  "$(CFG)" == "OpenDL_Ex - Win32 Release"

# ADD CPP /nologo /Yu"stdafx.h" /FR /GX 
!ENDIF

# End Source File
# Begin Source File

SOURCE=Elements\ODLEx_Element_Histogram.cpp

!IF  "$(CFG)" == "OpenDL_Ex - Win32 Debug"

# ADD CPP /nologo /Od /Yu"stdafx.h" /GZ /GX 
!ELSEIF  "$(CFG)" == "OpenDL_Ex - Win32 Release"

# ADD CPP /nologo /Yu"stdafx.h" /FR /GX 
!ENDIF

# End Source File
# Begin Source File

SOURCE=Elements\ODLEx_Element_Label.cpp

!IF  "$(CFG)" == "OpenDL_Ex - Win32 Debug"

# ADD CPP /nologo /Od /Yu"stdafx.h" /GZ /GX 
!ELSEIF  "$(CFG)" == "OpenDL_Ex - Win32 Release"

# ADD CPP /nologo /Yu"stdafx.h" /FR /GX 
!ENDIF

# End Source File
# Begin Source File

SOURCE=.\Elements\ODLEx_Element_Report.cpp
# End Source File
# Begin Source File

SOURCE=Elements\ODLEx_Element_SafeArea.cpp

!IF  "$(CFG)" == "OpenDL_Ex - Win32 Debug"

# ADD CPP /nologo /Od /Yu"stdafx.h" /GZ /GX 
!ELSEIF  "$(CFG)" == "OpenDL_Ex - Win32 Release"

# ADD CPP /nologo /Yu"stdafx.h" /FR /GX 
!ENDIF

# End Source File
# Begin Source File

SOURCE=Elements\ODLEx_Element_TextArea.cpp

!IF  "$(CFG)" == "OpenDL_Ex - Win32 Debug"

# ADD CPP /nologo /Od /Yu"stdafx.h" /GZ /GX 
!ELSEIF  "$(CFG)" == "OpenDL_Ex - Win32 Release"

# ADD CPP /nologo /Yu"stdafx.h" /FR /GX 
!ENDIF

# End Source File
# Begin Source File

SOURCE=.\Elements\ODLEx_Element_Tips.cpp
# End Source File
# Begin Source File

SOURCE=Elements\ODLEx_Element_Toolbar.cpp

!IF  "$(CFG)" == "OpenDL_Ex - Win32 Debug"

# ADD CPP /nologo /Od /Yu"stdafx.h" /GZ /GX 
!ELSEIF  "$(CFG)" == "OpenDL_Ex - Win32 Release"

# ADD CPP /nologo /Yu"stdafx.h" /FR /GX 
!ENDIF

# End Source File
# Begin Source File

SOURCE=Elements\ODLEx_Element_ZoomFrame.cpp

!IF  "$(CFG)" == "OpenDL_Ex - Win32 Debug"

# ADD CPP /nologo /Od /Yu"stdafx.h" /GZ /GX 
!ELSEIF  "$(CFG)" == "OpenDL_Ex - Win32 Release"

# ADD CPP /nologo /Yu"stdafx.h" /FR /GX 
!ENDIF

# End Source File
# Begin Source File

SOURCE=OpenDL_Ex.cpp

!IF  "$(CFG)" == "OpenDL_Ex - Win32 Debug"

# ADD CPP /nologo /Od /Yu"stdafx.h" /GZ /GX 
!ELSEIF  "$(CFG)" == "OpenDL_Ex - Win32 Release"

# ADD CPP /nologo /Yu"stdafx.h" /FR /GX 
!ENDIF

# End Source File
# Begin Source File

SOURCE=ResourceLoader.cpp

!IF  "$(CFG)" == "OpenDL_Ex - Win32 Debug"

# ADD CPP /nologo /Od /Yu"stdafx.h" /GZ /GX 
!ELSEIF  "$(CFG)" == "OpenDL_Ex - Win32 Release"

# ADD CPP /nologo /Yu"stdafx.h" /FR /GX 
!ENDIF

# End Source File
# Begin Source File

SOURCE=stdafx.cpp

!IF  "$(CFG)" == "OpenDL_Ex - Win32 Debug"

# ADD CPP /nologo /Od /Yc"stdafx.h" /GZ /GX 
!ELSEIF  "$(CFG)" == "OpenDL_Ex - Win32 Release"

# ADD CPP /nologo /Yc"stdafx.h" /FR /GX 
!ENDIF

# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;inc;xsd"
# Begin Source File

SOURCE=Elements\ODLEx_Element_Button.h
# End Source File
# Begin Source File

SOURCE=.\Elements\ODLEx_Element_CanvasTitle.h
# End Source File
# Begin Source File

SOURCE=.\Elements\ODLEx_Element_CheckBox.h
# End Source File
# Begin Source File

SOURCE=Elements\ODLEx_Element_CheckButton.h
# End Source File
# Begin Source File

SOURCE=Elements\ODLEx_Element_Coordinate.h
# End Source File
# Begin Source File

SOURCE=Elements\ODLEx_Element_CrossLine.h
# End Source File
# Begin Source File

SOURCE=Elements\ODLEx_Element_CurveBase.h
# End Source File
# Begin Source File

SOURCE=.\Elements\ODLEx_Element_CurveCase.h
# End Source File
# Begin Source File

SOURCE=Elements\ODLEx_Element_DefaultToolbar.h
# End Source File
# Begin Source File

SOURCE=Elements\ODLEx_Element_DiagramPreview.h
# End Source File
# Begin Source File

SOURCE=Elements\ODLEx_Element_Histogram.h
# End Source File
# Begin Source File

SOURCE=Elements\ODLEx_Element_Label.h
# End Source File
# Begin Source File

SOURCE=.\Elements\ODLEx_Element_Report.h
# End Source File
# Begin Source File

SOURCE=Elements\ODLEx_Element_SafeArea.h
# End Source File
# Begin Source File

SOURCE=Elements\ODLEx_Element_TextArea.h
# End Source File
# Begin Source File

SOURCE=.\Elements\ODLEx_Element_Tips.h
# End Source File
# Begin Source File

SOURCE=Elements\ODLEx_Element_Toolbar.h
# End Source File
# Begin Source File

SOURCE=Elements\ODLEx_Element_ZoomFrame.h
# End Source File
# Begin Source File

SOURCE=OpenDL.h
# End Source File
# Begin Source File

SOURCE=Resource.h
# End Source File
# Begin Source File

SOURCE=ResourceLoader.h
# End Source File
# Begin Source File

SOURCE=stdafx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "rc;ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe;resx"
# Begin Source File

SOURCE=res\drag_axi.ico
# End Source File
# Begin Source File

SOURCE=res\ico00001.ico
# End Source File
# Begin Source File

SOURCE=res\ico00002.ico
# End Source File
# Begin Source File

SOURCE=res\ico00003.ico
# End Source File
# Begin Source File

SOURCE=res\ico00004.ico
# End Source File
# Begin Source File

SOURCE=res\ico00005.ico
# End Source File
# Begin Source File

SOURCE=res\ico00006.ico
# End Source File
# Begin Source File

SOURCE=res\ico00007.ico
# End Source File
# Begin Source File

SOURCE=res\ico00008.ico
# End Source File
# Begin Source File

SOURCE=res\ico00009.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00010.ico
# End Source File
# Begin Source File

SOURCE=res\icon1.ico
# End Source File
# Begin Source File

SOURCE=OpenDL_Ex.rc

!IF  "$(CFG)" == "OpenDL_Ex - Win32 Debug"

# ADD RSC /l 1033 /d "_DEBUG" 
!ELSEIF  "$(CFG)" == "OpenDL_Ex - Win32 Release"

# ADD RSC /l 1033 /d "NDEBUG" 
!ENDIF

# End Source File
# Begin Source File

SOURCE=res\OpenDL_Ex.rc2
# End Source File
# End Group
# Begin Source File

SOURCE=ReadMe.txt
# End Source File
# End Target
# End Project

