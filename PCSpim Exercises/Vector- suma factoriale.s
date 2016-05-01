.data
negalcu: .asciiz "n="
endline: .asciiz "\n"
vegalcu: .asciiz "Dati elementele vectorului:"
spatiu: .asciiz " "
n: .byte 0
v: .space 256

.text

factorial:
li $s1, 1
li $s2, 1
bucla_produs:
bgt $s2, $s3, final_produs 
mulo $s1, $s1, $s2
addi $s2, 1
j bucla_produs
final_produs:
jr $ra


main:

li $v0, 4
la $a0, negalcu
syscall

li $v0, 5
syscall
sb $v0, n

li $v0, 4
la $a0, endline
syscall

li $v0, 4
la $a0, vegalcu
syscall

li $t1, 0
la $t2, v
lb $t3, n

bucla_citire:

beq $t1, $t3, final_citire
li $v0, 5
syscall
sb $v0, ($t2)
addi $t1, 1
addi $t2, 1 
j bucla_citire

final_citire:

li $t1, 0
la $t2, v

bucla_afisare:

beq $t1, $t3, final_afisare
li $v0, 1
lb $a0, ($t2)
syscall
li $v0, 4
la $a0, spatiu
syscall
addi $t1, 1
addi $t2, 1
j bucla_afisare

final_afisare:

li $v0, 4
la $a0, endline
syscall

li $t1, 0
la $t2, v
li $t9, 0

bucla_suma:
beq $t1, $t3, final_program
lb $s3, ($t2)
jal factorial
add $t9, $t9, $s1
addi $t1, 1
addi $t2, 1
j bucla_suma


final_program: 
li $v0, 1
move $a0, $t9
syscall

li $v0, 10
syscall