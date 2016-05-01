.data
n: .byte 0
p: .byte 0
v: .space 256
negalcu: .asciiz "n = "
vegalcu: .asciiz "v = "
pegalcu: .asciiz "p = "
endl: .asciiz "\n"
spatiu: .asciiz " "

.text

putere:
move $t0, $s0						# $t0 = p
move $t1, $a1						# $t1 = v[i]

li $t3, 1							# Pr = 1
li $t2, 0							# i = 0
bucla:
beq $t2, $t0, final_bucla
mulo $t3, $t3, $t1					# Pr = Pr*x
addi $t2, 1 						# i++
j bucla

final_bucla:
move $v0, $t3						# $v0 = P
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

li $v0, 4
la $a0, pegalcu						# afiseaza "p="
syscall

li $v0, 5
syscall								# citeste p
sb $v0, p

lb $s0, p 							# $s0 = p
move $a0, $s0						# $a0 = p

li $s2, 0							# i = 0
li $s4, 0							# S = 0

bucla_suma:
beq $s2, $s1, final_suma			# if (i == n) j final_suma
lb $s3, v($s2)						# $s3 = v[i]
move $a1, $s3						# $a1 = v[i]
jal putere							# ridica v[i] la puterea p
move $s5, $v0						# $s5 = Pr
add $s4, $s4, $s5					# S = S + Pr
addi $s2, 1 						# i++
j bucla_suma

final_suma:
li $v0, 4
la $a0, endl						# afiseaza endl
syscall

li $v0, 1
move $a0, $s4						# afiseaza S
syscall

final:
li $v0, 10
syscall
