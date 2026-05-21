# 27 - Entity Component System (ECS)

# Criando ECS em Raylib (C)

# Objetivo da Aula

Nesta aula iremos aprender a criar:

```text
Entity Component System (ECS)
```

Agora o projeto começará a usar:

- arquitetura moderna de jogos
- entidades
- componentes
- systems
- desacoplamento
- composição
- organização usada em engines profissionais

Isso é a base de:
- engines AAA
- ECS frameworks
- arquiteturas modernas
- engines escaláveis

---

# O que iremos aprender

Nesta aula vamos estudar:

- ECS
- entidades
- componentes
- systems
- composição
- desacoplamento
- arquitetura moderna
- data oriented design

---

# O que é ECS?

ECS significa:

```text
Entity Component System
```

---

# ECS divide o jogo em:

| Parte | Função |
|---|---|
| Entity | identificador |
| Component | dados |
| System | lógica |

---

# O mais importante

No ECS:

```text
objetos NÃO possuem comportamento
```

O comportamento fica nos:

```text
systems
```

---

# Arquitetura Tradicional

Arquitetura antiga:

```text
Player
├── update()
├── draw()
├── physics()
├── audio()
```

Problemas:
- acoplamento
- difícil manutenção
- pouca escalabilidade

---

# Arquitetura ECS

```text
ENTITY
│
├── PositionComponent
├── VelocityComponent
├── SpriteComponent
└── HealthComponent
```

E os systems fazem:

```text
MovementSystem
RenderSystem
HealthSystem
AISystem
```

---

# Jogos e Engines que usam ECS

| Engine | ECS |
|---|---|
| Unity DOTS | ✔ |
| Unreal Mass | ✔ |
| Bevy | ✔ |
| Flecs | ✔ |
| EnTT | ✔ |

---

# Visualização Mental

```text
ENTITY
↓
apenas ID

COMPONENT
↓
dados

SYSTEM
↓
processa componentes
```

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

#define MAX_ENTITIES 100

// =========================================
// ENTITY
// =========================================

typedef int Entity;

// =========================================
// COMPONENTES
// =========================================

// Position Component
typedef struct PositionComponent
{
    Vector2 position;

} PositionComponent;

// Velocity Component
typedef struct VelocityComponent
{
    Vector2 velocity;

} VelocityComponent;

// Render Component
typedef struct RenderComponent
{
    Color color;

    float size;

} RenderComponent;

// =========================================
// STORAGE DOS COMPONENTES
// =========================================

PositionComponent positions[MAX_ENTITIES];

VelocityComponent velocities[MAX_ENTITIES];

RenderComponent renders[MAX_ENTITIES];

// =========================================
// FLAGS DE COMPONENTES
// =========================================

bool hasPosition[MAX_ENTITIES] = {0};

bool hasVelocity[MAX_ENTITIES] = {0};

bool hasRender[MAX_ENTITIES] = {0};

// =========================================
// ENTITY COUNTER
// =========================================

int entityCount = 0;

// =========================================
// CREATE ENTITY
// =========================================

Entity CreateEntity()
{
    return entityCount++;
}

// =========================================
// ADD COMPONENTS
// =========================================

void AddPosition(
    Entity entity,
    Vector2 position)
{
    positions[entity].position = position;

    hasPosition[entity] = true;
}

void AddVelocity(
    Entity entity,
    Vector2 velocity)
{
    velocities[entity].velocity = velocity;

    hasVelocity[entity] = true;
}

void AddRender(
    Entity entity,
    Color color,
    float size)
{
    renders[entity].color = color;

    renders[entity].size = size;

    hasRender[entity] = true;
}

// =========================================
// MOVEMENT SYSTEM
// =========================================

void MovementSystem(float delta)
{
    for (int i = 0; i < entityCount; i++)
    {
        // Entidade precisa ter:
        // Position + Velocity

        if (hasPosition[i] &&
            hasVelocity[i])
        {
            positions[i].position.x +=
                velocities[i].velocity.x *
                delta;

            positions[i].position.y +=
                velocities[i].velocity.y *
                delta;
        }
    }
}

// =========================================
// RENDER SYSTEM
// =========================================

