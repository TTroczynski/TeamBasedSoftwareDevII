#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "Manager.h"
#include "Franchisee.h"
#include "Corporate.h"

#define WORK_MAX_CHAR 'f'
#define MANA_MAX_CHAR 'm'
#define FRAN_MAX_CHAR 'n'
#define CORP_MAX_CHAR 'f'

#define LOG_MAX_CHAR 'd'

PNODE logIn(PNODE, int);

void logOut(PNODE);

bool punchIn(PNODE, int);

bool punchOut(PNODE, int);

int getLogInID(void);

void displayMenu(int);

char displayWorkerMenu(char);

char displayManagerMenu(char);

char displayFranchiseeMenu(char);

char displayCorporateMenu(char);

void displayLogInPrompt(void);

void performWorkerChoice(PNODE, PNODE, char);

void performManagerChoice(PNODE, PNODE, char);

void performFranchiseeChoice(PNODE, char);

void performCorporateChoice(PNODE, PFRANCHISEE, char);

void exitInterface(PNODE);