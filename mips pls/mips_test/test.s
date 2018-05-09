addi $t0, $zero, 31; l
bgtz $t0, Label 2;


Label 1:
add $t1, $t0, $t0;   #4
sub $t2, $R2, $zero; #8

Label 2: 
slt $s0, $s1, $zero; #12
sw $t0, 32($s0); #16
lw $t1, 32($s0); #20

j Label 1; #24
jal Label 2; #28

slt $t0, $a0, $ra; #32
bne $t0, $ra, Label 1; #36
beq $t0, $zero, Label 2; #40
bgez $t0, Label 1;#44
bgezal $t0, Label 2;#48
lui $at, 0xFF;
eret;
syscall;

jr $t0;
jalr $t0, $t1;
jalr $t0;

mfhi $t0;
mflo $t1;
mthi $t0;
mtlo $t1;

break;

mfc0 $t0, $t1;
mfc0 $t0, $t1, 3;
mtc0 $t0, $t1;
mtc0 $t0, $t1, 4;


li $t0, 0xFFFF0000;
li $t0, 0xFFFF1111;
la $t0, 0x0000FFFF;

Label 3:
addi $t0, $t0, 0xf;
move $t0, $t1;
addi $t0, $t0, 1;
addi $t0, $t0, 1;
addi $t0, $t0, -1;
andi $t0, $t0, 1;

j Label 3;
j Label 3;










