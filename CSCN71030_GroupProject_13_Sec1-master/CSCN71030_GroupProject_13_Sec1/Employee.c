#include "Employee.h"

SCHEDULE* getSchedule(PEMPLOYEE employee) {
	SCHEDULE* temp = NULL;
	time_t timeNow = time(0);
	struct tm* timeNowDT = (struct tm*)malloc(sizeof(struct tm));
	int week = 0;
	int day = 0;
	int error = 0;

	if (timeNowDT) {
		error = localtime_s(timeNowDT, &timeNow);
	}
	else {
		return NULL;
	}
	
	if (error) {
		return NULL;
	}

	week = (timeNowDT->tm_mday / DAYSINWEEK) - 1;
	day = timeNowDT->tm_mday % DAYSINWEEK;
	temp = &employee->schedule[day][week];

	free(timeNowDT);
	return temp;

}

//Purpose: To retrieve an employee’s current weeks schedule
//Returns : returns a schedule ADT containing employee schedule information
//Parameters : An Employee(ADT) pointer, a integer representing the week and an integer representing the day of that week

SCHEDULE* getNextWeekSchedule(SCHEDULE* employeeSchedule) {
	SCHEDULE* nextWeek = NULL;
	int error;
	int day = 0;
	struct tm* timeNowDT = (struct tm*)malloc(sizeof(struct tm));
	time_t now;
	SCHEDULE* tempPtr = employeeSchedule;

	if (timeNowDT) {
		now = time(0);
		error = localtime_s(timeNowDT, &now);
		day = (timeNowDT->tm_mday % DAYSINWEEK) + ((timeNowDT->tm_mday / DAYSINWEEK) * DAYSINWEEK) + DAYSINWEEK;
	}

	if ((int)day <= (DAYSINWEEK * WEEKSINMONTH) && day >= 0) {
		nextWeek = ++tempPtr;
	}
	else
	{
		nextWeek = NULL;
		//change to:
		//int toIndex = (day%(DAYSINWEEK*WEEKSINMONTH))%DAYSINWEEK;
		//int toDecrement = (timeNowDT->tm_mday / DAYSINWEEK) - toIndex;
		//tempPtr - toDecrement;
		//nextWeek == tempPtr;

		//wraps around the array
	}

	return nextWeek;
}

//Purpose: To retrieve the next weeks schedule.
//Returns : Returns a schedule(ADT) pointer.This function indexes to the next element in the multidimensional schedule array
//Parameters : a schedule(ADT) pointer

SCHEDULE createSchedule(time_t punchIn, time_t punchOut)
{
	SCHEDULE newSchedule = { 0 };
	newSchedule.absent = false;
	newSchedule.late = false;
	newSchedule.working = false;
	newSchedule.punchIn = punchIn;
	newSchedule.punchOut = punchOut;

	return newSchedule;
}
//Purpose: to create a schedule in the appropriate format
//Returns: a schedule type containing the employees schedule data
//Parameters: time_t type holding the employees scheduled punch in time, and a time_t holding the employees scheduled punch out time

void setSchedule(PEMPLOYEE employee, SCHEDULE newSchedule, int day, int week)
{
	employee->schedule[day][week] = newSchedule;

	return;
}
//Purpose: to set the schedule of an employee on a particular day of a week, of 4 available weeks
//Returns: nothing. The function sets a value and no returns are made within.
//Parameters: A schedule to set, an empoyee to set of the schedule for, an integer representing the day of the week and an integer representing the week of the month.

