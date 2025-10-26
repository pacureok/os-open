// Definición de la dirección de la memoria de video VGA
unsigned short* const VGA_MEMORY = (unsigned short*)0xB8000;
const int VGA_WIDTH = 80;
const int VGA_HEIGHT = 25;

// Dibuja un caracter simple (un punto) con un color en la posición (x, y)
void draw_dot(int x, int y, unsigned char color) {
    // Caracter: 0x2E es el código ASCII para un punto '.'
    unsigned short entry = (unsigned short)0x2E | (unsigned short)color << 8;
    VGA_MEMORY[y * VGA_WIDTH + x] = entry;
}

// Función principal del núcleo (Kernel)
extern "C" void kmain(void) {
    // Limpiar la pantalla (opcional)
    for (int y = 0; y < VGA_HEIGHT; y++) {
        for (int x = 0; x < VGA_WIDTH; x++) {
            VGA_MEMORY[y * VGA_WIDTH + x] = (unsigned short)0x20 | (unsigned short)0x00 << 8; // Espacio en blanco
        }
    }

    // Dibujar un punto ('.') en la posición central (40, 12) con color rojo (4)
    draw_dot(40, 12, 0x04); 

    // Bucle del núcleo (manejo de drivers de teclado/ratón y procesos irían aquí)
    while (1) {
        // En un SO real, aquí se gestionarían las interrupciones
        // de dispositivos como el teclado y el ratón.
        // La implementación de los drivers de teclado/ratón y la lectura de puertos I/O (in/out)
        // se realizan con código C/Ensamblador de bajo nivel, no con funciones estándar.
    }
}
