#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

void saveGameData(int data) {
    FILE* file = fopen("saved_game.dat", "wb");
    if (file != NULL) {
        fwrite(&data, sizeof(int), 1, file);
        fclose(file);
        printf("Game data saved successfully.\n");
    }
    else {
        printf("Failed to save game data.\n");
    }
}

int loadGameData() {
    int score;
    FILE* saveFile = fopen("save.dat", "rb"); // read binary
    if (saveFile != NULL) {
        fread(&score, sizeof(int), 1, saveFile);
        fclose(saveFile);
        printf("Game data loaded successfully.\n");
        return score;
    }
    else {
        printf("Failed to load game data. Initializing with 0 instead.\n");
        return 0;
    }
}
