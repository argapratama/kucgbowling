# Microsoft Developer Studio Project File - Name="BasicShader" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=BasicShader - Win32 Debug WGL
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "BasicShader.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "BasicShader.mak" CFG="BasicShader - Win32 Debug WGL"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "BasicShader - Win32 Debug GLUT" (based on "Win32 (x86) Application")
!MESSAGE "BasicShader - Win32 Release GLUT" (based on "Win32 (x86) Application")
!MESSAGE "BasicShader - Win32 Debug DX" (based on "Win32 (x86) Application")
!MESSAGE "BasicShader - Win32 Release DX" (based on "Win32 (x86) Application")
!MESSAGE "BasicShader - Win32 Debug WGL" (based on "Win32 (x86) Application")
!MESSAGE "BasicShader - Win32 Release WGL" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "BasicShader - Win32 Debug GLUT"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug GLUT"
# PROP BASE Intermediate_Dir "Debug GLUT"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug\GLUT"
# PROP Intermediate_Dir "Debug\GLUT"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\..\Include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "WML_USE_GLUT" /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 WmlApplication3.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /entry:"mainCRTStartup" /subsystem:windows /debug /machine:I386 /pdbtype:sept /libpath:"..\..\..\Library\$(OutDir)" /libpath:"..\..\..\Library\Debug"

!ELSEIF  "$(CFG)" == "BasicShader - Win32 Release GLUT"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release GLUT"
# PROP BASE Intermediate_Dir "Release GLUT"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release\GLUT"
# PROP Intermediate_Dir "Release\GLUT"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\..\..\Include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "WML_USE_GLUT" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 WmlApplication3.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /entry:"mainCRTStartup" /subsystem:windows /machine:I386 /libpath:"..\..\..\Library\$(OutDir)" /libpath:"..\..\..\Library\Release"

!ELSEIF  "$(CFG)" == "BasicShader - Win32 Debug DX"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "BasicShader___Win32_Debug_DX"
# PROP BASE Intermediate_Dir "BasicShader___Win32_Debug_DX"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug\DX"
# PROP Intermediate_Dir "Debug\DX"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\..\Include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "WML_USE_GLUT" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\..\Include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "WML_USE_DX" /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 WmlApplication3.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /entry:"mainCRTStartup" /subsystem:windows /debug /machine:I386 /pdbtype:sept /libpath:"..\..\..\Library\$(OutDir)" /libpath:"..\..\..\Library\Debug"
# ADD LINK32 WmlApplication3.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /entry:"" /subsystem:windows /debug /machine:I386 /pdbtype:sept /libpath:"..\..\..\Library\$(OutDir)" /libpath:"..\..\..\Library\Debug"

!ELSEIF  "$(CFG)" == "BasicShader - Win32 Release DX"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "BasicShader___Win32_Release_DX"
# PROP BASE Intermediate_Dir "BasicShader___Win32_Release_DX"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release\DX"
# PROP Intermediate_Dir "Release\DX"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /I "..\..\..\Include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "WML_USE_GLUT" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\..\..\Include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "WML_USE_DX" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 WmlApplication3.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /entry:"mainCRTStartup" /subsystem:windows /machine:I386 /libpath:"..\..\..\Library\$(OutDir)" /libpath:"..\..\..\Library\Release"
# ADD LINK32 WmlApplication3.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /entry:"" /subsystem:windows /machine:I386 /libpath:"..\..\..\Library\$(OutDir)" /libpath:"..\..\..\Library\Release"

!ELSEIF  "$(CFG)" == "BasicShader - Win32 Debug WGL"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "BasicShader___Win32_Debug_WGL"
# PROP BASE Intermediate_Dir "BasicShader___Win32_Debug_WGL"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug\WGL"
# PROP Intermediate_Dir "Debug\WGL"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\..\Include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "WML_USE_DX" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\..\Include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "WML_USE_WGL" /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 WmlApplication3.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /entry:"" /subsystem:windows /debug /machine:I386 /pdbtype:sept /libpath:"..\..\..\Library\$(OutDir)" /libpath:"..\..\..\Library\Debug"
# ADD LINK32 WmlApplication3.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /entry:"" /subsystem:windows /debug /machine:I386 /pdbtype:sept /libpath:"..\..\..\Library\$(OutDir)" /libpath:"..\..\..\Library\Debug"

