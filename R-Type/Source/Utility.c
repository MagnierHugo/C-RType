#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../Include/Structs.h"
#include "../Include/HandleSDL.h"

int RdmInt(int min, int max, bool nonZero)
{
    int rdm;
    do
    {
        rdm = min + rand() % (max - min + 1);
    } while (nonZero && rdm == 0);

    return rdm;
}

void Swap(void* element1, void* element2)
{
    void* tempElement = element1;
    element1 = element2;
    element2 = tempElement;
}

void CheckPointer(void* pointer, char* errorMessage, SDL sdl)
{
    if (pointer == NULL) {
        ErrorHandling(errorMessage, sdl);
    }
}

//void CheckPointer(void* pointer)
//{
//    if (pointer) free(pointer);
//}