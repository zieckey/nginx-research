# Microsoft Developer Studio Project File - Name="libeay32" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=libeay32 - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "libeay32.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "libeay32.mak" CFG="libeay32 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "libeay32 - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "libeay32 - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "libeay32 - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "../../out32dll/Release"
# PROP Intermediate_Dir "../../tmp32dll/Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "LIBEAY32_EXPORTS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "../../inc32" /I "../../tmp32dll" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "LIBEAY32_EXPORTS" /D "OPENSSL_NO_DYNAMIC_ENGINE" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ws2_32.lib /nologo /dll /machine:I386

!ELSEIF  "$(CFG)" == "libeay32 - Win32 Debug"

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
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "LIBEAY32_EXPORTS" /YX /FD /GZ /c
# ADD CPP /nologo /MD /W3 /GX /ZI /Od /I "../../inc32" /I "../../tmp32dll" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "LIBEAY32_EXPORTS" /D "MK1MF_BUILD" /D "OPENSSL_USE_APPLINK" /D "WIN32_LEAN_AND_MEAN" /D "OPENSSL_NO_DYNAMIC_ENGINE" /YX /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG"
# ADD RSC /l 0x804 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ws2_32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "libeay32 - Win32 Release"
# Name "libeay32 - Win32 Debug"
# Begin Group "aes"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\crypto\aes\aes_cbc.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\aes\aes_cfb.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\aes\aes_core.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\aes\aes_ctr.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\aes\aes_ecb.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\aes\aes_misc.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\aes\aes_ofb.c
# End Source File
# End Group
# Begin Group "asn1"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\crypto\asn1\a_bitstr.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\asn1\a_bool.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\asn1\a_bytes.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\asn1\a_d2i_fp.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\asn1\a_digest.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\asn1\a_dup.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\asn1\a_enum.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\asn1\a_gentm.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\asn1\a_hdr.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\asn1\a_i2d_fp.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\asn1\a_int.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\asn1\a_mbstr.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\asn1\a_meth.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\asn1\a_object.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\asn1\a_octet.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\asn1\a_print.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\asn1\a_set.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\asn1\a_sign.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\asn1\a_strex.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\asn1\a_strnid.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\asn1\a_time.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\asn1\a_type.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\asn1\a_utctm.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\asn1\a_utf8.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\asn1\a_verify.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\asn1\asn1_err.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\asn1\asn1_gen.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\asn1\asn1_lib.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\asn1\asn1_par.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\asn1\asn_moid.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\asn1\asn_pack.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\asn1\d2i_pr.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\asn1\d2i_pu.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\asn1\evp_asn1.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\asn1\f_enum.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\asn1\f_int.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\asn1\f_string.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\asn1\i2d_pr.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\asn1\i2d_pu.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\asn1\n_pkey.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\asn1\nsseq.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\asn1\p5_pbe.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\asn1\p5_pbev2.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\asn1\p8_pkey.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\asn1\t_bitst.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\asn1\t_crl.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\asn1\t_pkey.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\asn1\t_req.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\asn1\t_spki.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\asn1\t_x509.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\asn1\t_x509a.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\asn1\tasn_dec.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\asn1\tasn_enc.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\asn1\tasn_fre.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\asn1\tasn_new.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\asn1\tasn_typ.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\asn1\tasn_utl.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\asn1\x_algor.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\asn1\x_attrib.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\asn1\x_bignum.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\asn1\x_crl.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\asn1\x_exten.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\asn1\x_info.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\asn1\x_long.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\asn1\x_name.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\asn1\x_pkey.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\asn1\x_pubkey.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\asn1\x_req.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\asn1\x_sig.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\asn1\x_spki.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\asn1\x_val.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\asn1\x_x509.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\asn1\x_x509a.c
# End Source File
# End Group
# Begin Group "bf"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\crypto\bf\bf_cfb64.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\bf\bf_ecb.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\bf\bf_enc.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\bf\bf_ofb64.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\bf\bf_skey.c
# End Source File
# End Group
# Begin Group "bio"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\crypto\bio\b_dump.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\bio\b_print.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\bio\b_sock.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\bio\bf_buff.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\bio\bf_lbuf.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\bio\bf_nbio.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\bio\bf_null.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\bio\bio_cb.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\bio\bio_err.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\bio\bio_lib.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\bio\bss_acpt.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\bio\bss_bio.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\bio\bss_conn.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\bio\bss_dgram.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\bio\bss_fd.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\bio\bss_file.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\bio\bss_log.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\bio\bss_mem.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\bio\bss_null.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\bio\bss_sock.c
# End Source File
# End Group
# Begin Group "bn"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\crypto\bn\bn_add.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\bn\bn_asm.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\bn\bn_blind.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\bn\bn_const.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\bn\bn_ctx.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\bn\bn_depr.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\bn\bn_div.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\bn\bn_err.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\bn\bn_exp.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\bn\bn_exp2.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\bn\bn_gcd.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\bn\bn_gf2m.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\bn\bn_kron.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\bn\bn_lib.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\bn\bn_mod.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\bn\bn_mont.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\bn\bn_mpi.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\bn\bn_mul.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\bn\bn_nist.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\bn\bn_prime.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\bn\bn_print.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\bn\bn_rand.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\bn\bn_recp.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\bn\bn_shift.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\bn\bn_sqr.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\bn\bn_sqrt.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\bn\bn_word.c
# End Source File
# Begin Source File

