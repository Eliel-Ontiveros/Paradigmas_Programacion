#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <raylib.h>

#define TAMANO_CUADRO 64
#define FILAS 15
#define COLUMNAS 10

typedef enum GameScreen { TITLE, GAME, END, RANKING } GameScreen;
static GameScreen currentScreen = TITLE;
static int selectedOption = 0; 
static short comidaPos[2], serpientePos[2], direccionSerpiente = 0, perdido = 0, enfriamientoJuego = 0, tiempoParteSerpiente[FILAS][COLUMNAS], poderCreacion = 2;
static int framesCounter = 0; 
static int score = 0;

#define MAX_RANKINGS 10
static int rankings[MAX_RANKINGS] = { 0 };
const char* rankingsFilePath = "C:/raylib/Proyectos/src/Snake_Paradigmas/Docs/rankings.txt"; 

void updateRanking(int newScore) {
    for (int i = 0; i < MAX_RANKINGS; i++) {
        if (newScore > rankings[i]) {
            for (int j = MAX_RANKINGS - 1; j > i; j--) {
                rankings[j] = rankings[j - 1];
            }
            rankings[i] = newScore;
            break;
        }
    }
}


void loadRanking() {
    FILE* file = fopen(rankingsFilePath, "r");
    if (file) {
        for (int i = 0; i < MAX_RANKINGS; i++) {
            if (fscanf(file, "%d", &rankings[i]) != 1) {
                rankings[i] = 0;
            }
        }
        fclose(file);
    }
}

void saveRanking() {
    FILE* file = fopen(rankingsFilePath, "w");
    if (file) {
        for (int i = 0; i < MAX_RANKINGS; i++) {
            fprintf(file, "%d\n", rankings[i]);
        }
        fclose(file);
    }
}