void RenderSystem()
{
    for (int i = 0; i < entityCount; i++)
    {
        // Entidade precisa ter:
        // Position + Render

        if (hasPosition[i] &&
            hasRender[i])
        {
            DrawCircleV(
                positions[i].position,
                renders[i].size,
                renders[i].color
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
        1200,
        700,
        "Entity Component System"
    );

    // FPS
    SetTargetFPS(60);

    // =========================================
    // PLAYER ENTITY
    // =========================================

    Entity player =
        CreateEntity();

    AddPosition(
        player,
        (Vector2){300, 300}
    );

    AddVelocity(
        player,
        (Vector2){120, 80}
    );

    AddRender(
        player,
        BLUE,
        30
    );

    // =========================================
    // ENEMY ENTITY
    // =========================================

    Entity enemy =
        CreateEntity();

    AddPosition(
        enemy,
        (Vector2){700, 400}
    );

    AddVelocity(
        enemy,
        (Vector2){-100, 60}
    );

    AddRender(
        enemy,
        RED,
        40
    );

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
        // INPUT PLAYER
        // =========================================

        if (IsKeyDown(KEY_RIGHT))
        {
            velocities[player].velocity.x += 5;
        }

        if (IsKeyDown(KEY_LEFT))
        {
            velocities[player].velocity.x -= 5;
        }

        if (IsKeyDown(KEY_UP))
        {
            velocities[player].velocity.y -= 5;
        }

        if (IsKeyDown(KEY_DOWN))
        {
            velocities[player].velocity.y += 5;
        }

        // =========================================
        // SYSTEMS
        // =========================================

        MovementSystem(delta);

        // =========================================
        // BOUNDARY COLLISION
        // =========================================

        for (int i = 0; i < entityCount; i++)
        {
            if (hasPosition[i] &&
                hasVelocity[i])
            {
                if (positions[i].position.x < 0 ||
                    positions[i].position.x > 1200)
                {
                    velocities[i].velocity.x *= -1;
                }

                if (positions[i].position.y < 0 ||
                    positions[i].position.y > 700)
                {
                    velocities[i].velocity.y *= -1;
                }
            }
        }

        // =========================================
        // DRAW
        // =========================================

        BeginDrawing();

        ClearBackground(RAYWHITE);

        // =========================================
        // RENDER ECS
        // =========================================

        RenderSystem();

        // =========================================
        // HUD
        // =========================================

        DrawRectangle(
            0,
            0,
            1200,
            140,
            Fade(LIGHTGRAY, 0.9f)
        );

        DrawText(
            "Entity Component System (ECS)",
            20,
            20,
            40,
            DARKBLUE
        );

        DrawText(
            "Setas = altera velocidade do player",
            20,
            70,
            20,
            DARKGRAY
        );

        DrawText(
            TextFormat(
                "Entities: %d",
                entityCount
            ),
            20,
            100,
            20,
            BLACK
        );

        DrawText(
            "ECS = Entities + Components + Systems",
            620,
            100,
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

# 1. O que é Entity?

Entity é:

```text
apenas um identificador
```

---

# Exemplo

```c
typedef int Entity;
```

A entidade:
- não possui lógica
- não possui comportamento

Ela é apenas:

```text
um ID
```

---

# Exemplo visual

```text
Entity 0
Entity 1
Entity 2
```

---

# 2. O que é Component?

Component é:

```text
dados
```

---

# Exemplo

```c
PositionComponent
```

guarda:
- posição

---

# VelocityComponent

guarda:
- velocidade

---

# RenderComponent

guarda:
- aparência visual

---

# O mais importante

Componentes:

```text
NÃO possuem lógica
```

Eles apenas armazenam:
- informações

---

# 3. Storage de componentes

```c
PositionComponent positions[MAX_ENTITIES];
```

Armazena:
- todas as posições

---

# Isso é MUITO importante

ECS normalmente usa:

```text
dados contíguos em memória
```

---

# Isso melhora performance

Muito usado em:
- engines modernas
- AAA
- data oriented design

---

# 4. Flags de componentes

```c
bool hasPosition[MAX_ENTITIES];
```

Indica:
- se entidade possui componente

---

# Exemplo

```text
Entity 0 → possui Position
Entity 1 → não possui
```

---

# 5. CreateEntity()

```c
CreateEntity()
```

Cria:
- nova entidade

---

# Resultado

```text
0
1
2
3
```

---

# 6. AddPosition()

```c
AddPosition()
```

Adiciona:
- componente Position

---

# Isso é composição

A entidade:
- ganha capacidades

---

# Exemplo

```text
Entity
↓
+ Position
↓
+ Velocity
↓
+ Render
```

---

# Isso forma um “objeto”

---

# 7. MovementSystem

```c
MovementSystem()
```

Processa:
- entidades com Position + Velocity

---

# O mais importante

O system:

```text
não sabe se é player
não sabe se é inimigo
não sabe se é NPC
```

Ele apenas processa:

```text
componentes
```

---

# Isso é desacoplamento

MUY importante em:
- engines modernas

---

# 8. Verificando componentes

```c
if (hasPosition[i] &&
    hasVelocity[i])
```

Significa:

```text
processa apenas entidades válidas
```

---

# 9. Movimento ECS

```c
positions[i].position.x +=
velocities[i].velocity.x * delta;
```

System altera:
- componentes

---

# 10. RenderSystem

```c
RenderSystem()
```

Processa:
- Position + Render

---

# Resultado

Qualquer entidade com:
- posição
- render

será desenhada.

---

# Isso é MUITO poderoso

Você pode criar:
- player
- inimigos
- projéteis
- partículas

usando:
- os mesmos systems

---

# 11. ECS e composição

Arquitetura tradicional:

```text
Player herda Character
Enemy herda Character
```

Problema:
- herança complexa

---

# ECS usa composição

```text
Entity
+ Position
+ Velocity
+ Render
+ Health
+ AI
```

---

# Isso é MUITO moderno

---

# 12. Fluxo completo ECS

```text
ENTITY
↓
adiciona componentes
↓
systems processam
↓
renderização acontece
```

---

# Visualização mental

```text
ENTITY
│
├── Position
├── Velocity
└── Render

↓

SYSTEMS

↓

MOVEMENT
RENDER
AI
PHYSICS
```

---

# 13. Data Oriented Design

ECS é baseado em:

```text
dados organizados para performance
```

---

# Isso melhora:

- cache CPU
- paralelismo
- escalabilidade
- SIMD
- multithreading

---

# 14. ECS em engines modernas

Hoje:
- ECS domina engines modernas

---

# Exemplos

| Engine | ECS |
|---|---|
| Unity DOTS | ✔ |
| Bevy | ✔ |
| Unreal Mass | ✔ |
| Flecs | ✔ |

---

# Conceitos profissionais aprendidos

| Conceito | Foi usado |
|---|---|
| ECS | ✔ |
| Entity | ✔ |
| Component | ✔ |
| System | ✔ |
| Composition | ✔ |
| Data Oriented Design | ✔ |
| Desacoplamento | ✔ |
| Arquitetura Moderna | ✔ |

---

# O que você aprende de verdade

# você entende:

```text
jogos modernos NÃO giram em torno de objetos gigantes
```

Eles giram em torno de:

```text
dados
↓
componentes
↓
systems
```

E entende:
- arquitetura moderna
- composição
- desacoplamento
- organização AAA
- ECS profissional

---

# Curiosidade MUITO importante

Muitas engines modernas abandonaram:
- herança pesada
- OOP clássico

e migraram para:

```text
ECS + Data Oriented Design
```

Porque:
- escala melhor
- usa melhor CPU
- facilita paralelismo

---

# Resultado esperado

Você verá:

✅ entities funcionando  
✅ components funcionando  
✅ systems funcionando  
✅ arquitetura ECS  
✅ entidades desacopladas  
✅ organização moderna  

---

# Atividade da Aula

## Exercício 1

Crie:
- HealthComponent

---

## Exercício 2

Crie:
- AISystem

---

## Exercício 3

Crie:
- CollisionSystem

---

## Exercício 4

Adicione:
- dezenas de entidades

---

# Desafio Extra

Crie:
- sistema de projéteis ECS

---

# Super Desafio

Transforme isso em:
- mini ECS engine
- multithreading
- job system
- physics ECS
- rendering ECS
- arquitetura AAA

---

# Próximo passo

Na próxima aula podemos evoluir para:

```text
28 - Networking Multiplayer.md
```

onde iremos aprender:

- multiplayer
- sockets
- cliente/servidor
- sincronização
- arquitetura online
- multiplayer básico em C