SOURCE="..\..\crypto\bn\vms-helper.c"
# End Source File
# End Group
# Begin Group "buffer"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\crypto\buffer\buf_err.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\buffer\buffer.c
# End Source File
# End Group
# Begin Group "cast"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\crypto\cast\c_cfb64.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\cast\c_ecb.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\cast\c_enc.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\cast\c_ofb64.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\cast\c_skey.c
# End Source File
# End Group
# Begin Group "comp"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\crypto\comp\c_rle.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\comp\c_zlib.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\comp\comp_err.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\comp\comp_lib.c
# End Source File
# End Group
# Begin Group "conf"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\crypto\conf\conf_api.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\conf\conf_def.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\conf\conf_err.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\conf\conf_lib.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\conf\conf_mall.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\conf\conf_mod.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\conf\conf_sap.c
# End Source File
# End Group
# Begin Group "des"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\crypto\des\cbc3_enc.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\des\cbc_cksm.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\des\cbc_enc.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\des\cfb64ede.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\des\cfb64enc.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\des\cfb_enc.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\des\des_enc.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\des\des_old.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\des\des_old2.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\des\ecb3_enc.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\des\ecb_enc.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\des\ede_cbcm_enc.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\des\enc_read.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\des\enc_writ.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\des\fcrypt.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\des\fcrypt_b.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\des\ofb64ede.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\des\ofb64enc.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\des\ofb_enc.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\des\pcbc_enc.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\des\qud_cksm.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\des\rand_key.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\des\read2pwd.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\des\rpc_enc.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\des\set_key.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\des\str2key.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\des\xcbc_enc.c
# End Source File
# End Group
# Begin Group "dh"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\crypto\dh\dh_asn1.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\dh\dh_check.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\dh\dh_depr.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\dh\dh_err.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\dh\dh_gen.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\dh\dh_key.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\dh\dh_lib.c
# End Source File
# End Group
# Begin Group "dsa"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\crypto\dsa\dsa_asn1.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\dsa\dsa_depr.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\dsa\dsa_err.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\dsa\dsa_gen.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\dsa\dsa_key.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\dsa\dsa_lib.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\dsa\dsa_ossl.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\dsa\dsa_sign.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\dsa\dsa_vrf.c
# End Source File
# End Group
# Begin Group "dso"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\crypto\dso\dso_dl.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\dso\dso_dlfcn.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\dso\dso_err.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\dso\dso_lib.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\dso\dso_null.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\dso\dso_openssl.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\dso\dso_vms.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\dso\dso_win32.c
# End Source File
# End Group
# Begin Group "ec"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\crypto\ec\ec2_mult.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\ec\ec2_smpl.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\ec\ec_asn1.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\ec\ec_check.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\ec\ec_curve.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\ec\ec_cvt.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\ec\ec_err.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\ec\ec_key.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\ec\ec_lib.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\ec\ec_mult.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\ec\ec_print.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\ec\ecp_mont.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\ec\ecp_nist.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\ec\ecp_smpl.c
# End Source File
# End Group
# Begin Group "ecdh"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\crypto\ecdh\ech_err.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\ecdh\ech_key.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\ecdh\ech_lib.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\ecdh\ech_ossl.c
# End Source File
# End Group
# Begin Group "ecdsa"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\crypto\ecdsa\ecs_asn1.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\ecdsa\ecs_err.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\ecdsa\ecs_lib.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\ecdsa\ecs_ossl.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\ecdsa\ecs_sign.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\ecdsa\ecs_vrf.c
# End Source File
# End Group
# Begin Group "engine"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\crypto\engine\eng_all.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\engine\eng_cnf.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\engine\eng_cryptodev.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\engine\eng_ctrl.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\engine\eng_dyn.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\engine\eng_err.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\engine\eng_fat.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\engine\eng_init.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\engine\eng_lib.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\engine\eng_list.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\engine\eng_openssl.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\engine\eng_padlock.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\engine\eng_pkey.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\engine\eng_table.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\engine\tb_cipher.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\engine\tb_dh.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\engine\tb_digest.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\engine\tb_dsa.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\engine\tb_ecdh.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\engine\tb_ecdsa.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\engine\tb_rand.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\engine\tb_rsa.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\engine\tb_store.c
# End Source File
# End Group
# Begin Group "err"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\crypto\err\err.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\err\err_all.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\err\err_prn.c
# End Source File
# End Group
# Begin Group "evp"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\crypto\evp\bio_b64.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\evp\bio_enc.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\evp\bio_md.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\evp\bio_ok.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\evp\c_all.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\evp\c_allc.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\evp\c_alld.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\evp\digest.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\evp\e_aes.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\evp\e_bf.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\evp\e_cast.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\evp\e_des.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\evp\e_des3.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\evp\e_idea.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\evp\e_null.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\evp\e_old.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\evp\e_rc2.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\evp\e_rc4.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\evp\e_rc5.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\evp\e_xcbc_d.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\evp\encode.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\evp\evp_acnf.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\evp\evp_enc.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\evp\evp_err.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\evp\evp_key.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\evp\evp_lib.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\evp\evp_pbe.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\evp\evp_pkey.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\evp\m_dss.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\evp\m_dss1.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\evp\m_ecdsa.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\evp\m_md2.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\evp\m_md4.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\evp\m_md5.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\evp\m_mdc2.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\evp\m_null.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\evp\m_ripemd.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\evp\m_sha.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\evp\m_sha1.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\evp\names.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\evp\openbsd_hw.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\evp\p5_crpt.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\evp\p5_crpt2.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\evp\p_dec.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\evp\p_enc.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\evp\p_lib.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\evp\p_open.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\evp\p_seal.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\evp\p_sign.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\evp\p_verify.c
# End Source File
# End Group
# Begin Group "hmac"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\crypto\hmac\hmac.c
# End Source File
# End Group
# Begin Group "idea"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\crypto\idea\i_cbc.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\idea\i_cfb64.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\idea\i_ecb.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\idea\i_ofb64.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\idea\i_skey.c
# End Source File
# End Group
# Begin Group "krb5"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\crypto\krb5\krb5_asn.c
# End Source File
# End Group
# Begin Group "lhash"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\crypto\lhash\lh_stats.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\lhash\lhash.c
# End Source File
# End Group
# Begin Group "md2"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\crypto\md2\md2_dgst.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\md2\md2_one.c
# End Source File
# End Group
# Begin Group "md4"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\crypto\md4\md4_dgst.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\md4\md4_one.c
# End Source File
# End Group
# Begin Group "md5"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\crypto\md5\md5_dgst.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\md5\md5_one.c
# End Source File
# End Group
# Begin Group "mdc2"

