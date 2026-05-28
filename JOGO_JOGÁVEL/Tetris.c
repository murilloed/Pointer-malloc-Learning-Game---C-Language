#include "raylib.h"
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#define BOARD_WIDTH 10
#define BOARD_HEIGHT 20
#define CELL_SIZE 40

#define screenWidth (BOARD_WIDTH * CELL_SIZE + 200)
#define screenHeight (BOARD_HEIGHT * CELL_SIZE)

// Cores das peças
const Color colors[] = {DARKGRAY, SKYBLUE, BLUE,   ORANGE,
                        YELLOW,   GREEN,   PURPLE, RED};

// ESTRUTURAS

typedef struct {
  int size;
  int **shape;
} PieceTemplate;

typedef struct {
  int x, y;
  int size;
  int **shape;
  int colorId;
} Piece;

// Globais
PieceTemplate *templates[7];
int board[BOARD_HEIGHT][BOARD_WIDTH] = {0};
Piece currentPiece;
bool gameOver = false;
bool gameStarted = false;
float fallTimer = 0.0f;
float fallSpeed = 0.5f;
int score = 0;

// Sons e Música
Sound sndGameOver;
Sound sndLineCleared;
Music theme;

// FUNÇÕES DE ALOCAÇÃO E TEMPLATES

PieceTemplate *CreatePieceTemplate(int size, int data[]) {
  PieceTemplate *pt = (PieceTemplate *)malloc(sizeof(PieceTemplate));
  pt->size = size;

  pt->shape = (int **)malloc(size * sizeof(int *));
  for (int i = 0; i < size; i++) {
    pt->shape[i] = (int *)malloc(size * sizeof(int));
    for (int j = 0; j < size; j++) {
      pt->shape[i][j] = data[i * size + j];
    }
  }
  return pt;
}

void InitTemplates() {
  int I_data[] = {0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0};
  templates[0] = CreatePieceTemplate(4, I_data);

  int J_data[] = {2, 0, 0, 2, 2, 2, 0, 0, 0};
  templates[1] = CreatePieceTemplate(3, J_data);

  int L_data[] = {0, 0, 3, 3, 3, 3, 0, 0, 0};
  templates[2] = CreatePieceTemplate(3, L_data);

  int O_data[] = {4, 4, 4, 4};
  templates[3] = CreatePieceTemplate(2, O_data);

  int S_data[] = {0, 5, 5, 5, 5, 0, 0, 0, 0};
  templates[4] = CreatePieceTemplate(3, S_data);

  int T_data[] = {0, 6, 0, 6, 6, 6, 0, 0, 0};
  templates[5] = CreatePieceTemplate(3, T_data);

  int Z_data[] = {7, 7, 0, 0, 7, 7, 0, 0, 0};
  templates[6] = CreatePieceTemplate(3, Z_data);
}

void FreePieceTemplate(PieceTemplate *pt) {
  if (!pt)
    return;
  for (int i = 0; i < pt->size; i++) {
    free(pt->shape[i]);
  }
  free(pt->shape);
  free(pt);
}

void FreeAllTemplates() {
  for (int i = 0; i < 7; i++) {
    FreePieceTemplate(templates[i]);
  }
}

// FUNÇÕES DA PEÇA

Piece SpawnPiece() {
  int type = GetRandomValue(0, 6);
  Piece p;
  p.size = templates[type]->size;
  p.x = BOARD_WIDTH / 2 - p.size / 2;
  p.y = 0;
  p.colorId = type + 1; // 1 a 7

  p.shape = (int **)malloc(p.size * sizeof(int *));
  for (int i = 0; i < p.size; i++) {
    p.shape[i] = (int *)malloc(p.size * sizeof(int));
    for (int j = 0; j < p.size; j++) {
      p.shape[i][j] = templates[type]->shape[i][j];
    }
  }
  return p;
}

void FreePiece(Piece *p) {
  if (p->shape) {
    for (int i = 0; i < p->size; i++) {
      free(p->shape[i]);
    }
    free(p->shape);
    p->shape = NULL;
  }
}

void RotatePiece(Piece *p) {
  int **temp = (int **)malloc(p->size * sizeof(int *));
  for (int i = 0; i < p->size; i++) {
    temp[i] = (int *)malloc(p->size * sizeof(int));
    for (int j = 0; j < p->size; j++) {
      temp[i][j] = p->shape[p->size - 1 - j][i];
    }
  }

  for (int i = 0; i < p->size; i++) {
    for (int j = 0; j < p->size; j++) {
      p->shape[i][j] = temp[i][j];
    }
    free(temp[i]);
  }
  free(temp);
}

