; ex_success2.as

	.extern e
	mov e,r2
	inc S1
	add S1,  #9
	bne %S1
STOP: stop


sub r4, r1
stop

prn S1

S1: .data 1234