# PROP Default_Filter ""
# End Group
# Begin Group "objects"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\crypto\objects\o_names.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\objects\obj_dat.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\objects\obj_err.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\objects\obj_lib.c
# End Source File
# End Group
# Begin Group "ocsp"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\crypto\ocsp\ocsp_asn.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\ocsp\ocsp_cl.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\ocsp\ocsp_err.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\ocsp\ocsp_ext.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\ocsp\ocsp_ht.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\ocsp\ocsp_lib.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\ocsp\ocsp_prn.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\ocsp\ocsp_srv.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\ocsp\ocsp_vfy.c
# End Source File
# End Group
# Begin Group "pem"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\crypto\pem\pem_all.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\pem\pem_err.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\pem\pem_info.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\pem\pem_lib.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\pem\pem_oth.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\pem\pem_pk8.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\pem\pem_pkey.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\pem\pem_seal.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\pem\pem_sign.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\pem\pem_x509.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\pem\pem_xaux.c
# End Source File
# End Group
# Begin Group "pkcs7"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\crypto\pkcs7\example.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\pkcs7\pk7_asn1.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\pkcs7\pk7_attr.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\pkcs7\pk7_dgst.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\pkcs7\pk7_doit.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\pkcs7\pk7_enc.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\pkcs7\pk7_lib.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\pkcs7\pk7_mime.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\pkcs7\pk7_smime.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\pkcs7\pkcs7err.c
# End Source File
# End Group
# Begin Group "pkcs12"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\crypto\pkcs12\p12_add.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\pkcs12\p12_asn.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\pkcs12\p12_attr.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\pkcs12\p12_crpt.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\pkcs12\p12_crt.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\pkcs12\p12_decr.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\pkcs12\p12_init.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\pkcs12\p12_key.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\pkcs12\p12_kiss.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\pkcs12\p12_mutl.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\pkcs12\p12_npas.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\pkcs12\p12_p8d.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\pkcs12\p12_p8e.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\pkcs12\p12_utl.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\pkcs12\pk12err.c
# End Source File
# End Group
# Begin Group "pqueue"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\crypto\pqueue\pqueue.c
# End Source File
# End Group
# Begin Group "rand"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\crypto\rand\md_rand.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\rand\rand_egd.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\rand\rand_err.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\rand\rand_lib.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\rand\rand_nw.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\rand\rand_os2.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\rand\rand_unix.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\rand\rand_vms.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\rand\rand_win.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\rand\randfile.c
# End Source File
# End Group
# Begin Group "rc2"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\crypto\rc2\rc2_cbc.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\rc2\rc2_ecb.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\rc2\rc2_skey.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\rc2\rc2cfb64.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\rc2\rc2ofb64.c
# End Source File
# End Group
# Begin Group "rc4"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\crypto\rc4\rc4_enc.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\rc4\rc4_skey.c
# End Source File
# End Group
# Begin Group "rc5"

