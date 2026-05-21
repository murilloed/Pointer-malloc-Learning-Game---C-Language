# 03 - Basic Movement

# Movimento Básico em Raylib (C)

```c
#include "raylib.h"

int main()
{
    InitWindow(800, 600, "Basic Movement");

    int x = 0;

    while (!WindowShouldClose())
    {
        x += 1;

        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawRectangle(x, 250, 100, 100, BLUE);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
```

---

# O que foi adicionado nesta etapa

Nesta etapa aprendemos:

* variáveis
* movimentação
* atualização por frame
* animação básica
* mudança de posição
* lógica contínua

Agora o jogo começa realmente a ganhar vida.

---

# Explicação linha por linha

## Criar janela

```c
InitWindow(800, 600, "Basic Movement");
```

Cria a janela principal.

---

# Variável de posição

```c
int x = 0;
```

Criamos uma variável chamada:

```text
x
```

Ela guarda a posição horizontal do retângulo.

---

# O que é uma variável

Uma variável é:

> um espaço de memória que guarda um valor.

Nesse caso:

```c
int
```

significa:

```text
integer
```

ou seja:

> número inteiro.

---

# Posição inicial

```c
x = 0
```

Significa:

> começar no canto esquerdo da tela.

---

# Loop principal

```c
while (!WindowShouldClose())
```

O jogo continuará rodando infinitamente.

A cada frame:

* atualiza lógica
* redesenha tela
* move objetos

---

# Movimento do retângulo

```c
x += 1;
```

Isso significa:

```c
x = x + 1;
```

Ou seja:

> aumente 1 pixel na posição X.

---

# O que acontece visualmente

Frame por frame:

```text
Frame 1 → x = 0
Frame 2 → x = 1
Frame 3 → x = 2
Frame 4 → x = 3
```

O objeto vai andando para direita.

---

# Começar renderização

```c
BeginDrawing();
```

Inicia o desenho do frame.

---

# Limpar fundo

```c
ClearBackground(RAYWHITE);
```

Apaga o frame anterior.

Sem isso:

* o quadrado deixaria rastros
* pareceria um pincel desenhando

---

# Desenhando o objeto

```c
DrawRectangle(x, 250, 100, 100, BLUE);
```

Parâmetros:

| Valor | Significado        |
| ----- | ------------------ |
| x     | posição horizontal |
| 250   | posição vertical   |
| 100   | largura            |
| 100   | altura             |
| BLUE  | cor                |

---

# Entendendo o movimento

Como o valor de:

```c
x
```

muda constantemente,

o retângulo muda de posição.

Isso gera:

```text
ANIMAÇÃO
```

---

# Finalizar renderização

```c
EndDrawing();
```

Mostra o frame pronto na tela.

---

# Fechar programa

```c
CloseWindow();
```

Encerra corretamente.

---

# Fluxo visual do programa

```text
x = 0

↓ LOOP

x += 1
    ↓
BeginDrawing()
    ↓
ClearBackground()
    ↓
DrawRectangle(x, ...)
    ↓
EndDrawing()
```

---

# Conceito novo aprendido

| Conceito     | Explicação            |
| ------------ | --------------------- |
| Variável     | guarda valores        |
| Movimento    | mudança de posição    |
| Frame Update | atualização contínua  |
| Animação     | sequência de frames   |
| Estado       | valor atual do objeto |

---

# O que acontece internamente

A CPU:

1. aumenta o valor de `x`
2. envia nova posição para GPU
3. GPU desenha no novo local
4. monitor mostra o frame atualizado

Isso acontece dezenas de vezes por segundo.

---

# O que é animação em jogos

Animação em jogos normalmente é:

```text
mudança rápida de posição
```

ou:

```text
mudança rápida de imagens
```

frame após frame.

---

# Taxa de atualização

Seu monitor normalmente trabalha em:

```text
60 FPS
```

Significa:

```text
60 frames por segundo
```

Então o valor de:

```c
x += 1;
```

acontece muitas vezes por segundo.

---

# Resultado esperado

Você verá:

* um quadrado azul
* andando da esquerda para direita
* continuamente

---

# Problema importante

O quadrado irá:

```text
sumir da tela
```

porque o valor de:

```c
x
```

continua aumentando infinitamente.

Isso é normal.

Depois aprenderemos:

* limites
* colisão
* reset de posição

---

# Curiosidade

Quase todos os jogos funcionam com:

```text
posição + velocidade + atualização contínua
```

Mesmo jogos gigantes usam essa lógica básica.

---

# Desafio

## Desafio 1

Aumente velocidade:

```c
x += 5;
```

---

## Desafio 2

Mude a cor:

```c
BLUE
```

para:

```c
RED
```

---

## Desafio 3

Mude tamanho:

```c
100, 100
```

para:

```c
200, 50
```

---

## Desafio 4

Faça o quadrado começar do centro:

```c
int x = 400;
```

---

## Desafio 5

Tente criar:

* dois quadrados
* velocidades diferentes
* cores diferentes

---

# O que vem depois

Na próxima etapa iremos aprender:

* FPS
* controle de velocidade
* sincronização
* frame rate

usando:

```c
SetTargetFPS(60);
```
