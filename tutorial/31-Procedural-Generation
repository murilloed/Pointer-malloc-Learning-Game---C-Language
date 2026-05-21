# 31 - Procedural Generation

# Criando Geração Procedural em Raylib (C)

# Objetivo da Aula

Nesta aula iremos aprender a criar:

```text
geração procedural
```

Agora o jogo poderá criar:

- mapas automáticos
- terrenos infinitos
- mundos aleatórios
- cavernas
- biomas
- dungeons
- geração dinâmica

Isso é a base de:
- Minecraft
- Terraria
- No Man’s Sky
- Rogue-like
- jogos infinitos

---

# O que iremos aprender

Nesta aula vamos estudar:

- procedural generation
- random
- noise
- Perlin Noise
- mapas automáticos
- geração de terreno
- seed
- algoritmos procedurais

---

# O que é geração procedural?

Geração procedural significa:

```text
conteúdo criado automaticamente por algoritmos
```

---

# Em vez de desenhar tudo manualmente

o computador:
- gera o mundo sozinho

---

# Exemplos famosos

| Jogo | Procedural |
|---|---|
| Minecraft | ✔ |
| Terraria | ✔ |
| No Man’s Sky | ✔ |
| Diablo | ✔ |
| Hades | ✔ |

---

# O que pode ser procedural?

| Elemento | Procedural |
|---|---|
| terreno | ✔ |
| cavernas | ✔ |
| loot | ✔ |
| inimigos | ✔ |
| mapas | ✔ |
| planetas | ✔ |

---

# Conceito MAIS importante

Procedural generation normalmente usa:

```text
matemática + randomização
```

---

# O que é Seed?

Seed é:

```text
valor inicial da geração aleatória
```

---

# Exemplo

```c
SetRandomSeed(123);
```

Sempre gera:
- o mesmo mundo

---

# Isso é MUITO importante

Minecraft funciona assim.

---

# Estrutura do Projeto

```text
procedural_world/
│
├── src/
│   └── main.c
│
└── assets/
```

---

# Código Completo