# PROP Default_Filter ""
# End Group
# Begin Group "ripemd"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\crypto\ripemd\rmd_dgst.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\ripemd\rmd_one.c
# End Source File
# End Group
# Begin Group "rsa"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\crypto\rsa\rsa_asn1.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\rsa\rsa_chk.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\rsa\rsa_depr.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\rsa\rsa_eay.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\rsa\rsa_err.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\rsa\rsa_gen.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\rsa\rsa_lib.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\rsa\rsa_none.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\rsa\rsa_null.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\rsa\rsa_oaep.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\rsa\rsa_pk1.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\rsa\rsa_pss.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\rsa\rsa_saos.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\rsa\rsa_sign.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\rsa\rsa_ssl.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\rsa\rsa_x931.c
# End Source File
# End Group
# Begin Group "sha"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\crypto\sha\sha1_one.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\sha\sha1dgst.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\sha\sha256.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\sha\sha512.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\sha\sha_dgst.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\sha\sha_one.c
# End Source File
# End Group
# Begin Group "stack"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\crypto\stack\stack.c
# End Source File
# End Group
# Begin Group "store"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\crypto\store\str_err.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\store\str_lib.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\store\str_mem.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\store\str_meth.c
# End Source File
# End Group
# Begin Group "threads"

# PROP Default_Filter ""
# Begin Source File

