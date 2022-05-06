#pragma once
#include "Corporate.h"
#include <stdbool.h>

#define TYPE_EMPLOYEE 10

void removeBadChars(char*);
bool saveToDisk(NODE, FRANCHISEE, CORPORATE, char*);
bool loadFromDisk(NODE*, FRANCHISEE* franchisee, CORPORATE* corporate, char*);