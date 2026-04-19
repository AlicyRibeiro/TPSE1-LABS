# Praticas_BeagleBone
Este repositório reúne as práticas desenvolvidas na disciplina Técnicas de Programação para Sistemas Embarcados I, utilizando a BeagleBone Black em ambiente bare-metal.

---

## Estrutura do Repositório

Cada prática está organizada em diretórios separados, contendo os arquivos-fonte, binários gerados, scripts auxiliares e documentação utilizada durante o desenvolvimento.

Exemplo de organização da Prática 02:

```text
pratica02/
├── bin/                 # Binários gerados após a compilação
├── inc/                 # Arquivos de cabeçalho (.h)
├── src/                 # Arquivos-fonte em C e Assembly
├── Makefile             # Automação da compilação do projeto
├── memmap.ld            # Linker Script para posicionamento na memória
├── pratica_02_led_21.pdf# Documento de apoio da prática
├── script.txt           # Comandos utilizados no U-Boot
├── start.s              # Código de inicialização em Assembly ARM
└── README.md            # Explicação detalhada da prática

```
