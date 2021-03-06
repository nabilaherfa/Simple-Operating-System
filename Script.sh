dd if=/dev/zero of=system.img bs=512 count=2880
dd if=/dev/zero of=sectors.img bs=512 count=1
dd if=/dev/zero of=dir.img bs=512 count=2
nasm bootloader.asm -o bootloader
dd if=bootloader of=system.img bs=512 count=1 conv=notrunc
dd if=map.img of=system.img bs=512 count=1 seek=256 conv=notrunc
dd if=dir.img of=system.img bs=512 count=2 seek=257 conv=notrunc
dd if=sectors.img of=system.img bs=512 count=1 seek=259 conv=notrunc
bcc -ansi -c -o kernel.o kernel.c
bcc -ansi -c -o mathmodule.o mathmodule.c
bcc -ansi -c -o textmodule.o textmodule.c
bcc -ansi -c -o fileIOmodule.o fileIOmodule.c
bcc -ansi -c -o folderIOmodule.o folderIOmodule.c
nasm -f as86 kernel.asm -o kernel_asm.o
ld86 -o kernel -d kernel.o kernel_asm.o mathmodule.o textmodule.o fileIOmodule.o folderIOmodule.o
dd if=kernel of=system.img bs=512 conv=notrunc seek=1
gcc loadFile.c -o loadFile
bcc -ansi -c -o shell.o shell.c
nasm -f as86 lib.asm -o lib_asm.o
ld86 -o shell -d shell.o lib_asm.o
./loadFile shell
bcc -ansi -c cat.c -o cat.o
ld86 -o cat -d cat.o lib_asm.o textmodule.o fileIOmodule.o mathmodule.o
./loadFile cat
bcc -ansi -c rm.c -o rm.o
ld86 -o rm -d rm.o lib_asm.o textmodule.o fileIOmodule.o folderIOmodule.o mathmodule.o
./loadFile rm
bcc -ansi -c mkdir.c -o mkdir.o
ld86 -o mkdir -d mkdir.o lib_asm.o
./loadFile mkdir
bcc -ansi -c mv.c -o mv.o
ld86 -o mv -d mv.o lib_asm.o
./loadFile mv
./loadFile halo.txt
rm bochsout.txt bootloader cat cat.o fileIOmodule.o folderIOmodule.o kernel kernel.o kernel_asm.o
rm lib_asm.o loadFile mathmodule.o mkdir mkdir.o rm rm.o shell shell.o textmodule.o
rm mv mv.o
echo c | bochs -f if2230.config
