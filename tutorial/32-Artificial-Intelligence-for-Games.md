# 32 - Artificial Intelligence for Games

# Criando Inteligência Artificial para Jogos em Raylib (C)

# Objetivo da Aula

Nesta aula iremos aprender a criar:

```text
Inteligência Artificial para jogos
```

Agora o projeto poderá possuir:

- inimigos inteligentes
- perseguição
- patrulha
- tomada de decisão
- comportamento automático
- pathfinding
- FSM
- steering behaviors

Isso é a base de:
- NPCs
- inimigos
- bots
- jogos modernos
- IA de gameplay

---

# O que iremos aprender

Nesta aula vamos estudar:

- game AI
- FSM
- pathfinding
- behavior
- steering
- chase system
- patrulha
- tomada de decisão
- IA de inimigos

---

# O que é IA em jogos?

IA em jogos significa:

```text
personagens controlados pelo computador
```

---

# O mais importante

IA de jogos NÃO é:

```text
ChatGPT
```

---

# IA de jogos normalmente é:

- matemática
- regras
- estados
- comportamento automático

---

# Exemplos famosos

| Jogo | IA |
|---|---|
| Left 4 Dead | ✔ |
| Halo | ✔ |
| FEAR | ✔ |
| GTA | ✔ |
| Terraria | ✔ |

---

# Tipos de IA em jogos

| Tipo | Função |
|---|---|
| FSM | estados |
| Pathfinding | encontrar caminho |
| Steering | movimentação |
| Behavior Tree | decisões complexas |
| Utility AI | escolhas inteligentes |

---

# O que iremos construir?

Um inimigo que:

- patrulha
- detecta jogador
- persegue jogador
- retorna patrulha

---

# Estrutura Mental

