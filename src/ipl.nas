; haribote-ipl
; TAB=4

		ORG		0x7c00			; 偙偺僾儘僌儔儉偑偳偙偵撉傒崬傑傟傞偺偐

; 埲壓偼昗弨揑側FAT12僼僅乕儅僢僩僼儘僢僺乕僨傿僗僋偺偨傔偺婰弎

		JMP		entry
		DB		0x90
		DB		"HARIBOTE"		; 僽乕僩僙僋僞偺柤慜傪帺桼偵彂偄偰傛偄乮8僶僀僩乯
		DW		512				; 1僙僋僞偺戝偒偝乮512偵偟側偗傟偽偄偗側偄乯
		DB		1				; 僋儔僗僞偺戝偒偝乮1僙僋僞偵偟側偗傟偽偄偗側偄乯
		DW		1				; FAT偑偳偙偐傜巒傑傞偐乮晛捠偼1僙僋僞栚偐傜偵偡傞乯
		DB		2				; FAT偺屄悢乮2偵偟側偗傟偽偄偗側偄乯
		DW		224				; 儖乕僩僨傿儗僋僩儕椞堟偺戝偒偝乮晛捠偼224僄儞僩儕偵偡傞乯
		DW		2880			; 偙偺僪儔僀僽偺戝偒偝乮2880僙僋僞偵偟側偗傟偽偄偗側偄乯
		DB		0xf0			; 儊僨傿傾偺僞僀僾乮0xf0偵偟側偗傟偽偄偗側偄乯
		DW		9				; FAT椞堟偺挿偝乮9僙僋僞偵偟側偗傟偽偄偗側偄乯
		DW		18				; 1僩儔僢僋偵偄偔偮偺僙僋僞偑偁傞偐乮18偵偟側偗傟偽偄偗側偄乯
		DW		2				; 僿僢僪偺悢乮2偵偟側偗傟偽偄偗側偄乯
		DD		0				; 僷乕僥傿僔儑儞傪巊偭偰側偄偺偱偙偙偼昁偢0
		DD		2880			; 偙偺僪儔僀僽戝偒偝傪傕偆堦搙彂偔
		DB		0,0,0x29		; 傛偔傢偐傜側偄偗偳偙偺抣偵偟偰偍偔偲偄偄傜偟偄
		DD		0xffffffff		; 偨傇傫儃儕儏乕儉僔儕傾儖斣崋
		DB		"HARIBOTEOS "	; 僨傿僗僋偺柤慜乮11僶僀僩乯
		DB		"FAT12   "		; 僼僅乕儅僢僩偺柤慜乮8僶僀僩乯
		RESB	18				; 偲傝偁偊偢18僶僀僩偁偗偰偍偔

; 僾儘僌儔儉杮懱

entry:
		MOV		AX,0			; 儗僕僗僞弶婜壔
		MOV		SS,AX
		MOV		SP,0x7c00
		MOV		DS,AX

; 僨傿僗僋傪撉傓

		MOV		AX,0x0820
		MOV		ES,AX
		MOV		CH,0			; 僔儕儞僟0
		MOV		DH,0			; 僿僢僪0
		MOV		CL,2			; 僙僋僞2

		MOV		AH,0x02			; AH=0x02 : 僨傿僗僋撉傒崬傒
		MOV		AL,1			; 1僙僋僞
		MOV		BX,0
		MOV		DL,0x00			; A僪儔僀僽
		INT		0x13			; 僨傿僗僋BIOS屇傃弌偟
		JC		error

; 撉傒廔傢偭偨偗偳偲傝偁偊偢傗傞偙偲側偄偺偱怮傞

fin:
		HLT						; 壗偐偁傞傑偱CPU傪掆巭偝偣傞
		JMP		fin				; 柍尷儖乕僾

error:
		MOV		SI,msg
putloop:
		MOV		AL,[SI]
		ADD		SI,1			; SI偵1傪懌偡
		CMP		AL,0
		JE		fin
		MOV		AH,0x0e			; 堦暥帤昞帵僼傽儞僋僔儑儞
		MOV		BX,15			; 僇儔乕僐乕僪
		INT		0x10			; 價僨僆BIOS屇傃弌偟
		JMP		putloop
msg:
		DB		0x0a, 0x0a		; 夵峴傪2偮
		DB		"load error"
		DB		0x0a			; 夵峴
		DB		0

		RESB	0x7dfe-$		; 0x7dfe傑偱傪0x00偱杽傔傞柦椷

		DB		0x55, 0xaa

