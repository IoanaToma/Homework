.data
n: .byte 0
a: .space 256								# a = matricea
negalcu: .asciiz "n="
endline: .asciiz "\n"
spatiu: .asciiz " "
aegalcu: .asciiz "Dati elementele matricei:"

.text

suma:
li $s1, 0
li $s2, 0
la $s4, a
add $s5, $s5, $s3
addi $s5, 1
mulo $s3, $s3, $s3

bucla:
bgt $s1, $s3, final_bucla
lb $s6, ($s4)
add $s2, $s2, $s6
add $s4,$s4,$s5
add $s1, $s1, $s5
j bucla

final_bucla:
jr $ra


main:

li $v0, 4
la $a0, negalcu								# afiseaza "n = "								
syscall

li $v0, 5
syscall										# citeste n
sb $v0, n

li $v0, 4
la $a0, endline								# endl
syscall

li $v0, 4
la $a0, aegalcu								# "Dati elementele matricei"
syscall

li $t1, 0									# $t1 = i = 0
lb $t3, n 									# $t3 = n
la $t4, a 									# $t4 = a

for_i:
beq $t1, $t3, final_for_i					# i == n final_for_i
li $t2, 0 									# $t2 = j = 0

for_j:
beq $t2, $t3, final_for_j					# j == n final_for_j

li $v0, 5
syscall										# citeste a[i][j]
sb $v0, ($t4)

addi $t2, 1 								# j++
addi $t4, 1 								# a++, adica trece la urmatoarea locatie de memorie
j for_j

final_for_j:
addi $t1, 1 								# i++
j for_i

final_for_i:

li $t1, 0									# $t1 = i = 0
la $t4, a 									# $t4 = a

bucla_afisare_i:
beq $t1, $t3, final_i 						# i == n final_i
li $t2, 0 									# $t2 = j = 0

bucla_afisare_j:
beq $t2, $t3, final_j 						# j == n final_j

li $v0, 1
lb $a0, ($t4) 								# afiseaza a[i][j]
syscall

li $v0, 4
la $a0, spatiu 								# afiseaza spatiu
syscall

addi $t2, 1 								# j++
addi $t4, 1 								# a++
j bucla_afisare_j

final_j:
addi $t1, 1 								# i++

li $v0, 4
la $a0, endline 							# endl
syscall
j bucla_afisare_i

final_i:
move $s3, $t3
jal suma

li $v0, 1
move $a0, $s2
syscall

li $v0, 10
syscall 


