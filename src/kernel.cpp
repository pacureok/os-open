// Archivo: src/kernel.cpp

// Define la dirección base de la memoria de video (Framebuffer) y las dimensiones.
// Estos valores son EJEMPLOS, dependen de la configuración de tu bootloader.
#define FRAMEBUFFER_BASE 0xE0000000
#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768

// Funcion de bajo nivel para dibujar un pixel (usada internamente)
void draw_pixel(int x, int y, unsigned int color) {
    if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT) {
        unsigned int* fb = (unsigned int*)FRAMEBUFFER_BASE;
        fb[y * SCREEN_WIDTH + x] = color;
    }
}

// Clase simple que representa el punto que deseas dibujar
class Point {
public:
    int x;
    int y;
    unsigned int color;

    Point(int px, int py, unsigned int c) : x(px), y(py), color(c) {}

    void draw() {
        draw_pixel(x, y, color);
    }
};

// Función principal del Kernel. 
// El 'extern "C"' es crucial para que el Ensamblador pueda llamarla.
extern "C" void kmain() {
    
    // Configuración Inicial del sistema de video (omitiendo código complejo)
    // El código real necesitaría inicializar el modo gráfico VESA/GOP aquí.
    
    // Crear una instancia de la clase Point (el ".") en el centro de la pantalla
    // Color: 0x00FF0000 (Rojo brillante en formato ARGB)
    Point dot_center(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0x00FF0000);
    
    dot_center.draw(); // Dibuja el punto

    // Bucle principal del Kernel: aquí iría el manejo de procesos y drivers
    while (1) {
        // En un SO de escritorio, esta parte gestiona los eventos de teclado y ratón
        // (a través de drivers y gestores de interrupciones que no están incluidos).
    }
}
