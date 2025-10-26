; Archivo: boot.asm

; -------------------------------------------
; CABECERA MULTIBOOT
; Requerido por GRUB/OCP para cargar el kernel en memoria
; -------------------------------------------
section .multiboot
    ; Alineación para el siguiente campo
    align 4
    
    ; El número mágico de Multiboot
    dd 0x1BADB002
    
    ; Flags (Flags = 0, no necesitamos flags especiales por ahora)
    dd 0x00000000
    
    ; Checksum: La suma de (Magic + Flags + Checksum) debe ser cero
    dd - (0x1BADB002 + 0x00000000) 

; -------------------------------------------
; SECCIÓN DEL CÓDIGO
; -------------------------------------------
section .text
bits 32

; Declaración de la función kmain de C++
; Esta vez, SÍ debe estar presente ya que el código se compila como objeto ELF
extern kmain 

; Dirección inicial de la pila (Stack) del Kernel
%define KERNEL_STACK_START 0x200000

global start

start:
    ; 1. Deshabilitar interrupciones (necesario antes de configurar cosas críticas)
    cli 

    ; 2. Inicializar la Pila del Kernel
    ; La pila es esencial para que C++ pueda usar llamadas a funciones
    mov esp, KERNEL_STACK_START 

    ; 3. Configuración de 64 bits (Long Mode) - Omitida
    ; (Se asume que OCP o el bootloader de fase 1 ya realizaron la configuración
    ; de Paginación, GDT y el salto a 64 bits. Si no, debe ir aquí).
    
    ; 4. Preparación y Llamada al Núcleo C++
    ; Limpiar registros según las convenciones de llamada (ABI)
    xor eax, eax
    xor ebx, ebx
    xor ecx, ecx

    ; Llama a la función principal del kernel en C++
    call kmain 

    ; 5. Bucle de detención (Halt Loop)
    ; Después de que kmain regresa (lo cual nunca debería pasar en un OS real)
    cli         ; Deshabilitar interrupciones
.halt:
    hlt         ; Detener la CPU
    jmp .halt   ; Bucle infinito
