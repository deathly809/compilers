		INIT
		JMP L1
L2		NOP
		PROC 1
		ALLOC 10
		LDC 0
		ST 1 2
L3		LDV 1 2
		LDC 10
		LT
		JMPF L4
		LDV 1 2
		LDA 1 1
		ADD
		LDV 1 2
		LDV 1 2
		MULT
		STL
		LDV 1 2
		LDC 1
		ADD
		ST 1 2
		JMP L3
L4		LDC 0
		ST 1 2
L5		LDV 1 2
		LDC 10
		LT
		JMPF L6
		LDV 1 2
		LDA 1 1
		ADD
		IND
		OUT
		LDV 1 2
		LDC 1
		ADD
		ST 1 2
		JMP L5
L6		ALLOC -10
		RET 1
L1		CALL L2
		HALT