.data
n: .byte 0
s: .space 256
s1: .space 256
negalcu: .asciiz "n = "
segalcu: .asciiz "s = "
endl: .asciiz "\n"
spatiu: .asciiz " "

.text

transformare: 

move $t0, $a1 					# $t0 = numarul de caractere din sir
li $t1, 0 						# $t1 = i = 0
move $t2, $t0 					# $t2 = nr de caractere

bucla_mutare:
beqz $t2, final_bucla_mutare
lb $t3, s($t2)					# $t3 = s[i]
sb $t3, s1($t1)
addi $t1, 1
sub $t2, 1
b bucla_mutare

final_bucla_mutare:
li $t1, 0 						# i = 0
subu $sp, $sp, 1
sb $t1, 0($sp)					# pune in varful stivei 0

li $t1, 0 						# i = 0
bucla1:
lb $t2, s1($t1)					# $t2 = s[i]
beqz $t2, final_bucla1			
subu $sp, $sp, 1 				# scade varful stivei
sb $t2, 0($sp)					# salveaza in varful stivei s[i]
addi $t1, 1 					# i++
j bucla1

final_bucla1:
li $t1, 0						# i = 0

bucla2:
lb $t2, 0($sp)					# $t2 = elementul din varful stivei
li $t4, ' '
beqz $t2, final_bucla2
addu $sp, $sp, 1 				# pop
sb $t2, s($t1)					# s[i] = $t2
addi $t1, 1
sb $t4, s($t1)
addi $t1, 1 					# i++
j bucla2

final_bucla2:
jr $ra

main:

li $v0, 4						# sa afiseze string
la $a0, negalcu					# n = 
syscall							# afiseaza

li $v0, 5						# sa citeasca int
syscall							# citeste (in $v0)
sb $v0, n 						# retine in n

li $v0, 4						# sa afiseze string
la $a0, endl					# endl
syscall							# afiseaza

li $v0, 4						# sa afiseze string
la $a0, segalcu					# s = 
syscall							# afiseaza

li $v0, 8						# sa citeasca string
la $a0, s 						# in $a0 se salveaza adresa unde va fi memorat sirul
lb $a1, n 						# in $a1 se salveaza numarul de elemente+1 cate vor fi citite
addi $a1, 1
syscall

li $v0, 4						# sa afiseze string
la $a0, endl					# endl
syscall							# afiseaza

li $v0, 4
la $a0, s 						# afiseaza sirul s
syscall

li $v0, 4						# sa afiseze string
la $a0, endl					# endl
syscall							# afiseaza

li $s1, 0						# $s1 = i = 0
bucla_numarare:
lb $t2, s($s1)
beqz $t2, final_bucla_numarare
addi $s1, 1
b bucla_numarare

final_bucla_numarare:
move $a1, $s1 					# $a1 = numarul de caractere din sir

jal transformare

li $v0, 4						# sa afiseze string
la $a0, s						# s
syscall							# afiseaza

iesire:
li $v0, 10
syscall