
# Blink LED

## Descrição

Prática inicial de programação bare metal na BeagleBone Black, responsável por piscar o LED USR0 utilizando o pino GPIO1_21.

---

##  Funcionamento

O programa habilita o clock do GPIO1, configura o pino GPIO1_21 como saída e alterna seu estado lógico utilizando os registradores SETDATAOUT e CLEARDATAOUT, criando o efeito de pisca-pisca com um delay por software.

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


---

## Resultado Esperado