```text
PLAYER
↓
ENEMY AI
│
├── PATROL
├── CHASE
└── RETURN
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
// ESTADOS DA IA
// =========================================

typedef enum EnemyState
{
    PATROL,
    CHASE,
    RETURN

} EnemyState;

// =========================================
// ENEMY
// =========================================

typedef struct Enemy
{
    Vector2 position;

    Vector2 origin;

    float speed;

    float detectionRadius;

    EnemyState state;

} Enemy;

// =========================================
// NORMALIZA DIREÇÃO
// =========================================

Vector2 Normalize(Vector2 v)
{
    float length =
        sqrtf(v.x * v.x + v.y * v.y);

    if (length != 0)
    {
        v.x /= length;
        v.y /= length;
    }

    return v;
}

// =========================================
// DISTÂNCIA
// =========================================

float Distance(Vector2 a, Vector2 b)
{
    float dx = a.x - b.x;

    float dy = a.y - b.y;

    return sqrtf(dx * dx + dy * dy);
}

// =========================================
// UPDATE AI
// =========================================

void UpdateEnemyAI(
    Enemy *enemy,
    Vector2 player,
    float delta)
{
    // =========================================
    // DISTÂNCIA PLAYER
    // =========================================

    float distance =
        Distance(
            enemy->position,
            player
        );

    // =========================================
    // DETECÇÃO
    // =========================================

    if (distance <
        enemy->detectionRadius)
    {
        enemy->state = CHASE;
    }

    // =========================================
    // PLAYER LONGE
    // =========================================

    else if (
        enemy->state == CHASE &&
        distance >
        enemy->detectionRadius + 50)
    {
        enemy->state = RETURN;
    }

    // =========================================
    // FSM
    // =========================================

    switch (enemy->state)
    {
        // =====================================
        // PATROL
        // =====================================

        case PATROL:
        {
            enemy->position.x +=
                sin(GetTime()) *
                40 *
                delta;

            break;
        }

        // =====================================
        // CHASE
        // =====================================

        case CHASE:
        {
            Vector2 direction =
            {
                player.x -
                enemy->position.x,

                player.y -
                enemy->position.y
            };

            direction =
                Normalize(direction);

            enemy->position.x +=
                direction.x *
                enemy->speed *
                delta;

            enemy->position.y +=
                direction.y *
                enemy->speed *
                delta;

            break;
        }

        // =====================================
        // RETURN
        // =====================================

        case RETURN:
        {
            Vector2 direction =
            {
                enemy->origin.x -
                enemy->position.x,

                enemy->origin.y -
                enemy->position.y
            };

            direction =
                Normalize(direction);

            enemy->position.x +=
                direction.x *
                enemy->speed *
                delta;

            enemy->position.y +=
                direction.y *
                enemy->speed *
                delta;

            // =================================
            // CHEGOU ORIGEM
            // =================================

            if (Distance(
                enemy->position,
                enemy->origin) < 5)
            {
                enemy->state =
                    PATROL;
            }

            break;
        }
    }
}

// =========================================
// MAIN
// =========================================

int main(void)
{
    // =========================================
    // CRIA JANELA
    // =========================================

    InitWindow(
        1280,
        720,
        "Artificial Intelligence"
    );

    // FPS
    SetTargetFPS(60);

    // =========================================
    // PLAYER
    // =========================================

    Vector2 player =
        {300, 300};

    float playerSpeed = 300;

    // =========================================
    // ENEMY
    // =========================================

    Enemy enemy;

    enemy.position =
        (Vector2){800, 300};

    enemy.origin =
        enemy.position;

    enemy.speed = 200;

    enemy.detectionRadius = 200;

    enemy.state = PATROL;

    // =========================================
    // LOOP PRINCIPAL
    // =========================================

    while (!WindowShouldClose())
    {
        // =========================================
        // DELTA TIME
        // =========================================

        float delta =
            GetFrameTime();

        // =========================================
        // MOVIMENTO PLAYER
        // =========================================

        if (IsKeyDown(KEY_RIGHT))
            player.x +=
                playerSpeed * delta;

        if (IsKeyDown(KEY_LEFT))
            player.x -=
                playerSpeed * delta;

        if (IsKeyDown(KEY_UP))
            player.y -=
                playerSpeed * delta;

        if (IsKeyDown(KEY_DOWN))
            player.y +=
                playerSpeed * delta;

        // =========================================
        // UPDATE IA
        // =========================================

        UpdateEnemyAI(
            &enemy,
            player,
            delta
        );

        // =========================================
        // DRAW
        // =========================================

        BeginDrawing();

        ClearBackground(RAYWHITE);

        // =========================================
        // DETECTION RADIUS
        // =========================================

        DrawCircleLines(
            enemy.position.x,
            enemy.position.y,
            enemy.detectionRadius,
            LIGHTGRAY
        );

        // =========================================
        // PLAYER
        // =========================================

        DrawCircleV(
            player,
            30,
            BLUE
        );

        // =========================================
        // ENEMY
        // =========================================

        DrawCircleV(
            enemy.position,
            35,
            RED
        );

        // =========================================
        // LINHA CHASE
        // =========================================

        if (enemy.state == CHASE)
        {
            DrawLineV(
                enemy.position,
                player,
                RED
            );
        }

        // =========================================
        // HUD
        // =========================================

        DrawRectangle(
            0,
            0,
            1280,
            140,
            Fade(BLACK, 0.5f)
        );

        DrawText(
            "Artificial Intelligence",
            20,
            20,
            40,
            WHITE
        );

        DrawText(
            "Setas = mover jogador",
            20,
            70,
            20,
            WHITE
        );

        // =========================================
        // ESTADO DA IA
        // =========================================

        const char *stateText;

        switch (enemy.state)
        {
            case PATROL:
                stateText = "PATROL";
                break;

            case CHASE:
                stateText = "CHASE";
                break;

            case RETURN:
                stateText = "RETURN";
                break;

            default:
                stateText = "UNKNOWN";
        }

        DrawText(
            TextFormat(
                "Estado IA: %s",
                stateText
            ),
            20,
            100,
            20,
            YELLOW
        );

        DrawText(
            "FSM + Chase AI",
            900,
            100,
            20,
            SKYBLUE
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

# 1. O que é IA de jogos?

IA de jogos é:

```text
comportamento automático controlado por algoritmos
```

---

# Não é IA generativa

Normalmente:
- não usa LLM
- não usa ChatGPT

---

# Usa:

- matemática
- estados
- lógica
- regras

---

# 2. FSM

FSM significa:

```text
Finite State Machine
```

---

# Máquina de estados

A IA possui:
- estados
- transições

---

# Exemplo visual

```text
PATROL
   ↓ detecta player

CHASE
   ↓ perde player

RETURN
   ↓ chega origem

