	AREA datos,DATA, READWRITE	
										
dfila DCB 0x00, 0xFF, 0xFF, 0x01
dcolumna DCB 0xFF, 0x00, 0xFF, 0xFF	
N_DELTAS EQU 4
K_SIZE EQU 4
	AREA code,CODE,READONLY
	ENTRY
										
	EXPORT conecta_K_hay_linea_arm_c
	IMPORT conecta_K_buscar_alineamiento_c
	PRESERVE8
											
conecta_K_hay_linea_arm_c

	mov ip, sp
	stmdb   R13!, {r4-r10,fp,ip,lr,pc}
	sub fp,ip,#4
	mov r4, r0    		; r4 = t
	mov r5, r1			; r5 = fila
	mov r6, r2			; r6 = columna
	mov r7, r3			; r7 = color
	ldr r8, =dfila		; r8 = @delta_fila
	ldr r9, =dcolumna	; r9 = @delta_columna
	mov r10, #0
	
bucle
	teq r10, #N_DELTAS
	mov r0, #0
	beq fin_bucle		; fila = i
	ldrsb r1, [r8, r10]	;r1 = delta_fila[i]
	ldrsb r2, [r9, r10]	; r2 = delta_columna[i]
	stmdb sp!, {r1,r2}	; push delta_fila[i], delta_columna[i ] 
	mov r1, r5			; r1 = fila
	mov r2, r6			; r6 = columna
	mov r0, r4			; r0 = t
	mov r3, r7			; r3 = color
	
	bl conecta_K_buscar_alineamiento_c
	mov r11, r0			; linea = linea + "buscar_alineamiento"
	ldm sp!, {r1,r2}
	cmp r0, #K_SIZE		; "return buscar_alineamiento" >= k_size
	movge r0, #1		; return true
	bge fin_bucle
	mov r0,r4			; r0 = @t
	rsb r1,r1,#0		; inverso de delta_fila
	rsb r2,r2,#0		; inverso de delta_columna
	stmdb sp!, {r1,r2}	; push
	add r1, r5, r1		; r1 = fila + -delta_fila
	add r2, r6, r2		; r2 = colunmna + -delta_columna
	mov r3, r7
	bl conecta_K_buscar_alineamiento_c
	add sp, sp, #8		; restauramos pila
	add r0, r0, r11		; 
	add r10, r10, #1	; r10 = i + 1
	cmp r0, #K_SIZE		; linea >= k_size
	blt bucle 
	mov r0, #1			; return true
	
fin_bucle
	ldmia sp, {r4-r10,fp,sp,pc}				
	END