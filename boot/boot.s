.section	.text

.globl	_start
_start:
.code16
	#escreve '>' na linha
	mov	$'>', %al
	call	print_char
	loop_read_cmd:			#loop de leitura de comandos
		#le comando
		mov	$0x00, %ah	#codigo de leitura de caracter
		int	$0x16		#interrupção de teclado (armazena em %al)

		#jump de funções
		cmp	$'1', %al
		je	clear

		cmp	$'2', %al
		je	print_string_version

		cmp	$'3', %al
		je	print_string_devices

		cmp	$'4', %al
		je	print_string_memory

		cmp	$'5', %al
		je	reboot

		cmp	$13, %al
		je	enter

		#escreve a entrada do teclado
		call	print_char

		jmp	loop_read_cmd

	clear:
		movb    $0x00, %ah	#Set Video Mode
		movb    $0x03, %al	#80x25 Text
		int	    $0x10
		jmp	_start

	print_string_version:
		mov	$version, %ecx
		call	print_string
		jmp	enter

	print_string_devices:
		call	fdevices
		jmp	enter

	print_string_memory:
		call	fmemory
		jmp	enter

	reboot:
		int	$0x19		#interrupção de reboot

	enter:
		mov	$nextline, %ecx
		call	print_string
		jmp	loop_read_cmd

.type	print_char, @function
print_char:				#al <- char
	pusha

	mov	$0x0E, %ah		#codigo de inserção de caracter
	int	$0x10			#interrupção de video

	popa
	ret	

.type	print_string, @function
print_string:				#ecx <- string
	pusha

	loop_print_string:
		movb	(%ecx), %al		#coloca em al o próximo caracter da string
		cmp	$0, %al			#compara com \0
		je	end_print_string	#se for \0 pula para o fim

		call	print_char
		
		inc	%ecx			#incrementa a posição do ecx
		jmp	loop_print_string

	end_print_string:
	popa
	ret

.type	fdevices, @function
fdevices:
	pusha

	xor	%ax, %ax
	int	$0x11
	mov	%ax, %dx

	disketteIPL:
		push	%dx
		mov	$0x01, %cx
		and	%dx, %cx
		pop	%dx
		jz	coprocessor
		mov	$disketteIPL_found, %ecx
		call	print_string

	coprocessor:
		push	%dx
		mov	$0x02, %cx
		and	%dx, %cx
		pop	%dx
		jz	dma
		mov	$coprocessor_found, %ecx
		call	print_string

	dma:
		push	%dx
		mov	$0x100, %cx
		and	%dx, %cx
		pop	%dx
		jnz	devices_end
		mov	$dma_found, %ecx
		call	print_string

	devices_end:
	popa
	ret


.type	fmemory, @function
fmemory:
	pusha

	mov	$hexStr, %ecx
	call	print_string

	xor	%ax, %ax  	#Limpa Parametro de Retorno da Interrupção 
	int	$0x12 		#Memory Size Determination
	movb	%al, %ch	#Divide o AX em 2 partes
	movb	%ah, %cl

	call	printHex

	popa
	ret
	
#		Switch(bh)
#		funcao que atribui um valor a al dependendo do valor existente em bh
.type assign, @function
assign:
	cmp	$0x0, %bh	
	jne	notZero		#if(bh == 0) al = '0'
	movb	$'0', %al
	ret

	notZero:
	cmp	$0x1, %bh
	jne	notOne		#if(bh == 1) al = '1'
	movb	$'1', %al
	ret

	notOne:
	cmp	$0x2, %bh
	jne	notTwo		#if(bh == 2) al = '2'
	movb	$'2', %al
	ret

	notTwo:
	cmp	$0x3, %bh
	jne	notTree		#if(bh == 3) al = '3'
	movb	$'3', %al
	ret

	notTree:
	cmp	$0x4, %bh
	jne	notFour		#if(bh == 4) al = '4'
	movb	$'4', %al
	ret

	notFour:
	cmp	$0x5, %bh
	jne	notFive		#if(bh == 5) al = '5'
	movb	$'5', %al
	ret

	notFive:
	cmp	$0x6, %bh
	jne	notSix		#if(bh == 6) al = '6'
	movb	$'6', %al
	ret

	notSix:
	cmp	$0x7, %bh
	jne	notSeven	#if(bh == 7) al = '7'
	movb	$'7', %al
	ret

	notSeven:
	cmp	$0x8, %bh
	jne	notEight	#if(bh == 8) al = '8'
	movb	$'8', %al
	ret

	notEight:
	cmp	$0x9, %bh
	jne	notNine		#if(bh == 9) al = '9'
	movb	$'9', %al
	ret

	notNine:
	cmp	$0xA, %bh
	jne	notA		#if(bh == A) al = 'A'
	movb	$'A', %al
	ret

	notA:
	cmp	$0xB, %bh
	jne	notB		#if(bh == B) al = 'B'
	movb	$'B', %al
	ret

	notB:
	cmp	$0xC, %bh
	jne	notC		#if(bh == C) al = 'C'
	movb	$'C', %al
	ret

	notC:
	cmp	$0xD, %bh
	jne	notD		#if(bh == D) al = 'D'
	movb	$'D', %al
	ret

	notD:
	cmp	$0xE, %bh
	jne	notE		#if(bh == E) al = 'E'
	movb	$'E', %al
	ret

	notE:
	cmp	$0xF, %bh	#if(bh == F) al = 'F'
	movb	$'F', %al
	ret


.type printHex, @function
printHex:		
	movb	$0xf0, %bh
	andb	%cl, %bh
	shrb	$0x4, %bh
	call	assign
		
	movb	$0x0e, %ah	#codigo de inserção de caracter
	int	$0x10 		#interrupcao de video

	movb	$0xf, %bh
	andb	%cl, %bh
	call	assign
		
	movb	$0x0e, %ah	#codigo de inserção de caracter
	int	$0x10		#interrupcao de video

	movb	$0xf0, %bh
	andb	%ch, %bh
	shrb	$0x4, %bh
	call	assign
		
	movb	$0x0e, %ah	#codigo de inserção de caracter
	int	$0x10		#interrupcao de video

	movb	$0xf, %bh
	andb	%ch, %bh
	call	assign

	movb	$0x0e, %ah	#codigo de inserção de caracter
	int	$0x10		#interrupcao de video
	ret

version:		.asciz "OSiX v0.1"
nextline:		.asciz "\n\r>"
coprocessor_found:	.asciz "\n\rMath coprocessor found!"
dma_found:		.asciz "\n\rDMA found!"
disketteIPL_found:	.asciz "\n\rIPL Diskette installed!"
hexStr:  		.asciz "Memory Available: 0x"

. = _start + 510
.byte		0x55, 0xAA
