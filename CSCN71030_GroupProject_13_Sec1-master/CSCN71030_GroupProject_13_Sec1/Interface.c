#include "Interface.h"
#include "UserInput.h"

/// <summary>
/// logIn will take a list of employees, and find an employee with the matching log-in ID.
/// It will then return a pointer to the employee that the system will stored as the logged in employee.
/// </summary>
/// <param name="employeeList"></param>
/// <param name="id"></param>
/// <returns>employee node</returns>
PNODE logIn(PNODE employeeList, int employeeID)
{
	PNODE found = findNode(employeeList, employeeID);

	return found;
}

/// <summary>
/// This function will clear any saved employee information holding the currently logged in employee, reseting to the home interface..
/// </summary>
/// <param name=""></param>
void logOut(PNODE employee)
{
	memset(employee, 0, sizeof(NODE));
}

/// <summary>
/// punchIn will find a user in the list with a matching ID of the currently logged in employee, 
/// and punch them in if they are currently punched out.
/// </summary>
/// <param name="list"></param>
/// <param name="enteredID"></param>
/// <returns>success</returns>
bool punchIn(PNODE list, int enteredID)
{
	PNODE found = findNode(list, enteredID);			//If a user is found with the matching ID in the list, we will hold that employee.

	if (found->employee->schedule[0][0].working == true)		//if the employee is already working, they can't punch in again.
		return false;
	else
		found->employee->schedule[0][0].working = true;

	//late/absence tracking will need to be added.

	return true;
}

/// <summary>
/// punchOut will find a user in the list with a matching ID of the currently logged in employee, 
/// and punch them out if they are currently punched in.
/// </summary>
/// <param name="list"></param>
/// <param name="enteredID"></param>
/// <returns>success</returns>
bool punchOut(PNODE list, int enteredID)
{
	PNODE found = findNode(list, enteredID);			//If a user is found with the matching ID in the list, we will hold that node.

	if (found->employee->schedule[0][0].working == false)	//if the employee isn't already working, they can't punch out.
		return false;
	else
		found->employee->schedule[0][0].working= false;

	return true;
}

/// <summary>
/// displayLogInPrompt will prompt the user for an 8-digit ID number to sign in (their employeeNumber).
/// </summary>
/// <param name=""></param>
void displayLogInPrompt(void) {
	
	printf("Please enter your 8-digit ID number to log in: ");
}

/// <summary>
/// performWorkerChoice guides user input and menu selection of a worker with base permissions.
/// </summary>
/// <param name="employeeList"></param>
/// <param name="loggedInEmployee"></param>
/// <param name="choice"></param>
void performWorkerChoice(PNODE employeeList, PNODE loggedInEmployee, char choice)
{
		switch (choice) {
		case 'a':	//Punch In
			if (punchIn(employeeList, loggedInEmployee->employee->employeeNumber))
				printf("Successfully punched in.\n");
			else
				printf("Unsuccessfully punched in.\n");
			break;

		case 'b':	//Punch Out
			if (punchOut(employeeList, loggedInEmployee->employee->employeeNumber))
				printf("Successfully punched out.\n");
			else
				printf("Unsuccessfully punched out.\n");
			break;

		case 'c':	//View Schedule
			displaySchedule(loggedInEmployee->employee);
			break;

		case 'd':	//View Income
			if (loggedInEmployee->employee->position == WORK)
				printf("Your hourly wage is %.2f.\n", loggedInEmployee->employee->income.wage);
			else
				printf("Your salary is %.2f.\n", loggedInEmployee->employee->income.salary);
			break;

		case 'e':	//Display Personal Info
			displayPersonalInfo(loggedInEmployee->employee);
			break;

		case 'f':	//return to menu
			printf("Logging out.\n");
		}

	putchar('\0');
}

