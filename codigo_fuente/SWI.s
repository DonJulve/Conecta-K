;/*****************************************************************************/
;/* SWI.S: SWI Handler                                                        */
;/*****************************************************************************/
;/* This file is part of the uVision/ARM development tools.                   */
;/* Copyright (c) 2005-2006 Keil Software. All rights reserved.               */
;/* This software may only be used under the terms of a valid, current,       */
;/* end user licence from KEIL for a compatible version of KEIL software      */
;/* development tools. Nothing else gives you the right to use this software. */
;/*****************************************************************************/

T_Bit           EQU     0x20
I_BIT			EQU		0x80
F_BIT			EQU		0x40

                PRESERVE8                      ; 8-Byte aligned Stack
                AREA    SWI_Area, CODE, READONLY
                ARM
				ENTRY
                EXPORT  SWI_Handler
SWI_Handler   

                STMFD   SP!, {R12, LR}         ; Store R12, LR
                MRS     R12, SPSR              ; Get SPSR
                STMFD   SP!, {R8, R12}         ; Store R8, SPSR
                TST     R12, #T_Bit            ; Check Thumb Bit
                LDRNEH  R12, [LR,#-2]          ; Thumb: Load Halfword
                BICNE   R12, R12, #0xFF00      ; Extract SWI Number
                LDREQ   R12, [LR,#-4]          ; ARM:   Load Word
                BICEQ   R12, R12, #0xFF000000  ; Extract SWI Number

; add code to enable/disable the global IRQ flag
                CMP     R12,#0xFC             
                BEQ     __read_IRQ_bit
				
				CMP     R12,#0xFD           
                BEQ     __disable_fiq
				
				CMP     R12,#0xFE        
                BEQ     __disable_irq
				
				CMP     R12,#0xFF             
                BEQ     __enable_irq

                LDR     R8, SWI_Count
                CMP     R12, R8
                BHS     SWI_Dead               ; Overflow
                ADR     R8, SWI_Table
                LDR     R12, [R8,R12,LSL #2]   ; Load SWI Function Address
                MOV     LR, PC                 ; Return Address
                BX      R12                    ; Call SWI Function 

                LDMFD   SP!, {R8, R12}         ; Load R8, SPSR
                MSR     SPSR_cxsf, R12         ; Set SPSR
                LDMFD   SP!, {R12, PC}^        ; Restore R12 and Return

SWI_Dead        B       SWI_Dead               ; None Existing SWI

SWI_Cnt         EQU    (SWI_End-SWI_Table)/4
SWI_Count       DCD     SWI_Cnt

                IMPORT  __SWI_0               
;				IMPORT  __SWI_1
;               IMPORT  __SWI_2
;               IMPORT  __SWI_3
SWI_Table
                DCD     __SWI_0                ; SWI 0 Function Entry
;				DCD     __SWI_1                ; SWI 1 Function Entry
;               DCD     __SWI_2                ; SWI 2 Function Entry
;               DCD     __SWI_3                ; SWI 3 Function Entry

;               ...
SWI_End

				EXTERN shared_var [DATA,SIZE=4]

__read_IRQ_bit
				MRS r0, SPSR
				AND R0, #I_BIT
				TEQ R0, #0
				MOVEQ R0, #0
				MOVNE R0, #1
				; mrs para pasar el cpsr a un reg
				; msr para pasar de un reg al cpsr
				LDMFD   SP!, {R8, R12}         ; Load R8, SPSR
                MSR     SPSR_c, R12         ; Set SPSR
                LDMFD   SP!, {R12, PC}^        ; Restore R12 and 
				
__disable_irq
                MRS     R0, SPSR     ; Cargar SPSR
                ORR     R0, R0, #I_BIT   ; Deshabilitar IRQs en SPSR
                MSR     SPSR_cxsf, R0    ; Actualizar SPSR
                MOV     R14, LR      ; Guardar LR en R14 para restaurar más adelante
                LDMFD   SP!, {R8, R12}   ; Cargar R8, SPSR
                MOV     LR, R14      ; Restaurar LR
                LDMFD   SP!, {R12, PC}^  ; Restaurar R12 y volver al modo usuario
				
__enable_irq
                MRS     R0, SPSR     ; Cargar SPSR
                BIC     R0, R0, #I_BIT   ; Habilitar IRQs en SPSR
                MSR     SPSR_cxsf, R0    ; Actualizar SPSR
                MOV     R14, LR      ; Guardar LR en R14 para restaurar más adelante
                LDMFD   SP!, {R8, R12}   ; Cargar R8, SPSR
                MOV     LR, R14      ; Restaurar LR
                LDMFD   SP!, {R12, PC}^  ; Restaurar R12 y volver al modo usuario
				
__disable_fiq
                MRS     R0, SPSR     ; Cargar SPSR
                ORR     R0, R0, #F_BIT   ; Deshabilitar FIQs en SPSR
                MSR     SPSR_cxsf, R0    ; Actualizar SPSR
                MOV     R14, LR      ; Guardar LR en R14 para restaurar más adelante
                LDMFD   SP!, {R8, R12}   ; Cargar R8, SPSR
                MOV     LR, R14      ; Restaurar LR
                LDMFD   SP!, {R12, PC}^  ; Restaurar R12 y volver al modo usuario
				END
