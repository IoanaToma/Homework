.data
n: .byte 0
k: .byte 0
s: .space 256
negalcu: .asciiz "n = "
kegalcu: .asciiz "k = "
segalcu: .asciiz "s = "
endl: .asciiz "\n"

.text

criptare:
move $t0, $a0					# $t0 = k

li $t1, 'A'
li $t2, 'Z'						# $t2 = 'Z'
sub $t1, $t2, $t1				# $t1 = 'Z' - 'A'
addi $t1, 1

li $t3, 0						# $t3 = i = 0

bucla:
lb $t4, s($t3)					# $t4 = s[i]
beqz $t4, final_bucla
add $t4, $t4, $t0				# $t4 = s[i] + k
ble $t4, $t2, skip				# if $t4 < 'Z' skip
sub $t4, $t4, $t1 				# $t4 = $t4 - ('Z' - 'A')

skip:
sb $t4, s($t3)					# s[i] = $t4
addi $t3, 1 					# i++
j bucla

final_bucla:
jr $ra

main:

li $v0, 4						# sa afiseze string
la $a0, negalcu					# n = 
syscall							# afiseaza

li $v0, 5						# sa citeasca int
syscall							# citeste (in $v0)
sb $v0, n 						# retine in n

li $v0, 4						# sa afiseze string
la $a0, kegalcu					# n = 
syscall							# afiseaza

li $v0, 5						# sa citeasca int
syscall							# citeste (in $v0)
sb $v0, k 						# retine in n

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

lb $s0, k 						# $s0 = k
move $a0, $s0					# $a0 = k

jal criptare

li $v0, 4
la $a0, s 						# afiseaza sirul s
syscall

final:
li $v0, 10
syscall