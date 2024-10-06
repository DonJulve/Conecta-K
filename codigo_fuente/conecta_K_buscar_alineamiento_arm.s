		AREA datos,DATA, READWRITE
EXITO EQU 0X0
ERROR EQU 0XFF
MAX_NO_CERO EQU 0X6
NUM_COLUMNAS EQU 0X7
NUM_FILAS EQU 0X7
DIFERENCIA EQU NUM_FILAS*MAX_NO_CERO
	
		AREA code,CODE,READONLY
		ENTRY
										
		EXPORT conecta_K_buscar_alineamiento_arm
		;IMPORT tablero_buscar_color
		PRESERVE8
			
tablero_buscar_color
		
		mov ip, sp
		stmdb   R13!, {r4-r10,fp,ip,lr,pc}
		sub fp,ip,#4
		
		; Comprobacion fila valida
		cmp r1,#NUM_FILAS
		bgt error					; fila > NUM_FILAS
		cmp r1,#0
		blt error				; fila < 0
		
		; Comprobacion columna valida
		cmp r2,#NUM_FILAS
		bgt error					; columna > NUM_COLUMNAS
		cmp r2,#0
		blt error					; columna < 0
		
		mov r6,#0xFF
		mov r5, #0
		mov r8, #MAX_NO_CERO		;se le resta una para que corresponda con la fila que nos interesa
		mul r7, r8, r1				; calcular la direccion de memoria donde empieza la fila
		add r7, r0, r7					
buc		cmp r5, #MAX_NO_CERO		; no existe ficha
		bhi error
		teq r6, r2			; ficha encontrada
		beq fin_buc
		ldrb r6, [r7]			; cargamos ficha
		add r5, r5, #1
		add r7, r7, #1
		b buc
		
fin_buc
		cmp r5, #MAX_NO_CERO		; no existe ficha
		bhi error
		sub r7, r7, #1			; restamos uno para estar en la direccion correcta
		ldrb r6, [r7, #DIFERENCIA]
		and r6, r6, #3			; color
		teq r6, r3
		moveq r0, #EXITO
		ldmiaeq sp, {r4-r10,fp,sp,pc}		
		
error
		mov r0, #ERROR
		ldmia sp, {r4-r10,fp,sp,pc}
		
		
		
											
conecta_K_buscar_alineamiento_arm	
		mov ip, sp
		stmdb   R13!, {r4-r10,fp,ip,lr,pc}
		sub fp,ip,#4
				
		mov r4, r0    	; r4 = t
		mov r5, r1		; r5 = fila
		mov r6, r2		; r6 = columna
		mov r7, r3		; r7 = color
						
		ldr r8, [fp, #4]	; r8 = delta_fila  Esto se tendra que unificar 
		ldr r9, [fp, #8]	; r9 = delta_columna
		bl tablero_buscar_color
		cmp r0, #EXITO			; Comparar con la variable EXITO
		movne r0, #0
		ldmiane sp, {r4-r10,fp,sp,pc}
									
		add r1, r5, r8		; nueva_fila = fila + delta_fila
		add r2, r6, r9		; nueva_columna = columna + delta_columna
		mov r0, r4
		mov r3, r7
								
		stmdb sp!, {r8,r9}
		bl conecta_K_buscar_alineamiento_arm
		add sp, sp, #8
		add r0,r0,#1		; 1 + conecta_K_buscar_alineamiento_arm
		ldmia sp, {r4-r10,fp,sp,pc}
																											
		END