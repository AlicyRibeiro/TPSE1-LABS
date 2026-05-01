#include <sys/stat.h>
#include <sys/types.h>
#include <stddef.h>

// Ativação do clock do GPIO1
#define CM_PER_GPIO1_CLKCTRL_REG (*(volatile unsigned int *)(0x44E00000 + 0xAC))
#define CM_PER_GPIO1_CLKCTRL_MODULEMODE_ENABLE (0x2u)
#define CM_PER_GPIO1_CLKCTRL_OPTFCLKEN_GPIO_1_GDBCLK (0x40000u)

// Configuração do pino GPIO1_21
#define GPIO1_21_CONF (*(volatile unsigned int *)0x44E1085C)

// GPIO1 registros
#define GPIO_1_OE (*(volatile unsigned int *)0x4804C134)
#define GPIO_1_CLEARDATAOUT (*(volatile unsigned int *)0x4804C190)
#define GPIO_1_SETDATAOUT (*(volatile unsigned int *)0x4804C194)

// Syscalls mínimas para o linker
void _exit(int status) { while (1); }
void *_sbrk(ptrdiff_t incr) { return NULL; }
int _close(int file) { return -1; }
int _fstat(int file, struct stat *st) { st->st_mode = S_IFCHR; return 0; }
int _isatty(int file) { return 1; }
int _lseek(int file, int ptr, int dir) { return 0; }
int _read(int file, char *ptr, int len) { return 0; }
int _write(int file, char *ptr, int len) { return len; }

int _main(void) {
    unsigned char pisca = 0;
    unsigned int valor;
    volatile unsigned int i;

    // Ativar clock do GPIO1
    CM_PER_GPIO1_CLKCTRL_REG = CM_PER_GPIO1_CLKCTRL_MODULEMODE_ENABLE |
                                CM_PER_GPIO1_CLKCTRL_OPTFCLKEN_GPIO_1_GDBCLK;

    // Configurar pino GPIO1_21 como GPIO (modo 7)
    GPIO1_21_CONF = 0x07;

    // Configurar GPIO1_21 como saída
    valor = GPIO_1_OE;
    valor &= ~(1 << 21); // Bit 21 = saída
    GPIO_1_OE = valor;

    // Loop infinito para piscar
    while (1) {
        pisca ^= 1;
        if (pisca)
            GPIO_1_SETDATAOUT = (1 << 21);
        else
            GPIO_1_CLEARDATAOUT = (1 << 21);

        for (i = 0; i < 1000000; i++);
    }

    return 0;
}

