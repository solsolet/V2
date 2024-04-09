;; Calling Convention = passar els parametros d'una manera concreta
;; ABI: Aplication Binary Interface
;; System V : convenció de Linux

;; Raylib Functions and Values
extern InitWindow
extern CloseWindow
extern BeginDrawing
extern EndDrawing
extern IsKeyPressed

KEY_SPACE EQU 256 ;; EQU es "="

sys_exit equ 60

;section .data
section .bss ;;block starting symbol


section .rodata
    window_title db "Game", 0

section .text

;; Parameters to functions are passed in the registers
;; rdi, rsi, rdx, rcx, r8, r9, and

;; RDI: This
game_init:
    sub rsp, 8 ;; per  alinear la pila
;; InitWindow(640, 48, "Game");
    mov     edi, 640 ;; edi = 640
    mov     esi, 48
    mov     rdx, window_title
    call    InitWindow

;global main
;main:
global _start
_start:
    ;; PIE: Position Indemendent Executable
    ;; PIC: Position Indemendent Code

    ;; the stack is 16byte aligned just before the call instruction is called

    

    

    main_loop:
        call    BeginDrawing
        call    EndDrawing

        ;; if (IsKeyPressed(KEY_SPACE)) exit;
        mov     rdi, KEY_SPACE
        call    IsKeyPressed    ;; RAX | EAX | AX | AH | AL
        ;sub    al, 0
        or      al, al
        jne      exit_loop
    jmp main_loop

    exit_loop:

    ;; CloseWindow();
    call    CloseWindow

    ;add rsp, 8

    ;;ret quan tenim el _start ja no ens serveix
    mov eax, sys_exit
    mov rdi, 0
    syscall