# Microsoft Developer Studio Generated NMAKE File, Based on PreComputation.dsp
!IF "$(CFG)" == ""
CFG=PreComputation - Win32 Debug
!MESSAGE No configuration specified. Defaulting to PreComputation - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "PreComputation - Win32 Release" && "$(CFG)" != "PreComputation - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "PreComputation.mak" CFG="PreComputation - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "PreComputation - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "PreComputation - Win32 Debug" (based on "Win32 (x86) Static Library")
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

!IF  "$(CFG)" == "PreComputation - Win32 Release"

OUTDIR=.\..\lib
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\..\lib
# End Custom Macros

ALL : "$(OUTDIR)\PreComputation.lib"


CLEAN :
	-@erase "$(INTDIR)\AggDBWriter.obj"
	-@erase "$(INTDIR)\AggFileWriter.obj"
	-@erase "$(INTDIR)\AggWriter.obj"
	-@erase "$(INTDIR)\FileHandle.obj"
	-@erase "$(INTDIR)\FreqPool.obj"
	-@erase "$(INTDIR)\Globals.obj"
	-@erase "$(INTDIR)\MolapCCPreComputation.obj"
	-@erase "$(INTDIR)\MolapFCPreComputation.obj"
	-@erase "$(INTDIR)\MolapMTCCPreComputation.obj"
	-@erase "$(INTDIR)\MolapPreComputationBase.obj"
	-@erase "$(INTDIR)\MTPDCCPreComputation.obj"
	-@erase "$(INTDIR)\PreCmptException.obj"
	-@erase "$(INTDIR)\PreComputation.obj"
	-@erase "$(INTDIR)\PreComputationbase.obj"
	-@erase "$(INTDIR)\RolapCCPreComputation.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\PreComputation.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP_PROJ=/nologo /MT /W3 /GX /O2 /I "..\include" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /Fp"$(INTDIR)\PreComputation.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\PreComputation.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"$(OUTDIR)\PreComputation.lib" 
LIB32_OBJS= \
	"$(INTDIR)\AggDBWriter.obj" \
	"$(INTDIR)\AggFileWriter.obj" \
	"$(INTDIR)\AggWriter.obj" \
	"$(INTDIR)\FileHandle.obj" \
	"$(INTDIR)\FreqPool.obj" \
	"$(INTDIR)\MolapCCPreComputation.obj" \
	"$(INTDIR)\MolapFCPreComputation.obj" \
	"$(INTDIR)\MolapMTCCPreComputation.obj" \
	"$(INTDIR)\MolapPreComputationBase.obj" \
	"$(INTDIR)\MTPDCCPreComputation.obj" \
	"$(INTDIR)\PreCmptException.obj" \
	"$(INTDIR)\PreComputation.obj" \
	"$(INTDIR)\PreComputationbase.obj" \
	"$(INTDIR)\RolapCCPreComputation.obj" \
	"$(INTDIR)\Globals.obj"

"$(OUTDIR)\PreComputation.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "PreComputation - Win32 Debug"

OUTDIR=.\..\lib
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\..\lib
# End Custom Macros

ALL : "$(OUTDIR)\PreComputation.lib" "$(OUTDIR)\PreComputation.bsc"


