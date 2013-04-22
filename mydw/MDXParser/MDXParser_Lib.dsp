# Microsoft Developer Studio Project File - Name="MDXParser_Lib" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=MDXParser_Lib - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "MDXParser_Lib.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "MDXParser_Lib.mak" CFG="MDXParser_Lib - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "MDXParser_Lib - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "MDXParser_Lib - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "MDXParser_Lib - Win32 Release"

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
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD BASE RSC /l 0x804 /d "NDEBUG"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "MDXParser_Lib - Win32 Debug"

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
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /I "../include" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD BASE RSC /l 0x804 /d "_DEBUG"
# ADD RSC /l 0x804 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\lib\MDXParser_Lib.lib"

!ENDIF 

# Begin Target

# Name "MDXParser_Lib - Win32 Release"
# Name "MDXParser_Lib - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\calcMemFormat.cpp
# End Source File
# Begin Source File

SOURCE=.\calculatedMember.cpp
# End Source File
# Begin Source File

SOURCE=.\FunParam.cpp
# End Source File
# Begin Source File

SOURCE=.\lex.cpp
# End Source File
# Begin Source File

SOURCE=.\main.cpp
# End Source File
# Begin Source File

SOURCE=.\MemberFunFactory.cpp
# End Source File
# Begin Source File

SOURCE=.\ParsedMDX.cpp
# End Source File
# Begin Source File

SOURCE=.\QueryMember.cpp
# End Source File
# Begin Source File

SOURCE=.\QueryTuple.cpp
# End Source File
# Begin Source File

SOURCE=.\SetFunFactory.cpp
# End Source File
# Begin Source File

SOURCE=.\SymTab.cpp
# End Source File
# Begin Source File

SOURCE=.\SyntTree.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\include\MdxParser\calcMemFormat.h
# End Source File
# Begin Source File

SOURCE=..\include\MdxParser\calculatedMember.h
# End Source File
# Begin Source File

SOURCE=..\include\MdxParser\Common.h
# End Source File
# Begin Source File

SOURCE=..\include\MdxParser\FunParam.h
# End Source File
# Begin Source File

SOURCE=..\include\MdxParser\GlobalFun.h
# End Source File
# Begin Source File

SOURCE=..\include\MdxParser\MemberFunFactory.h
# End Source File
# Begin Source File

SOURCE=..\include\MdxParser\ParsedMDX.h
# End Source File
# Begin Source File

SOURCE=..\include\MdxParser\QueryMember.h
# End Source File
# Begin Source File

SOURCE=..\include\MdxParser\QueryTuple.h
# End Source File
# Begin Source File

SOURCE=..\include\MdxParser\SetFunFactory.h
# End Source File
# Begin Source File

SOURCE=..\include\MdxParser\SymTab.h
# End Source File
# Begin Source File

SOURCE=..\include\MdxParser\SyntTree.h
# End Source File
# Begin Source File

SOURCE=..\include\MdxParser\unistd.h
# End Source File
# Begin Source File

SOURCE=..\include\MdxParser\yacc.h
# End Source File
# Begin Source File

SOURCE=..\include\MdxParser\yacc1.h
# End Source File
# End Group
# End Target
# End Project
