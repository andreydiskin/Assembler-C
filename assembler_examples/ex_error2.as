; ex_error2.as

not: add r1,r2
add: stop
21lbl: stop
add r1,r2,r3,r4
lbl: inc #3
mov: add r1,r2
bne r1,r3,#111
rts #1,#2