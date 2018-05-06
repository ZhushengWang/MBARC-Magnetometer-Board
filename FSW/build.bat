@echo off
REM D:\QB50\qb50_software\FSW\build.bat
REM This file is used to build a GNU m68k-elf target application
REM Windows NT/2000/XP
REM WinIDE Version 2.35, P&E Microcomputer Systems, Inc.
REM Copyright (c) 2005 P&E Microcomputer Systems, Inc.
REM http://www.pemicro.com


cd D:\QB50\qb50_software\FSW
D:

REM files to build
set SRCFILE0=D:\QB50\qb50_software\FSW\main.c
set SRCFILE1=D:\QB50\qb50_software\FSW\pe_crt0_MCF51ACxA_MCF51ACxB.S
set SRCFILE2=D:\QB50\qb50_software\FSW\pe_hooks.c
set SRCFILE3=D:\QB50\qb50_software\FSW\pe_vectors_MCF51ACx.c
set SRCFILE4=D:\QB50\qb50_software\FSW\console.c
set SRCFILE5=D:\QB50\qb50_software\FSW\adc.c
set SRCFILE6=D:\QB50\qb50_software\FSW\power_control.c
set SRCFILE7=D:\QB50\qb50_software\FSW\lithium.c
set SRCFILE8=D:\QB50\qb50_software\FSW\util.c
set SRCFILE9=D:\QB50\qb50_software\FSW\op_status.c
set SRCFILE10=D:\QB50\qb50_software\FSW\time_code.c
set SRCFILE11=D:\QB50\qb50_software\FSW\deploy.c
set SRCFILE12=D:\QB50\qb50_software\FSW\telecommand.c
set SRCFILE13=D:\QB50\qb50_software\FSW\mag.c
set SRCFILE14=D:\QB50\qb50_software\FSW\mtq.c
set SRCFILE15=D:\QB50\qb50_software\FSW\epson_imu2.c
set SRCFILE16=D:\QB50\qb50_software\FSW\dac_ctl.c
set SRCFILE17=D:\QB50\qb50_software\FSW\st_imu1.c
set SRCFILE18=D:\QB50\qb50_software\FSW\mram.c
set SRCFILE19=D:\QB50\qb50_software\FSW\fsw_ctl.c
set SRCFILE20=D:\QB50\qb50_software\FSW\telemetry.c
set SRCFILE21=D:\QB50\qb50_software\FSW\fipex.c
set SRCFILE22=D:\QB50\qb50_software\FSW\fipex_script.c
set SRCFILE23=D:\QB50\qb50_software\FSW\fipex_data.c
set SRCFILE24=D:\QB50\qb50_software\FSW\adcs.c
set SRCFILE25=D:\QB50\qb50_software\FSW\watchdog.c

REM ELF output file
set ELFFILE=D:\QB50\qb50_software\FSW\main.elf

REM linker script
set LINKERSCRIPT=D:\QB50\qb50_software\FSW\pe_MCF51ACxA_MCF51ACxB.ld

REM s-record output file
set S19=D:\QB50\qb50_software\FSW\main.s19

REM assembler listing file
set LISTING=D:\QB50\qb50_software\FSW\main.lst

REM error log file
set ERRLOG=D:\QB50\qb50_software\FSW\err.log

REM READELF input file
set DEBUGDUMPIN=D:\QB50\qb50_software\FSW\main.elf

REM READELF output file
set DEBUGDUMPOUT=D:\QB50\qb50_software\FSW\elfdwarf_dump.txt

REM binary search path
PATH C:\PEMicro\PKGCFZ~1\gnu\bin;C:\PEMicro\PKGCFZ~1\gnu\m68k-elf\bin;C:\PEMicro\PKGCFZ~1\gnu\lib\gcc-lib\m68k-elf\2.95.3;C:\PEMicro\PKGCFZ~1\pkgcfz\

REM include path
set INCPATH=-IC:\PEMicro\PKGCFZ~1\gnu\lib\gcc-lib\m68k-elf\295~1.3\include -IC:\PEMicro\PKGCFZ~1\gnu\m68k-elf\include -IC:\PEMicro\PKGCFZ~1\gnu\m68k-elf\lib\m5200\mhwdiv

REM library path
set LIBPATH=-Xlinker -L -Xlinker C:\PEMicro\PKGCFZ~1\gnu\m68k-elf\lib\m5200\mhwdiv -Xlinker -L -Xlinker C:\PEMicro\PKGCFZ~1\gnu\lib\gcc-lib\m68k-elf\295~1.3\m5200\mhwdiv

REM general flags
set GENFLAGS=-m5200 -mhwdiv -mmac -Wall -gdwarf-2 -O03 -Wa,-a=D:\QB50\qb50_software\FSW\main.lst

REM symbols passed directly to linker
set USRSYMB=

REM commands to compile and link
set LINK=%GENFLAGS% -T %LINKERSCRIPT% %INCPATH% %USRSYMB%


REM build
m68k-elf-gcc.exe %LINK% -nostartfiles %LIBPATH% %SRCFILE0% %SRCFILE1% %SRCFILE2% %SRCFILE3% %SRCFILE4% %SRCFILE5% %SRCFILE6% %SRCFILE7% %SRCFILE8% %SRCFILE9% %SRCFILE10% %SRCFILE11% %SRCFILE12% %SRCFILE13% %SRCFILE14% %SRCFILE15% %SRCFILE16% %SRCFILE17% %SRCFILE18% %SRCFILE19% %SRCFILE20% %SRCFILE21% %SRCFILE22% %SRCFILE23% %SRCFILE24% %SRCFILE25% -o %ELFFILE% 2> %ERRLOG%
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
