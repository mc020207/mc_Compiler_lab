main: 
push {r11}
mov r11, r13
mov r1, r14
L1:
mov r0, #0
mov r0, #3
mov r2, #3
mov r8, #3
str r8 , [r13 , #0]
mov r3, #3
mov r14, #3
mov r4, #3
mov r5, #3
mov r6, #3
mov r8, #3
str r8 , [r13 , #4]
add r7, r0, r2
ldr r8 , [r13 , #0]
add r7, r7, r8
add r7, r7, r3
add r7, r7, r14
add r7, r7, r4
add r7, r7, r5
add r7, r7, r6
ldr r8 , [r13 , #4]
add r9, r7, r8
str r9 , [r13 , #4]
add r0, r0, r2
ldr r8 , [r13 , #0]
add r0, r0, r8
add r0, r0, r3
add r0, r0, r14
add r0, r0, r4
add r0, r0, r5
add r0, r0, r6
ldr r8 , [r13 , #4]
add r0, r0, r8
mov r13, r11
pop {r11}
bx r1
L0:
mov r0, #-1
mov r13, r11
pop {r11}
bx r1

