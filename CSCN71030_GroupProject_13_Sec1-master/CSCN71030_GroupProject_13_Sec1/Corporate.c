#include "Corporate.h"
#include <string.h>

/*
Purpose: Creates a Corporate "object" with a given first, last nameand a password.

Returns : Corporate. New Corporate "object" created with data passed.

Parameters :

	char fName[]. First name of the Corporate.

	char lName[]. Last name of the Corporate.

	char password[]. Correspondent password to be used for log - in.

*/
CORPORATE createCorporate(char fName[], char lName[], char password[])
{
	CORPORATE new_corporate;

	strncpy_s(new_corporate.fName, NAMEMAX, fName, NAMEMAX);
	strncpy_s(new_corporate.lName, NAMEMAX, lName, NAMEMAX);
	strncpy_s(new_corporate.password, NAMEMAX, password, NAMEMAX);

	return new_corporate;
}

/*
* Purpose: Compare two corporates.
*	
* Returns: bool. True if the corporates are the same, false if not.
*
* Parameters: Corporate f1. First corporate to be compared.
*			  Corporate f2. Second corporate to be compared.
*/ 
bool compareCorporates(CORPORATE c1, CORPORATE c2)
{
	bool comparison = true;

	if (strcmp(c1.fName, c2.fName))
		comparison = false;
	if (strcmp(c1.lName, c2.lName))
		comparison = false;
	if (strcmp(c1.password, c2.password))
		comparison = false;

	return comparison;
}

/*
Purpose: Set a Corporate's first name. This follows a crucial Object-Oriented Programming (even though C is not OOP) concept, Encapsulation.
Hiding actual data from modules outside of Corporate (or modules that inherit from it) to avoid access to its implementation.

Returns : void. Only action done is setting a character array(string).

Parameters :

	Corporate * thisCorporate. Pointer to a Corporate to modify its fName member.

	char firstName[]. String corresponding to the first name to be set to the franchisee.
*/
void setCorporateFName(PCORPORATE thisCorporate, char firstName[])
{
	strncpy_s(thisCorporate->fName, NAMEMAX, firstName, NAMEMAX);
}

/*
Purpose: Set a Corporate's last name. This follows a crucial Object-Oriented Programming (even though C is not OOP) concept, Encapsulation.
Hiding actual data from modules outside of Corporate (or modules that inherit from it) to avoid access to its implementation.

Returns : void. Only action done is setting a character array(string).

Parameters :

	Corporate * thisCorporate. Pointer to a Corporate to modify its lName member.

	char lastName[]. String corresponding to the last name to be set to the franchisee.
*/
void setCorporateLName(PCORPORATE thisCorporate, char lastName[])
{
	strncpy_s(thisCorporate->lName, NAMEMAX, lastName, NAMEMAX);
}


/*
Purpose: Set a Corporate's password. This follows a crucial Object-Oriented Programming (even though C is not OOP) concept, Encapsulation.
Hiding actual data from modules outside of Corporate (or modules that inherit from it) to avoid access to its implementation.

Returns : void. Only action done is setting a character array(string).

Parameters :

	Corporate * thisCorporate. Pointer to a Corporate to modify its password member.

	char password[]. String corresponding to the password to be set to the franchisee.
*/
void setCorporatePassword(PCORPORATE thisCorporate, char password[])
{
	strncpy_s(thisCorporate->password, NAMEMAX, password, NAMEMAX);
}

/*
Purpose: Get a Corporate's first name. This follows a crucial Object-Oriented Programming (even though C is not OOP) concept, Encapsulation.
Hiding actual data from modules outside of Corporate (or modules that inherit from it) to avoid access to its implementation.

Returns : char* . Returns a character array(string) which corresponds to the Corporate's first name.

Parameters :

	Corporate* thisCorporate. Pointer to a Corporate "object" to get its fName member.
*/
char* getCorporateFName(PCORPORATE thisCorporate)
{
	return (thisCorporate->fName);
}


/*
Purpose: Get a Corporate's last name. This follows a crucial Object-Oriented Programming (even though C is not OOP) concept, Encapsulation.
Hiding actual data from modules outside of Corporate (or modules that inherit from it) to avoid access to its implementation.

Returns : char* . Returns a character array(string) which corresponds to the Corporate's last name.

Parameters :

	Corporate* thisCorporate. Pointer to a Corporate "object" to get its lName member.
*/
char* getCorporateLName(PCORPORATE thisCorporate)
{
	return (thisCorporate->lName);
}


/*
Purpose: Get a Corporate's last name. This follows a crucial Object-Oriented Programming (even though C is not OOP) concept, Encapsulation.
Hiding actual data from modules outside of Corporate (or modules that inherit from it) to avoid access to its implementation.

Returns : char* . Returns a character array(string) which corresponds to the Corporate's last name.

Parameters :

	Corporate* thisCorporate. Pointer to a Corporate "object" to get its lName member.
*/
char* getCorporatePassword(PCORPORATE thisCorporate)
{
	return (thisCorporate->password);
}

/*
Purpose: Displays the total labor costs of a franchise's current list of staff, including a fixed franchisee revenue to simulate a total costs generation.
Takes the head node in the linked list of employees.
The function traverses through the list and determines the sum of all the employee's income(using getIncome from the Employee module).
The fixed franchisee revenue is added to this sum.This total cost is displayed to the console.

Returns : void. Only displays the total costs.

Parameters :

	PNODE list. Pointer to the head node in the linked list of employees.
*/
void viewTotalCosts(PNODE list)
{
	double sum = 0;

	PNODE current = list;
	if (getEmployee(current))
	{
		while (current)
		{
			for (int i = 0; i < WEEKSINMONTH; i++)
			{
				for (int j = 0; j < DAYSINWEEK; j++)
				{
					sum += getDayEarnings(getEmployee(current), i, j);
				}

			}

			current = getNextNode(current);
		}
		sum += FRANCHISEE_REVENUE;
		printf("\nTotal costs from Corporate: %.2lf\n\n", sum);
	}
	else
		printf("\nThere are no employees in the system at the moment.\n\n");
	

	
}

void displayCurrentFranchisee(PFRANCHISEE thisFranchisee)
{
	if (getFranchiseeExistance(thisFranchisee))
	{
		printf("Franchisee information: \nFirst name: %s\n", getFranchiseeFName(thisFranchisee));
		printf("Last name: %s\n", getFranchiseeLName(thisFranchisee));
		printf("Password: %s\n", getFranchiseePassword(thisFranchisee));
	}
	else
		printf("No franchisee currently exists.\n");
}