.data
s: .space 256
n: .byte 0
negalcu: .asciiz "n = "
segalcu: .asciiz "s = "
endl: .asciiz "\n"

.text

interschimbare:

# $t0 = n
# $t1 = n/2
# $t2 = i
# $t3 = j
# $t4 = s[i]
# $t5 = s[j]

move $t0, $a0					# $t0 = n
li $t1, 2						# $t2 = 2
div $t1, $t0, $t1				# n = n/2

li $t2, 0						# i = 0
move $t3, $t1					# j = n/2

bucla_transformare:
beq $t2, $t1, final_bucla		# daca j = n final bucla
lb $t4, s($t2)					# $t4 = s[i]
lb $t5, s($t3)					# $t5 = s[j]	
sb $t5, s($t2)					# s[i] = $t5
sb $t4, s($t3)					# s[j] = $t4
addi $t2, 1 					# i++
addi $t3, 1 					# j++
j bucla_transformare

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

lb $s0, n 						# $s0 = n
move $a0, $s0					# $a0 = n

jal interschimbare

li $v0, 4
la $a0, s
syscall

li $v0, 10
syscall