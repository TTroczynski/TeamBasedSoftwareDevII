#pragma once

#include "Manager.h"
#include "Employee.h"
#include "Manager.h"
#include <stdbool.h>

#define MAX_DAY 31

typedef struct Franchisee
{
	char fName[NAMEMAX];
	char lName[NAMEMAX];
	char password[DIGITMAX + 2];
	bool exists;
	
}FRANCHISEE, *PFRANCHISEE;

bool compareFranchisees(FRANCHISEE, FRANCHISEE);
PEMPLOYEE makeTestManager(void);
FRANCHISEE createFranchisee(char[], char[], char[], bool);
void setFranchiseeFName(PFRANCHISEE, char[]);
void setFranchiseeLName(PFRANCHISEE, char[]);
void setFranchiseePassword(PFRANCHISEE, char[]);
void setFranchiseeExistance(PFRANCHISEE, bool);
char* getFranchiseeFName(PFRANCHISEE);
char* getFranchiseeLName(PFRANCHISEE);
char* getFranchiseePassword(PFRANCHISEE);
bool getFranchiseeExistance(PFRANCHISEE);
bool addManager(PNODE, PEMPLOYEE);
bool removeManager(PNODE, int);
bool editManager(PNODE, PEMPLOYEE);
bool adjustWage(PNODE, int);
bool adjustSalary(PNODE, int);
void viewLaborCosts(PNODE);
void generateRandomFRN(PFRANCHISEE);