# Prática 02_atividade 2 - Controle de 5 LEDs com GPIO como OUTPUT

##  Objetivo

Esta prática tem como objetivo expandir o exemplo de controle de GPIO em modo saída na BeagleBone Black, utilizando não apenas um LED externo, mas também os quatro LEDs internos da placa.

A aplicação realiza o controle de cinco LEDs ao todo:

- 1 LED externo conectado ao pino GPIO1_28
- 4 LEDs internos da placa:
  - USR0 → GPIO1_21
  - USR1 → GPIO1_22
  - USR2 → GPIO1_23
  - USR3 → GPIO1_24

Essa atividade corresponde à extensão proposta no material, que pede para adicionar os quatro LEDs internos ao sistema de pisca LED e controlar os cinco LEDs de diferentes formas. :contentReference[oaicite:0]{index=0}

---

## Conceitos Trabalhados

- Programação Bare Metal
- Manipulação direta de registradores
- Configuração de GPIO como saída
- Configuração de multiplexação dos PADs
- Controle simultâneo de múltiplos LEDs
- Sequenciamento de estados
- Delay por software

---

##  Funcionamento do Programa

O programa inicializa o módulo GPIO1, configura os pinos dos LEDs internos e do LED externo como saída e, em seguida, entra em um laço infinito alternando os estados dos LEDs.

### LEDs utilizados

- **GPIO1_28** → LED externo
- **GPIO1_21** → USR0
- **GPIO1_22** → USR1
- **GPIO1_23** → USR2
- **GPIO1_24** → USR3

---

##  Etapas da Inicialização

### 1. Ativação do clock do GPIO1

Antes de usar o periférico GPIO1, é necessário habilitar seu clock no módulo CM_PER. O material da prática indica que a inicialização do clock do GPIO1 deve ser feita via `SOC_CM_PER_REGS + CKM_PER_GPIO1_CLKCTRL`, habilitando o módulo e o clock funcional. :contentReference[oaicite:1]{index=1}

No código, isso é feito em `ledInit()`.

---

### 2. Configuração dos PADs

Os pinos da BeagleBone Black possuem multiplexação, então cada pino precisa ser configurado para funcionar como GPIO. O material mostra que, para usar um pino como GPIO, o software deve configurar o registrador de controle correspondente com o modo adequado. :contentReference[oaicite:2]{index=2}

Neste código, são configurados os PADs:

- `CM_conf_gpmc_be1n` → GPIO1_28
- `CM_conf_gpmc_a5` → GPIO1_21
- `CM_conf_gpmc_a6` → GPIO1_22
- `CM_conf_gpmc_a7` → GPIO1_23
- `CM_conf_gpmc_a8` → GPIO1_24

Todos são colocados em modo GPIO com valor `7`.

---

### 3. Configuração da direção dos pinos

O registrador `GPIO_OE` define se cada pino será entrada ou saída:

- bit = `1` → entrada
- bit = `0` → saída

O material explica que, para configurar um pino como saída, é necessário zerar o bit correspondente no registrador `GPIO_OE`. :contentReference[oaicite:3]{index=3}

No código, os bits dos pinos 21, 22, 23, 24 e 28 são zerados para que todos funcionem como saída.

---

##  Lógica de Controle dos LEDs

A função `ledToggle()` implementa a lógica principal.

### Quando `flagBlink` vale 1:

- o LED externo é ligado;
- todos os LEDs internos são apagados;
- apenas **um LED interno** é aceso por vez, de acordo com a variável `estadoLED`.

### Quando `flagBlink` vale 0:

- todos os LEDs internos e o LED externo são desligados;
- o estado avança para o próximo LED interno.

Assim, o comportamento observado é:

1. acende o LED externo + USR0
2. apaga tudo
3. acende o LED externo + USR1
4. apaga tudo
5. acende o LED externo + USR2
6. apaga tudo
7. acende o LED externo + USR3
8. apaga tudo

Depois disso, o ciclo recomeça.

---

##  Delay por software

A temporização é feita com um laço vazio:

```c
for(ra = 0; ra < TIME; ra ++);
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

Ao executar o programa:

- o LED externo pisca em conjunto com um LED interno;
- os LEDs internos acendem em sequência: USR0, USR1, USR2 e USR3;
- entre cada troca, todos os LEDs são apagados.

Esse comportamento mostra que o controle de múltiplos GPIOs como saída está funcionando corretamente.
