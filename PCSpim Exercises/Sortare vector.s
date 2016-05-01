.data
n: .byte 0
v: .space 256
negalcu: .asciiz "n = "
vegalcu: .asciiz "v = "
pegalcu: .asciiz "p = "
endl: .asciiz "\n"
spatiu: .asciiz " "

.text

sortare:
move $t0, $a0						# $t0 = n
li $t1, 0 							# $t1 = i = 0

bucla1:
beq $t1, $t0, final_bucla1 			# if (i == n) final_bucla1
move $t2, $t1 						# $t2 = j = i
addi $t2, 1 						# $t2 = j = i+1

bucla2:
beq $t2, $t0, final_bucla2 			# if (j == n) final_bucla2
lb $t3, v($t1) 						# $t3 = v[i]
lb $t4, v($t2) 						# $t4 = v[j]
ble $t3, $t4, skip 					# if (v[i] <= v[j]) skip
sb $t3, v($t2)						# v[j] = v[i]
sb $t4, v($t1)						# v[i] = v[j]

skip:
addi $t2, 1 						# j++
b bucla2

final_bucla2:
addi $t1, 1 						# i++
b bucla1

final_bucla1:
move $v0, $t0 						# $v0 = n
jr $ra




main:

li $v0, 4
la $a0, negalcu						# afiseaza "n="
syscall

li $v0, 5
syscall								# citeste n
sb $v0, n

li $v0, 4
la $a0, vegalcu						# afiseaza "v="
syscall

li $s0, 0							# i = 0
lb $s1, n 							# $s1 = n

bucla_citire_v:
beq $s0, $s1, final_citire_v

li $v0, 5				
syscall								# citeste v[i]
sb $v0, v($s0)

addi $s0, 1 						# i++
j bucla_citire_v

final_citire_v:
li $v0, 4
la $a0, endl						# afiseaza endl
syscall

li $s0, 0							# i = 0
bucla_afisare_v:
beq $s0, $s1, final_afisare_v		# if (i == n) j final

li $v0, 1
lb $a0, v($s0)						# afiseaza v[i]
syscall

li $v0, 4
la $a0, spatiu						# afiseaza " "
syscall

addi $s0, 1 						# i++
j bucla_afisare_v

final_afisare_v:
li $v0, 4
la $a0, endl						# afiseaza endl
syscall

move $a0, $s1 						# $a0 = n
jal sortare

move $s1, $v0
li $s0, 0							# i = 0
bucla_afisare_v1:
beq $s0, $s1, final_afisare_v1		# if (i == n) j final

li $v0, 1
lb $a0, v($s0)						# afiseaza v[i]
syscall

li $v0, 4
la $a0, spatiu						# afiseaza " "
syscall

addi $s0, 1 						# i++
j bucla_afisare_v1

final_afisare_v1:

iesire:
li $v0, 10
syscall