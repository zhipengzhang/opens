# Microsoft Developer Studio Project File - Name="Query" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=Query - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Query.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Query.mak" CFG="Query - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Query - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "Query - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Query - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\lib"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /FR /YX /FD /c
# ADD BASE RSC /l 0x804 /d "NDEBUG"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "Query - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\lib"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /FR /YX /FD /GZ /c
# ADD BASE RSC /l 0x804 /d "_DEBUG"
# ADD RSC /l 0x804 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ENDIF 

# Begin Target

# Name "Query - Win32 Release"
# Name "Query - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\AggDBReader.cpp
# End Source File
# Begin Source File

SOURCE=.\AggFileReader.cpp
# End Source File
# Begin Source File

SOURCE=.\AggReader.cpp
# End Source File
# Begin Source File

SOURCE=.\MolapCCInvertListQuery.cpp
# End Source File
# Begin Source File

SOURCE=.\MolapQueryComputationBase.cpp
# End Source File
# Begin Source File

SOURCE=.\MTCCQuery.cpp
# End Source File
# Begin Source File

SOURCE=.\QueryCmptException.cpp
# End Source File
# Begin Source File

SOURCE=.\QueryComputation.cpp
# End Source File
# Begin Source File

SOURCE=.\RolapCCQuery.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\include\PreComputation\AggDBWriter.h
# End Source File
# Begin Source File

SOURCE=..\include\PreComputation\AggFileWriter.h
# End Source File
# Begin Source File

SOURCE=..\include\PreComputation\AggWriter.h
# End Source File
# Begin Source File

SOURCE=..\include\PreComputation\Common.h
# End Source File
# Begin Source File

SOURCE=..\include\PreComputation\FileHandle.h
# End Source File
# Begin Source File

SOURCE=..\include\PreComputation\FreqPool.h
# End Source File
# Begin Source File

SOURCE=..\include\PreComputation\MolapCCPreComputation.h
# End Source File
# Begin Source File

SOURCE=..\include\PreComputation\MolapFCPreComputation.h
# End Source File
# Begin Source File

SOURCE=..\include\PreComputation\MolapMTCCPreComputation.h
# End Source File
# Begin Source File

SOURCE=..\include\PreComputation\MolapPreComputationBase.h
# End Source File
# Begin Source File

SOURCE=..\include\PreComputation\MTPDCCPreComputation.h
# End Source File
# Begin Source File

SOURCE=..\include\PreComputation\PreCmptException.h
# End Source File
# Begin Source File

SOURCE=..\include\PreComputation\PreComputation.h
# End Source File
# Begin Source File

SOURCE=..\include\PreComputation\PreComputationbase.h
# End Source File
# Begin Source File

SOURCE=..\include\PreComputation\RolapCCPreComputation.h
# End Source File
# End Group
# End Target
# End Project
