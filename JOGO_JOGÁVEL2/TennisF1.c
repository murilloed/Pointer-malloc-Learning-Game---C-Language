#include "raylib.h"
#include <stdbool.h>
#include <stdlib.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

// Estruturas

typedef struct {
  float x, y;
  float speedX, speedY;
  float radius;
  Color color;
} Ball;

typedef struct {
  float x, y;
  float width, height;
  float speed;
  Color color;
} Paddle;

typedef struct {
  Ball *ball;
  Paddle *paddle;
  int score;
  bool gameOver;
  bool isCrazyMode;
  bool gameStarted;
} GameState;

// Funções de Alocação e Desalocação
GameState *InitGame() {
  GameState *game = (GameState *)malloc(sizeof(GameState));

  game->ball = (Ball *)malloc(sizeof(Ball));
  game->ball->radius = 10.0f;
  game->ball->x = SCREEN_WIDTH / 2.0f;
  game->ball->y = SCREEN_HEIGHT / 2.0f;
  game->ball->speedX = 5.0f;
  game->ball->speedY = -5.0f;
  game->ball->color = RED;

  game->paddle = (Paddle *)malloc(sizeof(Paddle));
  game->paddle->width = 120.0f;
  game->paddle->height = 15.0f;
  game->paddle->x = SCREEN_WIDTH / 2.0f - game->paddle->width / 2.0f;
  game->paddle->y = SCREEN_HEIGHT - 40.0f;
  game->paddle->speed = 8.0f;
  game->paddle->color = DARKBLUE;

  game->score = 0;
  game->gameOver = false;
  game->gameStarted = false;
  game->isCrazyMode = false;

  return game;
}

void FreeGame(GameState *game) {
  if (game != NULL) {
    if (game->ball != NULL)
      free(game->ball);
    if (game->paddle != NULL)
      free(game->paddle);
    free(game); // Libera o struct principal depois dos structs internos
  }
}

int main() {
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Tennis For One - Aprendendo Malloc");
  SetTargetFPS(60);

  // Inicializando e carregando os áudios requeridos
  InitAudioDevice();
  Sound sndPong = LoadSound("Assets/pong.mp3");
  Sound sndGameOver = LoadSound("Assets/gameover.mp3");
  Music musCrazyTrain = LoadMusicStream("Assets/Crazy_Train.mp3");

  // Aloca a estrutura inteira do jogo na inicialização
  GameState *game = InitGame();

  while (!WindowShouldClose()) {
    // Atualiza a música continuamente se o modo estiver ativado
    if (game->isCrazyMode) {
      UpdateMusicStream(musCrazyTrain);
    }

    if (!game->gameStarted) {
      if (IsKeyPressed(KEY_ENTER)) {
        game->gameStarted = true;
      }
    } else if (game->gameOver) {
      if (IsKeyPressed(KEY_ENTER)) {

        FreeGame(game);
        game = InitGame();
        StopMusicStream(musCrazyTrain);
      }
    } else {
      if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) {
        game->paddle->x -= game->paddle->speed;
      }
      if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) {
        game->paddle->x += game->paddle->speed;
      }

      if (game->paddle->x < 0)
        game->paddle->x = 0;
      if (game->paddle->x + game->paddle->width > SCREEN_WIDTH)
        game->paddle->x = SCREEN_WIDTH - game->paddle->width;

      game->ball->x += game->ball->speedX;
      game->ball->y += game->ball->speedY;

      if ((game->ball->x - game->ball->radius <= 0 && game->ball->speedX < 0) ||
          (game->ball->x + game->ball->radius >= SCREEN_WIDTH && game->ball->speedX > 0)) {
        game->ball->speedX *= -1.0f;
      }

      if (game->ball->y - game->ball->radius <= 0 && game->ball->speedY < 0) {
        game->ball->speedY *= -1.0f;
      }

      Rectangle paddleRect = {game->paddle->x, game->paddle->y,
                              game->paddle->width, game->paddle->height};
      Vector2 ballCenter = {game->ball->x, game->ball->y};

      if (CheckCollisionCircleRec(ballCenter, game->ball->radius, paddleRect)) {
        if (game->ball->speedY > 0) {
          game->ball->speedY *= -1.0f;

          float hitPoint =
              (game->ball->x - (game->paddle->x + game->paddle->width / 2)) /
              (game->paddle->width / 2);
          game->ball->speedX = hitPoint * 7.0f;

          game->ball->speedY -= 0.5f;

          game->score++;
          PlaySound(sndPong);

          if (game->score >= 10 && !game->isCrazyMode) {
            game->isCrazyMode = true;
            PlayMusicStream(musCrazyTrain);
            game->ball->color = PURPLE;
            game->paddle->color = RED;
          }
        }
      }

      if (game->ball->y >= SCREEN_HEIGHT) {
        game->gameOver = true;
        PlaySound(sndGameOver);
        StopMusicStream(musCrazyTrain);
      }
    }

    // DESENHO
    BeginDrawing();

    if (game->isCrazyMode) {
      ClearBackground(ColorFromHSV((float)GetTime() * 150, 0.2f, 0.9f));
    } else {
      ClearBackground(RAYWHITE);
    }

    if (!game->gameStarted) {
      DrawText("TENNIS FOR ONE",
               SCREEN_WIDTH / 2 - MeasureText("TENNIS FOR ONE", 40) / 2,
               SCREEN_HEIGHT / 2 - 50, 40, DARKGRAY);
      DrawText("Pressione ENTER para Comecar",
               SCREEN_WIDTH / 2 -
                   MeasureText("Pressione ENTER para Comecar", 20) / 2,
               SCREEN_HEIGHT / 2 + 10, 20, GRAY);
      DrawText("Controles: A / D ou Setas",
               SCREEN_WIDTH / 2 -
                   MeasureText("Controles: A / D ou Setas", 20) / 2,
               SCREEN_HEIGHT / 2 + 40, 20, GRAY);
    } else if (game->gameOver) {
      DrawText("GAME OVER!",
               SCREEN_WIDTH / 2 - MeasureText("GAME OVER!", 40) / 2,
               SCREEN_HEIGHT / 2 - 40, 40, RED);
      DrawText(
          TextFormat("Pontuacao Final: %d", game->score),
          SCREEN_WIDTH / 2 -
              MeasureText(TextFormat("Pontuacao Final: %d", game->score), 20) /
                  2,
          SCREEN_HEIGHT / 2 + 10, 20, DARKGRAY);
      DrawText("Pressione ENTER para Reiniciar",
               SCREEN_WIDTH / 2 -
                   MeasureText("Pressione ENTER para Reiniciar", 20) / 2,
               SCREEN_HEIGHT / 2 + 40, 20, GRAY);
    } else {
      DrawRectangleRec((Rectangle){game->paddle->x, game->paddle->y,
                                   game->paddle->width, game->paddle->height},
                       game->paddle->color);
      DrawCircleV((Vector2){game->ball->x, game->ball->y}, game->ball->radius,
                  game->ball->color);

      DrawText(TextFormat("Score: %d", game->score), 20, 20, 30,
               game->isCrazyMode ? BLACK : DARKGRAY);

      if (game->isCrazyMode) {
        DrawText("CRAZY TRAIN MODE!",
                 SCREEN_WIDTH / 2 - MeasureText("CRAZY TRAIN MODE!", 30) / 2,
                 20, 30, PURPLE);
      }
    }

    EndDrawing();
  }

  FreeGame(game);

  UnloadSound(sndPong);
  UnloadSound(sndGameOver);
  UnloadMusicStream(musCrazyTrain);
  CloseAudioDevice();

  CloseWindow();

  return 0;
}
