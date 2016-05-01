.data

sir: .asciiz "abc"

.text

main:

subu $sp, $sp, 1		# push: incrementam varful stivei in jos
sb $0, ($sp)			# push: la adresa din sp punem un zero (ca sa se opreasca acolo la afisare)

la $s2, sir			# s2 va tine adresa de inceput a sirului
bucla:
lb $s1, ($s2)			# in s1 copiem ce este la adresa din s2
addi $s2, 1			# asciiz sunt pe 1 byte => incrementam cu 1

subu $sp, $sp, 1		# push: incrementam varful stivei in jos
sb $s1, ($sp)			# push: la adresa din sp punem s1

bnez $s1, bucla			# daca nu am ajuns la sfarsitul sirului, repetam

li $v0, 4			# vrem sa afisam string
la $a0, 1($sp)			# vrem sa afisam ce este la adresa din varful stivei plus 1 (adica delimitatorul nul pe care l-am pus cand am bagat in stiva sirul)
syscall				# evaluam cu syscall ca sa afiseze


li $v0, 10 			#oprire executie program
syscall