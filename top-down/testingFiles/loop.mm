		INIT
		ALLOC 2
		LDC 0
		ST 0 1
		LDC 10
		ST 0 2
		JMP L1
L2		NOP
		PROC 1
L3		LDV 0 1
		LDV 0 2
		LE
		JMPF L4
		LDV 0 1
		OUT
		LDV 0 2
		OUT
		LDV 0 1
		LDC 1
		ADD
		ST 0 1
		LDV 0 2
		LDC 1
		SUB
		ST 0 2
		JMP L3
L4		RET 1
L1		CALL L2
		ALLOC -2
		HALT
