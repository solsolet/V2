;; Calling Convention = passar els parametros d'una manera concreta
;; ABI: Aplication Binary Interface
;; System V : convenció de Linux

;; Raylib Functions and Values
extern InitWindow
extern CloseWindow
extern BeginDrawing
extern EndDrawing
extern IsKeyPressed

KEY_SPACE   EQU 256 ;; EQU es "="
sys_exit    EQU 60
TRUE        EQU 1
FALSE       EQU 0

ENTITY_WIDTH    EQU 64
PLAYER_START_X  EQU ENTITY_WIDTH/2
PLAYER_COLOR    EQU 0xFFF27900 ;;esta al revés per que es posa en little endian
NUM_ENEMIES     EQU 4

; typedef struct {
;     int x;
;     int vx;
;     Color color;
; } Entity;

; typedef struct {
;     Entity player;
;     bool playing;
;     Entity enemies[NUM_ENEMIES];
; } Game;

;section .data
section .bss ;;block starting symbol
    game resb 80

    entity_x    EQU 0
    entity_vx   EQU 4
    entity_color EQU 12
    entity_size EQU 16 ;;per a previndre l'alineament

    player      EQU 0 ;; 0-11
    player_size EQU entity_size
    playing     EQU 12
    enemies     EQU (game + player_size)

section .rodata
    window_title db "Game", 0

section .text

;; Parameters to functions are passed in the registers
;; rdi, rsi, rdx, rcx, r8, r9, and

;; RDI: This (Game *)
game_init:
    ;sub     rsp, 8 ;; per  alinear la pila
    push    rdi
;; InitWindow(640, 48, "Game");
    mov     edi, 640 ;; edi = 640
    mov     esi, 48
    mov     rdx, window_title
    call    InitWindow

    pop     rdi

    add     rsp, 8

    ;; BASE + OP*INDEX + OFFSET     ;; OP = 1,2,4,8
    mov     BYTE [rdi + playing], TRUE   ;;playing = true
    ;; player
    mov     DWORD [rdi + (player + entity_x)], PLAYER_START_X
    mov     DWORD [rdi + (player + entity_vx)], 0
    mov     DWORD [rdi + (player + entity_color)], PLAYER_COLOR
    ;; enemies
    xor     rax, rax ; mov rax, 0
    lea     rsi, [rdi + enemies] ;;empieza el 1r enemigo    ;; rsi -> actua como PUNTERO
    .loop:
        mov DWORD [rsi + (player + entity_x)], PLAYER_START_X ;;cambiar a lo dels enemics
        mov DWORD [rsi + (player + entity_vx)], 0
        mov DWORD [rsi + (player + entity_color)], PLAYER_COLOR

        add rsi, entity_size

        inc rax
        cmp rax, NUM_ENEMIES
    jne .loop

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

    ;;ret quan tenim el _start ja no ens serveix
    mov eax, sys_exit
    mov rdi, 0
    syscall