```c
// =========================================
// IMPORTA RAYLIB
// =========================================

#include "raylib.h"

// =========================================
// IMPORTA MATH
// =========================================

#include <math.h>

// =========================================
// CONSTANTES
// =========================================

#define MAP_WIDTH 100

#define MAP_HEIGHT 60

#define TILE_SIZE 20

// =========================================
// TIPOS DE TILE
// =========================================

typedef enum TileType
{
    TILE_GRASS,
    TILE_DIRT,
    TILE_STONE,
    TILE_WATER

} TileType;

// =========================================
// MAPA
// =========================================

TileType world[MAP_HEIGHT][MAP_WIDTH];

// =========================================
// GERA MUNDO
// =========================================

void GenerateWorld()
{
    // =========================================
    // SEED ALEATÓRIA
    // =========================================

    SetRandomSeed(GetTime());

    // =========================================
    // HEIGHTMAP
    // =========================================

    int alturaBase = 25;

    // =========================================
    // LOOP X
    // =========================================

    for (int x = 0; x < MAP_WIDTH; x++)
    {
        // =========================================
        // NOISE SIMPLES
        // =========================================

        float noise =
            sin(x * 0.2f) * 5;

        // =========================================
        // ALTURA DO TERRENO
        // =========================================

        int terrainHeight =
            alturaBase +
            noise +
            GetRandomValue(-2, 2);

        // =========================================
        // LOOP Y
        // =========================================

        for (int y = 0; y < MAP_HEIGHT; y++)
        {
            // =========================================
            // CÉU
            // =========================================

            if (y < terrainHeight)
            {
                world[y][x] =
                    TILE_WATER;
            }

            // =========================================
            // GRAMA
            // =========================================

            else if (y == terrainHeight)
            {
                world[y][x] =
                    TILE_GRASS;
            }

            // =========================================
            // TERRA
            // =========================================

            else if (y < terrainHeight + 4)
            {
                world[y][x] =
                    TILE_DIRT;
            }

            // =========================================
            // PEDRA
            // =========================================

            else
            {
                world[y][x] =
                    TILE_STONE;
            }
        }
    }
}

// =========================================
// DRAW WORLD
// =========================================

void DrawWorld()
{
    // =========================================
    // LOOP MAPA
    // =========================================

    for (int y = 0; y < MAP_HEIGHT; y++)
    {
        for (int x = 0; x < MAP_WIDTH; x++)
        {
            Color color;

            // =========================================
            // DEFINE COR
            // =========================================

            switch (world[y][x])
            {
                case TILE_GRASS:
                    color = GREEN;
                    break;

                case TILE_DIRT:
                    color = BROWN;
                    break;

                case TILE_STONE:
                    color = GRAY;
                    break;

                case TILE_WATER:
                    color = SKYBLUE;
                    break;

                default:
                    color = BLACK;
            }

            // =========================================
            // DESENHA TILE
            // =========================================

            DrawRectangle(
                x * TILE_SIZE,
                y * TILE_SIZE,
                TILE_SIZE,
                TILE_SIZE,
                color
            );
        }
    }
}

// =========================================
// MAIN
// =========================================

int main(void)
{
    // Cria janela
    InitWindow(
        1280,
        720,
        "Procedural Generation"
    );

    // FPS
    SetTargetFPS(60);

    // =========================================
    // GERA MUNDO
    // =========================================

    GenerateWorld();

    // =========================================
    // LOOP PRINCIPAL
    // =========================================

    while (!WindowShouldClose())
    {
        // =========================================
        // REGERA MUNDO
        // =========================================

        if (IsKeyPressed(KEY_R))
        {
            GenerateWorld();
        }

        // =========================================
        // DRAW
        // =========================================

        BeginDrawing();

        ClearBackground(RAYWHITE);

        // =========================================
        // DESENHA MUNDO
        // =========================================

        DrawWorld();

        // =========================================
        // HUD
        // =========================================

        DrawRectangle(
            0,
            0,
            1280,
            120,
            Fade(BLACK, 0.5f)
        );

        DrawText(
            "Procedural Generation",
            20,
            20,
            40,
            WHITE
        );

        DrawText(
            "R = gerar novo mundo",
            20,
            70,
            20,
            WHITE
        );

        DrawText(
            "Terreno gerado proceduralmente",
            700,
            70,
            20,
            YELLOW
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

# 1. O que é procedural generation?

É:

```text
geração automática de conteúdo
```

---

# O computador cria

- mapas
- terrenos
- cavernas
- planetas

usando:
- algoritmos

---

# 2. Mundo como matriz

```c
TileType world[MAP_HEIGHT][MAP_WIDTH];
```

Representa:
- mapa 2D

---

# Cada posição

é um:
- tile

---

# Visualização mental

```text
[GRASS][GRASS][DIRT]
[DIRT ][STONE][STONE]
```

---

# 3. TileType

```c
typedef enum TileType
```

Cria:
- tipos de blocos

---

# Tipos

| Tile | Significado |
|---|---|
| GRASS | grama |
| DIRT | terra |
| STONE | pedra |
| WATER | água |

---

# 4. GenerateWorld()

```c
GenerateWorld()
```

Responsável por:
- criar mapa automaticamente

---

# Isso é o “algoritmo procedural”

---

# 5. Seed

```c
SetRandomSeed(GetTime());
```

Define:
- aleatoriedade do mundo

---

# Seed controla

```text
qual mundo será criado
```

---

# Mesma seed

```text
mesmo mundo
```

---

# 6. Noise

```c
sin(x * 0.2f)
```

Cria:
- variação suave

---

# Isso simula terreno

Sem noise:
- mundo ficaria reto

---

# 7. Terrain Height

```c
terrainHeight
```

Define:
- altura do terreno

---

# Exemplo

```text
x = 10
altura = 20