// LÓGICA DO JOGO

bool CheckCollision(Piece *p, int offsetX, int offsetY) {
  for (int i = 0; i < p->size; i++) {
    for (int j = 0; j < p->size; j++) {
      if (p->shape[i][j] != 0) {
        int newX = p->x + j + offsetX;
        int newY = p->y + i + offsetY;

        if (newX < 0 || newX >= BOARD_WIDTH || newY >= BOARD_HEIGHT) {
          return true;
        }

        if (newY >= 0 && board[newY][newX] != 0) {
          return true;
        }
      }
    }
  }
  return false;
}

void LockPiece(Piece *p) {
  for (int i = 0; i < p->size; i++) {
    for (int j = 0; j < p->size; j++) {
      if (p->shape[i][j] != 0) {
        int boardY = p->y + i;
        int boardX = p->x + j;
        if (boardY >= 0 && boardY < BOARD_HEIGHT && boardX >= 0 &&
            boardX < BOARD_WIDTH) {
          board[boardY][boardX] = p->colorId;
        }
      }
    }
  }
}

void ClearLines() {
  int linesCleared = 0;
  for (int i = BOARD_HEIGHT - 1; i >= 0; i--) {
    bool lineFull = true;
    for (int j = 0; j < BOARD_WIDTH; j++) {
      if (board[i][j] == 0) {
        lineFull = false;
        break;
      }
    }

    if (lineFull) {
      linesCleared++;
      for (int k = i; k > 0; k--) {
        for (int j = 0; j < BOARD_WIDTH; j++) {
          board[k][j] = board[k - 1][j];
        }
      }
      for (int j = 0; j < BOARD_WIDTH; j++) {
        board[0][j] = 0;
      }
      i++;
    }
  }

  if (linesCleared > 0) {
    score += linesCleared * 100;
    PlaySound(sndLineCleared);
    if (fallSpeed > 0.1f)
      fallSpeed -= 0.02f;
  }
}

void ResetGame() {
  for (int i = 0; i < BOARD_HEIGHT; i++) {
    for (int j = 0; j < BOARD_WIDTH; j++) {
      board[i][j] = 0;
    }
  }
  if (currentPiece.shape != NULL) {
    FreePiece(&currentPiece);
  }
  score = 0;
  fallSpeed = 0.5f;
  currentPiece = SpawnPiece();
  gameOver = false;
}

