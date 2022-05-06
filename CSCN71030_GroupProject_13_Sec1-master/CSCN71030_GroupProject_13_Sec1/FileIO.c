#define _CRT_SECURE_NO_WARNINGS

#include "FileIO.h"
#include <stdio.h>
#include <stdlib.h>

void removeBadChars(char* string)
{
	for (size_t index = 0; index < strlen(string); index++)
	{
		if (string[index] == '\n')
			string[index] = '\0';
	}
}

bool saveToDisk(NODE list, FRANCHISEE thisFranchisee, CORPORATE thisCorporate, char* path)
{
	FILE* fp;
	if ((fp = fopen(path, "w")) == NULL)
	{
		fprintf(stderr, "Error saving file.\n");
		return false;
	}
	else
	{
		//fprintf(fp, "CORPORATE\n");
		fprintf(fp, "%s\n", getCorporateFName(&thisCorporate));
		fprintf(fp, "%s\n", getCorporateLName(&thisCorporate));
		if (!getFranchiseeExistance(&thisFranchisee))
		{
			fprintf(fp, "%s", getCorporatePassword(&thisCorporate));
			return true;
		}
		else
			fprintf(fp, "%s\n", getCorporatePassword(&thisCorporate));
				
		
		//fprintf(fp, "FRANCHISEE\n");
		fprintf(fp, "%s\n", getFranchiseeFName(&thisFranchisee));
		fprintf(fp, "%s\n", getFranchiseeLName(&thisFranchisee));
		fprintf(fp, "%s\n", getFranchiseePassword(&thisFranchisee));
		fprintf(fp, "%d\n", getFranchiseeExistance(&thisFranchisee));

		PNODE current = &list;

		char fName[NAMEMAX];
		char address[ADDRESSMAX];
		char lName[NAMEMAX];
		char SIN[SINMAX];

		while (current && getEmployee(current))
		{
			PEMPLOYEE currentEmployee = getEmployee(current);
			if (current->employee->position == WORK)
				fprintf(fp, "WORKER\n");
			else
				fprintf(fp, "MANAGER\n");

			// Writing personal struct

			getFirstName(fName, currentEmployee);
			getLastName(lName, currentEmployee);
			getAddress(address, currentEmployee);
			getSin(SIN, currentEmployee);

			fprintf(fp, "%s\n", fName);
			fprintf(fp, "%s\n", lName);
			fprintf(fp, "%s\n", SIN);
			fprintf(fp, "%s\n", address);
			const time_t birthday = getBirthday(currentEmployee);
			struct tm tm = *localtime(&birthday);
			fprintf(fp, "%d\n%d\n%d\n", tm.tm_year + 1900, tm.tm_mday, tm.tm_mon + 1);

			// Writing employee number
			fprintf(fp, "%d\n", getEmployeeNumber(currentEmployee));

			// Writing employee income
			fprintf(fp, "%lf\n", getIncome(currentEmployee));

			// Writing employee schedule
			for (int i = 0; i < DAYSINWEEK; i++)
			{

				for (int j = 0; j < WEEKSINMONTH; j++)
				{
					// Punch in time from current day
					const time_t punchIn = currentEmployee->schedule[i][j].punchIn;
					tm = *localtime(&punchIn);
					fprintf(fp, "%d\n%d\n%d\n%d\n%d\n", tm.tm_year, tm.tm_mday, tm.tm_mon, tm.tm_hour, tm.tm_min);

					// Punch out time from current day
					const time_t punchOut = currentEmployee->schedule[i][j].punchOut;
					tm = *localtime(&punchOut);
					fprintf(fp, "%d\n%d\n%d\n%d\n%d\n", tm.tm_year, tm.tm_mday, tm.tm_mon, tm.tm_hour, tm.tm_min);

					// Working, late and absent boolean status
					fprintf(fp, "%d\n%d\n%d\n", currentEmployee->schedule[i][j].working, currentEmployee->schedule[i][j].late, currentEmployee->schedule[i][j].absent);
				}
			}
			current = getNextNode(current);
		}

		return true;
	}

}

bool loadFromDisk(NODE* list, FRANCHISEE* franchisee, CORPORATE* corporate, char* path)
{
	FILE* fp;
	if ((fp = fopen(path, "r")) == NULL)
	{
		fprintf(stderr, "Error reading file.\n");
		return false;
	}
	else
	{
		char fName[NAMEMAX];
		char lName[NAMEMAX];
		char password[DIGITMAX + 2];
		char address[ADDRESSMAX];
		char SIN[SINMAX];
		char type[TYPE_EMPLOYEE];

		// Reading corporate data from file
		fgets(fName, NAMEMAX, fp);
		removeBadChars(fName);
		setCorporateFName(corporate, fName);

		fgets(lName, NAMEMAX, fp);
		removeBadChars(lName);
		setCorporateLName(corporate, lName);

		fgets(password, DIGITMAX + 2, fp);
		removeBadChars(password);
		setCorporatePassword(corporate, password);

		if (feof(fp))
		{
			return true;
		}

		// Reading franchisee data from file
		fgets(fName, NAMEMAX, fp);
		removeBadChars(fName);
		setFranchiseeFName(franchisee, fName);

		fgets(lName, NAMEMAX, fp);
		removeBadChars(lName);
		setFranchiseeLName(franchisee, lName);

		fgets(password, DIGITMAX + 2, fp);
		removeBadChars(password);
		setFranchiseePassword(franchisee, password);

		int exists = 0;

		if (fscanf(fp, "%d\n", &exists) != 1)
		{
			fprintf(stderr, "error reading franchisee exitance\n");
			return false;
		}

		setFranchiseeExistance(franchisee, exists);

		double income;
		int empNumber;
		while (!feof(fp))
		{
			// Read the employee type (worker or manager)
			fgets(type, TYPE_EMPLOYEE, fp);
			removeBadChars(type);

			TYPE new_t;
			if (!strcmp(type, "WORKER"))
				new_t = WORK;
			else
				new_t = MANA;

			PERSONAL new_p = { 0 };

			// Create new employee with empty personal, and set type
			PEMPLOYEE currentEmployee = createEmployee(new_p, new_t);

			// Using setters for personal data
			fgets(fName, NAMEMAX, fp);
			removeBadChars(fName);
			setFirstName(currentEmployee, fName);

			fgets(lName, NAMEMAX, fp);
			removeBadChars(lName);
			setLastName(currentEmployee, lName);

			fgets(SIN, SINMAX, fp);
			removeBadChars(SIN);
			setSin(SIN, currentEmployee);

			fgets(address, ADDRESSMAX, fp);
			removeBadChars(address);
			setAddress(currentEmployee, address);

			struct tm birth = { 0 };

			if (fscanf(fp, "%d\n%d\n%d\n", &birth.tm_year, &birth.tm_mday, &birth.tm_mon) != 3)
			{
				fprintf(stderr, "birth date couldn't be read from file.\n");
				return false;
			}

			if (fscanf(fp, "%d\n", &empNumber) != 1)
			{
				fprintf(stderr, "employee number couldn't be read from file.\n");
				return false;
			}

			birth.tm_year -= 1900;
			birth.tm_mon -= 1;
			time_t birthday = mktime(&birth);
			setBirthday(currentEmployee, birthday);

			setEmployeeNumber(currentEmployee, empNumber);

			if (fscanf(fp, "%lf\n", &income) != 1)
			{
				fprintf(stderr, "income couldn't be read from file.\n");
				return false;
			}

			setIncome(currentEmployee, income);
			for (int i = 0; i < DAYSINWEEK; i++)
			{
				for (int j = 0; j < WEEKSINMONTH; j++)
				{
					struct tm punch = { 0 };

					// Reading punch in information
					if (fscanf(fp, "%d\n%d\n%d\n%d\n%d\n", &punch.tm_year, &punch.tm_mday, &punch.tm_mon, &punch.tm_hour, &punch.tm_min) != 5)
					{
						fprintf(stderr, "error reading punchIn information.\n");
						return false;
					}

					punch.tm_year -= 1900;
					punch.tm_mon -= 1;
					time_t punchIn = mktime(&punch);
					currentEmployee->schedule[i][j].punchIn = punchIn;

					// Reading punch out information
					if (fscanf(fp, "%d\n%d\n%d\n%d\n%d\n", &punch.tm_year, &punch.tm_mday, &punch.tm_mon, &punch.tm_hour, &punch.tm_min) != 5)
					{
						fprintf(stderr, "error reading punchOut information.\n");
						return false;
					}

					punch.tm_year -= 1900;
					punch.tm_mon -= 1;
					time_t punchOut = mktime(&punch);
					currentEmployee->schedule[i][j].punchOut = punchOut;

					// Reading working, late and absent status.
					int temp1, temp2, temp3;
					if (fscanf(fp, "%d\n%d\n%d\n", &temp1, &temp2, &temp3) != 3)
					{
						fprintf(stderr, "error reading working, late and absent status.\n");
						return false;
					}

					currentEmployee->schedule[i][j].working = temp1;
					currentEmployee->schedule[i][j].absent = temp2;
					currentEmployee->schedule[i][j].late = temp3;
				}
			}

			PNODE new_node = createNode(currentEmployee);
			addNode(list, new_node);
		}

		return true;

	}
}