/// <summary>
/// performManagerChoice guides user input and menu selection of a manager with increased permissions.
/// </summary>
/// <param name="employeeList"></param>
/// <param name="loggedInEmployee"></param>
/// <param name="choice"></param>
void performManagerChoice(PNODE employeeList, PNODE loggedInEmployee, char choice)
{
	int num;
	PNODE found;
	PEMPLOYEE newEmployee;

		switch (choice) {
		case 'a':	//Punch In
			if (punchIn(employeeList, loggedInEmployee->employee->employeeNumber))
				printf("Successfully punched in.\n");
			else
				printf("Unsuccessfully punched in.\n");
			break;

		case 'b':	//Punch Out
			if (punchOut(employeeList, loggedInEmployee->employee->employeeNumber))
				printf("Successfully punched out.\n");
			else
				printf("Unsuccessfully punched out.\n");
			break;

		case 'c':	//View Schedule
			displaySchedule(loggedInEmployee->employee);
			break;

		case 'd':	//View Income
			if (loggedInEmployee->employee->position == WORK)
				printf("Your hourly wage is %.2f.\n", loggedInEmployee->employee->income.wage);
			else
				printf("Your salary is %.2f.\n", loggedInEmployee->employee->income.salary);
			break;

		case 'e':	//Display Personal Info
			displayPersonalInfo(loggedInEmployee->employee);
			break;

		case 'f':	//Add Employee
			printf("ADDING NEW EMPLOYEE\n");
			newEmployee = makeNewWorker();
			
			if (!addEmployee(employeeList, newEmployee))
				printf("Error adding employee.\n");
			else
				printf("Success adding employee.\n");
			break;

		case 'g':	//Edit Employee
			printf("EDITING EMPLOYEE\n");

			printf("Enter ID of employee to edit: ");
			num = getInteger(10000000, 99999999);

			found = findNode(employeeList, num);

			if (!found || found->employee->position != WORK) {
				printf("Employee not found.\n");
			}
			else {
				PEMPLOYEE user = getEmployee(found);
				newEmployee = makeNewWorker();
				newEmployee->employeeNumber = user->employeeNumber;

				if (!editEmployee(found, newEmployee))
					printf("Error editing employee.\n");
				else
					printf("Success editing employee.\n");
			}

			break;

		case 'h':	//Remove Employee
			printf("REMOVING EMPLOYEE\n");
			printf("Enter employee ID # to find and remove: ");
			num = getInteger(10000000, 99999999);

			if (!removeEmployee(employeeList, num))
				printf("Error removing employee.\n");
			else
				printf("Success removing employee.\n");
			break;

		case 'i':	//View Employee list
			
			displayAll(employeeList);
				
			break;

		case 'j':	//View All Lates			

			while (employeeList != NULL) {
				num = 0;

				for (int i = 0; i < DAYSINWEEK; i++) {
					for (int j = 0; i < WEEKSINMONTH; i++) {
						if (employeeList->employee->schedule[i][j].late == true)
							num++;
					}
				}
				printf("%s has %d lates.\n", employeeList->employee->details.fName, num);

				employeeList = employeeList->next;
			}

			break;

		case 'k':	//View All Absences

			while (employeeList != NULL) {
				num = 0;

				for (int i = 0; i < DAYSINWEEK; i++) {
					for (int j = 0; j < WEEKSINMONTH; j++) {
						if (employeeList->employee->schedule[i][j].absent == true)
							num++;
					}
				}
				printf("%s has %d absences.\n", employeeList->employee->details.fName, num);

				employeeList = employeeList->next;
			}

			break;

		case 'l':	//View All Employee Schedules

			while (employeeList != NULL) {
				displaySchedule(employeeList->employee);
				employeeList = employeeList->next;
			}

			break;

		case 'm':	//return to menu
			printf("Logging out.\n");
		}

		putchar('\n');
}