int main() {
  InitWindow(screenWidth, screenHeight,
             "Tetris - Aprendendo Ponteiros e malloc");
  SetTargetFPS(60);

  InitAudioDevice();
  sndGameOver = LoadSound("assets/Gameover.mp3");
  sndLineCleared = LoadSound("assets/Linecleared.mp3");
  theme = LoadMusicStream("assets/Theme.mp3");
  PlayMusicStream(theme);

  SetRandomSeed((unsigned int)time(NULL));

  InitTemplates();
  currentPiece.shape = NULL;

  while (!WindowShouldClose()) {
    UpdateMusicStream(theme);

    if (!gameStarted) {
      if (IsKeyPressed(KEY_ENTER)) {
        gameStarted = true;
        ResetGame();
      }
    } else if (gameOver) {
      if (IsKeyPressed(KEY_ENTER)) {
        ResetGame();
      }
    } else {
      if (IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A)) {
        if (!CheckCollision(&currentPiece, -1, 0)) {
          currentPiece.x--;
        }
      }
      if (IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D)) {
        if (!CheckCollision(&currentPiece, 1, 0)) {
          currentPiece.x++;
        }
      }
      if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_SPACE)) {
        RotatePiece(&currentPiece);
        if (CheckCollision(&currentPiece, 0, 0)) {
          RotatePiece(&currentPiece);
          RotatePiece(&currentPiece);
          RotatePiece(&currentPiece);
        }
      }

      // Queda mais rápida se segurar S ou SETA PARA BAIXO (Soft Drop)
      bool fastDrop = IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S);
      float currentFallSpeed = fastDrop ? 0.05f : fallSpeed;

      fallTimer += GetFrameTime();
      if (fallTimer >= currentFallSpeed) {
        fallTimer = 0.0f;
        if (!CheckCollision(&currentPiece, 0, 1)) {
          currentPiece.y++;
        } else {
          LockPiece(&currentPiece);
          ClearLines();
          FreePiece(&currentPiece);

          currentPiece = SpawnPiece();

          if (CheckCollision(&currentPiece, 0, 0)) {
            gameOver = true;
            PlaySound(sndGameOver);
          }
        }
      }
    }

    // DESENHO NA TELA
    BeginDrawing();
    ClearBackground(RAYWHITE);

    DrawRectangle(0, 0, BOARD_WIDTH * CELL_SIZE, BOARD_HEIGHT * CELL_SIZE,
                  BLACK);

    for (int i = 0; i < BOARD_HEIGHT; i++) {
      for (int j = 0; j < BOARD_WIDTH; j++) {
        if (board[i][j] != 0) {
          DrawRectangle(j * CELL_SIZE, i * CELL_SIZE, CELL_SIZE, CELL_SIZE,
                        colors[board[i][j]]);
          DrawRectangleLines(j * CELL_SIZE, i * CELL_SIZE, CELL_SIZE, CELL_SIZE,
                             WHITE);
        } else {
          DrawRectangleLines(j * CELL_SIZE, i * CELL_SIZE, CELL_SIZE, CELL_SIZE,
                             DARKGRAY);
        }
      }
    }

    if (gameStarted && !gameOver && currentPiece.shape != NULL) {
      for (int i = 0; i < currentPiece.size; i++) {
        for (int j = 0; j < currentPiece.size; j++) {
          if (currentPiece.shape[i][j] != 0) {
            int px = currentPiece.x + j;
            int py = currentPiece.y + i;
            if (py >= 0) {
              DrawRectangle(px * CELL_SIZE, py * CELL_SIZE, CELL_SIZE,
                            CELL_SIZE, colors[currentPiece.colorId]);
              DrawRectangleLines(px * CELL_SIZE, py * CELL_SIZE, CELL_SIZE,
                                 CELL_SIZE, WHITE);
            }
          }
        }
      }
    }

    // UI E HUD
    DrawText("TETRIS", BOARD_WIDTH * CELL_SIZE + 20, 20, 30, BLACK);
    DrawText(TextFormat("SCORE: %d", score), BOARD_WIDTH * CELL_SIZE + 20, 70,
             20, DARKGRAY);
    DrawText("Controles:", BOARD_WIDTH * CELL_SIZE + 20, 120, 20, DARKGRAY);
    DrawText("A / D: Lados", BOARD_WIDTH * CELL_SIZE + 20, 150, 15, DARKGRAY);
    DrawText("Espaco: Girar", BOARD_WIDTH * CELL_SIZE + 20, 170, 15, DARKGRAY);
    DrawText("S / Baixo: Acelerar", BOARD_WIDTH * CELL_SIZE + 20, 190, 15,
             DARKGRAY);

    if (!gameStarted) {
      DrawRectangle(0, screenHeight / 2 - 40, screenWidth, 80,
                    Fade(BLACK, 0.8f));
      DrawText("Pressione ENTER",
               screenWidth / 2 - MeasureText("Pressione ENTER", 20) / 2,
               screenHeight / 2 - 20, 20, WHITE);
      DrawText("para Comecar",
               screenWidth / 2 - MeasureText("para Comecar", 20) / 2,
               screenHeight / 2 + 5, 20, WHITE);
    } else if (gameOver) {
      DrawRectangle(0, screenHeight / 2 - 40, screenWidth, 80,
                    Fade(BLACK, 0.8f));
      DrawText("GAME OVER!",
               screenWidth / 2 - MeasureText("GAME OVER!", 30) / 2,
               screenHeight / 2 - 20, 30, RED);
      DrawText("ENTER p/ reiniciar",
               screenWidth / 2 - MeasureText("ENTER p/ reiniciar", 20) / 2,
               screenHeight / 2 + 10, 20, WHITE);
    }

    EndDrawing();
  }

  if (currentPiece.shape != NULL) {
    FreePiece(&currentPiece);
  }
  FreeAllTemplates();

  UnloadSound(sndGameOver);
  UnloadSound(sndLineCleared);
  UnloadMusicStream(theme);
  CloseAudioDevice();

  CloseWindow();

  return 0;
}
