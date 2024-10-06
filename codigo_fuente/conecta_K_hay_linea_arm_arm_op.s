	AREA datos,DATA, READWRITE
EXITO EQU 0X0
ERROR EQU 0XFF
MAX_NO_CERO EQU 0X6
NUM_COLUMNAS EQU 0X7
NUM_FILAS EQU 0X7
DIFERENCIA EQU NUM_FILAS*MAX_NO_CERO
dfila DCB 0x00, 0xFF, 0xFF, 0x01
dcolumna DCB 0xFF, 0x00, 0xFF, 0xFF	
N_DELTAS EQU 4
K_SIZE EQU 4
	
	
	AREA code,CODE,READONLY
	ENTRY
										
	EXPORT conecta_K_hay_linea_arm_arm_op
	PRESERVE8
		
		
conecta_K_buscar_alineamiento_arm_general

;tablero_buscar_color

buscar_color
		; Comprobacion fila valida
		cmp r1,#NUM_FILAS
		bgt error_buscar_color					; fila > NUM_FILAS
		cmp r1,#0
		blt error_buscar_color				; fila < 0
		
		; Comprobacion columna valida
		cmp r2,#NUM_COLUMNAS
		bgt error_buscar_color					; columna > NUM_COLUMNAS
		cmp r2,#0
		blt error_buscar_color					; columna < 0
	
		mov r6,#0xFF
		mov r7, #MAX_NO_CERO
		;mul r7, r8, r1				; calcula cuantas componentes hay desde el inicio hasta la seleccionada
		;add r7, r0, r7				; calcula la direccion de memoria
		mla r9, r7, r1, r0			; calcula la direccion de memoria a mirar.
		mov r7, #0
		
buc_buscar_color
		;cmp r7, #MAX_NO_CERO	
		;movhi r11, #ERROR
		;bhi fin_buscar_color		; col > max_no_cero
		;teq r6, r2					
		;beq fin_buc_buscar_color	; col = columna
		ldrb r6, [r9, r7]			; celda = (@columnas + col)
		add r7, r7, #1				; col++
		;add r9, r9, #1				; @celda++
		;b buc_buscar_color
		teq r6, r2					
		beq fin_buc_buscar_color	; col = columna
		
		;2
		;cmp r7, #MAX_NO_CERO				
		;beq fin_buc_buscar_color	; col = columna
		ldrb r6, [r9, r7]			; celda = (@columnas + col)	
		add r7, r7, #1				; col++
		teq r6, r2					
		beq fin_buc_buscar_color	; col = columna
		
		;3
		;cmp r7, #MAX_NO_CERO	
		;bhi fin_buscar_color		; col > max_no_cero
		ldrb r6, [r9, r7]			; celda = (@columnas + col)
		add r7, r7, #1				; col++
		teq r6, r2					
		beq fin_buc_buscar_color	; col = columna
		
		;4
		;cmp r7, #MAX_NO_CERO	
		;bhi fin_buscar_color		; col > max_no_cero
		ldrb r6, [r9, r7]			; celda = (@columnas + col)
		add r7, r7, #1				; col++
		teq r6, r2					
		beq fin_buc_buscar_color	; col = columna
		
		;5
		;cmp r7, #MAX_NO_CERO	
		;bhi fin_buscar_color		; col > max_no_cero
		ldrb r6, [r9, r7]			; celda = (@columnas + col)
		add r7, r7, #1				; col++
		teq r6, r2					
		beq fin_buc_buscar_color	; col = columna
		
		;6
		;cmp r7, #MAX_NO_CERO	
		;bhi fin_buscar_color		; col > max_no_cero
		ldrb r6, [r9, r7]			; celda = (@columnas + col)
		add r7, r7, #1				; col++
		teq r6, r2					
		beq fin_buc_buscar_color	; col = columna


		cmp r7, #MAX_NO_CERO		
		bge error_general
