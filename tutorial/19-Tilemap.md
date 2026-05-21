# 19 - Tilemap

# Criando Tilemap em Raylib (C)

# Objetivo da Aula

Nesta aula iremos aprender a criar:

```text
Tilemaps
```

Agora deixaremos de desenhar objetos soltos no mapa e começaremos a construir:

- fases
- cenários
- terrenos
- paredes
- plataformas
- mapas completos

usando:

```text
tiles
```

---

# O que iremos aprender

Nesta aula vamos estudar:

- o que é tilemap
- tiles
- grid
- mapa 2D
- matriz de inteiros
- renderização de tiles
- colisão de cenário
- construção de mapas
- mapas estilo Mario/Terraria

---

# O que é um Tile?

Um tile é:

```text
um pequeno bloco gráfico
```

Exemplo:

| Tile | Função |
|---|---|
| grama | chão |
| pedra | parede |
| água | lago |
| lava | perigo |

---

# O que é Tilemap?

Tilemap é:

```text
um mapa formado por vários tiles
```

Exemplo visual:

```text
┌──┬──┬──┬──┬──┐
│1 │1 │1 │1 │1 │
├──┼──┼──┼──┼──┤
│0 │0 │0 │0 │0 │
├──┼──┼──┼──┼──┤
│2 │2 │0 │2 │2 │
└──┴──┴──┴──┴──┘
```

Cada número representa:

```text
um tipo de tile
```

---

# Jogos que usam tilemaps

| Jogo | Usa Tilemap |
|---|---|
| Mario | ✔ |
| Terraria | ✔ |
| Stardew Valley | ✔ |
| Pokémon | ✔ |
| Zelda 2D | ✔ |

---

# Código Completo