CLEAN :
	-@erase "$(INTDIR)\AggDBWriter.obj"
	-@erase "$(INTDIR)\AggDBWriter.sbr"
	-@erase "$(INTDIR)\AggFileWriter.obj"
	-@erase "$(INTDIR)\AggFileWriter.sbr"
	-@erase "$(INTDIR)\AggWriter.obj"
	-@erase "$(INTDIR)\AggWriter.sbr"
	-@erase "$(INTDIR)\FileHandle.obj"
	-@erase "$(INTDIR)\FileHandle.sbr"
	-@erase "$(INTDIR)\FreqPool.obj"
	-@erase "$(INTDIR)\FreqPool.sbr"
	-@erase "$(INTDIR)\Globals.obj"
	-@erase "$(INTDIR)\Globals.sbr"
	-@erase "$(INTDIR)\MolapCCPreComputation.obj"
	-@erase "$(INTDIR)\MolapCCPreComputation.sbr"
	-@erase "$(INTDIR)\MolapFCPreComputation.obj"
	-@erase "$(INTDIR)\MolapFCPreComputation.sbr"
	-@erase "$(INTDIR)\MolapMTCCPreComputation.obj"
	-@erase "$(INTDIR)\MolapMTCCPreComputation.sbr"
	-@erase "$(INTDIR)\MolapPreComputationBase.obj"
	-@erase "$(INTDIR)\MolapPreComputationBase.sbr"
	-@erase "$(INTDIR)\MTPDCCPreComputation.obj"
	-@erase "$(INTDIR)\MTPDCCPreComputation.sbr"
	-@erase "$(INTDIR)\PreCmptException.obj"
	-@erase "$(INTDIR)\PreCmptException.sbr"
	-@erase "$(INTDIR)\PreComputation.obj"
	-@erase "$(INTDIR)\PreComputation.sbr"
	-@erase "$(INTDIR)\PreComputationbase.obj"
	-@erase "$(INTDIR)\PreComputationbase.sbr"
	-@erase "$(INTDIR)\RolapCCPreComputation.obj"
	-@erase "$(INTDIR)\RolapCCPreComputation.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\PreComputation.bsc"
	-@erase "$(OUTDIR)\PreComputation.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP_PROJ=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\PreComputation.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\PreComputation.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\AggDBWriter.sbr" \
	"$(INTDIR)\AggFileWriter.sbr" \
	"$(INTDIR)\AggWriter.sbr" \
	"$(INTDIR)\FileHandle.sbr" \
	"$(INTDIR)\FreqPool.sbr" \
	"$(INTDIR)\MolapCCPreComputation.sbr" \
	"$(INTDIR)\MolapFCPreComputation.sbr" \
	"$(INTDIR)\MolapMTCCPreComputation.sbr" \
	"$(INTDIR)\MolapPreComputationBase.sbr" \
	"$(INTDIR)\MTPDCCPreComputation.sbr" \
	"$(INTDIR)\PreCmptException.sbr" \
	"$(INTDIR)\PreComputation.sbr" \
	"$(INTDIR)\PreComputationbase.sbr" \
	"$(INTDIR)\RolapCCPreComputation.sbr" \
	"$(INTDIR)\Globals.sbr"

"$(OUTDIR)\PreComputation.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"$(OUTDIR)\PreComputation.lib" 
LIB32_OBJS= \
	"$(INTDIR)\AggDBWriter.obj" \
	"$(INTDIR)\AggFileWriter.obj" \
	"$(INTDIR)\AggWriter.obj" \
	"$(INTDIR)\FileHandle.obj" \
	"$(INTDIR)\FreqPool.obj" \
	"$(INTDIR)\MolapCCPreComputation.obj" \
	"$(INTDIR)\MolapFCPreComputation.obj" \
	"$(INTDIR)\MolapMTCCPreComputation.obj" \
	"$(INTDIR)\MolapPreComputationBase.obj" \
	"$(INTDIR)\MTPDCCPreComputation.obj" \
	"$(INTDIR)\PreCmptException.obj" \
	"$(INTDIR)\PreComputation.obj" \
	"$(INTDIR)\PreComputationbase.obj" \
	"$(INTDIR)\RolapCCPreComputation.obj" \
	"$(INTDIR)\Globals.obj"

"$(OUTDIR)\PreComputation.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
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
!IF EXISTS("PreComputation.dep")
!INCLUDE "PreComputation.dep"
!ELSE 
!MESSAGE Warning: cannot find "PreComputation.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "PreComputation - Win32 Release" || "$(CFG)" == "PreComputation - Win32 Debug"
SOURCE=.\AggDBWriter.cpp

!IF  "$(CFG)" == "PreComputation - Win32 Release"


"$(INTDIR)\AggDBWriter.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "PreComputation - Win32 Debug"


"$(INTDIR)\AggDBWriter.obj"	"$(INTDIR)\AggDBWriter.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\AggFileWriter.cpp

!IF  "$(CFG)" == "PreComputation - Win32 Release"


"$(INTDIR)\AggFileWriter.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "PreComputation - Win32 Debug"