int main()
{
    srand(time(0));
    InitWindow(FILAS * TAMANO_CUADRO, COLUMNAS * TAMANO_CUADRO, "Serpiente");
    InitAudioDevice();
    SetTargetFPS(60);

    Texture2D backgroundImage = LoadTexture("C:/raylib/Proyectos/src/Snake_Paradigmas/IMG/Menu_img.png");
    Texture2D loseImage = LoadTexture("C:/raylib/Proyectos/src/Snake_Paradigmas/IMG/Lose_img.png");
    Texture2D rankingImage = LoadTexture("C:/raylib/Proyectos/src/Snake_Paradigmas/IMG/Ranking_img.png");

    Texture2D snakeUp = LoadTexture("C:/raylib/Proyectos/src/Snake_Paradigmas/IMG/Graphics/Kirby_up.png");
    Texture2D snakeDown = LoadTexture("C:/raylib/Proyectos/src/Snake_Paradigmas/IMG/Graphics/Kirby_down.png");
    Texture2D snakeLeft = LoadTexture("C:/raylib/Proyectos/src/Snake_Paradigmas/IMG/Graphics/Kirby_left.png");
    Texture2D snakeRight = LoadTexture("C:/raylib/Proyectos/src/Snake_Paradigmas/IMG/Graphics/Kirby_right.png");

    Texture2D fruit = LoadTexture("C:/raylib/Proyectos/src/Snake_Paradigmas/IMG/Graphics/Cake.png");

    Texture2D body = LoadTexture("C:/raylib/Proyectos/src/Snake_Paradigmas/IMG/Graphics/star.png");

    Texture2D gameBackground = LoadTexture("C:/raylib/Proyectos/src/Snake_Paradigmas/IMG/Graphics/Background.png");

    const char* backgroundMusicPath = "C:/raylib/Proyectos/src/Snake_Paradigmas/FX/Back.wav";
    const char* eatSoundPath = "C:/raylib/Proyectos/src/Snake_Paradigmas/FX/Yoshi.mp3";
    const char* loseSound = "C:/raylib/Proyectos/src/Snake_Paradigmas/FX/Lose_Sound.mp3";

    Music music = LoadMusicStream(backgroundMusicPath);
    Sound eatSound = LoadSound(eatSoundPath);
    Sound losingSound = LoadSound(loseSound);

    SetMusicVolume(music, 0.10f);
    SetSoundVolume(eatSound, 0.5f);

    if (!music.stream.buffer) {
        printf("Error al cargar %s\n", backgroundMusicPath);
    }
    if (!eatSound.stream.buffer) {
        printf("Error al cargar %s\n", eatSoundPath);
    }

    if (!IsAudioDeviceReady()) {
        printf("Error al inicializar el dispositivo de audio.\n");
        return -1;
    }

    PlayMusicStream(music);

    loadRanking();

    comidaPos[0] = rand() % FILAS;
    comidaPos[1] = rand() % COLUMNAS;
    serpientePos[0] = FILAS / 2;
    serpientePos[1] = COLUMNAS / 2;
    memset(tiempoParteSerpiente, 0, sizeof(tiempoParteSerpiente));

    while (!WindowShouldClose())
    {
        UpdateMusicStream(music);

        BeginDrawing();
        ClearBackground(BLACK);

        if (currentScreen == TITLE) {

            PlayMusicStream(music);

            DrawTexture(backgroundImage, 0, 0, WHITE);

            int iniciarPosY = GetScreenHeight() / 2 - 80;
            int rankingPosY = GetScreenHeight() / 2;
            int cerrarPosY = GetScreenHeight() / 2 + 80;

            if (selectedOption == 0) {
                DrawRectangle(GetScreenWidth() / 2 - MeasureText("Iniciar", 40) / 2 - 10, iniciarPosY - 10, MeasureText("Iniciar", 40) + 20, 60, WHITE);
            }
            else if (selectedOption == 1) {
                DrawRectangle(GetScreenWidth() / 2 - MeasureText("Ranking", 40) / 2 - 10, rankingPosY - 10, MeasureText("Ranking", 40) + 20, 60, WHITE);
            }
            else {
                DrawRectangle(GetScreenWidth() / 2 - MeasureText("Cerrar juego", 40) / 2 - 10, cerrarPosY - 10, MeasureText("Cerrar juego", 40) + 20, 60, WHITE);
            }

            DrawText("Iniciar", GetScreenWidth() / 2 - MeasureText("Iniciar", 40) / 2, iniciarPosY, 40, selectedOption == 0 ? BLACK : WHITE);
            DrawText("Ranking", GetScreenWidth() / 2 - MeasureText("Ranking", 40) / 2, rankingPosY, 40, selectedOption == 1 ? BLACK : WHITE);
            DrawText("Cerrar juego", GetScreenWidth() / 2 - MeasureText("Cerrar juego", 40) / 2, cerrarPosY, 40, selectedOption == 2 ? BLACK : WHITE);

            if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_UP)) {
                selectedOption = (selectedOption + 1) % 3;
            }

            if (IsKeyPressed(KEY_SPACE)) {
                if (selectedOption == 0) {
                    perdido = 0;
                    poderCreacion = 2;
                    score = 0;
                    comidaPos[0] = rand() % FILAS;
                    comidaPos[1] = rand() % COLUMNAS;
                    serpientePos[0] = FILAS / 2;
                    serpientePos[1] = COLUMNAS / 2;
                    memset(tiempoParteSerpiente, 0, sizeof(tiempoParteSerpiente));
                    currentScreen = GAME;
                }
                else if (selectedOption == 1) {
                    currentScreen = RANKING;
                }
                else {
                    break;
                }
            }
        }

        else if (currentScreen == GAME) {
            framesCounter++;
            if (framesCounter >= 10) {
                serpientePos[0] += direccionSerpiente == 0 ? 1 : (direccionSerpiente == 1 ? -1 : 0);
                serpientePos[1] += direccionSerpiente == 2 ? 1 : (direccionSerpiente == 3 ? -1 : 0);

                if (serpientePos[0] < 0 || serpientePos[1] < 0 || serpientePos[0] >= FILAS || serpientePos[1] >= COLUMNAS || tiempoParteSerpiente[serpientePos[0]][serpientePos[1]] > 1) {
                    PauseMusicStream(music);
                    updateRanking(score); 
                    perdido = 1;
                    saveRanking();
                    PlaySound(losingSound);
                    currentScreen = END;
                }

                if (!perdido) {
                    tiempoParteSerpiente[serpientePos[0]][serpientePos[1]] = poderCreacion;
                }

                for (short i = 0; i < FILAS; i++) {
                    for (short j = 0; j < COLUMNAS; j++) {
                        if (tiempoParteSerpiente[i][j] > 0) {
                            tiempoParteSerpiente[i][j]--;
                        }
                    }
                }
                framesCounter = 0; 
            }

            enfriamientoJuego++;

            direccionSerpiente = IsKeyDown(KEY_LEFT) ? 1 : (IsKeyDown(KEY_RIGHT) ? 0 : (IsKeyDown(KEY_UP) ? 3 : (IsKeyDown(KEY_DOWN) ? 2 : direccionSerpiente)));

            if (serpientePos[0] == comidaPos[0] && serpientePos[1] == comidaPos[1])
            {
                do
                {
                    comidaPos[0] = rand() % FILAS;
                    comidaPos[1] = rand() % COLUMNAS;
                } while (tiempoParteSerpiente[comidaPos[0]][comidaPos[1]] > 0);

                poderCreacion++;
                score += 10;
                PlaySound(eatSound);
            }

            if (!perdido)
            {
                DrawTexture(gameBackground, 0, 0, WHITE);

                DrawTexture(fruit, comidaPos[0] * TAMANO_CUADRO, comidaPos[1] * TAMANO_CUADRO, WHITE);

                for (short i = 0; i < FILAS; i++)
                {
                    for (short j = 0; j < COLUMNAS; j++)
                    {
                        if (tiempoParteSerpiente[i][j] > 0)
                        {
                            if (i == serpientePos[0] && j == serpientePos[1]) continue; 
                            DrawTexture(body, i * TAMANO_CUADRO, j * TAMANO_CUADRO, WHITE);
                        }
                    }
                }

                Texture2D currentTexture;
                switch (direccionSerpiente) {
                case 0: currentTexture = snakeRight; break;
                case 1: currentTexture = snakeLeft; break;
                case 2: currentTexture = snakeDown; break;
                case 3: currentTexture = snakeUp; break;
                }
                DrawTexture(currentTexture, serpientePos[0] * TAMANO_CUADRO, serpientePos[1] * TAMANO_CUADRO, WHITE);
            }
        }

        else if (currentScreen == END) {
            
            ClearBackground(BLACK);
            DrawTexture(loseImage, 0, 0, WHITE);
            DrawText(TextFormat("Puntaje: %d", score),GetScreenWidth() / 2 - MeasureText(TextFormat("Puntaje: %d", score), 40) / 2,GetScreenHeight() / 2 + GetScreenHeight() / 6 - 40,40,RED);

            if (IsKeyPressed(KEY_SPACE)) {
                currentScreen = TITLE;
            }
        }

        else if (currentScreen == RANKING) {
            ClearBackground(BLACK);
            DrawTexture(rankingImage, 0, 0, WHITE); 
            DrawText(
                "Ranking",
                GetScreenWidth() / 2 - MeasureText("Ranking", 40) / 2,
                50 + GetScreenHeight() / 10,
                40,
                WHITE
            );

            for (int i = 0; i < MAX_RANKINGS; i++) {
                DrawText(
                    TextFormat("%d. %d", i + 1, rankings[i]),
                    GetScreenWidth() / 2 - MeasureText(TextFormat("%d. %d", i + 1, rankings[i]), 30) / 2,
                    100 + GetScreenHeight() / 10 + i * 40,
                    30,
                    WHITE
                );
            }

            DrawText("Presiona ESPACIO para regresar al menu", GetScreenWidth() / 2 - MeasureText("Presiona ESPACIO para regresar al menu", 20) / 2, GetScreenHeight() - 40, 20, WHITE);
            if (IsKeyPressed(KEY_SPACE)) {
                currentScreen = TITLE;
            }
        }

        EndDrawing();
    }

    UnloadMusicStream(music);
    UnloadSound(eatSound);
    CloseAudioDevice();
    UnloadTexture(backgroundImage);
    UnloadTexture(loseImage);
    UnloadTexture(snakeUp);
    UnloadTexture(snakeDown);
    UnloadTexture(snakeLeft);
    UnloadTexture(snakeRight);
    UnloadTexture(fruit);
    UnloadTexture(body);
    UnloadTexture(gameBackground);

    CloseWindow();

    return 0;
}