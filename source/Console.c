#include "header/Console.h"


void consolePrintInformation(const char* information){
    printf("Information : %s\n", information);
}

void consolePrintSection(const char* section){
    printf("=== %s ===\n", section);
}

void consolePrintError(const char* error){
    printf("ERROR : %s\n", error);
}