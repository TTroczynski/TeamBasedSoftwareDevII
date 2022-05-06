#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <stdio.h>

#include "Employee.h"

PEMPLOYEE createTestManager(void);
PEMPLOYEE createTestWorker(void);

bool addEmployee(PNODE, PEMPLOYEE);

bool editEmployee(PNODE, PEMPLOYEE);

bool removeEmployee(PNODE, int);

PEMPLOYEE makeNewWorker(void);

PEMPLOYEE makeNewManager(void);