SCHEDULE* getPrevWeekSchedule(SCHEDULE* employeeSchedule) {
	
	int day = 0;
	int error;
	struct tm* timeNowDT = (struct tm*)malloc(sizeof(struct tm));
	time_t now;
	SCHEDULE* prevWeek = NULL;
	SCHEDULE* tempPtr = employeeSchedule;

	if (timeNowDT) {
		now = time(0);
		error = localtime_s(timeNowDT, &now);
		day = (timeNowDT->tm_mday % DAYSINWEEK) + ((timeNowDT->tm_mday / DAYSINWEEK) * DAYSINWEEK) - DAYSINWEEK;
	}

	if ((int)day >= 0 && day <= (WEEKSINMONTH * DAYSINWEEK)) {
		prevWeek = --tempPtr;
	}
	else
	{
		prevWeek = NULL;
	}
	
	return prevWeek;
}

//Purpose: To retrieve the previous weeks schedule.
//Returns : Returns a schedule(ADT) pointer.This function indexes to the previous element in the multidimensional schedule array
//Parameters : a schedule(ADT) pointer

void displaySchedule(PEMPLOYEE employee) {
	
	SCHEDULE* temp = getSchedule(employee);
	char fName[NAMEMAX] = { 0 };
	char dateTimeIn[DATETIMEMAX] = { 0 };
	char dateTimeOut[DATETIMEMAX] = { 0 };

	if (!temp) {
		return;
	}
	
	getFirstName(fName, employee);

	printf("%s's Schedule:\n\n", fName);

	for (int i = 0; i < DAYSINWEEK; i++) {

		ctime_s(dateTimeIn, DATETIMEMAX, &temp->punchIn);
		ctime_s(dateTimeOut, DATETIMEMAX, &temp->punchOut);
			
		printf("Punch-In: %s\n", dateTimeIn);
		printf("to\n\n");
		printf("Punch-Out: %s\n", dateTimeOut);
		printf("\n");
		temp++;
	}
}

//Purpose: to display the employees schedule
//Returns : No return.
//Parameters : An Employee(ADT) pointer

void displayPersonalInfo(PEMPLOYEE employee) {
	PERSONAL info = getPersonalInfo(employee);
	struct tm* dobData = (struct tm*)malloc(sizeof(struct tm));

	if (dobData) {
		localtime_s(dobData, &info.dateOfBirth);
		const int YEAROFFSET = 1900;
		const int MONTHOFFSET = 1;

		printf("Name: %s, %s\n", info.lName, info.fName);
		printf("SIN Number: %s\n", info.sinNumber);
		printf("DOB: %d-%d-%d\n", dobData->tm_mday, dobData->tm_mon + MONTHOFFSET, dobData->tm_year + YEAROFFSET);
		printf("Address: %s\n", info.address);
	}
	free(dobData);
}
//Purpose: To display the personal information of an employee
//Returns: Nothing. It displays information passed to it
//Parameters: An employee pointer


void displayIncome(PEMPLOYEE employee) {

	printf("Paid: ");
	switch (employee->position)
	{
	case(WORK):
		printf("Hourly Wage\n");
		printf("Wage: %lf/hour\n", employee->income.wage);
		break;
	case(MANA):
		printf("Salary\n");
		printf("Salary: %lf/month\n", employee->income.salary);
		break;
	case(FRAN):
		printf("Franhisees earnings are based on store revenue\n");
		break;
	default:
		break;
	}
	//printf("\n");
}

//Purpose: to display the employees wage or salary.This will depend on the type of the employee.The type is stored as an enum named ‘type’.Workers are paid a wage and managers are paid a salary.
//Returns : No return.
//Parameters : An Employee(ADT) pointer

void setSin(char* sin_Source, PEMPLOYEE employee) {
	strncpy_s(employee->details.sinNumber, SINMAX, sin_Source, SINMAX);
}

//Purpose: To set the employees Social Insurance Number
//Returns : nothing.The passed char pointer is the source of the  Social Insurance Number
//Parameters : A char pointer containing the Social Insurance Number to set for an employeeand an Employee(ADT) pointer.

void setIncome(PEMPLOYEE employee, double income) {

	if (employee->position == WORK) {
		employee->income.wage = income;
	}
	else if (employee->position == MANA) {
		employee->income.salary = income;
	}
	else {
		return;
	}
	return;
}

