# Microsoft Developer Studio Project File - Name="OpenGLRenderer" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=OpenGLRenderer - Win32 Debug WGL
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "OpenGLRenderer.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "OpenGLRenderer.mak" CFG="OpenGLRenderer - Win32 Debug WGL"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "OpenGLRenderer - Win32 Debug GLUT" (based on "Win32 (x86) Static Library")
!MESSAGE "OpenGLRenderer - Win32 Release GLUT" (based on "Win32 (x86) Static Library")
!MESSAGE "OpenGLRenderer - Win32 Debug WGL" (based on "Win32 (x86) Static Library")
!MESSAGE "OpenGLRenderer - Win32 Release WGL" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "OpenGLRenderer - Win32 Debug GLUT"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug GLUT"
# PROP BASE Intermediate_Dir "Debug GLUT"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug\GLUT"
# PROP Intermediate_Dir "Debug\GLUT"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I ".\\" /I "..\..\Include" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /D "WML_USE_GLUT" /YX /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\..\Library\Debug\GLUT\WmlRenderer.lib"
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=copy *.h ..\..\Include
# End Special Build Tool

!ELSEIF  "$(CFG)" == "OpenGLRenderer - Win32 Release GLUT"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release GLUT"
# PROP BASE Intermediate_Dir "Release GLUT"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release\GLUT"
# PROP Intermediate_Dir "Release\GLUT"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I ".\\" /I "..\..\Include" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /D "WML_USE_GLUT" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\..\Library\Release\GLUT\WmlRenderer.lib"
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=copy *.h ..\..\Include
# End Special Build Tool

!ELSEIF  "$(CFG)" == "OpenGLRenderer - Win32 Debug WGL"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug WGL"
# PROP BASE Intermediate_Dir "Debug WGL"
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
# ADD BASE LIB32 /nologo /out:"..\..\Library\Debug\GLUT\WmlRenderer.lib"
# ADD LIB32 /nologo /out:"..\..\Library\Debug\WGL\WmlRenderer.lib"
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=copy *.h ..\..\Include
# End Special Build Tool

!ELSEIF  "$(CFG)" == "OpenGLRenderer - Win32 Release WGL"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release WGL"
# PROP BASE Intermediate_Dir "Release WGL"
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
# ADD BASE LIB32 /nologo /out:"..\..\Library\Release\GLUT\WmlRenderer.lib"
# ADD LIB32 /nologo /out:"..\..\Library\Release\WGL\WmlRenderer.lib"
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=copy *.h ..\..\Include
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "OpenGLRenderer - Win32 Debug GLUT"
# Name "OpenGLRenderer - Win32 Release GLUT"
# Name "OpenGLRenderer - Win32 Debug WGL"
# Name "OpenGLRenderer - Win32 Release WGL"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\glprocs.c
# End Source File
# Begin Source File

SOURCE=.\WmlGlutRenderer.cpp
# End Source File
# Begin Source File

SOURCE=.\WmlOpenGLAlphaState.cpp
# End Source File
# Begin Source File

SOURCE=.\WmlOpenGLBumpMap.cpp
# End Source File
# Begin Source File

SOURCE=.\WmlOpenGLCamera.cpp
# End Source File
# Begin Source File

SOURCE=.\WmlOpenGLCullState.cpp
# End Source File
# Begin Source File

SOURCE=.\WmlOpenGLDitherState.cpp
# End Source File
# Begin Source File

SOURCE=.\WmlOpenGLFogState.cpp
# End Source File
# Begin Source File

SOURCE=.\WmlOpenGLGlossMap.cpp
# End Source File
# Begin Source File

SOURCE=.\WmlOpenGLLightState.cpp
# End Source File
# Begin Source File

SOURCE=.\WmlOpenGLMaterialState.cpp
# End Source File
# Begin Source File

SOURCE=.\WmlOpenGLPlanarReflection.cpp
# End Source File
# Begin Source File

SOURCE=.\WmlOpenGLPlanarShadow.cpp
# End Source File
# Begin Source File

SOURCE=.\WmlOpenGLPolygonOffsetState.cpp
# End Source File
# Begin Source File

SOURCE=.\WmlOpenGLProjectedTexture.cpp
# End Source File
# Begin Source File

SOURCE=.\WmlOpenGLRenderer.cpp
# End Source File
# Begin Source File

SOURCE=.\WmlOpenGLShaders.cpp
# End Source File
# Begin Source File

SOURCE=.\WmlOpenGLShadeState.cpp
# End Source File
# Begin Source File

SOURCE=.\WmlOpenGLTextureState.cpp
# End Source File
# Begin Source File

SOURCE=.\WmlOpenGLVertexColorState.cpp
# End Source File
# Begin Source File

SOURCE=.\WmlOpenGLWireframeState.cpp
# End Source File
# Begin Source File

SOURCE=.\WmlOpenGLZBufferState.cpp
# End Source File
# Begin Source File

SOURCE=.\WmlWglRenderer.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\WmlGlutRenderer.h
# End Source File
# Begin Source File

SOURCE=.\WmlOpenGLCamera.h
# End Source File
# Begin Source File

SOURCE=.\WmlOpenGLExtensions.h
# End Source File
# Begin Source File

SOURCE=.\WmlOpenGLIncludes.h
# End Source File
# Begin Source File

SOURCE=.\WmlOpenGLRenderer.h
# End Source File
# Begin Source File

SOURCE=.\WmlRendererLibType.h
# End Source File
# Begin Source File

SOURCE=.\WmlWglRenderer.h
# End Source File
# End Group
# End Target
# End Project

