.data
n: .byte 0
k: .byte 0
s: .space 256
negalcu: .asciiz "n = "
segalcu: .asciiz "s = "
endl: .asciiz "\n"
spatiu: .asciiz " "

.text

transformare:
li $t0, 'A' 					# $t0 = A
li $t1, 'Z' 					# $t1 = Z
li $t2, 'a'						# $t2 = a
li $t3, 'z'						# $t3 = z
li $t7, ' '

lb $t6, s 						# $t6 = s[0]
blt $t6, $t2, skip 				# if (s[0] < 'a') skip
sub $t6, 32 					# s[0] = s[0] - 32
sb $t6, s

skip:
li $t5, 1						# $t5 = i = 0

bucla:
lb $t6, s($t5) 					# $t6 = s[i]
beqz $t6, final_bucla			# if (s[i] == 0) final_bucla
bne $t6, $t7, skip1 			# if (s[i] != ' ') skip1
addi $t5, 1 					# i++
lb $t6, s($t5) 					# $t6 = s[i]
blt $t6, $t2, skip1 			# if (s[i] < 'a') skip1
sub $t6, 32 					# s[i] = s[i] - 32
sb $t6, s($t5) 

skip1:
addi $t5, 1
b bucla

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

jal transformare

li $v0, 4
la $a0, s 						# afiseaza sirul s
syscall

iesire:
li $v0, 10
syscall