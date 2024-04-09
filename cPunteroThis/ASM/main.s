global main

;section .data
;section .bss ;;block starting symbol

section .rodata
    wondow_title db "Game", 0

section .text

main:
    call InitWindow
    call CloseWindow

    ret