//Purpose: to set the employees income.This will be either a wage or salary.The employees income is stored within the employee node addressed by the Employee pointer passed to this function.
//Returns : No return.
//Parameters : An Employee(ADT) pointer that stores all the employee's data. Income is stored with each employee. A double containing the new income of the employee. 

int getEmployeeNumber(PEMPLOYEE employee) {
	return employee->employeeNumber;
}

//Purpose: to retrieve an employees employee number stored within the employee node the Employee pointer passed to this function points to.
//Returns : an integer containing the employee number
//Parameters : An Employee(ADT) pointer that stores all the employee's data 

PEMPLOYEE getEmployee(PNODE listNode) {
	return listNode->employee;
}

//Purpose: to retrieve an employee from the listNode container.
//Returns : a employee(ADT) pointer to an employee
//Parameters : An listNode (ADT) ponter to a node containing the empoyees data. 

double getIncome(PEMPLOYEE employee) {

	if (employee->position == WORK) {
		return employee->income.wage;
	}
	else if (employee->position == MANA) {
		return employee->income.salary;
	}
	else
	{
		return -1;
	}
}

//Purpose: to retrieve the employees wage or salary stored within the employee node the Employee pointer passed to this function points to.
//Returns : a double type representing the employee's income. 
//Parameters : An Employee(ADT) pointer containing all the employee's data. 

double getDayEarnings(PEMPLOYEE employee, int weekOfMonth, int dayOfWeek) {

	SCHEDULE* temp;
	time_t timeNow = time(0);
	struct tm* dateTimeNow = (struct tm*)malloc(sizeof(struct tm));
	struct tm* punchInDT = (struct tm*)malloc(sizeof(struct tm));
	struct tm* punchOutDT = (struct tm*)malloc(sizeof(struct tm));
	double totalEarnings = 0;
	double hoursWorked;
	double minutesWorked;

	if (dateTimeNow && punchInDT && punchOutDT) {
		
		temp = &employee->schedule[dayOfWeek][weekOfMonth];

		localtime_s(punchInDT, &temp->punchIn);
		localtime_s(punchOutDT, &temp->punchOut);

		hoursWorked = (double)punchOutDT->tm_hour -(double)punchInDT->tm_hour;
		minutesWorked = (double)punchOutDT->tm_min - (double)punchInDT->tm_min;

		if (hoursWorked < 0) {
			hoursWorked = fabs((double)punchInDT->tm_hour - punchOutDT->tm_hour) - 2;
		}


		if ((int)minutesWorked >= 0) {
			minutesWorked = (minutesWorked / MINUTESINHOUR);
			hoursWorked = hoursWorked + minutesWorked;
		}
		else {

			hoursWorked--;
			minutesWorked = (MINUTESINHOUR + minutesWorked);
			hoursWorked = hoursWorked + (minutesWorked / MINUTESINHOUR);
		}
	}
	else {
		return -1;
	}

	
	totalEarnings = getIncome(employee) * hoursWorked;
	free(dateTimeNow);
	free(punchInDT);
	free(punchOutDT);

	return totalEarnings;
}
//Purpose: To retrieve a specified shifts earnings
//Returns: a double containing the earned income of a particular day
//Parameters: An employee (ADT) pointer representing the employee, an integer specifying the week, and integer specifying the day of the week.

void setPersonalInfo(PEMPLOYEE employee, PERSONAL personalInfo) {
	PEMPLOYEE temp = employee;
	temp->details = personalInfo;
	return;
}

//Purpose: To set the personal information of an employee stored within the employee node the Employee pointer passed to this function points to.
//Returns : nothing.
//Parameters : An employee pointerand a Personal(ADT) type.

PERSONAL getPersonalInfo(PEMPLOYEE employee) {
	return employee->details;
}

//Purpose: To retrieve the personal information stored within the employee node the Employee pointer passed to this function points to.
//Returns : a Personal(ADT) type
//Parameters : An employee pointer to an employee(ADT) type.

