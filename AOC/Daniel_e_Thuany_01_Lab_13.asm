# Arquivo do programa: Daniel_A_e_Thuany_01_1ab_13.asm
# Autor: Daniel Alexsandro Abrão e Thuany Muraro Soares
# Implemente o pseudocódigo abaixo em assembly MIPS/MARS
# total = 0
# for (i = 0; i < n; i++) {
# if (i % 5 > 2) continue
# total += i
# }

.text

li $t0, 0 #armazena total = 0 em t0
li $t1, 0 #armazena i=0 em t1
li $t2, 5 #armazena n=5 em t2

loop:
bgt $t2, $t1, condition 
#se i for menor que n, vai para condition
j end

condition: 
#rem a, b, n === a=b%n
rem $t3, $t1, $t2
li $t4, 2
addi $t1, $t1, 1 #i +=1
addi $t0, $t0, 1 #total += i

bgt $t3, $t4, loop #se t3 > t4, vai para loop

end:
li $v0, 10
syscall