"$(INTDIR)\AggFileWriter.obj"	"$(INTDIR)\AggFileWriter.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\AggWriter.cpp

!IF  "$(CFG)" == "PreComputation - Win32 Release"


"$(INTDIR)\AggWriter.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "PreComputation - Win32 Debug"


"$(INTDIR)\AggWriter.obj"	"$(INTDIR)\AggWriter.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\FileHandle.cpp

!IF  "$(CFG)" == "PreComputation - Win32 Release"


"$(INTDIR)\FileHandle.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "PreComputation - Win32 Debug"


"$(INTDIR)\FileHandle.obj"	"$(INTDIR)\FileHandle.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\FreqPool.cpp

!IF  "$(CFG)" == "PreComputation - Win32 Release"


"$(INTDIR)\FreqPool.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "PreComputation - Win32 Debug"


"$(INTDIR)\FreqPool.obj"	"$(INTDIR)\FreqPool.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\Globals.cpp

!IF  "$(CFG)" == "PreComputation - Win32 Release"


"$(INTDIR)\Globals.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "PreComputation - Win32 Debug"


"$(INTDIR)\Globals.obj"	"$(INTDIR)\Globals.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\MolapCCPreComputation.cpp

!IF  "$(CFG)" == "PreComputation - Win32 Release"


"$(INTDIR)\MolapCCPreComputation.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "PreComputation - Win32 Debug"


"$(INTDIR)\MolapCCPreComputation.obj"	"$(INTDIR)\MolapCCPreComputation.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\MolapFCPreComputation.cpp

!IF  "$(CFG)" == "PreComputation - Win32 Release"


"$(INTDIR)\MolapFCPreComputation.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "PreComputation - Win32 Debug"


"$(INTDIR)\MolapFCPreComputation.obj"	"$(INTDIR)\MolapFCPreComputation.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\MolapMTCCPreComputation.cpp

!IF  "$(CFG)" == "PreComputation - Win32 Release"


"$(INTDIR)\MolapMTCCPreComputation.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "PreComputation - Win32 Debug"


"$(INTDIR)\MolapMTCCPreComputation.obj"	"$(INTDIR)\MolapMTCCPreComputation.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\MolapPreComputationBase.cpp

!IF  "$(CFG)" == "PreComputation - Win32 Release"

CPP_SWITCHES=/nologo /MTd /W3 /GX /O2 /I "..\include" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /Fp"$(INTDIR)\PreComputation.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\MolapPreComputationBase.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "PreComputation - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\PreComputation.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\MolapPreComputationBase.obj"	"$(INTDIR)\MolapPreComputationBase.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\MTPDCCPreComputation.cpp

!IF  "$(CFG)" == "PreComputation - Win32 Release"


"$(INTDIR)\MTPDCCPreComputation.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "PreComputation - Win32 Debug"


"$(INTDIR)\MTPDCCPreComputation.obj"	"$(INTDIR)\MTPDCCPreComputation.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\PreCmptException.cpp

!IF  "$(CFG)" == "PreComputation - Win32 Release"


"$(INTDIR)\PreCmptException.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "PreComputation - Win32 Debug"


"$(INTDIR)\PreCmptException.obj"	"$(INTDIR)\PreCmptException.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\PreComputation.cpp

!IF  "$(CFG)" == "PreComputation - Win32 Release"


"$(INTDIR)\PreComputation.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "PreComputation - Win32 Debug"


"$(INTDIR)\PreComputation.obj"	"$(INTDIR)\PreComputation.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\PreComputationbase.cpp

!IF  "$(CFG)" == "PreComputation - Win32 Release"


"$(INTDIR)\PreComputationbase.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "PreComputation - Win32 Debug"


"$(INTDIR)\PreComputationbase.obj"	"$(INTDIR)\PreComputationbase.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\RolapCCPreComputation.cpp

!IF  "$(CFG)" == "PreComputation - Win32 Release"


"$(INTDIR)\RolapCCPreComputation.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "PreComputation - Win32 Debug"


"$(INTDIR)\RolapCCPreComputation.obj"	"$(INTDIR)\RolapCCPreComputation.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 


!ENDIF 

