# 18 - Camera2D

# Criando Camera2D em Raylib (C)

# Objetivo da Aula

Nesta aula iremos aprender a criar:

```text
uma câmera 2D
```

Agora o jogo deixará de ficar preso apenas à tela.

Vamos criar:

- câmera seguindo jogador
- mundo maior que a janela
- scrolling
- movimentação de mapa
- sensação de espaço
- visão de jogo profissional

---

# O que iremos aprender

Nesta aula vamos estudar:

- Camera2D
- target
- offset
- zoom
- rotação
- BeginMode2D
- coordenadas do mundo
- câmera seguindo jogador
- mapa maior que a tela

---

# O que é Camera2D?

A câmera define:

```text
o que o jogador está vendo
```

Sem câmera:

```text
o jogo inteiro fica preso na janela
```

Com câmera:

```text
o mundo pode ser gigante
```

---

# Exemplo visual

Sem câmera:

```text
┌───────────────┐
│ jogador       │
│ mapa pequeno  │
└───────────────┘
```

Com câmera:

```text
MUNDO GIGANTE
┌──────────────────────────────────────┐
│                                      │
│          CAMERA MOSTRA APENAS        │
│              UMA PARTE               │
│                                      │
└──────────────────────────────────────┘
```

---

# Jogos que usam câmera

Praticamente TODOS:

| Jogo | Tipo de câmera |
|---|---|
| Mario | side scrolling |
| GTA | câmera dinâmica |
| Terraria | segue jogador |
| Zelda | câmera top-down |
| Hollow Knight | câmera suave |

---

# Código Completo

