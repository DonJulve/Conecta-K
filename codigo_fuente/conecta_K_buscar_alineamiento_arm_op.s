		AREA datos,DATA, READWRITE
EXITO EQU 0X0
ERROR EQU 0XFF
MAX_NO_CERO EQU 0X6
NUM_COLUMNAS EQU 0X7
NUM_FILAS EQU 0X7
DIFERENCIA EQU NUM_FILAS*MAX_NO_CERO
	
		AREA code,CODE,READONLY
		ENTRY
										
		EXPORT conecta_K_buscar_alineamiento_arm_op
		;IMPORT tablero_buscar_color
		PRESERVE8		
		
											
conecta_K_buscar_alineamiento_arm_op	; r0 = t, r1 = fila, r2 = columna, r3 = color, r4 = delta_fila, r5 = delta_columna, 
										; r6 = celda, r7 = col (va mirando si es la columna interesada), r8 = MAX_NO_CEROS	
										; R9 = @direccion columnas y no ceros, r10 = numeros de exitos, r11 = ¿EXITO?
		mov ip, sp
		stmdb   R13!, {r4-r10,fp,ip,lr,pc}
		sub fp,ip,#4
		mov r4, r0    	; r4 = t
		mov r5, r1		; r5 = fila
		mov r6, r2		; r6 = columna
		mov r7, r3		; r7 = color	
		ldr r4, [fp, #4]	; r8 = delta_fila  Esto se tendra que unificar 
		ldr r5, [fp, #8]	; r9 = delta_columna
		mov r10, #0
		
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
		mov r7, #0
		mov r8, #MAX_NO_CERO
		;mul r7, r8, r1				; calcula cuantas componentes hay desde el inicio hasta la seleccionada
		;add r7, r0, r7				; calcula la direccion de memoria
		mla r9, r8, r1, r0			; calcula la direccion de memoria a mirar.
		
buc_buscar_color
		cmp r7, #MAX_NO_CERO	
		movhi r11, #ERROR
		bhi fin_buscar_color		; col > max_no_cero
		teq r6, r2					
		beq fin_buc_buscar_color	; col = columna
		ldrb r6, [r9]				; celda = (@celda)
		add r7, r7, #1				; col++
		add r9, r9, #1				; @celda++
		b buc_buscar_color

fin_buc_buscar_color
		cmp r7, #MAX_NO_CERO		
		bhi error
		sub r9, r9, #1
		ldrb r6, [r9, #DIFERENCIA]	; celda = @celda_no_ceros
		and r6, r6, #3				; r6 = color celda
		teq r6, r3					
		moveq r11, #EXITO			; color de la celda seleccionada == color
		beq fin_buscar_color
		
error_buscar_color
		mov r11, #ERROR				;
		
fin_buscar_color
; FIN tablero_buscar_color
		teq r11, #EXITO			; Comparar con la variable EXITO
		bne	error
		add r10, r10, #1	; numero_de_exitos++
		add r1, r4, r1		; nueva_fila = fila + delta_fila
		add r2, r5, r2		; nueva_columna = columna + delta_columna						
		b buscar_color
		
error
		mov r0, r10			; return numero_de_exitos
		ldmia sp, {r4-r10,fp,sp,pc}
																											
		END