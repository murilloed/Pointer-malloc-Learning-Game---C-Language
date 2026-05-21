# 30 - Shader Programming

# Criando Shaders em Raylib (C)

# Objetivo da Aula

Nesta aula iremos aprender a criar:

```text
Shaders
```

Agora o projeto começará a usar:

- programação de GPU
- efeitos gráficos modernos
- fragment shaders
- vertex shaders
- iluminação
- pós-processamento
- renderização moderna

Isso é a base de:
- gráficos modernos
- engines AAA
- efeitos visuais
- pipelines gráficos
- renderização profissional

---

# O que iremos aprender

Nesta aula vamos estudar:

- shaders
- GPU programming
- GLSL
- fragment shader
- vertex shader
- uniforms
- render pipeline
- efeitos gráficos
- programação gráfica moderna

---

# O que é Shader?

Shader é:

```text
um programa executado pela GPU
```

---

# O mais importante

Shaders NÃO rodam na CPU.

Eles rodam:

```text
diretamente na placa de vídeo
```

---

# O que shaders fazem?

Shaders controlam:

- cores
- iluminação
- sombras
- partículas
- água
- fogo
- pós-processamento
- materiais

---

# Jogos modernos usam shaders o tempo todo

| Jogo | Shaders |
|---|---|
| Minecraft RTX | ✔ |
| Fortnite | ✔ |
| Cyberpunk | ✔ |
| GTA V | ✔ |
| Terraria | ✔ |

---

# Pipeline Gráfico Moderno

```text
CPU
↓
Raylib
↓
OpenGL
↓
Vertex Shader
↓
Fragment Shader
↓
GPU
↓
Monitor
```

---

# Tipos principais de shader

| Shader | Função |
|---|---|
| Vertex Shader | processa vértices |
| Fragment Shader | processa pixels |

---

# O que é Vertex Shader?

Vertex Shader controla:
- posição
- rotação
- transformação
- geometria

---

# O que é Fragment Shader?

Fragment Shader controla:
- cor dos pixels
- brilho
- efeitos
- iluminação

---

# Estrutura do Projeto

```text
shader_project/
│
├── assets/
│   └── shaders/
│       ├── vertex.glsl
│       └── fragment.glsl
│
├── src/
│   └── main.c
```

---

# Código Completo

# vertex.glsl

```glsl
#version 330

// =========================================
// INPUTS
// =========================================

in vec3 vertexPosition;

in vec2 vertexTexCoord;

in vec4 vertexColor;

// =========================================
// OUTPUTS
// =========================================

out vec2 fragTexCoord;

out vec4 fragColor;

// =========================================
// MATRIZES
// =========================================

uniform mat4 mvp;

// =========================================
// MAIN
// =========================================

void main()
{
    // Passa textura
    fragTexCoord = vertexTexCoord;

    // Passa cor
    fragColor = vertexColor;

    // Calcula posição final
    gl_Position =
        mvp *
        vec4(vertexPosition, 1.0);
}
```

---

# fragment.glsl

```glsl
#version 330

// =========================================
// INPUTS
// =========================================

in vec2 fragTexCoord;

in vec4 fragColor;

// =========================================
// OUTPUT
// =========================================

out vec4 finalColor;

// =========================================
// TEXTURA
// =========================================

uniform sampler2D texture0;

// =========================================
// TEMPO
// =========================================

uniform float time;

// =========================================
// MAIN
// =========================================

void main()
{
    // Cor da textura
    vec4 texel =
        texture(texture0, fragTexCoord);

    // Efeito pulsante
    float glow =
        sin(time * 2.0) * 0.5 + 0.5;

    // Cor final
    finalColor =
        texel *
        vec4(
            glow,
            0.5,
            1.0,
            1.0
        ) *
        fragColor;
}
```

---

