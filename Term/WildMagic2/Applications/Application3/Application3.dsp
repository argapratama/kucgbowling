# Microsoft Developer Studio Project File - Name="Application3" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=Application3 - Win32 Debug WGL
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Application3.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Application3.mak" CFG="Application3 - Win32 Debug WGL"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Application3 - Win32 Debug GLUT" (based on "Win32 (x86) Static Library")
!MESSAGE "Application3 - Win32 Release GLUT" (based on "Win32 (x86) Static Library")
!MESSAGE "Application3 - Win32 Debug DX" (based on "Win32 (x86) Static Library")
!MESSAGE "Application3 - Win32 Release DX" (based on "Win32 (x86) Static Library")
!MESSAGE "Application3 - Win32 Debug WGL" (based on "Win32 (x86) Static Library")
!MESSAGE "Application3 - Win32 Release WGL" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Application3 - Win32 Debug GLUT"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Application3___Win32_Debug_GLUT"
# PROP BASE Intermediate_Dir "Application3___Win32_Debug_GLUT"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug\GLUT"
# PROP Intermediate_Dir "Debug\GLUT"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I ".\\" /I "..\..\Include" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I ".\\" /I "..\..\Include" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /D "WML_USE_GLUT" /YX /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\Library\Debug\WmlApplication3.lib"
# ADD LIB32 /nologo /out:"..\..\Library\Debug\GLUT\WmlApplication3.lib"
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=copy *.h ..\..\Include	copy *.inl ..\..\Include
# End Special Build Tool

!ELSEIF  "$(CFG)" == "Application3 - Win32 Release GLUT"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Application3___Win32_Release_GLUT"
# PROP BASE Intermediate_Dir "Application3___Win32_Release_GLUT"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release\GLUT"
# PROP Intermediate_Dir "Release\GLUT"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /I ".\\" /I "..\..\Include" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I ".\\" /I "..\..\Include" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /D "WML_USE_GLUT" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\Library\Release\WmlApplication3.lib"
# ADD LIB32 /nologo /out:"..\..\Library\Release\GLUT\WmlApplication3.lib"
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=copy *.h ..\..\Include	copy *.inl ..\..\Include
# End Special Build Tool

!ELSEIF  "$(CFG)" == "Application3 - Win32 Debug DX"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Application3___Win32_Debug_DX"
# PROP BASE Intermediate_Dir "Application3___Win32_Debug_DX"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug\DX"
# PROP Intermediate_Dir "Debug\DX"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I ".\\" /I "..\..\Include" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /D "WML_USE_GLUT" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I ".\\" /I "..\..\Include" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /D "WML_USE_DX" /YX /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\Library\Debug\GLUT\WmlApplication3.lib"
# ADD LIB32 /nologo /out:"..\..\Library\Debug\DX\WmlApplication3.lib"
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=copy *.h ..\..\Include	copy *.inl ..\..\Include
# End Special Build Tool

!ELSEIF  "$(CFG)" == "Application3 - Win32 Release DX"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Application3___Win32_Release_DX"
# PROP BASE Intermediate_Dir "Application3___Win32_Release_DX"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release\DX"
# PROP Intermediate_Dir "Release\DX"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /I ".\\" /I "..\..\Include" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /D "WML_USE_GLUT" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I ".\\" /I "..\..\Include" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /D "WML_USE_DX" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\Library\Release\GLUT\WmlApplication3.lib"
# ADD LIB32 /nologo /out:"..\..\Library\Release\DX\WmlApplication3.lib"
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=copy *.h ..\..\Include	copy *.inl ..\..\Include
# End Special Build Tool

!ELSEIF  "$(CFG)" == "Application3 - Win32 Debug WGL"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Application3___Win32_Debug_WGL"
# PROP BASE Intermediate_Dir "Application3___Win32_Debug_WGL"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug\WGL"
# PROP Intermediate_Dir "Debug\WGL"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I ".\\" /I "..\..\Include" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /D "WML_USE_GLUT" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I ".\\" /I "..\..\Include" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /D "WML_USE_WGL" /YX /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\Library\Debug\GLUT\WmlApplication3.lib"
# ADD LIB32 /nologo /out:"..\..\Library\Debug\WGL\WmlApplication3.lib"
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=copy *.h ..\..\Include	copy *.inl ..\..\Include
# End Special Build Tool

!ELSEIF  "$(CFG)" == "Application3 - Win32 Release WGL"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Application3___Win32_Release_WGL"
# PROP BASE Intermediate_Dir "Application3___Win32_Release_WGL"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release\WGL"
# PROP Intermediate_Dir "Release\WGL"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /I ".\\" /I "..\..\Include" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /D "WML_USE_GLUT" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I ".\\" /I "..\..\Include" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /D "WML_USE_WGL" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\Library\Release\GLUT\WmlApplication3.lib"
# ADD LIB32 /nologo /out:"..\..\Library\Release\WGL\WmlApplication3.lib"
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=copy *.h ..\..\Include	copy *.inl ..\..\Include
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "Application3 - Win32 Debug GLUT"
# Name "Application3 - Win32 Release GLUT"
# Name "Application3 - Win32 Debug DX"
# Name "Application3 - Win32 Release DX"
# Name "Application3 - Win32 Debug WGL"
# Name "Application3 - Win32 Release WGL"
# Begin Group "Source Files"

# PROP Default_Filter "cpp"
# Begin Source File

SOURCE=.\WmlApplication.cpp
# End Source File
# Begin Source File

SOURCE=.\WmlDxApplication.cpp
# End Source File
# Begin Source File

SOURCE=.\WmlGlutApplication.cpp
# End Source File
# Begin Source File

SOURCE=.\WmlWglApplication.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h"
# Begin Source File

SOURCE=.\WmlApplication.h
# End Source File
# End Group
# Begin Group "Inline Files"

# PROP Default_Filter "inl"
# Begin Source File

SOURCE=.\WmlApplication.inl
# End Source File
# End Group
# End Target
# End Project

