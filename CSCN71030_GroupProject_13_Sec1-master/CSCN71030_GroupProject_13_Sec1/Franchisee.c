#define _CRT_SECURE_NO_WARNINGS

#include "UserInput.h"
#include "Franchisee.h"
#include "Employee.h"
#include <string.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#define LOWER_CASE_A 97
#define LOWER_CASE_Z 122

#define ASCII_0 48
#define ASCII_9 57

/*
* Purpose: Compare two franchisees.
*	
* Returns: bool. True if the franchisees are the same, false if not.
*
* Parameters: Franchisee f1. First franchisee to be compared.
*			  Franchisee f2. Second franchisee to be compared.
*/ 
bool compareFranchisees(FRANCHISEE f1, FRANCHISEE f2)
{
	bool comparison = true;

	if (strcmp(f1.fName, f2.fName))
		comparison = false;
	if (strcmp(f1.lName, f2.lName))
		comparison = false;
	if (strcmp(f1.password, f2.password))
		comparison = false;

	return comparison;
}

PEMPLOYEE makeTestManager(void)
{
    PERSONAL pTest;
    INCOME wTest;
    PEMPLOYEE eTest;

    eTest = (PEMPLOYEE)malloc(sizeof(EMPLOYEE));
    if (!eTest) {
        exit(EXIT_FAILURE);
    }

    SCHEDULE sTest[DAYSINWEEK][WEEKSINMONTH];

    //PUNCH IN TIME
    struct tm in;
    in.tm_mday = 12;
    in.tm_mon = 12;
    in.tm_year = 2021;
    in.tm_hour = 9;		//9am

    time_t timeIn = mktime(&in);

    //PUNCH OUT TIME
    struct tm out;
    out.tm_mday = 12;
    out.tm_mon = 12;
    out.tm_year = 2021;
    out.tm_hour = 17;	//5pm

    time_t timeOut = mktime(&out);

    //set up schedule for first day
    sTest[0][0].punchIn = timeIn;
    sTest[0][0].punchOut = timeOut;
    sTest[0][0].working = false;

    //BIRTHDATE
    struct tm birthday;
    birthday.tm_mday = 5;
    birthday.tm_mon = 5;
    birthday.tm_year = 2000;

    time_t converted = mktime(&birthday);

    //PERSONAL INFO SETUP
    strcpy(pTest.fName, "First");
    strcpy(pTest.lName, "Last");
    strcpy(pTest.sinNumber, "000000000");
    strcpy(pTest.address, "00 Lane");
    pTest.dateOfBirth = converted;

    wTest.wage = 20.11; // $20.11/hr


    eTest->position = 1; //manager

    //Combinging structs into employee
    eTest->details = pTest;
    eTest->income = wTest;
    eTest->schedule[0][0] = sTest[0][0];

    eTest->employeeNumber = 22222222;

    return eTest;
}

/*
Purpose: Creates a Franchisee "object" with a given first, last name and a password.

Returns : Franchisee. New franchisee "object" created with data passed.

Parameters :

	char fName[]. First name of the franchisee.

	char lName[]. Last name of the franchisee.

	char password[]. Correspondent password to be used for log - in.
*/
FRANCHISEE createFranchisee(char firstName[], char lastName[], char password[], bool ex)
{
	FRANCHISEE new_franchisee;

	strncpy_s(new_franchisee.fName, NAMEMAX, firstName, NAMEMAX);
	strncpy_s(new_franchisee.lName, NAMEMAX, lastName, NAMEMAX);
	strncpy_s(new_franchisee.password, DIGITMAX + 2, password, DIGITMAX + 2);
    new_franchisee.exists = ex;

	return new_franchisee;
}

/*
Purpose: Set a Franchisee's first name to the one passed. This follows a crucial Object-Oriented Programming (even though C is not OOP) concept,
Encapsulation. Hiding actual data from modules outside of Franchisee (or modules that inherit from it) to avoid access to its implementation.

Returns : void. The only action done is setting a character array(string).

Parameters :

	Franchisee * thisFranchisee. Pointer to a franchisee to modify its fName member.

	char first[]. String corresponding to the first name to be set to the franchisee.
*/
void setFranchiseeFName(PFRANCHISEE thisFranchisee, char first[])
{
	strncpy_s(thisFranchisee->fName, NAMEMAX, first, NAMEMAX);
}

/*
Purpose: Set a Franchisee's last name to the one passed. This follows a crucial Object-Oriented Programming (even though C is not OOP) concept,
Encapsulation. Hiding actual data from modules outside of Franchisee (or modules that inherit from it) to avoid access to its implementation.

Returns : void. The only action done is setting a character array(string).

Parameters :

	Franchisee * thisFranchisee.Pointer to a franchisee to modify its lName member.

	char last[]. String corresponding to the last name to be set to the franchisee.

*/
void setFranchiseeLName(PFRANCHISEE thisFranchisee, char last[])
{
	strncpy_s(thisFranchisee->lName, NAMEMAX, last, NAMEMAX);
}

/*
Purpose: Set a Franchisee's password to the one passed. This follows a crucial Object-Oriented Programming (even though C is not OOP) concept,
Encapsulation. Hiding actual data from modules outside of Franchisee (or modules that inherit from it) to avoid access to its implementation.

Returns : void. The only action done is setting a character array(string).

Parameters :

	Franchisee * thisFranchisee. Pointer to a franchisee to modify its password member.

	char password[]. String corresponding to the password to be set to the franchisee.
*/
void setFranchiseePassword(PFRANCHISEE thisFranchisee, char password[])
{
	strncpy_s(thisFranchisee->password, DIGITMAX + 2, password, DIGITMAX + 2);
}

/*
Purpose: Get a Franchisee's first name. This follows a crucial Object-Oriented Programming (even though C is not OOP) concept, Encapsulation.
Hiding actual data from modules outside of Franchisee (or modules that inherit from it) to avoid access to its implementation.

Returns : char*. Returns a character array(string) which corresponds to the franchisee's first name.

Parameters : Franchisee* thisFranchisee. Pointer to a Franchisee "object" to get its fName member.
*/
char* getFranchiseeFName(PFRANCHISEE thisFranchisee)
{
	return (thisFranchisee->fName);
}

/*
Purpose: Get a Franchisee's last name. This follows a crucial Object-Oriented Programming (even though C is not OOP) concept, Encapsulation.
Hiding actual data from modules outside of Franchisee (or modules that inherit from it) to avoid access to its implementation.

Returns : char*. Returns a character array(string) which corresponds to the franchisee's last name.

Parameters : Franchisee* thisFranchisee. Pointer to a Franchisee "object" to get its lName member.
*/
char* getFranchiseeLName(PFRANCHISEE thisFranchisee)
{
	return (thisFranchisee->lName);
}

/*
Purpose: Get a Franchisee's password. This follows a crucial Object-Oriented Programming (even though C is not OOP) concept, Encapsulation.
Hiding actual data from modules outside of Franchisee (or modules that inherit from it) to avoid access to its implementation.

Returns : char*. Returns a character array(string) which corresponds to the franchisee's password

Parameters : Franchisee* thisFranchisee. Pointer to a Franchisee "object" to get its password member.
*/
char* getFranchiseePassword(PFRANCHISEE thisFranchisee)
{
	return (thisFranchisee->password);
}

/*
Purpose: Adds a manager to a franchise's current list of staff. Takes the head node in the linked list of employees, and the manager to be added.
The function calls addNode from the Employee module: creates a new node using the manager, traverses through the list, and adds the manager to the end of it.

Return : bool. Returns true if the manager was successfully added to the list. False if not.

Parameters :

    PNODE list. Pointer to the head node in the linked list of employees.

    PEMPLOYEE manager. Manager to be added to the list.
*/
bool addManager(PNODE list, PEMPLOYEE manager)
{
    PNODE new_manager = (PNODE)malloc(sizeof(NODE));
    if (!new_manager)
    {
        fprintf(stderr, "error allocating manager memory\n");
        exit(EXIT_FAILURE);
    }
    
    new_manager->employee = manager;

    return (addNode(list, new_manager));
}


/*
Purpose: Removes a manager from a franchise's current list of staff.Takes the head node in the linked list of employees, and ID of the manager to be removed.
The function uses findNode from the employee module to determine if the manager exists in the list or not.
The function calls removeNode from the Employee module: traverses through the list until it finds the node that matches the manager passed and removes it. 
Memory is free'd since it is allocated in the heap.

Return : bool. True if the manager was successfully removed from the list. False either if the manager couldn't be found or there was an error removing.

Parameter(s) :

    PNODE list. Pointer to the head node in the linked list of employees.

    int managerID. ID of the Manager to be removed from the list.
*/
bool removeManager(PNODE list, int managerID)
{
    PNODE found = findNode(list, managerID);

    if (!found)
    {
        printf("Manager was not found in the list.\n");
        return false;
    }
    else if (found->employee->position != MANA)
    {
        printf("ID passed is not of a manager.\n");
        return false;
    }

    return (removeNode(list, found));
}


