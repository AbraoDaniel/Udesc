#Projeto do arquivo: Daniel_e_Thuany_Lab-13.asm
#Autor: Daniel Alexsandro Abrão e Thuany Muraro
#Programa que calcula fatorial de um número informado pelo usuário

.text

	main:
	li $t1, 1 # Passando o valor inicial do fatorial para dentro do registrador t1
	li $v0, 4 # Imprimindo a mensagem para o usuário informar o valor desejado
	la $a0, entrada
	syscall

	li $v0, 5 #Recebendo o valor informado pelo usuário e armazena em $v0
	syscall

	move $t0, $v0 # Move o valor presente em $v0 para o registrador $t0
		
	fatorial:
	
	bgt $t0, 1, operandoMult # Compara o valor presente no registrador $t0, para saber se o valor é maior que 1
	
	li $v0, 4 # Caso tenhamos o valor igual a 1, ele cai nessa condição e imprime a mensagem 
	la $a0, saida
	syscall
	
	li $v0, 1 # Informando a resultante fatorial final
	la $a0, ($t1)
	syscall
	
	li $v0, 10 # Finalizando o processo com o HALT
	syscall
	
	operandoMult:
	mul $t1, $t1, $t0 # Realizando multiplicação de variáveis para obter a resultante do cálculo fatorial
	subi $t0, $t0, 1 # Após o processo, subtrai-se uma unidade do contador do fatorial para prosseguir com o processo
	j fatorial # realizando o jump para a linha onde possui-se o label "fatorial", afim de continuar o processo
	
.data
	entrada: .asciiz "Informe o valor que deseja saber o respectivo fatorial: "
	saida: .asciiz "\n O fatorial do número informado é:  "

