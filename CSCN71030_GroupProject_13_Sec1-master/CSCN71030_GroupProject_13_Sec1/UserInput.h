#pragma once

#define MAX_STRING 32

#include <string.h>

char getCharInput(char);

void getString(char*, int);

int getInteger(int, int);

void getDigitLimitedString(char*, int);

double getDouble(double, double);

void removeNewLine(char*);