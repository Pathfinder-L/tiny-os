;; BOOT_INFO

MAIN    EQU     0x00280000      ;
DSKCAC	EQU		0x00100000		;
DSKCAC0	EQU		0x00008000		;

VBEMODE EQU 0x105
CYLS  EQU  0X0ff0 ;;
LEDS  EQU  0x0ff1
VMODE EQU  0x0ff2  ;; 颜色的信息数目，颜色信息位数
SCRNX EQU  0x0ff4  ;; 分辨率X
SCRNY EQU  0x0ff6  ;; 分辨率Y
VRAM  EQU  0x0ff8  ;; 图像缓冲区 的开始地址

org 0xc200  ;; 转入内存 0xc200

MOV		AL,0x13			; VGA僌儔僼傿僢僋僗丄320x200x8bit僇儔乕
MOV		AH,0x00
INT		0x10
MOV		BYTE [VMODE],8	; 夋柺儌乕僪傪儊儌偡傞乮C尵岅偑嶲徠偡傞乯
MOV		WORD [SCRNX],320
MOV		WORD [SCRNY],200
MOV		DWORD [VRAM],0x000a0000


keystatus:

mov ah,0x02
int 0x16
mov [LEDS],al


;; 切换为32位
mov al,0xff
out 0x21,al
nop
out 0xa1,al
cli ;;禁止cpu级别的中断

;;让cpu能够访问1mb以上的内存
call waitkbdout
mov al,0xd1
out 0x64,al
call waitkbdout
mov al,0xdf
out 0x60,al
call waitkbdout




;; 切换保护模式
[INSTRSET "i486p"]				; 486指令描述

		LGDT	[GDTR0]			; 设置临时GDT
		MOV		EAX,CR0
		AND		EAX,0x7fffffff	; bit31为0(禁止分页)
		OR		EAX,0x00000001	; bit0为1(切换到保护模式)
		MOV		CR0,EAX
		JMP		pipelineflush

;; 流水线刷新
pipelineflush:
		MOV		AX,1*8			;  可读性的段32bit
		MOV		DS,AX
		MOV		ES,AX
		MOV		FS,AX
		MOV		GS,AX
		MOV		SS,AX


        MOV		ESI,OS	;
		MOV		EDI,MAIN		;
		MOV		ECX,512*1024/4
		CALL	memcpy


		MOV		ESI,0x7c00		;
		MOV		EDI,DSKCAC		;
		MOV		ECX,512/4
		CALL	memcpy

		MOV		ESI,DSKCAC0+512	;
		MOV		EDI,DSKCAC+512	;
		MOV		ECX,0
		MOV		CL,BYTE [CYLS]
		IMUL	ECX,512*18*2/4	;
		SUB		ECX,512/4		;
		CALL	memcpy


		MOV		EBX,MAIN
		MOV		ECX,[EBX+16]
		ADD		ECX,3			; ECX += 3;
		SHR		ECX,2			; ECX /= 4;
		JZ		skip			;
		MOV		ESI,[EBX+20]	;
		ADD		ESI,EBX
		MOV		EDI,[EBX+12]	;
		CALL	memcpy
skip:
		MOV		ESP,[EBX+12]	;
		JMP		DWORD 2*8:0x0000001b

waitkbdout:
		IN		 AL,0x64
		AND		 AL,0x02
		JNZ		waitkbdout		;
		RET

memcpy:
		MOV		EAX,[ESI]
		ADD		ESI,4
		MOV		[EDI],EAX
		ADD		EDI,4
		SUB		ECX,1
		JNZ		memcpy			; 堷偒嶼偟偨寢壥偑0偱側偗傟偽memcpy傊
		RET
		ALIGNB	16
GDT0:
		RESB	8				;
		DW		0xffff,0x0000,0x9200,0x00cf	;
		DW		0xffff,0x0000,0x9a28,0x0047	;

		DW		0
GDTR0:
		DW		8*3-1
		DD		GDT0

		ALIGNB	16




OS:
