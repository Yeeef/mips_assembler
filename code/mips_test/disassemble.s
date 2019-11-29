addi $t0, $zero, 31;
bgtz $t0, Label 1;

Label 2:
add $t1, $t0, $t0;
sub $t2, $v0, $zero;

Label 1:
slt $s0, $s1, $zero;
sw $t0, 32($s0);
lw $t1, 32($s0);
j Label 2;
jal Label 1;
slt $t0, $a0, $ra;
bne $t0, $ra, Label 2;
beq $t0, $zero, Label 1;
bgez $t0, Label 2;
bgezal $t0, Label 1;
lui $at, 0xff;
eret;
syscall;
jr $t0;
jalr $t0, $t1;
jalr $ra, $t0;
mfhi $t0;
mflo $t1;
mthi $t0;
mtlo $t1;
break;
mfc0 $t0, $t1, 0;
mfc0 $t0, $t1, 3;
mtc0 $t0, $t1, 0;
mtc0 $t0, $t1, 4;
lui $at, 0xffff;
ori $t0, $at, 0x0;
lui $at, 0xffff;
ori $t0, $at, 0x1111;
lui $at, 0x0;
ori $t0, $at, 0xffff;

Label 3:
addi $t0, $t0, 15;
add $t0, $t1, $zero;
addi $t0, $t0, 1;
addi $t0, $t0, 1;
addi $t0, $t0, -1;
andi $t0, $t0, 0x1;
j Label 3;
j Label 3;