.data
n: .byte 0
s: .space 256
negalcu: .asciiz "n = "
segalcu: .asciiz "s = "
endl: .asciiz "\n"

.text

oglindire:
li $t0, 0						# $t0 = i = 0
subu $sp, $sp, 1
li $t1, 0						# $t1 = 0
sb $t1, 0($sp)					# pune in varful stivei 0

bucla1:
lb $t1, s($t0)					# $t1 = s[i]
beqz $t1, final_bucla1			
subu $sp, $sp, 1 				# scade varful stivei
sb $t1, 0($sp)					# salveaza in varful stivei s[i]
addi $t0, 1 					# i++
j bucla1

final_bucla1:
li $t0, 0						# i = 0

bucla2:
lb $t1, 0($sp)					# $t1 = elementul din varful stivei
beqz $t1, final_bucla2
addu $sp, $sp, 1 				# pop
sb $t1, s($t0)					# s[i] = $t0
addi $t0, 1 					# i++
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

jal oglindire

li $v0, 4
la $a0, s 						# afiseaza sirul s
syscall

final: 
li $v0, 10
syscall