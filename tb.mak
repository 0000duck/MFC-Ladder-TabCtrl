# Microsoft Developer Studio Generated NMAKE File, Based on tb.dsp
!IF "$(CFG)" == ""
CFG=tb - Win32 Debug
!MESSAGE No configuration specified. Defaulting to tb - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "tb - Win32 Release" && "$(CFG)" != "tb - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "tb.mak" CFG="tb - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "tb - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "tb - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "tb - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\tb.exe"


CLEAN :
	-@erase "$(INTDIR)\EditDlg.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\tb.obj"
	-@erase "$(INTDIR)\tb.pch"
	-@erase "$(INTDIR)\tb.res"
	-@erase "$(INTDIR)\tbDlg.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\VcTab.obj"
	-@erase "$(OUTDIR)\tb.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Fp"$(INTDIR)\tb.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x804 /fo"$(INTDIR)\tb.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\tb.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\tb.pdb" /machine:I386 /out:"$(OUTDIR)\tb.exe" 
LINK32_OBJS= \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\tb.obj" \
	"$(INTDIR)\tbDlg.obj" \
	"$(INTDIR)\VcTab.obj" \
	"$(INTDIR)\tb.res" \
	"$(INTDIR)\EditDlg.obj"

"$(OUTDIR)\tb.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "tb - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\tb.exe" "$(OUTDIR)\tb.bsc"


CLEAN :
	-@erase "$(INTDIR)\EditDlg.obj"
	-@erase "$(INTDIR)\EditDlg.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\tb.obj"
	-@erase "$(INTDIR)\tb.pch"
	-@erase "$(INTDIR)\tb.res"
	-@erase "$(INTDIR)\tb.sbr"
	-@erase "$(INTDIR)\tbDlg.obj"
	-@erase "$(INTDIR)\tbDlg.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\VcTab.obj"
	-@erase "$(INTDIR)\VcTab.sbr"
	-@erase "$(OUTDIR)\tb.bsc"
	-@erase "$(OUTDIR)\tb.exe"
	-@erase "$(OUTDIR)\tb.ilk"
	-@erase "$(OUTDIR)\tb.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\tb.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x804 /fo"$(INTDIR)\tb.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\tb.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\StdAfx.sbr" \
	"$(INTDIR)\tb.sbr" \
	"$(INTDIR)\tbDlg.sbr" \
	"$(INTDIR)\VcTab.sbr" \
	"$(INTDIR)\EditDlg.sbr"

"$(OUTDIR)\tb.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\tb.pdb" /debug /machine:I386 /out:"$(OUTDIR)\tb.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\tb.obj" \
	"$(INTDIR)\tbDlg.obj" \
	"$(INTDIR)\VcTab.obj" \
	"$(INTDIR)\tb.res" \
	"$(INTDIR)\EditDlg.obj"

"$(OUTDIR)\tb.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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
!IF EXISTS("tb.dep")
!INCLUDE "tb.dep"
!ELSE 
!MESSAGE Warning: cannot find "tb.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "tb - Win32 Release" || "$(CFG)" == "tb - Win32 Debug"
SOURCE=.\EditDlg.cpp

!IF  "$(CFG)" == "tb - Win32 Release"


"$(INTDIR)\EditDlg.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\tb.pch"


!ELSEIF  "$(CFG)" == "tb - Win32 Debug"


"$(INTDIR)\EditDlg.obj"	"$(INTDIR)\EditDlg.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\tb.pch"


!ENDIF 

SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "tb - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Fp"$(INTDIR)\tb.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\tb.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "tb - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\tb.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\tb.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\tb.cpp

!IF  "$(CFG)" == "tb - Win32 Release"


"$(INTDIR)\tb.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\tb.pch"


!ELSEIF  "$(CFG)" == "tb - Win32 Debug"


"$(INTDIR)\tb.obj"	"$(INTDIR)\tb.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\tb.pch"


!ENDIF 

SOURCE=.\tb.rc

"$(INTDIR)\tb.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\tbDlg.cpp

!IF  "$(CFG)" == "tb - Win32 Release"


"$(INTDIR)\tbDlg.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\tb.pch"


!ELSEIF  "$(CFG)" == "tb - Win32 Debug"


"$(INTDIR)\tbDlg.obj"	"$(INTDIR)\tbDlg.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\tb.pch"


!ENDIF 

SOURCE=.\VcTab.cpp

!IF  "$(CFG)" == "tb - Win32 Release"


"$(INTDIR)\VcTab.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\tb.pch"


!ELSEIF  "$(CFG)" == "tb - Win32 Debug"


"$(INTDIR)\VcTab.obj"	"$(INTDIR)\VcTab.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\tb.pch"


!ENDIF 


!ENDIF 

