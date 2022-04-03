global main
extern  GetStdHandle
extern  WriteFile
extern  ExitProcess

section .text

main:
    mov rcx, -11
    call GetStdHandle

    mov rcx, rax
    mov rdx, message
    mov r8, (message_end - message)
    mov r9, 0
    push 0
    call WriteFile
    pop rcx

    mov rcx, 0
    call ExitProcess

    hlt

section .data

message:
db "hello world", 10

message_end:

