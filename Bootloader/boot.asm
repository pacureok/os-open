section .text
bits 32
extern kmain

%define KERNEL_START 0x100000

global start

start:
    cli
    mov esp, KERNEL_START
    jmp call_kmain

call_kmain:
    ; Configuración de 64 bits (Long Mode) y tablas (GDT/IDT/Paging)
    ; Omitido por ser demasiado extenso y complejo.
    ; Se asume que el bootloader ya realizó estas tareas.

    ; Limpiar los registros
    xor eax, eax
    xor ebx, ebx
    xor ecx, ecx

    ; Llamar a la función principal del kernel en C
    call kmain

    ; Bucle infinito después de la ejecución del kernel
    cli
.halt:
    hlt
    jmp .halt
