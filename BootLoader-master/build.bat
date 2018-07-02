@echo off
REM C:\pemicro\pkgcfz_pro\BootLoader-master\BootLoader-master\build.bat
REM This file is used to build a GNU m68k-elf target application
REM Windows NT/2000/XP
REM WinIDE Version 2.35, P&E Microcomputer Systems, Inc.
REM Copyright (c) 2005 P&E Microcomputer Systems, Inc.
REM http://www.pemicro.com


cd C:\pemicro\PKGCFZ~1\BOOTLO~1\BOOTLO~1
C:

REM files to build
set SRCFILE0=C:\pemicro\PKGCFZ~1\BOOTLO~1\BOOTLO~1\main.c
set SRCFILE1=C:\pemicro\PKGCFZ~1\BOOTLO~1\BOOTLO~1\pe_crt0_MCF51ACxA_MCF51ACxB.S
set SRCFILE2=C:\pemicro\PKGCFZ~1\BOOTLO~1\BOOTLO~1\pe_hooks.c
set SRCFILE3=C:\pemicro\PKGCFZ~1\BOOTLO~1\BOOTLO~1\pe_vectors_MCF51ACx.c
set SRCFILE4=C:\pemicro\PKGCFZ~1\BOOTLO~1\BOOTLO~1\console.c
set SRCFILE5=C:\pemicro\PKGCFZ~1\BOOTLO~1\BOOTLO~1\adc.c
set SRCFILE6=C:\pemicro\PKGCFZ~1\BOOTLO~1\BOOTLO~1\power_control.c
set SRCFILE7=C:\pemicro\PKGCFZ~1\BOOTLO~1\BOOTLO~1\lithium.c
set SRCFILE8=C:\pemicro\PKGCFZ~1\BOOTLO~1\BOOTLO~1\util.c
set SRCFILE9=C:\pemicro\PKGCFZ~1\BOOTLO~1\BOOTLO~1\op_status.c
set SRCFILE10=C:\pemicro\PKGCFZ~1\BOOTLO~1\BOOTLO~1\time_code.c
set SRCFILE11=C:\pemicro\PKGCFZ~1\BOOTLO~1\BOOTLO~1\deploy.c
set SRCFILE12=C:\pemicro\PKGCFZ~1\BOOTLO~1\BOOTLO~1\telecommand.c
set SRCFILE13=C:\pemicro\PKGCFZ~1\BOOTLO~1\BOOTLO~1\mag.c
set SRCFILE14=C:\pemicro\PKGCFZ~1\BOOTLO~1\BOOTLO~1\dac_ctl.c
set SRCFILE15=C:\pemicro\PKGCFZ~1\BOOTLO~1\BOOTLO~1\st_imu1.c
set SRCFILE16=C:\pemicro\PKGCFZ~1\BOOTLO~1\BOOTLO~1\mram.c
set SRCFILE17=C:\pemicro\PKGCFZ~1\BOOTLO~1\BOOTLO~1\fsw_ctl.c
set SRCFILE18=C:\pemicro\PKGCFZ~1\BOOTLO~1\BOOTLO~1\telemetry.c

REM ELF output file
set ELFFILE=C:\pemicro\PKGCFZ~1\BOOTLO~1\BOOTLO~1\main.elf

REM linker script
set LINKERSCRIPT=C:\pemicro\PKGCFZ~1\BOOTLO~1\BOOTLO~1\pe_MCF51ACxA_MCF51ACxB.ld

REM s-record output file
set S19=C:\pemicro\PKGCFZ~1\BOOTLO~1\BOOTLO~1\main.s19

REM assembler listing file
set LISTING=C:\pemicro\PKGCFZ~1\BOOTLO~1\BOOTLO~1\main.lst

REM error log file
set ERRLOG=C:\pemicro\PKGCFZ~1\BOOTLO~1\BOOTLO~1\err.log

REM READELF input file
set DEBUGDUMPIN=C:\pemicro\PKGCFZ~1\BOOTLO~1\BOOTLO~1\main.elf

REM READELF output file
set DEBUGDUMPOUT=C:\pemicro\PKGCFZ~1\BOOTLO~1\BOOTLO~1\elfdwarf_dump.txt

REM binary search path
PATH C:\pemicro\PKGCFZ~1\pkgcfz;C:\pemicro\PKGCFZ~1\gnu\bin;C:\pemicro\PKGCFZ~1\gnu\m68k-elf\bin;C:\pemicro\PKGCFZ~1\gnu\lib\gcc-lib\m68k-elf\2.95.3;C:\pemicro\PKGCFZ~1\pkgcfz

REM include path
set INCPATH=-IC:\pemicro\PKGCFZ~1\pkgcfz -IC:\pemicro\PKGCFZ~1\gnu\lib\gcc-lib\m68k-elf\295~1.3\include -IC:\pemicro\PKGCFZ~1\gnu\m68k-elf\include -IC:\pemicro\PKGCFZ~1\gnu\m68k-elf\lib\m5200\mhwdiv

REM library path
set LIBPATH=-Xlinker -L -Xlinker C:\pemicro\PKGCFZ~1\pkgcfz -Xlinker -L -Xlinker C:\pemicro\PKGCFZ~1\gnu\m68k-elf\lib\m5200\mhwdiv -Xlinker -L -Xlinker C:\pemicro\PKGCFZ~1\gnu\lib\gcc-lib\m68k-elf\295~1.3\m5200\mhwdiv

REM general flags
set GENFLAGS=-m5200 -mhwdiv -mmac -Wall -gdwarf-2 -O03 -Wa,-a=C:\pemicro\PKGCFZ~1\BOOTLO~1\BOOTLO~1\main.lst

REM symbols passed directly to linker
set USRSYMB=

REM commands to compile and link
set LINK=%GENFLAGS% -T %LINKERSCRIPT% %INCPATH% %USRSYMB%


REM build
m68k-elf-gcc.exe %LINK% -nostartfiles %LIBPATH% %SRCFILE0% %SRCFILE1% %SRCFILE2% %SRCFILE3% %SRCFILE4% %SRCFILE5% %SRCFILE6% %SRCFILE7% %SRCFILE8% %SRCFILE9% %SRCFILE10% %SRCFILE11% %SRCFILE12% %SRCFILE13% %SRCFILE14% %SRCFILE15% %SRCFILE16% %SRCFILE17% %SRCFILE18% -o %ELFFILE% 2> %ERRLOG%
wait_for_file_to_be_available.exe %ELFFILE%
wait_for_file_to_be_available.exe %ERRLOG%

REM launch utilities
REM produce s19
m68k-elf-objcopy.exe -O srec %ELFFILE% %S19% 2>> %ERRLOG%
wait_for_file_to_be_available.exe %S19%
wait_for_file_to_be_available.exe %ERRLOG%

REM execute READELF
m68k-elf-readelf.exe -e -wl -wi %DEBUGDUMPIN% > %DEBUGDUMPOUT% 2>> %ERRLOG%
wait_for_file_to_be_available.exe %DEBUGDUMPOUT%
wait_for_file_to_be_available.exe %ERRLOG%
