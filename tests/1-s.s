mov $3, -(sp)
mov $5, -(sp)
jsr pc, _sub
add $4, sp

add r0, buf
mov $1, r0
sys write
buf
2

clr r0
sys exit

.data
buf: <0\n>

