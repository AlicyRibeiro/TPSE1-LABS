# =====================================================================================
#
#       Filename:  Makefile
#
#    Description:  Arquivo de automação da compilação do projeto bare metal
#                  para a BeagleBone Black.
#
#                  Responsável por:
#                  - Compilar o arquivo Assembly start.s
#                  - Compilar o arquivo C main.c
#                  - Linkar os objetos utilizando memmap.ld
#                  - Gerar o executável ELF
#                  - Converter o ELF para binário puro (.boot)
#                  - Copiar automaticamente o binário para o diretório TFTP
#                  - Gerar dump do executável para análise
#
#        Version:  1.0
#        Created:  
#       Revision:  none
#
#         Author:  Ana Alicy Ribeiro
#   Organization:  Universidade Federal do Ceará - Campus Quixadá
#      Discipline: Técnicas de Programação para Sistemas Embarcados I
#        Practice: Prática 02 - Primeiro código para piscar um LED
#
# =====================================================================================

CHAIN=arm-none-eabi
CFLAGS=-std=c99 -Wall
IPATH=-Iinc/
SRC=src/
OBJ=obj/
BIN=bin/

all: app

app: start.o main.o 
	$(CHAIN)-ld $(OBJ)start.o $(OBJ)main.o -T $(SRC)memmap.ld -o $(OBJ)main.elf
	$(CHAIN)-objcopy $(OBJ)main.elf $(BIN)spl.boot -O binary
	cp $(BIN)spl.boot /tftpboot/Gpio.bin

start.o: $(SRC)start.s
	$(CHAIN)-as $(IPATH) $(SRC)start.s -o $(OBJ)start.o

main.o: $(SRC)main.c
	$(CHAIN)-gcc $(CFLAGS) $(IPATH) -c $(SRC)main.c -o $(OBJ)main.o
                                        
copy:
	cp $(BIN)spl.boot /tftpboot/Gpio.bin

clean:
	rm -rf $(OBJ)*.o
	rm -rf $(OBJ)*.elf
	rm -rf $(BIN)*.boot

dump:
	$(CHAIN)-objdump -D $(OBJ)main.elf
