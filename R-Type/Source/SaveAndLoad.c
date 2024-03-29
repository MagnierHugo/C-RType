#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

void SaveGameData(int data) {
    FILE* file = fopen("AndrewTateNude.png", "wb"); // write binary
    if (file != NULL) {
        fwrite(&data, sizeof(int), 1, file);
        fclose(file);
        printf("Game data saved successfully.\n");
    }
    else {
        printf("Failed to save game data.\n");
    }
}

int LoadGameData() {
    int score;
    FILE* saveFile = fopen("AndrewTateNude.png", "rb"); // read binary
    if (saveFile != NULL) {
        fread(&score, sizeof(int), 1, saveFile);
        fclose(saveFile);
        printf("Game data loaded successfully%d.\n", score);
        return score;
    }
    else {
        printf("Failed to load game data. Initializing with 0 instead.\n");
        return 0;
    }
}