```c
// =========================================
// IMPORTA RAYLIB
// =========================================

#include "raylib.h"

// =========================================
// MAIN
// =========================================

int main(void)
{
    // Cria janela
    InitWindow(1200, 700, "Camera2D");

    // Define FPS
    SetTargetFPS(60);

    // =========================================
    // JOGADOR
    // =========================================

    // Posição do jogador no mundo
    Vector2 jogador = { 500, 500 };

    // Velocidade
    float velocidade = 300;

    // =========================================
    // CAMERA
    // =========================================

    Camera2D camera = { 0 };

    // Centro da câmera na tela
    camera.offset = (Vector2){ 600, 350 };

    // Alvo da câmera
    camera.target = jogador;

    // Rotação da câmera
    camera.rotation = 0.0f;

    // Zoom
    camera.zoom = 1.0f;

    // =========================================
    // LOOP PRINCIPAL
    // =========================================

    while (!WindowShouldClose())
    {
        // =========================================
        // UPDATE
        // =========================================

        // Delta time
        float delta = GetFrameTime();

        // Movimento direita
        if (IsKeyDown(KEY_RIGHT))
            jogador.x += velocidade * delta;

        // Movimento esquerda
        if (IsKeyDown(KEY_LEFT))
            jogador.x -= velocidade * delta;

        // Movimento cima
        if (IsKeyDown(KEY_UP))
            jogador.y -= velocidade * delta;

        // Movimento baixo
        if (IsKeyDown(KEY_DOWN))
            jogador.y += velocidade * delta;

        // Atualiza alvo da câmera
        camera.target = jogador;

        // Zoom com mouse wheel
        camera.zoom += GetMouseWheelMove() * 0.1f;

        // Limites do zoom
        if (camera.zoom < 0.2f)
            camera.zoom = 0.2f;

        if (camera.zoom > 3.0f)
            camera.zoom = 3.0f;

        // Rotação com teclas
        if (IsKeyDown(KEY_Q))
            camera.rotation -= 50 * delta;

        if (IsKeyDown(KEY_E))
            camera.rotation += 50 * delta;

        // =========================================
        // DRAW
        // =========================================

        BeginDrawing();

        // Fundo
        ClearBackground(RAYWHITE);

        // =========================================
        // MODO CAMERA 2D
        // =========================================

        BeginMode2D(camera);

        // =========================================
        // MUNDO
        // =========================================

        // Grid do mundo
        for (int x = -5000; x < 5000; x += 100)
        {
            DrawLine(x, -5000, x, 5000, LIGHTGRAY);
        }

        for (int y = -5000; y < 5000; y += 100)
        {
            DrawLine(-5000, y, 5000, y, LIGHTGRAY);
        }

        // Centro do mundo
        DrawCircle(0, 0, 20, RED);

        // Jogador
        DrawRectangleV(
            jogador,
            (Vector2){50, 50},
            BLUE
        );

        // Objetos do mundo
        DrawRectangle(1000, 300, 200, 200, GREEN);
        DrawRectangle(-800, -400, 300, 150, ORANGE);
        DrawCircle(-1200, 700, 100, PURPLE);

        // Finaliza modo câmera
        EndMode2D();

        // =========================================
        // HUD
        // =========================================

        DrawRectangle(0, 0, 1200, 120, Fade(LIGHTGRAY, 0.8f));

        DrawText(
            "Camera2D em Raylib",
            20,
            20,
            30,
            DARKBLUE
        );

        DrawText(
            "Setas = mover | Mouse Wheel = zoom | Q/E = rotacao",
            20,
            60,
            20,
            DARKGRAY
        );

        DrawText(
            TextFormat("Posicao: %.0f %.0f",
                       jogador.x,
                       jogador.y),
            20,
            90,
            20,
            BLACK
        );

        DrawText(
            TextFormat("Zoom: %.2f",
                       camera.zoom),
            350,
            90,
            20,
            BLACK
        );

        DrawText(
            TextFormat("Rotacao: %.1f",
                       camera.rotation),
            520,
            90,
            20,
            BLACK
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

# 1. O que é Camera2D?

```c
Camera2D
```

é uma struct da Raylib usada para controlar:

- posição da câmera
- zoom
- rotação
- alvo da câmera

---

# Estrutura interna da Camera2D

Internamente ela possui:

```c
typedef struct Camera2D
{
    Vector2 offset;
    Vector2 target;
    float rotation;
    float zoom;
} Camera2D;
```

---

# O que cada campo faz

| Campo | Função |
|---|---|
| offset | centro da câmera na tela |
| target | alvo que câmera segue |
| rotation | rotação |
| zoom | aproximação |

---

# 2. Offset

```c
camera.offset = (Vector2){ 600, 350 };
```

Define:

```text
onde a câmera fica na tela
```

Como a janela possui:

```text
1200 x 700
```

o centro é:

```text
600 x 350
```

---

# O que isso significa?

Queremos que:

```text
o jogador fique no centro da tela
```

---

# 3. Target

```c
camera.target = jogador;
```

Define:

```text
quem a câmera irá seguir
```

Neste caso:

```text
o jogador
```

---

# O que acontece?

Quando o jogador se move:

```text
a câmera acompanha
```

---

# 4. Rotação

```c
camera.rotation = 0.0f;
```

Controla:

```text
ângulo da câmera
```

---

# Exemplo

| Valor | Resultado |
|---|---|
| 0 | normal |
| 45 | inclinada |
| 90 | girada |

---

# 5. Zoom

```c
camera.zoom = 1.0f;
```

Controla:

```text
aproximação
```

---

# Exemplo

| Zoom | Resultado |
|---|---|
| 0.5 | afastado |
| 1.0 | normal |
| 2.0 | aproximado |

---

# 6. Delta Time

```c
float delta = GetFrameTime();
```

Usamos:

```text
movimento baseado no tempo
```

---

# 7. Movimento do jogador

```c
jogador.x += velocidade * delta;
```

Movimento profissional:

```text
velocidade × tempo
```

---

# 8. Atualizando a câmera

```c
camera.target = jogador;
```

A câmera:
- segue o jogador
- acompanha movimento

---

# 9. Zoom com mouse wheel

```c
camera.zoom += GetMouseWheelMove() * 0.1f;
```

Permite:

```text
aproximar e afastar câmera
```

---

# O que GetMouseWheelMove faz

Retorna:

```text
movimento da roda do mouse
```

---

# 10. Limites de zoom

```c
if (camera.zoom < 0.2f)
```

Evita:

```text
zoom negativo ou absurdo
```

---

# 11. Rotação com teclado

```c
camera.rotation += 50 * delta;
```

Gira câmera suavemente.

---

# 12. BeginMode2D

```c
BeginMode2D(camera);
```

Essa é uma das funções MAIS importantes da Raylib.

Ela diz:

```text
“agora tudo será desenhado usando a câmera”
```

---

# Tudo dentro do BeginMode2D

```c
BeginMode2D(camera)

