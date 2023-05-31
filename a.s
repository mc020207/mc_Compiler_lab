main: 
L1:
mov r0, #0
mov r6, #3
mov r7, #3
mov r0, #3
mov r1, #3
mov r8, #3
str r8 , [r13 , #0]
mov r2, #3
mov r3, #3
mov r14, #3
mov r4, #3
add r5, r6, r7
add r5, r5, r0
add r5, r5, r1
ldr r8 , [r13 , #0]
add r5, r5, r8
add r5, r5, r2
add r5, r5, r3
add r5, r5, r14
add r4, r5, r4
add r5, r6, r7
add r0, r5, r0
add r0, r0, r1
ldr r8 , [r13 , #0]
add r0, r0, r8
add r0, r0, r2
add r0, r0, r3
add r0, r0, r14
add r0, r0, r4
b L3
L0:
mov r0, #-1
b L3
L3:

