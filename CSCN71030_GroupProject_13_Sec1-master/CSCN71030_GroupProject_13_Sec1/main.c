#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

#include "FileIO.h"
#include "Interface.h"
#include "UserInput.h"
#define PATH 1
#define MINARGS 2

int main(int argc, char* argv[])
{
	char* path = NULL;

	if (argc != MINARGS) {
		exit(EXIT_FAILURE);
	}
	else {
		path = argv[PATH];
	}

	bool active = true;
	int id, permissions;
	char choice, logInChoice = 'a', menuChoice = 'a';
	char tempPass[9];

	NODE employeeList = { 0 };
	PNODE loggedInEmployee;
	CORPORATE co = { 0 };
	FRANCHISEE* fr = (PFRANCHISEE)malloc(sizeof(FRANCHISEE));
	if (!fr) {
		exit(EXIT_FAILURE);
	}

	memset(fr, 0, sizeof(FRANCHISEE));

	if (!loadFromDisk(&employeeList, fr, &co, path))
	{
		fprintf(stderr, "error reading data from text file.\n");
		exit(EXIT_FAILURE);
	}
	
	if (getFranchiseeExistance(fr) == false)
		generateRandomFRN(fr);

	do {
		printf("Log in as Employee/Manger, Franchisee, or Corporate?\n");
		printf("a) Employee/Manager\n");
		printf("b) Franchisee\n");
		printf("c) Corporate\n");
		printf("d) Exit\n");	
		logInChoice = getCharInput(LOG_MAX_CHAR);


		if (logInChoice == 'a') {		//WORKER / MANAGER

			if (getEmployee(&employeeList))
			{
				displayLogInPrompt();
				id = getInteger(10000000, 99999999);

				loggedInEmployee = logIn(&employeeList, id);

				if (loggedInEmployee != NULL) {

					permissions = loggedInEmployee->employee->position;

					if (permissions == WORK) {

						do {
							putchar('\0');
							displayMenu(WORK);
							choice = getCharInput(WORK_MAX_CHAR);
							performWorkerChoice(&employeeList, loggedInEmployee, choice);
						} while (choice != WORK_MAX_CHAR);

					}
					else if (permissions == MANA) {

						do {
							displayMenu(MANA);
							choice = getCharInput(MANA_MAX_CHAR);
							performManagerChoice(&employeeList, loggedInEmployee, choice);
						} while (choice != MANA_MAX_CHAR);

					}
					else
						printf("error.\n");

					logOut(loggedInEmployee);
				}
				else
					printf("Invalid ID. Please retry.\n\n");
			}
			else
				printf("\nThere are no employees in the system at the moment.\n\n");
			
		}
		else if (logInChoice == 'b') {	

			if (getFranchiseeExistance(fr))
			{
				displayLogInPrompt();
				id = getInteger(10000000, 99999999);
				_itoa(id, tempPass, 10);

				if (!strcmp(fr->password, tempPass)) {

					do {
						putchar('\0');
						choice = "";
						displayMenu(FRAN);
						choice = getCharInput(FRAN_MAX_CHAR);
						performFranchiseeChoice(&employeeList, choice);
					} while (choice != FRAN_MAX_CHAR);
				}
				else
					printf("Invalid ID. Please retry.\n\n");
			}
			else
				printf("\nThere are no franchisees in the system at the moment.\n\n");
			

		}
		else if (logInChoice == 'c') {

			displayLogInPrompt();
			id = getInteger(10000000, 99999999);
			_itoa(id, tempPass, 10);

			if (!strcmp(co.password, tempPass)) {

				do {
					putchar('\0');
					displayMenu(CORP);
					choice = getCharInput(CORP_MAX_CHAR);
					performCorporateChoice(&employeeList, fr, choice);
				} while (choice != CORP_MAX_CHAR);
			}
			else {
				printf("Invalid ID. Please retry.\n\n");
			}
		}
		else {
			printf("Logging out.\n\n");
			active = false;
		}

	} while (active == true);


	if (!saveToDisk(employeeList, *fr, co, path))
	{
		fprintf(stderr, "error saving file to text file.\n");
		exit(EXIT_FAILURE);
	}

	free(fr);
	exitInterface(&employeeList);

	return 0;
}