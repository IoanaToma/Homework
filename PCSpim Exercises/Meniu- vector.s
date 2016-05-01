.data
v: .space 256
n: .byte 0
k: .byte 0
s1: .asciiz "1. Suma elementelor\n"
s2: .asciiz "2. Ultimul element din vector\n"
s3: .asciiz "3. Elemente mai mari decat n\n"
s4: .asciiz "4. Iesire din problema\n"
s5: .asciiz "5. Introduceti optiunea: "
negalcu: .asciiz "n = "
kegalcu: .asciiz "k = "
vegalcu: .asciiz "v = "
spatiu: .asciiz " "
endl: .asciiz "\n"

.text

suma_elem:
move $t0, $a0				# $t0 = n
li $t1, 0 					# $t1 = S = 0
li $t2, 0 					# $t2 = i = 0

bucla:
beq $t2, $t0, final_bucla
lb $t3, v($t2)
add $t1, $t1, $t3
addi $t2, 1
b bucla

final_bucla:
move $v0, $t1
jr $ra

elem_n:
move $t0, $a1				# $t0 = n
li $t1, 0					# $t1 = i = 0
li $t2, 0 					# $t2 = nr = 0

bucla1:
beq $t1, $t0, final_bucla1
lb $t3, v($t1)
ble $t3, $t0, skip
addi $t2, 1

skip:
addi $t1, 1
b bucla1

final_bucla1:
move $v0, $t2
jr $ra

main:
li $v0, 4
la $a0, negalcu				# afiseaza "n = "
syscall

li $v0, 5
syscall						# citeste n
sb $v0, n

li $v0, 4
la $a0, vegalcu				# afiseaza "v = "
syscall

lb $s0, n 					# $s0 = n				
li $s1, 0					# $s1 = i = 0

bucla_citire:
beq $s1, $s0, final_citire	# if (i == n) final_citire

li $v0, 5
syscall
sb $v0, v($s1)				# v[i] = $v0

addi $s1, 1
b bucla_citire

final_citire:
li $s1, 0

bucla_afisare:
beq $s1, $s0, menu

li $v0, 1
lb $a0, v($s1)				# afiseaza v[i]
syscall

li $v0, 4
la $a0, spatiu				# afiseaza " "
syscall

addi $s1, 1
b bucla_afisare

menu:
li $v0, 4
la $a0, endl				
syscall

li $v0, 4
la $a0, s1				
syscall

li $v0, 4
la $a0, s2				
syscall

li $v0, 4
la $a0, s3				
syscall

li $v0, 4
la $a0, s4				
syscall

li $v0, 4
la $a0, s5				
syscall

li $v0, 5
syscall
sb $v0, k

lb $s5, k 					# $s5 = k
li $s1, 1
li $s2, 2
li $s3, 3
li $s4, 4

beq $s5, $s1, suma
beq $s5, $s2, ultim
beq $s5, $s3, elem
beq $s5, $s4, iesire
b menu

suma:
move $a0, $s0
jal suma_elem
move $s6, $v0				# $s6 = S

li $v0, 1
move $a0, $s6
syscall

b menu

ultim:
li $s7, 1
sub $s6, $s0, $s7				# $s6 = n-1

li $v0, 1
lb $a0, v($s6)
syscall

b menu

elem:
move $a1, $s0
jal elem_n
move $s6, $v0

li $v0, 1
move $a0, $s6
syscall

b menu

iesire:
li $v0 10
syscall