x = 11
altura = 21
```

---

# Isso cria montanhas

---

# 8. GetRandomValue()

```c
GetRandomValue(-2, 2)
```

Adiciona:
- caos aleatório

---

# Isso deixa mundo menos artificial

---

# 9. Loop X

```c
for (int x = 0; x < MAP_WIDTH; x++)
```

Percorre:
- colunas do mapa

---

# 10. Loop Y

```c
for (int y = 0; y < MAP_HEIGHT; y++)
```

Percorre:
- linhas do mapa

---

# Isso percorre mundo inteiro

---

# 11. Geração em camadas

```c
if (y < terrainHeight)
```

Define:
- céu/água

---

# Grama

```c
y == terrainHeight
```

---

# Terra

```c
y < terrainHeight + 4
```

---

# Pedra

```c
else
```

---

# Isso cria geologia simples

---

# 12. DrawWorld()

```c
DrawWorld()
```

Renderiza:
- todos os tiles

---

# Cada tile possui:

- posição
- cor
- tipo

---

# 13. DrawRectangle()

```c
DrawRectangle()
```

Desenha:
- blocos do mundo

---

# Isso é tilemap procedural

---

# 14. Regeneração dinâmica

```c
KEY_R
```

Cria:
- novo mundo instantaneamente

---

# Isso é MUITO importante

Jogos procedural:
- geram mundos infinitos

---

# 15. Noise

O conceito mais importante aqui é:

```text
noise
```

---

# Noise gera

- montanhas
- rios
- cavernas
- biomas

---

# Engines usam

| Tipo | Uso |
|---|---|
| Perlin Noise | terreno |
| Simplex Noise | mundos |
| Cellular Noise | cavernas |

---

# 16. Fluxo procedural

```text
SEED
↓
NOISE
↓
HEIGHTMAP
↓
TILES
↓
WORLD
```

---

# Visualização mental

```text
ALGORITMO
↓
gera alturas
↓
gera tiles
↓
cria mundo
```

---

# 17. Procedural moderno

Jogos modernos usam procedural para:
- economizar espaço
- criar mundos infinitos
- aumentar replayability

---

# Exemplo absurdo

No Man's Sky gera:

```text
QUINTILHÕES de planetas
```

---

# 18. Minecraft

Minecraft usa:
- Perlin Noise
- chunk generation
- procedural caves

---

# 19. Chunk System

Jogos grandes dividem mundo em:

```text
chunks
```

---

# Exemplo

```text
16x16 blocos
```

---

# Isso melhora performance

Muito importante.

---

# Conceitos profissionais aprendidos

| Conceito | Foi usado |
|---|---|
| Procedural Generation | ✔ |
| Noise | ✔ |
| Seed | ✔ |
| Tilemap | ✔ |
| Terrain Generation | ✔ |
| Heightmap | ✔ |
| Random | ✔ |
| World Generation | ✔ |

---

# O que você aprende de verdade

# você entende:

```text
mundos gigantes podem ser criados matematicamente
```

E entende:
- procedural generation
- noise
- geração automática
- terrenos
- tilemaps
- algoritmos procedurais
- arquitetura usada em Minecraft

---

# Curiosidade MUITO importante

Jogos modernos usam procedural para:
- mundos infinitos
- dungeons
- loot
- IA
- planetas
- vegetação
- cidades

Inclusive:
- Minecraft
- Terraria
- No Man's Sky
- Diablo
- Hades

---

# Resultado esperado

Você verá:

✅ terreno procedural  
✅ mundo aleatório  
✅ noise funcionando  
✅ geração automática  
✅ tilemap procedural  
✅ mundos regeneráveis  

---

# Atividade da Aula

## Exercício 1

Adicione:
- árvores

---

## Exercício 2

Adicione:
- cavernas

---

## Exercício 3

Adicione:
- rios

---

## Exercício 4

Adicione:
- biomas

---

# Desafio Extra

Crie:
- chunk system

---

# Super Desafio

Transforme isso em:
- Minecraft clone
- mundo infinito
- voxel engine
- procedural caves
- biomas dinâmicos
- terrain streaming

---

# Próximo passo

Na próxima aula podemos evoluir para:

```text
32 - Artificial Intelligence for Games.md
```

onde iremos aprender:

- IA para jogos
- pathfinding
- FSM
- behavior trees
- steering behaviors
- inimigos inteligentes