void setEmployee(PNODE listNode, PEMPLOYEE employee) {
	PNODE temp = listNode;
	temp->employee = employee;
	return;
}

//Purpose: to set an employees data into a node container that can be added to a list.
//Returns : a employee(ADT) pointer to an employee
//Parameters : An listNode (ADT) ponter to a node containing the empoyees data.

void setFirstName(PEMPLOYEE employee, char* fName) {
	PEMPLOYEE temp = employee;
	PERSONAL tempDetails = getPersonalInfo(temp);

	strncpy_s(tempDetails.fName, NAMEMAX, fName, NAMEMAX);
	setPersonalInfo(temp, tempDetails);

	return;
}

//Purpose: To set the first name of the employee.The first name is stored within the employee node the Employee pointer passed to this function points to.
//Returns : none
//Parameters : An Employee(ADT) pointerand a char pointer containing the employees first name

void setLastName(PEMPLOYEE employee, char* lName) {
	PEMPLOYEE temp = employee;
	PERSONAL tempDetails = getPersonalInfo(temp);

	strncpy_s(tempDetails.lName, NAMEMAX, lName, NAMEMAX);
	setPersonalInfo(temp, tempDetails);

	return;
}

//Purpose: To set the last name of the employee.The last name is stored within the employee node the Employee pointer passed to this function points to.
//Returns : none
//Parameters : An Employee(ADT) pointerand a char pointer containing the employee's last name 

int getAge(PEMPLOYEE employee) {
	PERSONAL temp = getPersonalInfo(employee);
	time_t tempDOB = temp.dateOfBirth;
	time_t now;
	struct tm* nowDT = (struct tm*)malloc(sizeof(struct tm));
	struct tm* tempDobDT = (struct tm*)malloc(sizeof(struct tm));
	int convertError_Now;
	int convertError_Dob;
	int age;

	time(&now);

	if (nowDT && tempDobDT) {
		convertError_Now = localtime_s(nowDT, &now);
		convertError_Dob = localtime_s(tempDobDT, &tempDOB);

		age = nowDT->tm_year - tempDobDT->tm_year;
		
	}
	else {
		return -1;
	}

	free(tempDobDT);
	free(nowDT);
	return age;
}

//Purpose: To get the age of the employee in a time_t type.The age is stored within the employee node the Employee pointer passed to this function points to.
//Returns : int type containing the number of years of age
//Parameters : An Employee(ADT) pointerand a char pointer containing the employee's age  

void getAgeString(PEMPLOYEE employee, char* age) {

	const int MAXAGEDIGITS = 4;
	int ageInt = getAge(employee);
	const int RADIX = 10;
	char status = _itoa_s(ageInt, age, MAXAGEDIGITS, RADIX);

	return;
}

//Purpose: To get the age of the employee in a char[] type.The age is stored within the employee node the Employee pointer passed to this function points to. The destination for output is the char* parameter.
//Returns : none
//Parameters : An Employee(ADT) pointerand a char pointer containing the employee's age  

void setAddress(PEMPLOYEE employee, char* address_Source) {

	PERSONAL temp = getPersonalInfo(employee);
	strncpy_s(temp.address, ADDRESSMAX, address_Source, ADDRESSMAX);
	setPersonalInfo(employee, temp);
	return;
}

//Purpose: To set the address of the employee.The address is stored within the employee node the Employee pointer passed to this function points to.
//Returns : none
//Parameters : An Employee(ADT) pointerand a char pointer containing the address

void setEmployeeNumber(PEMPLOYEE employee, int employeeID) {
	PEMPLOYEE temp = employee;
	temp->employeeNumber = employeeID;
	return;
}

//Purpose: To set the employee number of the employee
//Returns: Nothing. The employeeId is set in the employee the employee(ADT) pointer points to
//Parameters: An employee(ADT) pointer and an integer containing the employee ID

