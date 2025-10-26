unsigned short* const VGA_MEMORY = (unsigned short*)0xB8000;
const int VGA_WIDTH = 80;
const int VGA_HEIGHT = 25;
int cursor_x = 0;
int cursor_y = 0;
unsigned char console_color = 0x0A;

void clear_screen() {
    for (int y = 0; y < VGA_HEIGHT; y++) {
        for (int x = 0; x < VGA_WIDTH; x++) {
            VGA_MEMORY[y * VGA_WIDTH + x] = (unsigned short)0x20 | (unsigned short)0x00 << 8;
        }
    }
    cursor_x = 0;
    cursor_y = 0;
}

void print_char(char c) {
    if (c == '\n' || cursor_x >= VGA_WIDTH) {
        cursor_x = 0;
        cursor_y++;
    }

    if (cursor_y >= VGA_HEIGHT) {
        cursor_y = VGA_HEIGHT - 1;
    }
    
    if (c != '\n') {
        VGA_MEMORY[cursor_y * VGA_WIDTH + cursor_x] = (unsigned short)c | (unsigned short)console_color << 8;
        cursor_x++;
    }
}

void print_string(const char* str) {
    while (*str) {
        print_char(*str++);
    }
}

unsigned char inb(unsigned short port) {
    unsigned char result;
    __asm {
        mov dx, port
        in  al, dx
        mov result, al
    }
    return result;
}

void outb(unsigned short port, unsigned char data) {
    __asm {
        mov al, data
        mov dx, port
        out dx, al
    }
}

void run_os_console() {
    clear_screen();
    print_string("OS (CODE) v0.1 - Consola de Control\n");
    print_string("----------------------------------\n\n");
    print_string("os(code) $ ");
    
    while (1) {
    }
}

char scancode_to_ascii(unsigned char scancode) {
    if (scancode == 0x1E) {
        return 'A';
    }
    if (scancode == 0x9E) {
        return 0;
    }
    return '?';
}

extern "C" void kmain(void) {
    clear_screen();
    print_string("OS Kernel Iniciado. Presiona 'A' para iniciar la consola.\n");
    
    bool console_active = false;

    while (1) {
        if (inb(0x64) & 0x01) { 
            unsigned char scancode = inb(0x60); 

            if (!console_active) {
                char c = scancode_to_ascii(scancode);
                
                if (c == 'A') {
                    console_active = true;
                    run_os_console();
                }
            }
            for(volatile int i = 0; i < 1000; i++); 
        }
    }
}
