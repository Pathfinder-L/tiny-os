[FORMAT "WCOFF"]				;
[INSTRSET "i486p"]				;
[BITS 32]						;
[FILE "nasfunc.nas"]			;

		GLOBAL	_io_hlt, _io_cli, _io_sti, _io_stihlt
		GLOBAL	_io_in8,  _io_in16,  _io_in32
		GLOBAL	_io_out8, _io_out16, _io_out32
		GLOBAL	_io_load_eflags, _io_store_eflags
		GLOBAL	_load_gdtr, _load_idtr,_load_tr
		GLOBAL  _load_cr0,_store_cr0
		GLOBAL	_asm_inthandler20, _asm_inthandler21
    	GLOBAL	_asm_inthandler27, _asm_inthandler2c
		GLOBAL _puts,_memtest_sub
		GLOBAL	_taskswitch3, _taskswitch4 ,_farjmp

[SECTION .text]


_puts: ;;void puts(char *s)
    push ebx
    mov edx,2
    mov ebx,[esp+8]
    int 0x40
    pop ebx
    ret

_io_hlt:	; void io_hlt(void);
		HLT
		RET

_io_cli:	; void io_cli(void);
		CLI
		RET

_io_sti:	; void io_sti(void);
		STI
		RET

_io_stihlt:	; void io_stihlt(void);
		STI
		HLT
		RET

_io_in8:	; int io_in8(int port);
		MOV		EDX,[ESP+4]		; port
		MOV		EAX,0
		IN		AL,DX
		RET

_io_in16:	; int io_in16(int port);
		MOV		EDX,[ESP+4]		; port
		MOV		EAX,0
		IN		AX,DX
		RET

_io_in32:	; int io_in32(int port);
		MOV		EDX,[ESP+4]		; port
		IN		EAX,DX
		RET

_io_out8:	; void io_out8(int port, int data);
		MOV		EDX,[ESP+4]		; port
		MOV		AL,[ESP+8]		; data
		OUT		DX,AL
		RET

_io_out16:	; void io_out16(int port, int data);
		MOV		EDX,[ESP+4]		; port
		MOV		EAX,[ESP+8]		; data
		OUT		DX,AX
		RET

_io_out32:	; void io_out32(int port, int data);
		MOV		EDX,[ESP+4]		; port
		MOV		EAX,[ESP+8]		; data
		OUT		DX,EAX
		RET

_io_load_eflags:	; int io_load_eflags(void);
		PUSHFD		; PUSH EFLAGS
		POP		EAX
		RET

_io_store_eflags:	; void io_store_eflags(int eflags);
		MOV		EAX,[ESP+4]
		PUSH	EAX
		POPFD		; POP
		RET

_load_gdtr:		; void load_gdtr(int limit, int addr);
		MOV		AX,[ESP+4]		; limit
		MOV		[ESP+6],AX
		LGDT	[ESP+6]
		RET

_load_idtr:		; void load_idtr(int limit, int addr);
		MOV		AX,[ESP+4]		; limit
		MOV		[ESP+6],AX
		LIDT	[ESP+6]
		RET

_memtest_sub: ; unsigned int memtest_sub(unsigned int start,unsigned int end);
        push edi
        push esi
        push ebx
        mov esi, 0xaa55aa55
        mov edi, 0x55aa55aa
        mov eax, [esp + 12 + 4]


mts_loop:
        mov ebx,eax
        add ebx,0xffc
        mov edx,[ebx]
        mov [ebx],esi
        xor dword [ebx],0xffffffff
        cmp edi,[ebx]
        jne mts_fin
        xor dword [ebx],0xffffffff
        cmp esi,[ebx]
        jne mts_fin
        mov [ebx],edx
        add eax,0x1000
        cmp eax,[esp+12+8]
        jbe mts_loop
        pop ebx
        pop esi
        pop edi
        ret

mts_fin:
        mov [ebx],edx
        pop ebx
        pop esi
        pop edi
        ret


_load_cr0:
        mov eax,CR0
        ret

_store_cr0:
        mov eax,[esp+4]
        mov cr0,eax
        ret


_load_tr: ; // void load_tr(int tr);
    LTR [esp+4]
    ret

_farjmp: ; void farjmp(int eip,int cs)
        jmp far [esp+4] ; eip,cs
        ret



_taskswitch3:	; void taskswitch3(void);
		JMP		3*8:0
		RET

_taskswitch4:	; void taskswitch4(void);
		JMP		4*8:0
		RET