PATROL
```

---

# 3. EnemyState

```c
typedef enum EnemyState
```

Cria:
- estados da IA

---

# Estados

| Estado | Função |
|---|---|
| PATROL | patrulha |
| CHASE | perseguir |
| RETURN | voltar origem |

---

# 4. Enemy Struct

```c
typedef struct Enemy
```

Armazena:
- posição
- velocidade
- estado
- raio de detecção

---

# 5. Detection Radius

```c
float detectionRadius;
```

Representa:
- alcance da visão do inimigo

---

# 6. Distance()

```c
Distance(a, b)
```

Calcula:
- distância entre dois pontos

---

# Fórmula usada


::contentReference[oaicite:0]{index=0}


---

# Isso é MUITO usado em jogos

Para:
- visão
- colisão
- proximidade
- IA

---

# 7. Normalize()

```c
Normalize()
```

Transforma vetor em:

```text
direção unitária
```

---

# Isso é MUITO importante

Sem normalize:
- inimigo moveria rápido demais

---

# Vetor normalizado

Sempre possui:

:contentReference[oaicite:1]{index=1}

---

# 8. UpdateEnemyAI()

```c
UpdateEnemyAI()
```

Controla:
- comportamento da IA

---

# Isso é o “cérebro”

do inimigo.

---

# 9. Detecção do jogador

```c
if (distance < detectionRadius)
```

Significa:

```text
player entrou no alcance
```

---

# Então IA muda estado

```text
PATROL → CHASE
```

---

# 10. CHASE

No estado:

```text
CHASE
```

A IA:
- calcula direção
- anda até jogador

---

# Fórmula da direção

:contentReference[oaicite:2]{index=2}

---

# 11. RETURN

Quando jogador foge:
- inimigo retorna origem

---

# Isso é MUITO comum

Jogos stealth usam isso o tempo inteiro.

---

# 12. PATROL

Patrulha usa:

```c
sin(GetTime())
```

para:
- movimento automático

---

# Isso cria oscilação suave

---

# Fórmula do seno


::contentReference[oaicite:3]{index=3}


---

# 13. Steering Behavior

A perseguição aqui já é:

```text
steering behavior básico
```

---

# Steering significa

```text
movimento inteligente
```

---

# Muito usado em:

- NPCs
- carros
- multidões
- boids

---

# 14. Pathfinding

Nossa IA ainda NÃO possui:
- obstáculos
- navegação complexa

---

# Jogos modernos usam

| Algoritmo | Uso |
|---|---|
| A* | pathfinding |
| NavMesh | navegação |
| Flow Field | RTS |

---

# 15. Fluxo completo da IA

```text
PLAYER MOVE
↓
IA calcula distância
↓
FSM decide estado
↓
IA movimenta inimigo
↓
renderização
```

---

# Visualização mental

```text
PLAYER
   ↓
 DETECTION
   ↓
 FSM
   ↓
 CHASE
```

---

# 16. IA moderna em jogos

Jogos modernos usam:
- FSM
- Behavior Trees
- Utility AI
- GOAP
- Machine Learning

---

# Exemplos

| Técnica | Jogo |
|---|---|
| FSM | Terraria |
| Behavior Trees | Halo |
| Utility AI | The Sims |
| GOAP | FEAR |

---

# 17. FEAR

O jogo FEAR ficou famoso porque:
- inimigos pareciam inteligentes

Mas internamente usava:
- FSM + GOAP

---

# 18. IA e matemática

Grande parte da IA em jogos é:
- álgebra vetorial
- trigonometria
- estados
- heurísticas

---

# Conceitos profissionais aprendidos

| Conceito | Foi usado |
|---|---|
| FSM | ✔ |
| Game AI | ✔ |
| Steering | ✔ |
| Detection Radius | ✔ |
| Chase AI | ✔ |
| Distance Math | ✔ |
| Normalize | ✔ |
| State Machine | ✔ |

---

# O que você aprende de verdade

# você entende:

```text
IA de jogos é baseada em estados e matemática
```

E entende:
- FSM
- perseguição
- comportamento automático
- steering behaviors
- IA moderna de gameplay
- arquitetura usada em jogos reais

---

# Curiosidade MUITO importante

Mesmo jogos AAA ainda usam:
- FSM
- Behavior Trees
- steering
- pathfinding

Porque:
- são rápidos
- previsíveis
- eficientes

---

# Resultado esperado

Você verá:

✅ inimigo patrulhando  
✅ perseguição funcionando  
✅ FSM funcionando  
✅ estados de IA  
✅ steering básico  
✅ inimigo inteligente  

---

# Atividade da Aula

## Exercício 1

Adicione:
- ataque inimigo

---

## Exercício 2

Adicione:
- múltiplos inimigos

---

## Exercício 3

Adicione:
- vida do player

---

## Exercício 4

Adicione:
- obstáculos

---

# Desafio Extra

Implemente:
- pathfinding A*

---

# Super Desafio

Transforme isso em:
- stealth AI
- behavior trees
- GOAP
- squad AI
- tactical AI
- sistema AAA de inimigos

---

# Próximo passo

Na próxima aula podemos evoluir para:

```text
33 - Physics Engine.md
```

onde iremos aprender:

- física avançada
- gravidade
- rigid bodies
- forças
- impulso
- colisão real
- mini physics engine