void setBirthday(PEMPLOYEE employee, time_t birthday) {

	PERSONAL temp = getPersonalInfo(employee);
	temp.dateOfBirth = birthday;
	setPersonalInfo(employee, temp);
	return;

}

//Purpose: To set the date of birth of the employee.The date of birth is stored within the employee node the Employee pointer passed to this function points to.
//Returns : none
//Parameters : An Employee(ADT) pointerand a time_t value containing a date of birth

void getFirstName(char* fName_Destination, PEMPLOYEE employee) {

	PERSONAL temp = getPersonalInfo(employee);
	strncpy_s(fName_Destination, NAMEMAX, temp.fName, NAMEMAX);
	return;
}

//Purpose: To retrieve the employees first name stored within the employee node the Employee pointer passed to this function points to.
//Returns : nothing.The passed char pointer will be the destination of the retrieved first name.
//Parameters : a char pointer where the first name will be storedand Employee(ADT) pointer

void getLastName(char* lName_Destination, PEMPLOYEE employee) {

	PERSONAL temp = getPersonalInfo(employee);
	strncpy_s(lName_Destination, NAMEMAX, temp.lName, NAMEMAX);
	return;
}

//Purpose: To retrieve the employee’s last name stored within the employee node the Employee pointer passed to this function points to.
//Returns : nothing.The passed char pointer will be the destination of the retrieved last name.
//Parameters : a char pointer where the last name will be storedand Employee(ADT) pointer

void getAddress(char* address_Destination, PEMPLOYEE employee) {
	PERSONAL temp = getPersonalInfo(employee);
	strncpy_s(address_Destination, ADDRESSMAX, temp.address, ADDRESSMAX);
	return;
}

//Purpose: To retrieve the employee's address stored within the employee node the Employee pointer passed to this function points to. 
//Returns : Nothing.The passed char pointer is the destination of the retrieved address
//Parameters : a char pointer where the address will be stored and an Employee(ADT) pointer

void getSin(char* sin_Destination, PEMPLOYEE employee) {
	PERSONAL temp = getPersonalInfo(employee);
	strncpy_s(sin_Destination, SINMAX, temp.sinNumber, SINMAX);
	return;
}

//Purpose: To retrieve the employees Social Insurance Number stored within the employee node the Employee pointer passed to this function points to.
//Returns : nothing.The passed char pointer is the destination of the retrieved Social Insurance Number
//Parameters : A char pointer where the Social Insurance Number will be storedand an Employee(ADT) pointer

time_t getBirthday(PEMPLOYEE employee) {

	PERSONAL temp = getPersonalInfo(employee);
	return temp.dateOfBirth;
}

//Purpose: To get the date of birth of the employee stored within the employee node the Employee pointer passed to this function points to.
//Returns : a time_t type containing the date of birth
//Parameters : An Employee(ADT) pointer

int makeEmployeeNumber(char* fName, char* lName) {

	const int MAXVALUE = 89999999;
	const int MINVALUE = 10000000;
	int newNumber = 100000000;

	for (int i = 0; i < DIGITMAX; i++) {
		newNumber ^= (lName[i] << i);
		newNumber ^= (fName[i] >> i);
	}

	newNumber = abs(newNumber % (MAXVALUE - MINVALUE) + MINVALUE);
	newNumber ^= KEY;
	newNumber += MINVALUE;
	return newNumber;
}

//Purpose: To generate a unique employee number in a secure way.A number will be difficult to create by anyone who does not know how they are generated.This is important because employee numbers serve as passwords for punching inand out.
//Returns : an integer value representing the employee’s employee number
//Parameters : a char pointer containing the employees first name, and a char pointer containing the employees' last name.  