fin_buc_buscar_color
		add r9, r9, r7
		sub r9, r9, #1
		ldrb r6, [r9, #DIFERENCIA]	; celda = @celda_no_ceros
		and r6, r6, #3				; r6 = color celda
		teq r6, r3					; es el color
		moveq r6, #EXITO			; color de la celda seleccionada == color
		beq fin_buscar_color 
		
error_buscar_color
		movlt r6, #ERROR			; r6 = -1
		
fin_buscar_color
		movhi r6, #ERROR			; r6 = -1
		teq r10, #1
		beq fin_buscar_color_llamada1	; llamada 1
		bne fin_buscar_color_llamada2	; llamada 2
		
error_general
		teq r10, #1
		beq error						; fallo en llamada 1
		bne error_2						; fallo en llamada 2
		
fin_buscar_color_llamada1
		; FIN tablero_buscar_color
		teq r6, #EXITO			; Comparar con la variable EXITO
		bne	error
		add r5, r5, #1		; numero_de_exitos++
		ldr r6, =dfila		; r6 = @dfila
		ldrsb r6,[r6, r4]	; r6 = (@dfila)
		add r1, r6, r1		; nueva_fila = fila + delta_fila
		ldr r6, =dcolumna	; r6 = @dcolumna
		ldrsb r6,[r6, r4]	; r6 = (@dcolumna)
		add r2, r6, r2		; nueva_fila = fila + delta_fila						
		b buscar_color
		
fin_buscar_color_llamada2
; FIN tablero_buscar_color
		teq r6, #EXITO			; Comparar con la variable EXITO
		bne	error_2
		add r5, r5, #1			; numero_de_exitos++
		ldr r6, =dfila			; r6 = @dfila
		ldrsb r6,[r6, r4]		; r6 = (@dfila)
		;rsb r6, r6, #0
		sub r1, r1, r6		; nueva_fila = fila + (-delta_fila)
		ldr r6, =dcolumna		; r6 = @dcolumna
		ldrsb r6,[r6, r4]		; r6 = (@dcolumna)
		;rsb r6, r6, #0
		sub r2, r2, r6		; nueva_fila = fila + (-delta_fila)						
		b buscar_color



conecta_K_hay_linea_arm_arm_op	; r0 = t, r1 = fila, r2 = columna, r3 = color, r4 = i, r5 = numero_exitos
								; r6 = celda/¿exito?/delta_filas/delta_columnas, r7 = col /, r8 = max_ceros, 
								; r9 = @columnas y @no_ceros, r10 = llamada
		mov ip, sp
		stmdb   R13!, {r4-r10,fp,ip,lr,pc}
		sub fp,ip,#4
		mov r4, #0
	
bucle
		teq r4, #N_DELTAS
		moveq r0, #0		; r4 == N_DELTAS
		beq fin_bucle		; fila = i
		stmdb sp!, {r1,r2}	; push fila, columna 
		mov r5,#0			; r5 = 0
		mov r10, #1			; indica que es la llamada 1
		b buscar_color
error
		cmp r5, #K_SIZE		; "return buscar_alineamiento" >= k_size
		movge r0, #1		; return true
		addge sp, sp, #8
		bge fin_bucle
		ldm sp, {r1,r2}		; pop fila, columna
		ldr r6, =dfila		; r6 = @dfila
		ldrsb r6,[r6, r4]	; r6 = (dfilas)
		sub r1, r1, r6		; r1 = delta_filas[i] - fila
		ldr r6, =dcolumna	; r6 = @dcolumna
		ldrsb r6,[r6, r4]	; r6 = (dcolumnas)
		sub r2, r2, r6		; r2 = delta_columnas[i] - columna
		mov r10,#2			; indica llamada 2
		b buscar_color
error_2	
		ldm sp!, {r1,r2}	; r1 = fila, r2 = columna		 
		add r4, r4, #1		; r10 = i + 1
		cmp r5, #K_SIZE		; linea >= k_size
		blt bucle 
		mov r0, #1			; return true
	
fin_bucle 
		ldmia sp, {r4-r10,fp,sp,pc}				
		END