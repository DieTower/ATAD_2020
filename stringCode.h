#pragma once

typedef struct stringCode{
    char code[256];
} StringCode;

StringCode stringCodeCreate(char *str);

void stringCodePrint(StringCode);