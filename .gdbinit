set $MAX_LIV=4
set $MAX_SEM=1024
set $SEL_CODICE_SISTEMA=8
set $SEL_CODICE_UTENTE=19
set $SEL_DATI_UTENTE=27
set $MAX_PROC=1024
set $MAX_PRIORITY=1023
set $MIN_PRIORITY=1
set $I_SIS_C=0
set $I_SIS_P=1
set $I_MIO_C=2
set $I_UTN_C=256
set $I_UTN_P=384
set print static off
set print pretty on
set print array on
set pagination off
file build/sistema
source util/start.gdb
add-symbol-file /home/studenti/CE/lib/ce/boot.bin
add-symbol-file build/io
add-symbol-file build/utente
set arch i386:x86-64:intel
target remote gdb-socket
set wait_for_gdb=0
break sistema.s:start
continue
delete 1
source /home/studenti/CE/lib64/ce/libce-debug.py
source debug/nucleo.py
context