↓

mundo do jogo

↓

EndMode2D()
```

será afetado por:

- posição
- zoom
- rotação

---

# 13. Grid infinito

```c
for (int x = -5000; x < 5000; x += 100)
```

Cria:

```text
linhas do mundo
```

Isso ajuda a visualizar:
- movimento
- câmera
- espaço do mapa

---

# 14. Mundo grande

Observe:

```text
-5000 até 5000
```

Isso significa:

```text
mundo MUITO maior que a tela
```

---

# 15. EndMode2D

```c
EndMode2D();
```

Finaliza:
- modo câmera

Tudo desenhado depois disso:
- NÃO sofre efeito da câmera

---

# Isso é importante para HUD

HUD normalmente:
- não gira
- não dá zoom
- não acompanha mundo

---

# 16. HUD

A HUD continua fixa.

Isso é exatamente como jogos reais funcionam.

---

# Fluxo completo

```text
movimento jogador
   ↓
camera.target atualiza
   ↓
BeginMode2D()
   ↓
mundo desenhado
   ↓
camera move visão
   ↓
EndMode2D()
   ↓
HUD desenhada fixa
```

---

# Conceitos profissionais aprendidos

| Conceito | Foi usado |
|---|---|
| Camera2D | ✔ |
| Zoom | ✔ |
| Rotação | ✔ |
| Offset | ✔ |
| Target | ✔ |
| BeginMode2D | ✔ |
| Mundo grande | ✔ |
| Scrolling | ✔ |
| Coordenadas do mundo | ✔ |

---

# O que você aprende de verdade

voce entende:

```text
a câmera NÃO move o jogador
```

Ela move:

```text
a visão do mundo
```

Isso é MUITO importante.

---

# Curiosidade MUITO importante

Quase todos os jogos usam:
- câmera
- scrolling
- zoom
- viewport

Inclusive:
- Mario
- Terraria
- GTA
- Hollow Knight
- Zelda

---

# Resultado esperado

Você verá:

✅ câmera seguindo jogador  
✅ zoom com mouse  
✅ rotação da câmera  
✅ mundo gigante  
✅ grid infinito  
✅ HUD fixa  
✅ sensação de mapa real  

---

# Atividade da Aula

## Exercício 1

Aumente tamanho do mundo:

```c
-10000 até 10000
```

---

## Exercício 2

Aumente zoom máximo:

```c
camera.zoom > 5.0f
```

---

## Exercício 3

Faça câmera mais suave.

Dica:

```c
camera.target.x +=
(jogador.x - camera.target.x) * 0.1f;
```

---

## Exercício 4

Adicione mais objetos no mapa.

---

# Desafio Extra

Crie:

```text
mini mapa
```

---

# Super Desafio

Transforme isso em:

- side scrolling
- mundo aberto
- jogo top-down
- sandbox
- survival game

---

# Próximo passo

Na próxima aula podemos evoluir para:

```text
19 - Tilemap.md
```

onde iremos aprender:

- mapas 2D
- tiles
- blocos
- cenário
- construção de fases
- mundo estilo Mario/Terraria