/// <summary>
/// performFranchiseeChoices guides user input and menu selection of a Franchisee with 2nd highest permissions.
/// </summary>
/// <param name="employeeList"></param>
/// <param name="choice"></param>
void performFranchiseeChoice(PNODE employeeList, char choice)
{
	int num;
	double d_num;
	PNODE found_node = NULL;
	PEMPLOYEE newEmployee;

		switch (choice) {
		case 'a':	//Add Employee
			printf("ADDING NEW EMPLOYEE\n");
			newEmployee = makeNewWorker();

			if (!addEmployee(employeeList, newEmployee))
				printf("Error adding employee.\n");
			else
				printf("Success adding employee.\n");
			break;

		case 'b':	//Edit Employee

			if (getEmployee(employeeList))
			{
				printf("EDITING EMPLOYEE\n");

				printf("Enter ID of employee to edit: ");
				num = getInteger(10000000, 99999999);

				found_node = findNode(employeeList, num);

				if (!found_node || found_node->employee->position != WORK) {
					printf("Employee not found.\n");
				}
				else {
					newEmployee = makeNewWorker();

					if (!editEmployee(found_node, newEmployee))
						printf("Error editing employee.\n");
					else
						printf("Success editing employee.\n");
				}
			}
			else
			{
				printf("There are no employees in the list at the moment\n");
			}
			break;

		case 'c':	//Remove Employee

			if (getEmployee(employeeList))
			{
				printf("REMOVING EMPLOYEE\n");
				printf("Enter employee ID # to find and remove: ");
				num = getInteger(10000000, 99999999);

				if (!removeEmployee(employeeList, num))
					printf("Error removing employee.\n");
				else
					printf("Success removing employee.\n");
				break;
			}
			else
				printf("There are no employees in the list at this moment.\n");
			break;

		case 'd':	//View Employee list

			displayAll(employeeList);

			break;

		case 'e':	//View All Lates			

			while (employeeList != NULL) {
				num = 0;

				for (int i = 0; i < DAYSINWEEK; i++) {
					for (int j = 0; i < WEEKSINMONTH; i++) {
						if (employeeList->employee->schedule[i][j].late == true)
							num++;
					}
				}
				printf("%s has %d lates.\n", employeeList->employee->details.fName, num);

				employeeList = employeeList->next;
			}

			break;

		case 'f':	//View All Absences

			while (employeeList != NULL) {
				num = 0;

				for (int i = 0; i < DAYSINWEEK; i++) {
					for (int j = 0; j < WEEKSINMONTH; j++) {
						if (employeeList->employee->schedule[i][j].absent == true)
							num++;
					}
				}
				printf("%s has %d absences.\n", employeeList->employee->details.fName, num);

				employeeList = employeeList->next;
			}

			break;

		case 'g':	//View All Employee Schedules

			while (employeeList != NULL) {
				displaySchedule(employeeList->employee);
				employeeList = employeeList->next;
			}

			break;

		case 'h':	//add manager
			printf("ADDING NEW MANAGER\n");
			newEmployee = makeNewManager();

			if (!addEmployee(employeeList, newEmployee))
				printf("Error adding employee.\n");
			else
				printf("Success adding employee.\n");

			break;

		case 'i':	//edit manager
			
			if (getEmployee(employeeList))
			{
				printf("EDITING MANAGER\n");

				printf("Enter ID of manager to edit: ");
				num = getInteger(10000000, 99999999);

				found_node = findNode(employeeList, num);

				if (!found_node || found_node->employee->position != MANA) {
					printf("Manager not found.\n");
				}
				else {
					newEmployee = makeNewManager();

					if (!editEmployee(found_node, newEmployee))	//change to editManager
						printf("Error editing manager.\n");
					else
						printf("Success editing manager.\n");
				}
			}
			else
				printf("There are no employees in the list at the moment.\n");
			
			break;
		case 'j':	//remove manager

			if (getEmployee(employeeList))
			{
				printf("REMOVING MANAGER\n");

				printf("Enter employee ID # to find and remove: ");
				num = getInteger(10000000, 99999999);

				if (!removeEmployee(employeeList, num))
					printf("Error removing employee.\n");
				else
					printf("Success removing employee.\n");
			}
			else
				printf("There are no employees in the list at the moment\n");

			break;

		case 'k':	//adjust wage/salary
			if (getEmployee(employeeList))
			{
				printf("Enter employee ID # to edit wage: ");
				num = getInteger(10000000, 99999999);

				found_node = findNode(employeeList, num);

				if (!found_node)
					printf("not found.\n");
				else if (found_node->employee->position == WORK) {
					printf("Current wage is %.2f, enter new wage:", getIncome(found_node->employee));
					d_num = getDouble(0, 10000);
					setIncome(found_node->employee, d_num);
				}
				else {
					printf("Current salary is %.2f, enter new salary:", getIncome(found_node->employee));
					d_num = getDouble(0, 1000000);
					setIncome(found_node->employee, d_num);
				}
			}
			else
				printf("There are no employees in the list at this moment.\n");
			
			break;

		case 'l':	//view labor costs
			viewLaborCosts(employeeList);
			break;

		case 'm':	//edit employee schedule
			printf("Enter ID of employee whose schedule you wish to edit: \n");
			num = getInteger(10000000, 99999999);

			found_node = findNode(employeeList, num);

			if (!found_node)
				printf("not found.\n");
			else {
				printf("Enter day of the week (as a #): ");
				int day = getInteger(1, 7);

				printf("Enter week of the month (as a #): ");
				int week = getInteger(1, 4);

				printf("Enter hour of punch in (24/h time): ");
				int inH = getInteger(1, 24);

				printf("Enter hour of punch in (24/h time): ");
				int outH = getInteger(1, 24);

				if (inH > outH) {
					printf("Punch in time cannot be after punch out time.\n\n");
				}
				else {

					struct tm* in = malloc(sizeof(struct tm));
					struct tm* out = malloc(sizeof(struct tm));

					if (!in || !out) {
						exit(EXIT_FAILURE);
					}

					out->tm_year = 2020 - 1900;
					in->tm_year = 2020 - 1900;

					out->tm_mon = 1;
					in->tm_mon = 1;

					out->tm_mday = 1;
					in->tm_mday = 1;

					in->tm_hour = inH;
					in->tm_min = 0;
					in->tm_sec = 0;

					out->tm_hour = outH;
					out->tm_min = 0;
					out->tm_sec = 0;

					time_t inTime = mktime(in);
					time_t outTime = mktime(out);

					found_node->employee->schedule[day - 1][week - 1].punchIn = inTime;
					found_node->employee->schedule[day - 1][week - 1].punchOut = outTime;
				}
			}
			break;

		case 'n':	//return to menu
			printf("Logging out.\n");
		}

	putchar('\n');
}

