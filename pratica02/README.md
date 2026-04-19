# Prática 02 - Primeiro Código para Piscar um LED

##  Objetivo

Esta prática tem como objetivo desenvolver o primeiro programa bare metal para a BeagleBone Black, realizando o acionamento do LED USR0 através do GPIO1_21 do processador AM335x.

O programa é responsável por:

- Habilitar o clock do módulo GPIO1
- Configurar o pino GPIO1_21 como saída
- Alternar o estado lógico do pino
- Implementar um delay por software para criar o efeito de pisca-pisca

---

##  Conceitos Trabalhados

- Programação Bare Metal
- Manipulação direta de registradores
- Controle de GPIO
- Clock de periféricos
- Organização de memória com Linker Script
- Inicialização do processador em Assembly ARM
- Geração de binário para execução via U-Boot

---

## Funcionamento do Programa

### **1. Ativação do Clock do GPIO1**

Antes de utilizar qualquer periférico no `AM335x`, é necessário habilitar seu clock.

O registrador utilizado para habilitar o clock do `GPIO1` é:

```
#define CM_PER (*(volatile unsigned int *)0x44E00000)
#define CM_PER_GPIO1_CLKCTRL (0xACu)
```

O endereço efetivo do registrador de controle do clock do `GPIO1` é:
```
0x44E00000 + 0xAC = 0x44E000AC
```

O código realiza a ativação do módulo GPIO1 colocando o campo `MODULEMODE` em modo Enable. 

---

### **2. Configuração do GPIO1_21 como Saída**

O LED USR0 da BeagleBone Black está conectado ao pino `GPIO1_21`.

A direção do pino é configurada através do registrador `GPIO1_OE`:

```
#define GPIO_1_EO (*(volatile unsigned int *)0x4804C134)
```

No registrador `GPIO1_OE`:
```
Bit = 1 → Entrada
Bit = 0 → Saída
```

Para configurar o `GPIO1_21` como saída, o bit 21 é zerado:
```
valor &= ~(1 << 21);
```

---

### **3. Controle do LED**

Para alterar o estado do LED, o AM335x utiliza os registradores:

```
#define GPIO_1_SETDATAOUT   (*(volatile unsigned int *)0x4804C194)
#define GPIO_1_CLEARDATAOUT (*(volatile unsigned int *)0x4804C190)
SETDATAOUT → Coloca o pino em nível alto
CLEARDATAOUT → Coloca o pino em nível baixo
```

O programa alterna continuamente entre ligar e desligar o LED dentro de um `while(1)`.

---

## 4. Delay por Software

Como ainda não foi configurado nenhum timer de hardware, a pausa entre ligar e desligar o LED é feita através de um laço vazio:

```
for (i = 0; i < 1000000; i++);
```

Esse delay cria o efeito visual de pisca-pisca.

---

## Arquivos Importantes


`main.c`

Responsável pela lógica principal do programa:

- Ativação do clock do GPIO1
- Configuração do pino GPIO1_21
- Controle do LED
- Delay por software


`start.s`

Arquivo Assembly responsável pela inicialização do ambiente bare metal:

- Configuração do modo Supervisor `(SVC)`
- Inicialização da pilha
- Chamada da função _main


`memmap.ld`

Linker Script utilizado para definir onde o programa será carregado na memória RAM da BeagleBone Black.

```
MEMORY{
    ram : ORIGIN = 0x80000000, LENGTH = 0x1B400
}
```

O programa é carregado na RAM a partir do endereço:
```
0x80000000
```

---

## Compilação

Para compilar o projeto:
```

make
```
Para remover arquivos gerados:
```

make clean
```

---

## Execução na BeagleBone Black

Após compilar, o binário é copiado automaticamente para:

```
/tftpboot/Gpio.bin
```

No U-Boot, o programa pode ser executado com:

```
setenv app "setenv autoload no; setenv ipaddr 10.4.1.2; setenv serverip 10.4.1.1; tftp 0x80000000 Gpio.bin; echo ***Booting to BareMetal***; go 0x80000000"
run app
```

---

## Resultado Esperado

Ao executar o programa, o LED USR0 da BeagleBone Black deve piscar continuamente, indicando que:

- O clock do GPIO1 foi habilitado corretamente
- O pino GPIO1_21 foi configurado como saída
- O controle dos registradores está funcionando corretamente
- O binário foi carregado corretamente via TFTP e executado pelo U-Boot