```c
// =========================================
// IMPORTA RAYLIB
// =========================================

#include "raylib.h"

// =========================================
// CONSTANTES
// =========================================

// Quantidade de colunas
#define MAP_WIDTH 20

// Quantidade de linhas
#define MAP_HEIGHT 12

// Tamanho de cada tile
#define TILE_SIZE 64

// =========================================
// MAIN
// =========================================

int main(void)
{
    // Cria janela
    InitWindow(
        MAP_WIDTH * TILE_SIZE,
        MAP_HEIGHT * TILE_SIZE,
        "Tilemap em Raylib"
    );

    // Define FPS
    SetTargetFPS(60);

    // =========================================
    // MAPA
    // =========================================

    // Matriz do mapa
    int mapa[MAP_HEIGHT][MAP_WIDTH] =
    {
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,2,2,0,0,0,3,3,0,0,0,0,0,2,2,0,0,0,1},
        {1,0,0,0,0,0,0,3,3,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,2,2,2,2,2,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,3,3,0,0,0,0,0,0,0,2,2,2,0,0,0,0,1},
        {1,0,0,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
    };

    // =========================================
    // JOGADOR
    // =========================================

    Vector2 jogador = { 100, 100 };

    float velocidade = 250;

    // =========================================
    // LOOP PRINCIPAL
    // =========================================

    while (!WindowShouldClose())
    {
        // =========================================
        // UPDATE
        // =========================================

        float delta = GetFrameTime();

        // Guarda posição antiga
        Vector2 antigaPosicao = jogador;

        // Movimento
        if (IsKeyDown(KEY_RIGHT))
            jogador.x += velocidade * delta;

        if (IsKeyDown(KEY_LEFT))
            jogador.x -= velocidade * delta;

        if (IsKeyDown(KEY_UP))
            jogador.y -= velocidade * delta;

        if (IsKeyDown(KEY_DOWN))
            jogador.y += velocidade * delta;

        // =========================================
        // COLISÃO COM TILES
        // =========================================

        // Descobre coluna do jogador
        int coluna =
            jogador.x / TILE_SIZE;

        // Descobre linha do jogador
        int linha =
            jogador.y / TILE_SIZE;

        // Verifica limites
        if (linha >= 0 &&
            linha < MAP_HEIGHT &&
            coluna >= 0 &&
            coluna < MAP_WIDTH)
        {
            // Tile sólido
            if (mapa[linha][coluna] == 1)
            {
                // Volta posição antiga
                jogador = antigaPosicao;
            }
        }

        // =========================================
        // DRAW
        // =========================================

        BeginDrawing();

        ClearBackground(RAYWHITE);

        // =========================================
        // DESENHA MAPA
        // =========================================

        for (int linha = 0;
             linha < MAP_HEIGHT;
             linha++)
        {
            for (int coluna = 0;
                 coluna < MAP_WIDTH;
                 coluna++)
            {
                // Posição do tile
                int x = coluna * TILE_SIZE;
                int y = linha * TILE_SIZE;

                // Tipo do tile
                int tile = mapa[linha][coluna];

                // =========================================
                // TILE PAREDE
                // =========================================

                if (tile == 1)
                {
                    DrawRectangle(
                        x,
                        y,
                        TILE_SIZE,
                        TILE_SIZE,
                        DARKGRAY
                    );
                }

                // =========================================
                // TILE GRAMA
                // =========================================

                else if (tile == 2)
                {
                    DrawRectangle(
                        x,
                        y,
                        TILE_SIZE,
                        TILE_SIZE,
                        GREEN
                    );
                }

                // =========================================
                // TILE ÁGUA
                // =========================================

                else if (tile == 3)
                {
                    DrawRectangle(
                        x,
                        y,
                        TILE_SIZE,
                        TILE_SIZE,
                        BLUE
                    );
                }

                // =========================================
                // TILE VAZIO
                // =========================================

                else
                {
                    DrawRectangleLines(
                        x,
                        y,
                        TILE_SIZE,
                        TILE_SIZE,
                        LIGHTGRAY
                    );
                }
            }
        }

        // =========================================
        // DESENHA JOGADOR
        // =========================================

        DrawRectangleV(
            jogador,
            (Vector2){40, 40},
            RED
        );

        // =========================================
        // HUD
        // =========================================

        DrawRectangle(
            0,
            0,
            1280,
            90,
            Fade(LIGHTGRAY, 0.9f)
        );

        DrawText(
            "Tilemap em Raylib",
            20,
            20,
            30,
            DARKBLUE
        );

        DrawText(
            "Setas = mover jogador",
            20,
            55,
            20,
            DARKGRAY
        );

        DrawText(
            "Tilemaps = mapas feitos com blocos",
            700,
            55,
            20,
            MAROON
        );

        EndDrawing();
    }

    // Fecha janela
    CloseWindow();

    return 0;
}
```

---

# Explicação COMPLETA da Arquitetura

# 1. O que é Tilemap?

Tilemap é:

```text
um mapa construído usando pequenos blocos
```

Esses blocos são chamados:

```text
tiles
```

---

# 2. O que é Grid?

O mapa funciona como:

```text
uma grade
```

Exemplo:

```text
┌──┬──┬──┬──┐
│  │  │  │  │
├──┼──┼──┼──┤
│  │  │  │  │
├──┼──┼──┼──┤
│  │  │  │  │
└──┴──┴──┴──┘
```

Cada quadrado é:

```text
um tile
```

---

# 3. MAP_WIDTH

```c
#define MAP_WIDTH 20
```

Define:

```text
quantidade de colunas
```

---

# 4. MAP_HEIGHT

```c
#define MAP_HEIGHT 12
```

Define:

```text
quantidade de linhas
```

---

# 5. TILE_SIZE

```c
#define TILE_SIZE 64
```

Cada tile possui:

```text
64x64 pixels
```

---

# 6. Matriz do mapa

```c
int mapa[MAP_HEIGHT][MAP_WIDTH]
```

Essa matriz representa:

```text
o mundo do jogo
```

---

# Exemplo

```text
1 = parede
2 = grama
3 = água
0 = vazio
```

