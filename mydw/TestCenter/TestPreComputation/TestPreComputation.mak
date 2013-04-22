# Microsoft Developer Studio Generated NMAKE File, Based on TestPreComputation.dsp
!IF "$(CFG)" == ""
CFG=TestPreComputation - Win32 Debug
!MESSAGE No configuration specified. Defaulting to TestPreComputation - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "TestPreComputation - Win32 Release" && "$(CFG)" != "TestPreComputation - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "TestPreComputation.mak" CFG="TestPreComputation - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "TestPreComputation - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "TestPreComputation - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "TestPreComputation - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\TestPreComputation.exe"


CLEAN :
	-@erase "$(INTDIR)\PreComputationTest.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\TestPreComputation.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MTd /W3 /GX /O2 /I "..\..\include" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /Fp"$(INTDIR)\TestPreComputation.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\TestPreComputation.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib DWSchemaSLib.lib XODBCV6DM.lib xerces-c_2D.lib PreComputation.lib /nologo /subsystem:console /incremental:no /pdb:"$(OUTDIR)\TestPreComputation.pdb" /machine:I386 /out:"$(OUTDIR)\TestPreComputation.exe" /libpath:"..\..\lib" 
LINK32_OBJS= \
	"$(INTDIR)\PreComputationTest.obj"

"$(OUTDIR)\TestPreComputation.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "TestPreComputation - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\TestPreComputation.exe"


CLEAN :
	-@erase "$(INTDIR)\PreComputationTest.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\TestPreComputation.exe"
	-@erase "$(OUTDIR)\TestPreComputation.ilk"
	-@erase "$(OUTDIR)\TestPreComputation.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\..\include" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /Fp"$(INTDIR)\TestPreComputation.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\TestPreComputation.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib DWSchemaSLib.lib XODBCV6DM.lib xerces-c_2D.lib PreComputation.lib /nologo /subsystem:console /incremental:yes /pdb:"$(OUTDIR)\TestPreComputation.pdb" /debug /machine:I386 /out:"$(OUTDIR)\TestPreComputation.exe" /pdbtype:sept /libpath:"..\..\lib" 
LINK32_OBJS= \
	"$(INTDIR)\PreComputationTest.obj"

"$(OUTDIR)\TestPreComputation.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("TestPreComputation.dep")
!INCLUDE "TestPreComputation.dep"
!ELSE 
!MESSAGE Warning: cannot find "TestPreComputation.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "TestPreComputation - Win32 Release" || "$(CFG)" == "TestPreComputation - Win32 Debug"
SOURCE=.\PreComputationTest.cpp

"$(INTDIR)\PreComputationTest.obj" : $(SOURCE) "$(INTDIR)"



!ENDIF 

