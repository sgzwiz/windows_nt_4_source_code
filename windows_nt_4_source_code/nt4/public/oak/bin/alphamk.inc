!IF 0

Copyright (c) 1994-1996  Microsoft Corporation

Module Name:

    alphamk.inc

Abstract:

        This module contains the ALPHA specific build controls.  It is included
        by makefile.def.

Revision History:

!ENDIF

#
# Alpha option control
#

!undef USE_MAPSYM

UMBASE=$(UMBASE:*=alpha)
UMLIBS=$(UMLIBS:*=alpha)
NTRES=$(NTRES:*=alpha)
UMRES=$(UMRES:*=alpha)
UMOBJS=$(UMOBJS:*=alpha)
LINKLIBS=$(LINKLIBS:*=alpha)
GDI_DRIVER_LIBS=$(GDI_DRIVER_LIBS:*=alpha)
DLLBASE=$(DLLBASE:*=alpha)
DLLDEF=$(DLLDEF:*=alpha)
MACHINE_TARGETLIBS=$(MACHINE_TARGETLIBS:*=alpha)
TARGET=$(TARGET:*=alpha)
DYNLINK_LIB=$(DYNLINK_LIB:*=alpha)
TARGETEXEFILES=$(TARGETEXEFILES:*=alpha)
TARGETLIBFILES=$(TARGETLIBFILES:*=alpha)
TARGETOBJFILES=$(TARGETOBJFILES:*=alpha)
UMOBJFILES=$(UMOBJFILES:*=alpha)
UMEXEFILES=$(UMEXEFILES:*=alpha)
HEADERFILE=$(HEADERFILE:*=alpha)
HEADEROBJNAME=$(HEADEROBJNAME:*=alpha)
HEADEROBJ=$(HEADEROBJ:*=alpha)
PRECOMPILED=$(PRECOMPILED:*=alpha)
PRECOMPILED_CXX=$(PRECOMPILED_CXX:*=alpha)
PRECOMPILED_TARGET=$(PRECOMPILED_TARGET:*=alpha)
MFC_STATIC_LIB=$(MFC_STATIC_LIB:*=alpha)
CRT_LIB_PATH=$(CRT_LIB_PATH:*=alpha)
SDK_LIB_PATH=$(SDK_LIB_PATH:*=alpha)
ORDER=$(ORDER:*=alpha)

!ifdef NTTARGETFILES
NTTARGETFILES=$(NTTARGETFILES:*=alpha)
!endif
!ifdef NTTARGETFILE0
NTTARGETFILE0=$(NTTARGETFILE0:*=alpha)
!endif
!ifdef NTTARGETFILE1
NTTARGETFILE1=$(NTTARGETFILE1:*=alpha)
!endif

!IF "$(GPSIZE)" != "0"

!ifdef DEBUG_CRTS
LIBC_LIB=$(SDK_LIB_PATH)\smalld.lib $(LIBC_LIB)
!else
LIBC_LIB=$(SDK_LIB_PATH)\small.lib $(LIBC_LIB)
!endif
LINKGPSIZE=-gpsize:$(GPSIZE)

!ENDIF

ENTRY_SUFFIX=
GDI_ENTRY_SUFFIX=


!IFDEF ALPHA_WARNING_LEVEL
MSC_WARNING_LEVEL=$(ALPHA_WARNING_LEVEL)
!ENDIF

!ifdef ALPHA_PERFFLAGS
PERFFLAGS = $(ALPHA_PERFFLAGS)
!endif

# Set MSC_OPTIMIZATION.
# Order of precedence:
#   Platform specific override
#   Environment variable
#   System Default

!if defined(ALPHA_OPTIMIZATION)
MSC_OPTIMIZATION=$(ALPHA_OPTIMIZATION)
!elseif !defined(MSC_OPTIMIZATION)
MSC_OPTIMIZATION=$(DEFAULT_MSC_OPT)
!endif

