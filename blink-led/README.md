
# Blink LED

## Descrição

Prática inicial de programação bare metal na BeagleBone Black, responsável por piscar o LED USR0 utilizando o pino GPIO1_21.

---

##  Funcionamento


O funcionamento do programa segue as etapas básicas de configuração e controle do GPIO no AM335x:

#### 1. Ativação do clock do GPIO1

Antes de utilizar o periférico, é necessário habilitar seu clock no módulo CM_PER.  
Isso é feito configurando o registrador `CM_PER_GPIO1_CLKCTRL`, ativando o módulo e o clock funcional. 

---

#### 2. Configuração do pino como saída

O pino GPIO1_21 é configurado como saída através do registrador `GPIO_OE`.

- Valor `1` → entrada  
- Valor `0` → saída  

O código zera o bit 21, definindo o pino como saída. 

---

#### 3. Controle do LED

O estado do LED é controlado por dois registradores:

- `SETDATAOUT` → coloca o pino em nível alto (liga o LED)
- `CLEARDATAOUT` → coloca o pino em nível baixo (desliga o LED)

O programa alterna entre esses estados dentro de um loop infinito. 

---

#### 4. Delay por software

Um laço vazio é utilizado para criar uma pausa entre as mudanças de estado do LED, permitindo visualizar o efeito de pisca-pisca.

Esse método é comum em sistemas bare metal quando não há temporizadores configurados. 

---

##  Estrutura

```text
bin/        # Binários gerados
inc/        # Headers
src/        # Código-fonte
Makefile    # Compilação
memmap.ld   # Organização de memória
start.s     # Inicialização
script.txt  # Execução no U-Boot
README.md   # Este arquivo
```

---

## Como Compilar

No diretório da prática, execute:

```bash
make
```

O processo irá:

- Compilar os arquivos fonte (`C e Assembly`)
- Gerar o executável (`.elf`)
- Converter para binário (`.boot ou .bin`)
- Copiar automaticamente para o diretório `/tftpboot/`

#### **Execução**

No U-Boot, execute os comandos presentes no arquivo script.txt e, em seguida:
```bash
run app
```

---

## Resultado Esperado

O LED USR0 da BeagleBone Black deve piscar continuamente em intervalos regulares.
