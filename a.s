main: 
push {r11,r14}
add r11, r13, #4
push {r4}
push {r5}
push {r6}
push {r7}
push {r8}
sub r13, r13, #48
L1:
mov r0, #0
mov r0, #3
mov r1, #3
mov r2, #3
mov r3, #3
mov r14, #3
mov r4, #3
mov r5, #3
mov r6, #3
mov r7, #3
mov r8, #3
str r8 , [r13 , #0]
mov r8, #3
str r8 , [r13 , #4]
mov r8, #3
str r8 , [r13 , #8]
mov r8, #3
str r8 , [r13 , #12]
mov r8, #3
str r8 , [r13 , #16]
mov r8, #3
str r8 , [r13 , #20]
mov r8, #3
str r8 , [r13 , #24]
mov r8, #3
str r8 , [r13 , #28]
mov r8, #3
str r8 , [r13 , #32]
mov r8, #3
str r8 , [r13 , #36]
mov r8, #3
str r8 , [r13 , #40]
add r8, r0, r1
str r8 , [r13 , #44]
ldr r8 , [r13 , #44]
add r2, r8, r2
add r2, r2, r3
add r2, r2, r14
add r2, r2, r4
add r2, r2, r5
add r2, r2, r6
add r2, r2, r7
ldr r8 , [r13 , #0]
add r2, r2, r8
ldr r8 , [r13 , #4]
add r2, r2, r8
ldr r8 , [r13 , #8]
add r2, r2, r8
ldr r8 , [r13 , #12]
add r2, r2, r8
ldr r8 , [r13 , #16]
add r2, r2, r8
ldr r8 , [r13 , #20]
add r2, r2, r8
ldr r8 , [r13 , #24]
add r2, r2, r8
ldr r8 , [r13 , #28]
add r2, r2, r8
ldr r8 , [r13 , #32]
add r2, r2, r8
ldr r8 , [r13 , #36]
add r2, r2, r8
ldr r8 , [r13 , #40]
add r2, r2, r8
add r0, r0, r1
add r0, r0, r2
add r0, r0, r3
add r0, r0, r14
add r0, r0, r4
add r0, r0, r5
add r0, r0, r6
add r0, r0, r7
ldr r8 , [r13 , #0]
add r0, r0, r8
ldr r8 , [r13 , #4]
add r0, r0, r8
ldr r8 , [r13 , #8]
add r0, r0, r8
ldr r8 , [r13 , #12]
add r0, r0, r8
ldr r8 , [r13 , #16]
add r0, r0, r8
ldr r8 , [r13 , #20]
add r0, r0, r8
ldr r8 , [r13 , #24]
add r0, r0, r8
ldr r8 , [r13 , #28]
add r0, r0, r8
ldr r8 , [r13 , #32]
add r0, r0, r8
ldr r8 , [r13 , #36]
add r0, r0, r8
ldr r8 , [r13 , #40]
add r0, r0, r8
b L3
L0:
mov r0, #-1
b L3
L3:
add r13, r13, #48
pop {r8}
pop {r7}
pop {r6}
pop {r5}
pop {r4}
pop {r11,r14}
bx r14