DBGFLAGS=$(DBGFLAGS) $(MSC_OPTIMIZATION)

!IFDEF ALPHA_CPPFLAGS
MSC_CPPFLAGS=$(ALPHA_CPPFLAGS)
!ENDIF

ALPHA_AS=asaxp -nologo

ALPHA_START_FILE=start.obj

!ifndef USE_PDB_TO_COMPILE
DBGFLAGS=$(DBGFLAGS:/Zi=-Z7)
DBGFLAGS=$(DBGFLAGS:-Zi=-Z7)
!else
! if "$(TARGETTYPE)" == "LIBRARY"
DBGFLAGS=$(DBGFLAGS) /Fd$(TARGETPATH)\$(TARGET_DIRECTORY)\$(TARGETNAME).pdb
! else
DBGFLAGS=$(DBGFLAGS) /Fd$(MAKEDIR)\$(_OBJ_DIR)\alpha^\
! endif
!endif

!ifdef BROWSER_INFO
DBGFLAGS=$(DBGFLAGS) /FR$(MAKEDIR)\$(_OBJ_DIR)\alpha^\
!endif

!IFDEF NTBBT
DBGFLAGS=$(DBGFLAGS) /Z7 /QAl
ADBGFLAGS=-Zi
LINKER_FLAGS=$(LINKER_FLAGS) -debug:full -debugtype:cv,fixup
USE_PDB=1
!ENDIF

ENV_DEFINES=$(LIBC_DEFINES) $(C_DEFINES) $(NET_C_DEFINES) $(MSC_CPPFLAGS) $(NTCPPFLAGS)
STD_DEFINES=-DALPHA=1 -D_ALPHA_=1 -DNO_EXT_KEYS -DCONDITION_HANDLING=1 $(STD_DEFINES)

!ifdef NO_READONLY_STRINGS
STRING_POOLING = /Gf
!else
STRING_POOLING = /GF
!endif

!ifdef USE_NATIVE_EH
EH_FLAGS=/GX /GR
!else
EH_FLAGS=/GX- /GR-
!endif

STDFLAGS= /c /Zel /Zp8 /Gy $(EH_FLAGS) $(STRING_POOLING) $(MSC_WARNING_LEVEL) $(MFC_FLAGS)

CDEFINES=$(STD_DEFINES) $(TARGET_DBG_DEFINES) $(ENV_DEFINES)
CFLAGS=$(ALPHA_FLAGS) $(NTALPHAFLAGS) $(STDFLAGS) $(DBGFLAGS) $(PERFFLAGS) \
       -D__stdcall= -D__cdecl=

ALPHA_CDEFINES=$(CDEFINES)
ALPHA_CFLAGS=$(CFLAGS)

!IFNDEF _AXPACC_
_AXPACC_=0
!ENDIF

ALPHA_CC = cl $(CBSTRING) -nologo -d2"switch no*check*" $(USER_C_FLAGS)

C_COMPILER_NAME = $(ALPHA_CC)
CXX_COMPILER_NAME = $(ALPHA_CC)
C_PREPROCESSOR_NAME = $(ALPHA_CC)

GLOBAL_C_FLAGS = -Ialpha\ -I. $(INCPATH0) $(CDEFINES) \
                $(ALPHA_OPTIONS) $(CFLAGS) \
                /Gt$(GPSIZE) -DFPO=1

NP_COMPILER_FLAGS = $(GLOBAL_C_FLAGS) $(COMPILER_WARNINGS)

C_COMPILER_FLAGS = $(NP_COMPILER_FLAGS) $(PRECOMPILED)
CXX_COMPILER_FLAGS = $(NP_COMPILER_FLAGS) $(PRECOMPILED_CXX)
C_PREPROCESSOR_FLAGS = $(GLOBAL_C_FLAGS) -EP -Tc