SOURCE="..\..\crypto\threads\th-lock.c"
# End Source File
# End Group
# Begin Group "txt_db"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\crypto\txt_db\txt_db.c
# End Source File
# End Group
# Begin Group "ui"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\crypto\ui\ui_compat.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\ui\ui_err.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\ui\ui_lib.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\ui\ui_openssl.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\ui\ui_util.c
# End Source File
# End Group
# Begin Group "x509"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\crypto\x509\by_dir.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\x509\by_file.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\x509\x509_att.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\x509\x509_cmp.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\x509\x509_d2.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\x509\x509_def.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\x509\x509_err.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\x509\x509_ext.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\x509\x509_lu.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\x509\x509_obj.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\x509\x509_r2x.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\x509\x509_req.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\x509\x509_set.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\x509\x509_trs.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\x509\x509_txt.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\x509\x509_v3.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\x509\x509_vfy.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\x509\x509_vpm.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\x509\x509cset.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\x509\x509name.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\x509\x509rset.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\x509\x509spki.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\x509\x509type.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\x509\x_all.c
# End Source File
# End Group
# Begin Group "x509v3"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\crypto\x509v3\pcy_cache.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\x509v3\pcy_data.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\x509v3\pcy_lib.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\x509v3\pcy_map.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\x509v3\pcy_node.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\x509v3\pcy_tree.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\x509v3\tabtest.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\x509v3\v3_akey.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\x509v3\v3_akeya.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\x509v3\v3_alt.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\x509v3\v3_bcons.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\x509v3\v3_bitst.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\x509v3\v3_conf.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\x509v3\v3_cpols.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\x509v3\v3_crld.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\x509v3\v3_enum.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\x509v3\v3_extku.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\x509v3\v3_genn.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\x509v3\v3_ia5.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\x509v3\v3_info.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\x509v3\v3_int.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\x509v3\v3_lib.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\x509v3\v3_ncons.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\x509v3\v3_ocsp.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\x509v3\v3_pci.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\x509v3\v3_pcia.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\x509v3\v3_pcons.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\x509v3\v3_pku.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\x509v3\v3_pmaps.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\x509v3\v3_prn.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\x509v3\v3_purp.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\x509v3\v3_skey.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\x509v3\v3_sxnet.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\x509v3\v3_utl.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\x509v3\v3err.c
# End Source File
# End Group
# Begin Group "ms"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\ms\uplink.c
# End Source File
# End Group
# Begin Group "engines"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\engines\e_4758cca.c
# End Source File
# Begin Source File

SOURCE=..\..\engines\e_4758cca_err.c
# End Source File
# Begin Source File

SOURCE=..\..\engines\e_aep.c
# End Source File
# Begin Source File

SOURCE=..\..\engines\e_aep_err.c
# End Source File
# Begin Source File

SOURCE=..\..\engines\e_atalla.c
# End Source File
# Begin Source File

SOURCE=..\..\engines\e_atalla_err.c
# End Source File
# Begin Source File

SOURCE=..\..\engines\e_chil.c
# End Source File
# Begin Source File

SOURCE=..\..\engines\e_chil_err.c
# End Source File
# Begin Source File

SOURCE=..\..\engines\e_cswift.c
# End Source File
# Begin Source File

SOURCE=..\..\engines\e_cswift_err.c
# End Source File
# Begin Source File

SOURCE=..\..\engines\e_gmp.c
# End Source File
# Begin Source File

SOURCE=..\..\engines\e_gmp_err.c
# End Source File
# Begin Source File

SOURCE=..\..\engines\e_nuron.c
# End Source File
# Begin Source File

SOURCE=..\..\engines\e_nuron_err.c
# End Source File
# Begin Source File

SOURCE=..\..\engines\e_sureware.c
# End Source File
# Begin Source File

SOURCE=..\..\engines\e_sureware_err.c
# End Source File
# Begin Source File

SOURCE=..\..\engines\e_ubsec.c
# End Source File
# Begin Source File

SOURCE=..\..\engines\e_ubsec_err.c
# End Source File
# End Group
# Begin Source File

SOURCE=..\..\crypto\cpt_err.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\cryptlib.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\cversion.c

!IF  "$(CFG)" == "libeay32 - Win32 Release"

# ADD CPP /D "MK1MF_BUILD"

!ELSEIF  "$(CFG)" == "libeay32 - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\crypto\ebcdic.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\ex_data.c
# End Source File
# Begin Source File

SOURCE=..\..\ms\libeay32.def
# End Source File
# Begin Source File

SOURCE=..\..\crypto\mem.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\mem_clr.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\mem_dbg.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\o_dir.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\o_str.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\o_time.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\tmdiff.c
# End Source File
# Begin Source File

SOURCE=..\..\crypto\uid.c
# End Source File
# End Target
# End Project
