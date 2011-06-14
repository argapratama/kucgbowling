# Microsoft Developer Studio Project File - Name="DxRenderer" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=DxRenderer - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "DxRenderer.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "DxRenderer.mak" CFG="DxRenderer - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "DxRenderer - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "DxRenderer - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "DxRenderer - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I ".\\" /I "..\..\Include" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /D "WML_USE_DX" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\..\Library\Release\DX\WmlRenderer.lib"
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=copy *.h ..\..\Include	copy *.inl ..\..\Include
# End Special Build Tool

!ELSEIF  "$(CFG)" == "DxRenderer - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I ".\\" /I "..\..\Include" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /D "WML_USE_DX" /YX /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\..\Library\Debug\DX\WmlRenderer.lib"
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=copy *.h ..\..\Include	copy *.inl ..\..\Include
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "DxRenderer - Win32 Release"
# Name "DxRenderer - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\WmlDxAlphaState.cpp
# End Source File
# Begin Source File

SOURCE=.\WmlDxBumpMap.cpp
# End Source File
# Begin Source File

SOURCE=.\WmlDxCamera.cpp
# End Source File
# Begin Source File

SOURCE=.\WmlDxCullState.cpp
# End Source File
# Begin Source File

SOURCE=.\WmlDxDitherState.cpp
# End Source File
# Begin Source File

SOURCE=.\WmlDxException.cpp
# End Source File
# Begin Source File

SOURCE=.\WmlDxFogState.cpp
# End Source File
# Begin Source File

SOURCE=.\WmlDxGlossMap.cpp
# End Source File
# Begin Source File

SOURCE=.\WmlDxLightState.cpp
# End Source File
# Begin Source File

SOURCE=.\WmlDxMaterialState.cpp
# End Source File
# Begin Source File

SOURCE=.\WmlDxPlanarReflection.cpp
# End Source File
# Begin Source File

SOURCE=.\WmlDxPlanarShadow.cpp
# End Source File
# Begin Source File

SOURCE=.\WmlDxPolygonOffsetState.cpp
# End Source File
# Begin Source File

SOURCE=.\WmlDxProjectedTexture.cpp
# End Source File
# Begin Source File

SOURCE=.\WmlDxRenderer.cpp
# End Source File
# Begin Source File

SOURCE=.\WmlDxShaders.cpp
# End Source File
# Begin Source File

SOURCE=.\WmlDxShadeState.cpp
# End Source File
# Begin Source File

SOURCE=.\WmlDxTextureState.cpp
# End Source File
# Begin Source File

SOURCE=.\WmlDxVertexColorState.cpp
# End Source File
# Begin Source File

SOURCE=.\WmlDxWireframeState.cpp
# End Source File
# Begin Source File

SOURCE=.\WmlDxZBufferState.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h"
# Begin Source File

SOURCE=.\WmlDxCamera.h
# End Source File
# Begin Source File

SOURCE=.\WmlDxException.h
# End Source File
# Begin Source File

SOURCE=.\WmlDxRenderer.h
# End Source File
# Begin Source File

SOURCE=.\WmlDxUtility.h
# End Source File
# Begin Source File

SOURCE=.\WmlRendererLibType.h
# End Source File
# End Group
# Begin Group "Inline Files"

# PROP Default_Filter "inl"
# Begin Source File

SOURCE=.\WmlDxRenderer.inl
# End Source File
# End Group
# End Target
# End Project