!ELSEIF  "$(CFG)" == "BasicShader - Win32 Release WGL"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "BasicShader___Win32_Release_WGL"
# PROP BASE Intermediate_Dir "BasicShader___Win32_Release_WGL"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release\WGL"
# PROP Intermediate_Dir "Release\WGL"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /I "..\..\..\Include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "WML_USE_DX" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\..\..\Include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "WML_USE_WGL" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 WmlApplication3.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /entry:"" /subsystem:windows /machine:I386 /libpath:"..\..\..\Library\$(OutDir)" /libpath:"..\..\..\Library\Release"
# ADD LINK32 WmlApplication3.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /entry:"" /subsystem:windows /machine:I386 /libpath:"..\..\..\Library\$(OutDir)" /libpath:"..\..\..\Library\Release"

!ENDIF 

# Begin Target

# Name "BasicShader - Win32 Debug GLUT"
# Name "BasicShader - Win32 Release GLUT"
# Name "BasicShader - Win32 Debug DX"
# Name "BasicShader - Win32 Release DX"
# Name "BasicShader - Win32 Debug WGL"
# Name "BasicShader - Win32 Release WGL"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\BasicShader.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\BasicShader.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\BasicShader.cg

!IF  "$(CFG)" == "BasicShader - Win32 Debug GLUT"

# Begin Custom Build
InputPath=.\BasicShader.cg

"BasicShader.wvs;BasicShader.wps" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cgc BasicShader.cg -nocode -profile vs_2_x -entry vmain 
	cgc BasicShader.cg -nocode -profile ps_2_x -entry pmain 
	..\..\..\bin\CgConverter.exe BasicShader.cg -output BasicShader.wvs -vertex 
	..\..\..\bin\CgConverter.exe BasicShader.cg -output BasicShader.wps -pixel 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "BasicShader - Win32 Release GLUT"

# Begin Custom Build
InputPath=.\BasicShader.cg

"BasicShader.wvs;BasicShader.wps" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cgc BasicShader.cg -nocode -profile vs_2_x -entry vmain 
	cgc BasicShader.cg -nocode -profile ps_2_x -entry pmain 
	..\..\..\bin\CgConverter.exe BasicShader.cg -output BasicShader.wvs -vertex 
	..\..\..\bin\CgConverter.exe BasicShader.cg -output BasicShader.wps -pixel 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "BasicShader - Win32 Debug DX"

# Begin Custom Build
InputPath=.\BasicShader.cg

BuildCmds= \
	cgc BasicShader.cg -nocode -profile vs_2_x -entry vmain \
	cgc BasicShader.cg -nocode -profile ps_2_x -entry pmain \
	..\..\..\bin\CgConverter.exe BasicShader.cg -output BasicShader.wvs -vertex \
	..\..\..\bin\CgConverter.exe BasicShader.cg -output BasicShader.wps -pixel \
	

"BasicShader.wvs" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"BasicShader.wps" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "BasicShader - Win32 Release DX"

# Begin Custom Build
InputPath=.\BasicShader.cg

"BasicShader.wvs;BasicShader.wps" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cgc BasicShader.cg -nocode -profile vs_2_x -entry vmain 
	cgc BasicShader.cg -nocode -profile ps_2_x -entry pmain 
	..\..\..\bin\CgConverter.exe BasicShader.cg -output BasicShader.wvs -vertex 
	..\..\..\bin\CgConverter.exe BasicShader.cg -output BasicShader.wps -pixel 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "BasicShader - Win32 Debug WGL"

# Begin Custom Build
InputPath=.\BasicShader.cg

BuildCmds= \
	cgc BasicShader.cg -nocode -profile vs_2_x -entry vmain \
	cgc BasicShader.cg -nocode -profile ps_2_x -entry pmain \
	..\..\..\bin\CgConverter.exe BasicShader.cg -output BasicShader.wvs -vertex \
	..\..\..\bin\CgConverter.exe BasicShader.cg -output BasicShader.wps -pixel \
	

"BasicShader.wvs" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"BasicShader.wps" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "BasicShader - Win32 Release WGL"

# Begin Custom Build
InputPath=.\BasicShader.cg

"BasicShader.wvs;BasicShader.wps" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cgc BasicShader.cg -nocode -profile vs_2_x -entry vmain 
	cgc BasicShader.cg -nocode -profile ps_2_x -entry pmain 
	..\..\..\bin\CgConverter.exe BasicShader.cg -output BasicShader.wvs -vertex 
	..\..\..\bin\CgConverter.exe BasicShader.cg -output BasicShader.wps -pixel 
	
# End Custom Build

!ENDIF 

# End Source File
# End Group
# End Target
# End Project