# main.c

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
    InitWindow(
        1280,
        720,
        "Shader Programming"
    );

    // FPS
    SetTargetFPS(60);

    // =========================================
    // LOAD TEXTURE
    // =========================================

    Texture2D texture =
        LoadTexture(
            "assets/player.png"
        );

    // =========================================
    // LOAD SHADER
    // =========================================

    Shader shader =
        LoadShader(
            "assets/shaders/vertex.glsl",
            "assets/shaders/fragment.glsl"
        );

    // =========================================
    // UNIFORM LOCATION
    // =========================================

    int timeLoc =
        GetShaderLocation(
            shader,
            "time"
        );

    // =========================================
    // PLAYER
    // =========================================

    Vector2 position =
        {500, 250};

    // =========================================
    // LOOP PRINCIPAL
    // =========================================

    while (!WindowShouldClose())
    {
        // =========================================
        // TEMPO
        // =========================================

        float time =
            GetTime();

        // =========================================
        // ENVIA UNIFORM
        // =========================================

        SetShaderValue(
            shader,
            timeLoc,
            &time,
            SHADER_UNIFORM_FLOAT
        );

        // =========================================
        // DRAW
        // =========================================

        BeginDrawing();

        ClearBackground(RAYWHITE);

        // =========================================
        // BEGIN SHADER
        // =========================================

        BeginShaderMode(shader);

        // =========================================
        // DESENHA TEXTURA
        // =========================================

        DrawTexture(
            texture,
            position.x,
            position.y,
            WHITE
        );

        // =========================================
        // END SHADER
        // =========================================

        EndShaderMode();

        // =========================================
        // HUD
        // =========================================

        DrawRectangle(
            0,
            0,
            1280,
            140,
            Fade(LIGHTGRAY, 0.9f)
        );

        DrawText(
            "Shader Programming",
            20,
            20,
            40,
            DARKBLUE
        );

        DrawText(
            "GPU Programming com GLSL",
            20,
            70,
            20,
            DARKGRAY
        );

        DrawText(
            "Shader ativo na textura",
            20,
            100,
            20,
            MAROON
        );

        DrawText(
            "Fragment Shader criando glow",
            700,
            100,
            20,
            BLUE
        );

        EndDrawing();
    }

    // =========================================
    // UNLOAD
    // =========================================

    UnloadShader(shader);

    UnloadTexture(texture);

    CloseWindow();

    return 0;
}
```

---

# Explicação COMPLETA da Arquitetura

# 1. O que é um shader?

Shader é:

```text
um programa executado na GPU
```

---

# O mais importante

Enquanto C roda:
- na CPU

GLSL roda:
- na GPU

---

# Isso permite

- paralelismo massivo
- gráficos modernos
- efeitos avançados

---

# 2. GLSL

GLSL significa:

```text
OpenGL Shading Language
```

---

# Ela é a linguagem dos shaders

Parecida com:
- C

---

# 3. Vertex Shader

```glsl
vertex.glsl
```

Processa:
- vértices

---

# Ele controla

- posição
- rotação
- escala
- projeção

---

# 4. gl_Position

```glsl
gl_Position
```

Define:
- posição final do vértice na tela

---

# Isso é MUITO importante

Todo objeto renderizado passa por isso.

---

# 5. MVP Matrix

```glsl
uniform mat4 mvp;
```

Representa:

```text
Model
View
Projection
```

---

# Isso transforma objetos

do:
- espaço do mundo
- para tela

---

# 6. Fragment Shader

```glsl
fragment.glsl
```

Processa:
- pixels

---

# Cada pixel executa shader

Isso significa:
- MILHÕES de execuções paralelas

---

# GPU é extremamente paralela

Muito importante.

---

# 7. texture()

```glsl
texture(texture0, fragTexCoord)
```

Lê:
- cor da textura

---

# 8. Uniform

```glsl
uniform float time;
```

Uniform:
- variável enviada pela CPU

---

# CPU → GPU

```text
C envia dados
↓
shader usa dados
```

---

# 9. GetShaderLocation()

```c
GetShaderLocation()
```

Encontra:
- variável uniform no shader

---

# 10. SetShaderValue()

```c
SetShaderValue()
```

Envia:
- dados da CPU
- para GPU

---

# Isso é comunicação CPU/GPU

Muito importante.

---

# 11. Glow

```glsl
sin(time * 2.0)
```

Cria:
- oscilação
- efeito pulsante

---

# Isso gera animação procedural

Sem sprites.

---

# 12. BeginShaderMode()

```c
BeginShaderMode(shader);
```

Ativa:
- shader na GPU

---

# Tudo desenhado depois

usa:
- shader personalizado

---

# 13. EndShaderMode()

```c
EndShaderMode();
```

Desativa:
- shader

---

# 14. Pipeline gráfico

Fluxo real:

```text
CPU
↓
Raylib
↓
OpenGL
↓
Vertex Shader
↓
Rasterização
↓
Fragment Shader
↓
Framebuffer
↓
Monitor
```

---

# 15. Rasterização

GPU converte:
- triângulos
- em pixels

---

# 16. Shaders modernos

Hoje shaders fazem:
- iluminação
- ray tracing
- água
- fogo
- pós-processamento
- sombras
- partículas

---

# 17. GPU Programming

Agora você está literalmente:

```text
programando GPU
```

---

# Isso é MUITO avançado

É a base de:
- engines AAA
- renderização moderna
- gráficos profissionais

---

# 18. Fluxo completo

```text
CPU envia dados
↓
shader recebe uniforms
↓
GPU processa vértices
↓
GPU processa pixels
↓
imagem renderizada
```

---

# Visualização mental

```text
TEXTURA
↓
FRAGMENT SHADER
↓
EFEITO GLOW
↓
GPU
↓
TELA
```

---

# Conceitos profissionais aprendidos

| Conceito | Foi usado |
|---|---|
| Shader | ✔ |
| GLSL | ✔ |
| GPU Programming | ✔ |
| Fragment Shader | ✔ |
| Vertex Shader | ✔ |
| Uniforms | ✔ |
| Render Pipeline | ✔ |
| OpenGL | ✔ |

---

# O que você aprende de verdade

# você entende:

```text
gráficos modernos são programas rodando na GPU
```

E entende:
- shaders
- GPU programming
- render pipeline
- comunicação CPU/GPU
- efeitos gráficos modernos
- arquitetura gráfica profissional

---

# Curiosidade MUITO importante

Engines modernas usam:
- milhares de shaders
- pipelines gráficos complexos
- compute shaders
- ray tracing
- physically based rendering (PBR)

Inclusive:
- Unreal Engine 5
- Unity HDRP
- Frostbite
- id Tech

---

# Resultado esperado

Você verá:

✅ shader funcionando  
✅ glow animado  
✅ GPU processando pixels  
✅ efeito visual moderno  
✅ comunicação CPU/GPU  
✅ renderização profissional básica  

---

# Atividade da Aula

## Exercício 1

Troque:
- cores do shader

---

## Exercício 2

Crie:
- efeito de fogo

---

## Exercício 3

Crie:
- efeito de água

---

## Exercício 4

Adicione:
- iluminação dinâmica

---

# Desafio Extra

Crie:
- shader CRT retrô

---

# Super Desafio

Transforme isso em:
- pipeline PBR
- pós-processamento
- bloom
- SSAO
- raymarching
- mini renderer moderno

---

# Próximo passo

Na próxima aula podemos evoluir para:

```text
31 - Procedural Generation.md
```

onde iremos aprender:

- geração procedural
- noise
- Perlin Noise
- mapas automáticos
- mundos infinitos
- procedural worlds
