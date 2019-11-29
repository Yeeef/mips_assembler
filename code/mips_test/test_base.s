BaseAddre 00000010;
addi $t0, $t1, 31;
Label 1:
addi $t0, $t1, 31;
Label 2:
addi $t0, $t1, 31;

j Label 1;

DataAddre 00000020;
Data 1:
dd 0xf0000000, 0xff000000;
dw 0x0000, 0x1111;
db 0xff, 0xff, 0xff, 0xff;


