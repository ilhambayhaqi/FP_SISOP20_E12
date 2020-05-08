# FP_SISOP20_E12

## Command :
### CD
CD belum bisa berfungsi, agar berfungsi maka fungsi chdir harus diletakkan pada proses utama.
### TREE
Belum diimplementasikan
### CMP
cmp.c   : cmp [file1] [file2]
### MD5SUM
md5sum.c : md5sum [option] [file]  
Option
- "-a [file]" : untuk MD5 pada file pada seluruh byte
- "-f [file]" : untuk MD5 pada file pada byte tiap line
- string      : untuk MD5 pada string (belum bisa untuk string dengan spasi)
### BASE64
base64.c  : base64 [option] [file]
Option
- [file]      : untuk encode ke base64
- "-d [file]" : untuk decode dari base64
