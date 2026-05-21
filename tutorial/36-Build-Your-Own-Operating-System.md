# 36 - Build Your Own Operating System

# Criando Seu Próprio Sistema Operacional em C

# Objetivo da Aula

Nesta aula iremos aprender:

```text
como um sistema operacional funciona internamente
```

Agora vamos entrar no mundo de:

- bootloader
- kernel
- memória
- CPU
- interrupções
- hardware
- modo protegido
- gerenciamento de memória
- sistemas operacionais

Isso é a base de:
- Linux
- Windows
- macOS
- kernels
- sistemas embarcados
- computação de baixo nível

---

# O que iremos aprender

Nesta aula vamos estudar:

- bootloader
- kernel
- memória
- CPU
- BIOS
- interrupções
- registradores
- modo real
- modo protegido
- arquitetura de sistemas operacionais

---

# O que é um Sistema Operacional?

Sistema Operacional é:

```text
software que controla o hardware
```

---

# Ele faz a ponte entre:

```text
usuário
↓
programas
↓
hardware
```

---

# O sistema operacional controla:

- CPU
- memória RAM
- disco
- teclado
- mouse
- GPU
- processos
- arquivos

---

# Exemplos

| Sistema | Tipo |
|---|---|
| Linux | kernel monolítico |
| Windows | híbrido |
| macOS | Unix |
| Android | Linux Kernel |

---

# O mais importante

Quando o computador liga:

```text
NÃO EXISTE sistema operacional carregado
```

---

# O que acontece quando liga?

Fluxo real:

```text
ENERGIA
↓
CPU RESET
↓
BIOS/UEFI
↓
BOOTLOADER
↓
KERNEL
↓
SISTEMA OPERACIONAL
```

---

# O que é BIOS?

BIOS significa:

```text
Basic Input Output System
```

---

# BIOS é firmware

Ela:
- inicializa hardware
- testa memória
- encontra bootloader

---

# O que é Bootloader?

Bootloader é:

```text
programa que carrega o kernel
```

---

# Exemplos reais

| Bootloader | Sistema |
|---|---|
| GRUB | Linux |
| Windows Boot Manager | Windows |
| U-Boot | embarcados |

---

# O que é Kernel?

Kernel é:

```text
núcleo do sistema operacional
```

---

# Kernel controla:

- processos
- memória
- drivers
- CPU
- hardware

---

# Arquitetura simplificada

```text
APLICAÇÕES
↓
KERNEL
↓
HARDWARE
```

---

# Estrutura do Projeto

```text
my_os/
│
├── boot.asm
├── kernel.c
├── linker.ld
├── Makefile
└── build/
```

---

# O que iremos construir?

Um mini sistema operacional que:

- inicia via bootloader
- entra em modo texto
- escreve na tela
- executa kernel em C

---

# Código do Bootloader

# boot.asm

```asm
; =========================================
; BOOTLOADER 16 BITS
; =========================================

BITS 16

ORG 0x7C00

start:

    ; =====================================
    ; CONFIGURA SEGMENTOS
    ; =====================================

    mov ax, 0

    mov ds, ax

    mov es, ax

    mov ss, ax

    mov sp, 0x7C00

    ; =====================================
    ; LIMPA TELA
    ; =====================================

    mov ah, 0x00

    mov al, 0x03

    int 0x10

    ; =====================================
    ; ESCREVE TEXTO
    ; =====================================

    mov si, message

print:

    lodsb

    cmp al, 0

    je load_kernel

    mov ah, 0x0E

    int 0x10

    jmp print

load_kernel:

    ; =====================================
    ; LOOP INFINITO
    ; =====================================

    jmp $

message db "Bootloader iniciado!", 0

times 510-($-$$) db 0

dw 0xAA55
```

---

# O que esse código faz?

Ele:
- vira setor de boot
- é carregado pela BIOS
- executa antes do sistema operacional

---

# O que é 0x7C00?

Endereço:

```text
onde BIOS carrega bootloader
```

---

# Isso é MUITO importante

Historicamente:
- PCs iniciam assim há décadas

---

# O que é:

```asm
int 0x10
```

?

É:

```text
interrupção da BIOS para vídeo
```

---

# Interrupções

Interrupções são:

```text
chamadas para hardware/BIOS
```

---

# Exemplo

| Interrupção | Função |
|---|---|
| int 0x10 | vídeo |
| int 0x13 | disco |
| int 0x16 | teclado |

---

# Assinatura do Bootloader

```asm
dw 0xAA55
```

MUITO importante.

---

# BIOS verifica isso

Se existir:
- setor é bootável

---

# Sem isso

Computador:
- não inicializa boot

---

# Kernel em C

# kernel.c

```c
// =========================================
// VGA MEMORY
// =========================================

char *video =
    (char*) 0xB8000;

// =========================================
// KERNEL MAIN
// =========================================

void kernel_main()
{
    // =====================================
    // TEXTO
    // =====================================

    char *message =
        "Meu Primeiro Kernel!";

    // =====================================
    // ESCREVE NA VGA
    // =====================================

    for (int i = 0;
         message[i] != 0;
         i++)
    {
        video[i * 2] =
            message[i];

        video[i * 2 + 1] =
            0x0F;
    }

    // =====================================
    // LOOP INFINITO
    // =====================================

    while (1)
    {

    }
}
```

