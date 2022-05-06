#pragma once

#include "Employee.h"
#include "Franchisee.h"

#define FRANCHISEE_REVENUE 2355.27
typedef struct Corporate
{
	char fName[NAMEMAX];
	char lName[NAMEMAX];
	char password[NAMEMAX];
}CORPORATE, *PCORPORATE;

CORPORATE createCorporate(char[], char[], char[]);
bool compareCorporates(CORPORATE, CORPORATE);
void setCorporateFName(PCORPORATE, char[]);
void setCorporateLName(PCORPORATE, char[]);
void setCorporatePassword(PCORPORATE, char[]);
char* getCorporateFName(PCORPORATE);
char* getCorporateLName(PCORPORATE);
char* getCorporatePassword(PCORPORATE);
void viewTotalCosts(PNODE);
void displayCurrentFranchisee(PFRANCHISEE);