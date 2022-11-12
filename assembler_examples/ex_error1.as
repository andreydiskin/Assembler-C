; ex_error1.as

bne		#12
clr 		#11  
dec %BLUE
jsr r5,r0
.string missing"
#LBL: stop
stop r1
sababa 	 #54
#lbl: inc r1
not #88
.string ""hey
lea r1,#1
myadd r1,r9
.string "not good text""
stop %BLUE,r2
	.str not good ""
mov 	r1,  #2	
	jsr r3
inc #3
prn %BLUE