bool checkEmployeeNumber(PEMPLOYEE employee) {

	int employeeNumber = employee->employeeNumber;
	PERSONAL temp = getPersonalInfo(employee);

	const int MAXVALUE = 99999999;
	const int MINVALUE = 10000000;
	int newNumber = 100000000;

	for (int i = 0; i < DIGITMAX; i++) {
		newNumber ^= (temp.lName[i] << i);
		newNumber ^= (temp.fName[i] >> i);
	}
	newNumber = newNumber % (MAXVALUE - MINVALUE) + MINVALUE;

	if (employeeNumber == newNumber) {

		return true;
	}
	else {
		return false;
	}
	
}


//Purpose: To validate the employee number was generated by this punch clock
//Returns : true or false. True if the number was created with this punch clock
//Parameters : an employee(ADT) pointer

PEMPLOYEE createEmployee(PERSONAL personalInfo, TYPE position) {
	PEMPLOYEE newEmployee = (PEMPLOYEE)malloc(sizeof(EMPLOYEE));
	if (newEmployee) {
		newEmployee->details = personalInfo;
		newEmployee->position = position;
		newEmployee->employeeNumber = makeEmployeeNumber(personalInfo.fName, personalInfo.lName);
		return newEmployee;
	}
	return NULL;
}

//Purpose: To create a new employee
//Returns : a pointer to the new Employee(ADT)
//Parameters : A Personal(ADT) containing the personal information of the employeeand a Type(enum) that represents the new employee's position. 

bool addNode(PNODE listNode, PNODE node_To_Add) {

	PNODE temp = listNode;
	PNODE last = NULL;
	PEMPLOYEE tempEmployee = NULL;
	PEMPLOYEE toAddEmployee = NULL;


	node_To_Add->next = NULL;

	if (listNode->employee == NULL) {
		*listNode = *node_To_Add;
		return true;

	}

	while (temp != NULL) {
		last = temp;
		tempEmployee = getEmployee(listNode);
		toAddEmployee = getEmployee(node_To_Add);

		if (tempEmployee->employeeNumber == toAddEmployee->employeeNumber) {
			return false;
		}

		temp = temp->next;
	}

	if (last) {
		last->next = node_To_Add;
	}
	return true;
}

//Purpose: To add a new employee to the employee list.The list contains all employees currently working at the establishment.
//Returns : Nothing.The function only reassigns pointers
//Parameters : An listNode(ADT) pointer to add and a listNode(ADT) pointer to the list in which to store the Employee

bool removeNode(PNODE listNode, PNODE node_To_Remove) {
	PNODE temp = NULL;
	PNODE previous = NULL;
	PEMPLOYEE toRemove = NULL;

	temp = listNode;

	if (listNode->employee->employeeNumber == node_To_Remove->employee->employeeNumber) {
		temp = temp->next;
		deleteNode(listNode);
		if (temp) {
			*listNode = *temp;
		}
		return true;
	}

	while (temp != NULL) {

		if (temp != node_To_Remove) {
			previous = temp;
			temp = temp->next;
		}
		else {

			if (previous) {
				previous->next = temp->next;
				deleteNode(temp);
			}
			return true;
		}

	}
	return false;
}

//Purpose: To remove an employee from the employee list.The list contains all employees currently working at the establishment.
//Returns : 0 or -1 (integers). 0 if successful, -1 if unsuccessful.
//Parameters : a listNode (ADT) pointer to an employee to remove and listNode(ADT) pointer to the list containing all employees.

PNODE getNextNode(PNODE listNode) {
	return listNode->next;
}

//Purpose: To get the next node in the employee linked list
//Returns : An listNode (ADT) pointer to the next node of the passed employee list
//Parameters : A listNode (ADT) pointer

