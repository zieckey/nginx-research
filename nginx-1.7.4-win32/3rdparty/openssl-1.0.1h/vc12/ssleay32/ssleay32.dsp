# Microsoft Developer Studio Project File - Name="ssleay32" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=ssleay32 - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ssleay32.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ssleay32.mak" CFG="ssleay32 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ssleay32 - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ssleay32 - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ssleay32 - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "../../out32dll/Release"
# PROP Intermediate_Dir "../../tmp32dll/Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "SSLEAY32_EXPORTS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "../../inc32" /I "../../tmp32dll" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "SSLEAY32_EXPORTS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386

!ELSEIF  "$(CFG)" == "ssleay32 - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "../../out32dll/Debug"
# PROP Intermediate_Dir "../../tmp32dll/Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "SSLEAY32_EXPORTS" /YX /FD /GZ /c
# ADD CPP /nologo /MD /W3 /Gm /GX /ZI /Od /I "../../inc32" /I "../../tmp32dll" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "SSLEAY32_EXPORTS" /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG"
# ADD RSC /l 0x804 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "ssleay32 - Win32 Release"
# Name "ssleay32 - Win32 Debug"
# Begin Source File

SOURCE=..\..\ssl\bio_ssl.c
# End Source File
# Begin Source File

SOURCE=..\..\ssl\d1_both.c
# End Source File
# Begin Source File

SOURCE=..\..\ssl\d1_clnt.c
# End Source File
# Begin Source File

SOURCE=..\..\ssl\d1_enc.c
# End Source File
# Begin Source File

SOURCE=..\..\ssl\d1_lib.c
# End Source File
# Begin Source File

SOURCE=..\..\ssl\d1_meth.c
# End Source File
# Begin Source File

SOURCE=..\..\ssl\d1_pkt.c
# End Source File
# Begin Source File

SOURCE=..\..\ssl\d1_srvr.c
# End Source File
# Begin Source File

SOURCE=..\..\ssl\kssl.c
# End Source File
# Begin Source File

SOURCE=..\..\ssl\s23_clnt.c
# End Source File
# Begin Source File

SOURCE=..\..\ssl\s23_lib.c
# End Source File
# Begin Source File

SOURCE=..\..\ssl\s23_meth.c
# End Source File
# Begin Source File

SOURCE=..\..\ssl\s23_pkt.c
# End Source File
# Begin Source File

SOURCE=..\..\ssl\s23_srvr.c
# End Source File
# Begin Source File

SOURCE=..\..\ssl\s2_clnt.c
# End Source File
# Begin Source File

SOURCE=..\..\ssl\s2_enc.c
# End Source File
# Begin Source File

SOURCE=..\..\ssl\s2_lib.c
# End Source File
# Begin Source File

SOURCE=..\..\ssl\s2_meth.c
# End Source File
# Begin Source File

SOURCE=..\..\ssl\s2_pkt.c
# End Source File
# Begin Source File

SOURCE=..\..\ssl\s2_srvr.c
# End Source File
# Begin Source File

SOURCE=..\..\ssl\s3_both.c
# End Source File
# Begin Source File

SOURCE=..\..\ssl\s3_clnt.c
# End Source File
# Begin Source File

SOURCE=..\..\ssl\s3_enc.c
# End Source File
# Begin Source File

SOURCE=..\..\ssl\s3_lib.c
# End Source File
# Begin Source File

SOURCE=..\..\ssl\s3_meth.c
# End Source File
# Begin Source File

SOURCE=..\..\ssl\s3_pkt.c
# End Source File
# Begin Source File

SOURCE=..\..\ssl\s3_srvr.c
# End Source File
# Begin Source File

SOURCE=..\..\ssl\ssl_algs.c
# End Source File
# Begin Source File

SOURCE=..\..\ssl\ssl_asn1.c
# End Source File
# Begin Source File

SOURCE=..\..\ssl\ssl_cert.c
# End Source File
# Begin Source File

SOURCE=..\..\ssl\ssl_ciph.c
# End Source File
# Begin Source File

SOURCE=..\..\ssl\ssl_err.c
# End Source File
# Begin Source File

SOURCE=..\..\ssl\ssl_err2.c
# End Source File
# Begin Source File

SOURCE=..\..\ssl\ssl_lib.c
# End Source File
# Begin Source File

SOURCE=..\..\ssl\ssl_rsa.c
# End Source File
# Begin Source File

SOURCE=..\..\ssl\ssl_sess.c
# End Source File
# Begin Source File

SOURCE=..\..\ssl\ssl_stat.c
# End Source File
# Begin Source File

SOURCE=..\..\ssl\ssl_txt.c
# End Source File
# Begin Source File

SOURCE=..\..\ms\ssleay32.def
# End Source File
# Begin Source File

SOURCE=..\..\ssl\t1_clnt.c
# End Source File
# Begin Source File

SOURCE=..\..\ssl\t1_enc.c
# End Source File
# Begin Source File

SOURCE=..\..\ssl\t1_lib.c
# End Source File
# Begin Source File

SOURCE=..\..\ssl\t1_meth.c
# End Source File
# Begin Source File

SOURCE=..\..\ssl\t1_srvr.c
# End Source File
# End Target
# End Project