---

# Visualização

```text
1 1 1 1
1 0 0 1
1 2 3 1
1 1 1 1
```

---

# 7. Jogador

```c
Vector2 jogador = { 100, 100 };
```

Representa:
- posição do jogador no mapa

---

# 8. Movimento

```c
jogador.x += velocidade * delta;
```

Usamos:
- delta time
- movimento profissional

---

# 9. Colisão com tiles

Agora fazemos colisão usando:

```text
posição do jogador
↓
linha e coluna
↓
tipo do tile
```

---

# 10. Descobrindo coluna

```c
int coluna = jogador.x / TILE_SIZE;
```

---

# Exemplo

Se:

```text
jogador.x = 128
```

e:

```text
TILE_SIZE = 64
```

então:

```text
128 / 64 = coluna 2
```

---

# 11. Descobrindo linha

```c
int linha = jogador.y / TILE_SIZE;
```

---

# 12. Verificando tile sólido

```c
if (mapa[linha][coluna] == 1)
```

Significa:

```text
se o tile for parede
```

---

# 13. Cancelando movimento

```c
jogador = antigaPosicao;
```

Se colidir:
- volta para posição anterior

---

# Isso cria colisão

```text
movimento
↓
bate parede
↓
volta posição
```

---

# 14. Desenhando mapa

Usamos:

```c
for linha
↓
for coluna
```

para percorrer toda matriz.

---

# 15. Convertendo grid para pixels

```c
int x = coluna * TILE_SIZE;
int y = linha * TILE_SIZE;
```

---

# Exemplo

Coluna 5:

```text
5 * 64 = 320 pixels
```

---

# 16. Tipo do tile

```c
int tile = mapa[linha][coluna];
```

Pega:
- valor armazenado na matriz

---

# 17. Renderizando tiles

```c
if (tile == 1)
```

Desenha:
- parede

---

```c
else if (tile == 2)
```

Desenha:
- grama

---

```c
else if (tile == 3)
```

Desenha:
- água

---

# 18. Tile vazio

```c
DrawRectangleLines()
```

Desenha:
- grid vazio

---

# 19. Fluxo completo

```text
matriz
↓
linha e coluna
↓
converte para pixels
↓
desenha tile
↓
forma mapa completo
```

---

# Conceitos profissionais aprendidos

| Conceito | Foi usado |
|---|---|
| Tilemap | ✔ |
| Grid | ✔ |
| Matriz | ✔ |
| Colisão de cenário | ✔ |
| Coordenadas | ✔ |
| Renderização de tiles | ✔ |
| Mundo 2D | ✔ |
| Mapa procedural básico | ✔ |

---

# O que o aluno aprende de verdade

O aluno entende:

```text
mapas são dados
```

E que jogos armazenam fases usando:
- matrizes
- tiles
- grids

---

# Curiosidade MUITO importante

Muitos jogos clássicos usam:
- tilemaps
- grids
- matrizes

Inclusive:
- Mario
- Zelda
- Pokémon
- Terraria
- Stardew Valley

---

# Resultado esperado

Você verá:

✅ mapa completo  
✅ paredes  
✅ grama  
✅ água  
✅ jogador andando  
✅ colisão com paredes  
✅ grid visual  

---

# Atividade da Aula

## Exercício 1

Adicione novo tile:

```text
lava
```

---

## Exercício 2

Crie mapa maior.

---

## Exercício 3

Adicione árvores.

---

## Exercício 4

Faça tiles usando imagens.

---

# Desafio Extra

Crie:

```text
fase estilo Mario
```

---

# Super Desafio

Crie:
- editor de mapa
- salvar tilemap
- carregar mapa
- minimapa
- câmera seguindo jogador

---

# Próximo passo

Na próxima aula podemos evoluir para:

```text
20 - Physics.md
```

onde iremos aprender:

- gravidade
- velocidade vertical
- pulo
- aceleração
- física básica
- plataforma estilo Mario