---

# O que é VGA Memory?

Endereço:

```text
0xB8000
```

representa:

```text
memória da tela texto
```

---

# Isso é MUITO importante

Você escreve:
- diretamente na memória da GPU/VGA

---

# Sem API
# Sem Raylib
# Sem Windows

Direto no hardware.

---

# Cada caractere ocupa

| Byte | Função |
|---|---|
| primeiro | caractere |
| segundo | cor |

---

# Exemplo

```c
video[i * 2]
```

escreve:
- letra

---

# Exemplo

```c
video[i * 2 + 1]
```

escreve:
- cor

---

# Linker Script

# linker.ld

```ld
ENTRY(kernel_main)

SECTIONS
{
    . = 1M;

    .text :
    {
        *(.text)
    }

    .data :
    {
        *(.data)
    }

    .bss :
    {
        *(.bss)
    }
}
```

---

# O que isso faz?

Define:
- onde kernel será carregado na memória

---

# ENTRY()

```ld
ENTRY(kernel_main)
```

Define:
- ponto inicial do kernel

---

# O que é linker?

Linker junta:
- código
- funções
- binários

---

# Makefile

```make
all:
	nasm -f bin boot.asm -o boot.bin
	gcc -ffreestanding -c kernel.c -o kernel.o
	ld -T linker.ld -o kernel.bin kernel.o
```

---

# O que é:

```text
-ffreestanding
```

?

Significa:

```text
sem sistema operacional
```

---

# Porque o kernel NÃO possui:

- libc
- printf
- malloc
- sistema operacional

---

# Fluxo completo do boot

```text
LIGA COMPUTADOR
↓
BIOS
↓
CARREGA BOOTLOADER
↓
BOOTLOADER EXECUTA
↓
CARREGA KERNEL
↓
KERNEL CONTROLA HARDWARE
```

---

# Modos da CPU

CPU x86 possui:

| Modo | Função |
|---|---|
| Real Mode | antigo 16 bits |
| Protected Mode | moderno 32 bits |
| Long Mode | 64 bits |

---

# Nosso bootloader usa:

```text
Real Mode
```

---

# Sistemas modernos usam:

```text
Protected Mode
ou
Long Mode
```

---

# O que é Protected Mode?

Permite:
- multitarefa
- memória protegida
- 32 bits
- segurança

---

# O que é memória virtual?

Sistema operacional cria:

```text
ilusão de memória infinita
```

---

# Isso é feito com:

- paginação
- MMU
- tabelas de páginas

---

# O que é MMU?

MMU significa:

```text
Memory Management Unit
```

---

# CPU moderna possui MMU

Ela traduz:

```text
endereço virtual
↓
endereço físico
```

---

# Isso é ABSURDAMENTE importante

Todo sistema moderno usa isso.

---

# O que é Scheduler?

Scheduler decide:

```text
qual processo usa CPU
```

---

# Fluxo multitarefa

```text
PROCESSO A
↓
PROCESSO B
↓
PROCESSO C
↓
CPU alterna rapidamente
```

---

# Isso cria multitarefa

---

# O que é Context Switch?

Troca:
- registradores
- pilha
- estado da CPU

---

# Sistemas operacionais modernos fazem isso milhares de vezes

por segundo.

---

# O que é Driver?

Driver é:

```text
software que controla hardware
```

---

# Exemplos

| Driver | Hardware |
|---|---|
| GPU Driver | placa de vídeo |
| Audio Driver | som |
| Network Driver | internet |

---

# Linux Kernel

Linux possui:
- milhões de linhas
- milhares de drivers

---

# Windows Kernel

Windows usa:
- arquitetura híbrida
- NT Kernel

---

# O que é syscall?

Syscall é:

```text
pedido de programa para o kernel
```

---

# Exemplo

```text
programa pede:
abrir arquivo
```

---

# Então kernel faz

- acesso ao hardware

---

# Arquitetura real

```text
USER SPACE
↓ syscall
KERNEL SPACE
↓
HARDWARE
```

---

# O que é Ring 0?

CPUs modernas possuem:

| Ring | Permissão |
|---|---|
| Ring 0 | kernel |
| Ring 3 | aplicações |

---

# Isso protege sistema

Aplicações:
- não acessam hardware diretamente

---

# Visualização mental

```text
APP
↓
SYSCALL
↓
KERNEL
↓
CPU
↓
HARDWARE
```

---

# Conceitos profissionais aprendidos

| Conceito | Foi usado |
|---|---|
| Bootloader | ✔ |
| Kernel | ✔ |
| BIOS | ✔ |
| VGA Memory | ✔ |
| Interrupções | ✔ |
| Memória | ✔ |
| CPU Modes | ✔ |
| Hardware Control | ✔ |

---

# O que você aprende de verdade

# você entende:

```text
um sistema operacional é um software que assume controle total do hardware
```

E entende:
- boot
- kernel
- memória
- BIOS
- interrupções
- drivers
- arquitetura de SO
- fundamentos usados em Linux e Windows

---

# Curiosidade MUITO importante

Linux começou:
- como um kernel simples criado por Linus Torvalds

Hoje:
- roda servidores
- Android
- cloud
- supercomputadores

---