C_COMPILER= $(C_COMPILER_NAME) $(C_COMPILER_FLAGS)
CXX_COMPILER=$(CXX_COMPILER_NAME) $(CXX_COMPILER_FLAGS)
C_PREPROCESSOR = $(C_PREPROCESSOR_NAME) $(C_PREPROCESSOR_FLAGS)

ALPHA_ASSEMBLER=$(ALPHA_AS) -O1 -Ialpha\ -I. $(INCPATH0) $(CDEFINES) \
                    $(ALPHA_FLAGS) $(NTALPHAFLAGS) $(ADBGFLAGS) \
                    -D_LANGUAGE_ASSEMBLY

ECHO_MSG=ClAlpha $< " $(C_COMPILER) "
ECHO_CXX_MSG=ClAlpha $< " $(CXX_COMPILER) "

ECHO_PRECOMPILED_MSG1=CpAlpha $(PRECOMPILED_INCLUDE) \
                     "$(C_COMPILER_NAME) $(PRECOMPILED_FLAG) $(PRECOMPILED_SOURCEFILE) \
                      $(C_COMPILER_FLAGS) /Yl$(TARGETNAME) /Yc$(?F) $(HEADERFILE) $(HEADEROBJ)"

ECHO_PRECOMPILED_MSG2=CpAlpha $(PRECOMPILED_INCLUDE) \
                     "$(C_COMPILER_NAME) $(PRECOMPILED_FLAG) \
                      $(C_COMPILER_FLAGS) /Yl$(TARGETNAME) /Yc$(?F) $(HEADERFILE) $(HEADEROBJ)"

{..\alpha\}.s{$(_OBJ_DIR)\alpha\}.obj:
    @-erase $@ >nul 2>&1
    @echo AsAlpha $<            " $(ALPHA_ASSEMBLER) "
    @$(ALPHA_ASSEMBLER) -o $@ $(MAKEDIR)\..\alpha\$(<F)

{alpha\}.s{$(_OBJ_DIR)\alpha\}.obj:
    @-erase $@ >nul 2>&1
    @echo AsAlpha $<            " $(ALPHA_ASSEMBLER) "
    @$(ALPHA_ASSEMBLER) -o $@ $(MAKEDIR)\alpha\$(<F)

.SUFFIXES: .il

{}.il{}.cod:
    @-erase $@ >nul 2>&1
    @type <<
$(ECHO_MSG)
<<NOKEEP
    @$(C_COMPILER_NAME) @<< -FAac -Fa$(<B).cod -B1..\bootbin\null.exe -Bk$(<B). -Fo$(MAKEDIR)\$(_OBJ_DIR)\alpha\$(<B).o $(MAKEDIR)\$(<B).c
$(C_COMPILER_FLAGS: =
)
<<NOKEEP
    @del $(_OBJ_DIR)\alpha\$(<B).o

{}.il{$(_OBJ_DIR)\alpha\}.obj:
    @-erase $@ >nul 2>&1
    @type <<
$(ECHO_MSG)
<<NOKEEP
    @$(C_COMPILER_NAME) @<< -B1..\bootbin\null.exe -Bk$(<B). -Fo$(MAKEDIR)\$@  $(MAKEDIR)\$(<B).c
$(C_COMPILER_FLAGS: =
)
<<NOKEEP

!IFDEF CAIRO_PRODUCT
!IFDEF _CAIROALPHATREE
_NTTREE=$(_CAIROALPHATREE)
_NTTREE_NO_SPLIT=$(_CAIROALPHATREE_NS)
!ENDIF
!ELSE
!IFDEF _NTALPHATREE
_NTTREE=$(_NTALPHATREE)
_NTTREE_NO_SPLIT=$(_NTALPHATREE_NS)
!ENDIF
!ENDIF

!IFDEF _NTALPHALIBS
_NTLIBS=$(_NTALPHALIBS)
!ENDIF

COPYDST=$(ALPHACOPYDST)

LIB_COPY=ntalphacp.cmd

NTTEST_LINK_OPTIONS= -base:0x80080000 -fixed -entry:KiSystemStartup