/*
Purpose: Modifies employee information of a manager from a franchise's current list of staff.
Takes the node containing an old manager and a new employee containing the manager with edited information.

Returns : bool. Returns true if the manager was modified successfully. Returns false either if the manager was not found or an error occurred while editing.

Parameters :

    PNODE node. Node containing the old employee.
    PEMPLOYEE manager. Manager with new information that was edited.
*/
bool editManager(PNODE node, PEMPLOYEE manager)
{
    return (editEmployee(node, manager));
}


/*
Purpose: Modifies the wage of an employee from a franchise's current list of staff.
Takes the head node of the list of employees, and the ID of the employee whose salary is going to be adjusted.
The function uses findNode from the employee module to determine if the manager exists in the list or not.
This allows to call findNode from the employee module with the head node and ID to determine if there is an existing employee with that ID or not.
New wage is given by user input (using getDouble from the UserInput module) and calls setIncome from the Employee module: replaces the employee's wage with the new one.

Returns : bool. If the adjustment of the employee's wage is done returns true. False if not.

Parameters :

    PNODE list. Pointer to the head node in the linked list of employees.
    int employeeID. ID of the employee whose salary is going to be adjusted.
*/
bool adjustWage(PNODE list, int employeeID)
{
    PNODE found = findNode(list, employeeID);

    if (!found)
    {
        printf("Worker couldn't be found on the list.\n");
        return false;
    }
    else if (found->employee->position != WORK)
    {
        printf("ID passed is not of a worker.\n");
        return false;
    }

    printf("Insert a new wage for the worker: ");
    double newWage = getDouble(0, 100000);

    setIncome(getEmployee(found), newWage);
    return true;
}


/*
Purpose: Modifies the salary of a manager from a franchise's current list of staff.
Takes the head node of the list of employees, and the ID of the manager whose salary is going to be adjusted.
The function uses findNode from the employee module to determine if the manager exists in the list or not.
This allows to call findNode from the employee module with the head node and ID to determine if there is an existing manager with that ID or not.
New salary is given by user input (using getDouble from the UserInput module) and calls setIncome from the Employee module: replaces the manager's salary with the new one.

Returns : bool. If the adjustment of the manager's salary is done returns true. False if not.

Parameters :

    PNODE list. Pointer to the head node in the linked list of employees.
    int managerID. ID of the manager whose salary is going to be adjusted.
*/
bool adjustSalary(PNODE list, int managerID)
{
    PNODE found = findNode(list, managerID);

    if (!found)
    {
        printf("Manager couldn't be found on the list.\n");
        return false;
    }
    else if (found->employee->position != MANA)
    {
        printf("ID passed is not of a manager.\n");
        return false;
    }
        
    printf("Insert a new salary for the manager: \n");
    double newSalary = getDouble(0, 100000);

    setIncome(getEmployee(found), newSalary);
    return true;
}


/*
Purpose: Displays the total labor costs of a franchise's current list of staff.

Takes the head node in the linked list of employees.
The function traverses through the list and determines the sum of all the employee's wages (using getIncome from the Employee module).
This total labor costs is displayed to the console.

Returns : void. Only displays the total labor costs.

Parameters :

    PNODE list. Pointer to the head node in the linked list of employees.
*/
void viewLaborCosts(PNODE list)
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

        printf("\nTotal labor costs: %.2lf\n\n", sum);
    }
    else
        printf("\nThere are no employees at the moment.\n\n");
    
}

void generateRandomFRN(PFRANCHISEE thisFranchisee)
{
    srand(time(NULL));

    for (int nameIndex = 0; nameIndex < NAMEMAX - 2; nameIndex++)
    {
        thisFranchisee->fName[nameIndex] = (rand() % (LOWER_CASE_A - LOWER_CASE_Z + 1)) + LOWER_CASE_A;
        thisFranchisee->lName[nameIndex] = (rand() % (LOWER_CASE_A - LOWER_CASE_Z + 1)) + LOWER_CASE_A;
    }

    for (int passwordIndex = 0; passwordIndex < DIGITMAX; passwordIndex++)
    {
        thisFranchisee->password[passwordIndex] = (rand() % (ASCII_0 - ASCII_9 + 1)) + ASCII_0;
    }

    setFranchiseeExistance(thisFranchisee, true);

}

void setFranchiseeExistance(PFRANCHISEE f, bool ex) {
    f->exists = ex;
}

bool getFranchiseeExistance(PFRANCHISEE f) {
    return f->exists;
}