/// <summary>
/// performCorporateChoice guides user input and menu selection of a Corporate user with the highest permissions.
/// </summary>
/// <param name="employeeList"></param>
/// <param name="franchisee"></param>
/// <param name="choice"></param>
void performCorporateChoice(PNODE employeeList, PFRANCHISEE franchisee, char choice)
{
	char fName[NAMEMAX];
	char lName[NAMEMAX];
	char pass[DIGITMAX + 1];


	switch (choice) {
	case 'a':	//View Total Costs
		viewTotalCosts(employeeList);
		break;

	case 'b':	//Add Franchisee
		if (franchisee->exists == false){	//empty franchiseePointer
			printf("Enter the franchisee's first name: ");
			getString(fName, NAMEMAX);
			removeNewLine(fName);

			printf("Enter the franchisee's last name: ");
			getString(lName, NAMEMAX);
			removeNewLine(lName);

			printf("Enter the franchisee's password: ");
			getString(pass, DIGITMAX + 2);
			removeNewLine(pass);

			*franchisee = createFranchisee(fName, lName, pass, true);

			printf("New franchisee created.\n");
		} else
			printf("Max amount of franchisees.\n");

		break;

	case 'c':	//Edit Franchisee
		if (getFranchiseeExistance(franchisee))
		{
			printf("Enter the franchisee's first name: ");
			getString(fName, NAMEMAX);
			removeNewLine(fName);

			printf("Enter the franchisee's last name: ");
			getString(lName, NAMEMAX);
			removeNewLine(lName);

			printf("Enter the franchisee's password: ");
			getString(pass, DIGITMAX + 2);
			removeNewLine(pass);

			*franchisee = createFranchisee(fName, lName, pass, true);

			printf("Franchisee successfully edited.\n");
		}
		else
			printf("No franchisee currently exists.\n");

		break;

	case 'd':	//Remove Franchisee

		if (getFranchiseeExistance(franchisee)) {
			printf("Franchisee %s %s removed.\n", getFranchiseeFName(franchisee), getFranchiseeLName(franchisee));
			memset(franchisee, 0, sizeof(FRANCHISEE));
			setFranchiseeExistance(franchisee, false);
		}
		else {
			printf("No franchisee currently exists.\n");
		}

		break;
	case 'e':
		displayCurrentFranchisee(franchisee);
		break;
	case 'f':	//Log Out / return to menu
		printf("Logging out.\n");
	}

	putchar('\n');
}