void replaceNode(PNODE listNode, PNODE node_To_Keep, int employeeId) {
	PNODE tempPtr = listNode;
	PEMPLOYEE tempEmployee;
	PEMPLOYEE head = NULL;
	PNODE previous;

	head = getEmployee(listNode);
	if (head->employeeNumber == employeeId) {
		node_To_Keep->next = tempPtr->next;
		listNode = node_To_Keep;
		free(tempPtr);
		return;
	}
	
	while (tempPtr != NULL) {
		previous = tempPtr;
		tempEmployee = getEmployee(tempPtr);

		if (tempEmployee->employeeNumber != employeeId) {
			tempPtr = tempPtr->next;
		}
		else {
			previous->next = node_To_Keep;
			node_To_Keep->next = tempPtr->next;
			deleteNode(tempPtr);
			return;
		}
		
	}
	return;

}

//Purpose: To replace an existing employee with a matching employee id with a different employee
//Returns : nothing.
//Parameters : A listNode (ADT) that will replace a different employee, the listNode(ADT) list containing all employees, and an integer containing the employee ID to identify the employee to replace.

PNODE findNode(PNODE listNode, int employeeId) {
	PNODE tempPtr = listNode;
	PEMPLOYEE tempEmployee;
	
	while (tempPtr != NULL) {

		tempEmployee = getEmployee(tempPtr);
		
		if (tempEmployee->employeeNumber != employeeId) {
			tempPtr = tempPtr->next;
		}
		else {
			return tempPtr;
		}
	}
	return NULL;
}

//Purpose: To retrieve the listNode(ADT) pointer to the node containing the matching employee ID
//Returns : An Employee(ADT) pointer
//Parameters : a listNode(ADT) pointer and an integer containing the employee ID to find

void displayNode(PNODE listNode) {

	PEMPLOYEE employee = getEmployee(listNode);

	if (!employee) {
		return;
	}
	if (employee->position == WORK) {
		printf("Position: Worker\n");
	}
	else if (employee->position == MANA) {
		printf("Position: Manager\n");
	}

	displayPersonalInfo(employee);
	displayIncome(employee);
	printf("EMPLOYEE ID: %d\n\n", employee->employeeNumber);
	
	return;
}

//Purpose: To display an employee’s data
//Returns : nothing.
//Parameters : A listNode(ADT) pointer containing the employee data to be displayed

void displayAll(PNODE listNode) {

	PNODE temp = listNode;

	if (!getEmployee(temp)) {
		printf("\nThere are no employees in the list at the moment.\n");
		return;
	}
	
	while (temp != NULL) {
		displayNode(temp);
		temp = temp->next;
	}
	return;
}

//Purpose: To display all employees in the employee list.
//Returns : Nothing
//Parameters : An listNode(ADT) list pointer containing the data of all employees

void deleteNode(PNODE listNode) {
	PEMPLOYEE temp = getEmployee(listNode);
	free(temp);
	listNode->next = NULL;
	listNode->employee = NULL;
	listNode = NULL;
	temp = NULL;
	return;
}

//Purpose: To free allocated space of the desired employee(ADT) node in the listNode(ADT) list, deleting the employee from the list.
//Returns : nothing.
//Parameters : A listNode(ADT) list pointer containing all employee data.

void deleteList(PNODE listNode) {
	PNODE current = listNode;
	PNODE next = NULL;
	while(current) {
		next = current->next;
		deleteNode(current);
		current = next;
	}
	
	return;
}

//Purpose: To free all allocated space of the desired employee(ADT) nodes from the list
//Returns : nothing.
//Parameters : A listNode(ADT) list pointer containing all employee data.

NODE createList() {
	NODE newNode = { 0 };
	newNode.employee = NULL;
	newNode.next = NULL;
	return newNode;
}
//Purpose: To create the start of the list and initialize attributes
//Returns : nothing.
//Parameters : none

PNODE createNode(PEMPLOYEE employee) {
	PNODE newNode = (PNODE)malloc(sizeof(NODE));
	if (!newNode) {
		exit(EXIT_FAILURE);
	}
	newNode->employee = employee;
	newNode->next = NULL;
	return newNode;
}
//Purpose: To create the start of the list and initialize attributes
//Returns : nothing.
//Parameters : none