/// <summary>
/// getLogInID gets an 8-digit ID number using getInteger() to use to attempt a sign-in.
/// </summary>
/// <param name=""></param>
/// <returns></returns>
int getLogInID(void) {

	return getInteger(10000000, 99999999);
}

/// <summary>
/// displayMenu is a parent function for displaying all menu types based on logged in user permissions.
/// </summary>
/// <param name="permissions"></param>
void displayMenu(int permissions)
{
	char choice = 'a';

	switch (permissions) {
	case 0:
		choice = displayWorkerMenu(choice);
		printf("%c) Log out\n", choice);
		break;
	case 1:
		choice = displayWorkerMenu(choice);
		choice = displayManagerMenu(choice);
		printf("%c) Log out\n", choice);
		break;
	case 2:
		choice = displayManagerMenu(choice);
		choice = displayFranchiseeMenu(choice);
		printf("%c) Log out\n", choice);
		break;
	case 3:
		choice = displayCorporateMenu(choice);
		printf("%c) Log out\n", choice);
		break;
	}
	
	putchar('\0');
}

/// <summary>
/// displayWorkerMenu displays menu for workers and managers.
/// </summary>
/// <param name="c"></param>
/// <returns>currentMenuChar</returns>
char displayWorkerMenu(char c) {

	printf("%c) Punch In\n", c++);
	printf("%c) Punch Out\n", c++);
	printf("%c) View Schedule\n", c++);
	printf("%c) View Income\n", c++);
	printf("%c) Display Personal Info\n", c++);

	return c;
}

/// <summary>
/// displayManagerMenu displays menu for managers and franchisees.
/// </summary>
/// <param name="c"></param>
/// <returns>currentMenuChar</returns>
char displayManagerMenu(char c) {

	printf("%c) Add Employee\n", c++);
	printf("%c) Edit Employee\n", c++);
	printf("%c) Remove Employee\n", c++);
	printf("%c) View Employee List\n", c++);
	printf("%c) View All Lates\n", c++);
	printf("%c) View All Absences\n", c++);
	printf("%c) View All Employee Schedules\n", c++);

	return c;
}

/// <summary>
/// displayFranchiseeMenu displays menu exclusively for franchisees.
/// </summary>
/// <param name="c"></param>
/// <returns>currentMenuChar</returns>
char displayFranchiseeMenu(char c) {

	printf("%c) Add Manager\n", c++);
	printf("%c) Edit Manager\n", c++);
	printf("%c) Remove Manager\n", c++);
	printf("%c) Adjust Wage/Salary\n", c++);
	printf("%c) View Labor Costs\n", c++);
	printf("%c) Edit Employee Schedule\n", c++);

	return c;
}

/// <summary>
/// denta stix#7869
/// </summary>
/// <param name="c"></param>
/// <returns>currentMenuChar</returns>
char displayCorporateMenu(char c) {

	printf("%c) View Total Costs\n", c++);
	printf("%c) Add Franchisee\n", c++);
	printf("%c) Edit Franchisee\n", c++);
	printf("%c) Remove Franchisee\n", c++);
	printf("%c) Display current Franchisee\n", c++);

	return c;
}

/// <summary>
/// exitInterface will delete/free the current list of employees and save any changes to disk before exiting.
/// </summary>
/// <param name="employeeList"></param>
void exitInterface(PNODE employeeList)
{
	deleteList(employeeList); //Working?
}
