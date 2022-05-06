#include "Manager.h"
#include "UserInput.h"
#include <time.h>
#include <stdlib.h>

PEMPLOYEE createTestManager(void)
{
	PERSONAL pTest;
	INCOME wTest;
	PEMPLOYEE eTest;
	time_t currentPunchIn;
	time_t currentPunchOut;
	int day = 0;
	int week = 0;
	struct tm* dtNow;

	eTest = (PEMPLOYEE)malloc(sizeof(EMPLOYEE));
	if (!eTest) {
		exit(EXIT_FAILURE);
	}

	SCHEDULE sTest[DAYSINWEEK][WEEKSINMONTH];

	time_t timeNow = time(NULL);
	
	
	//creating schedule for the current day
	dtNow = localtime(&timeNow);

	day = dtNow->tm_mday%DAYSINWEEK;
	week = (dtNow->tm_mday / DAYSINWEEK) - 1;

	dtNow->tm_hour += 8;
	currentPunchIn = timeNow;
	currentPunchOut = mktime(dtNow);

	//PUNCH IN TIME
	struct tm in;
	in.tm_mday = 12;
	in.tm_mon = 12;
	in.tm_year = 2021;
	in.tm_hour = 9;		//9am

	time_t* timeIn = mktime(&in);

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
	memset(&birthday, 0, sizeof(struct tm));
	birthday.tm_mday = 5;
	birthday.tm_mon = 5 - 1;
	birthday.tm_year = 2000 - 1900;

	time_t converted = mktime(&birthday);

	//PERSONAL INFO SETUP
	strcpy(pTest.fName, "First");
	strcpy(pTest.lName, "Last");
	strcpy(pTest.sinNumber, "000000000");
	strcpy(pTest.address, "00 Lane");
	pTest.dateOfBirth = converted;

	wTest.salary = 3000.11; // $3000/mo


	eTest->position = 1; //manager

	//Combinging structs into employee
	eTest->details = pTest;
	eTest->income = wTest;
	eTest->schedule[0][0] = sTest[0][0];

	//setting schedule for the current day
	SCHEDULE currentDay;
	currentDay.punchIn = currentPunchIn;
	currentDay.punchOut = currentPunchOut;
	setSchedule(eTest, currentDay, day, week);

	eTest->employeeNumber = 22222222;

	return eTest;
}

PEMPLOYEE createTestWorker(void)
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
	struct tm in = { 0 };
	in.tm_mday = 12;
	in.tm_mon = 12 - 1;
	in.tm_year = 2021 - 1900;
	in.tm_hour = 9;		//9am

	time_t timeIn = mktime(&in);

	//PUNCH OUT TIME
	struct tm out = { 0 };
	out.tm_mday = 12;
	out.tm_mon = 12 - 1;
	out.tm_year = 2021 - 1900;
	out.tm_hour = 17;	//5pm

	time_t timeOut = mktime(&out);

	//set up schedule for first day
	sTest[0][0].punchIn = timeIn;
	sTest[0][0].punchOut = timeOut;
	sTest[0][0].working = false;

	//BIRTHDATE
	struct tm birthday = { 0 };
	birthday.tm_mday = 5;
	birthday.tm_mon = 5;
	birthday.tm_year = 2000 - 1900;

	time_t converted = mktime(&birthday);

	//PERSONAL INFO SETUP
	strcpy(pTest.fName, "First");
	strcpy(pTest.lName, "Last");
	strcpy(pTest.sinNumber, "000000000");
	strcpy(pTest.address, "00 Lane");
	pTest.dateOfBirth = converted;

	wTest.wage = 20.11; // $20.11/hr

	eTest->position = 0; //worker

	//Combinging structs into employee
	eTest->details = pTest;
	eTest->income = wTest;
	eTest->schedule[0][0] = sTest[0][0];

	eTest->employeeNumber = 12345678;

	return eTest;
}

/// <summary>
/// addEmployee takes the head of a list and a new Employee structure and creates a node, adding it to the end of the list.
/// </summary>
/// <param name="head_node"></param>
/// <param name="new_employee"></param>
/// <returns>success</returns>
bool addEmployee(PNODE head_node, PEMPLOYEE new_employee) {

	PNODE new_node = (PNODE)malloc(sizeof(NODE));
	if (!new_node) {
		printf("Error allocating memory.\n");
		exit(EXIT_FAILURE);
	}
	setEmployee(new_node, new_employee);
	
	return addNode(head_node, new_node); //Returns false if an employee with the same ID already exists
}

/// <summary>
/// removeEmployee finds a node in the list with a matching ID, and removes the node. It will be freed in removeNode().
/// </summary>
/// <param name="head_node"></param>
/// <param name="employeeID"></param>
/// <returns>success</returns>
bool removeEmployee(PNODE head_node, int employeeID) {
	
	PNODE found = findNode(head_node, employeeID);

	if (!found)
		return false;
	
	return removeNode(head_node, found);
}

/// <summary>
/// editEmployee handles finding a node in the list with a matching ID, creating a new node, and replacing the nodes.
/// </summary>
/// <param name="head_node"></param>
/// <param name="employeeID"></param>
/// <returns>success</returns>
bool editEmployee(PNODE head_node, PEMPLOYEE newEmployee) {
	
	PNODE toEdit = findNode(head_node, newEmployee->employeeNumber);

	if (!toEdit)		//Doesn't exist, return false
		return false;

	free(toEdit->employee);
	toEdit->employee = NULL;
	toEdit->employee = newEmployee;
	
	return true;
}

/// <summary>
/// makeNewWorker walks the user through all user input and assignment to create a new PEMPLOYEE node with a worker's permissions.
/// </summary>
/// <param name="">void</param>
/// <returns>newWorker</returns>
PEMPLOYEE makeNewWorker(void)
{
	PERSONAL p = { 0 };
	TYPE t = { 0 };

	PEMPLOYEE new_emp = createEmployee(p, t);

	char temp[MAX_STRING];
	char temp2[MAX_STRING];

	new_emp->position = WORK;

	//FIRST
	printf("Enter first name: ");
	getString(temp, NAMEMAX);
	removeNewLine(temp);
	setFirstName(new_emp, temp);

	//LAST
	printf("Enter last name: ");
	getString(temp, NAMEMAX);
	removeNewLine(temp);
	setLastName(new_emp, temp);

	//EMPLOYEE NUM GENERATION
	getFirstName(temp, new_emp);
	getLastName(temp2, new_emp);
	int employeeNum = makeEmployeeNumber(temp, temp2);
	setEmployeeNumber(new_emp, employeeNum);

	//SIN
	printf("Enter SIN: ");
	getString(temp, SINMAX);
	removeNewLine(temp);
	setSin(temp, new_emp);
	
	//ADDRESS
	printf("Enter Address: ");
	getString(temp, ADDRESSMAX);
	removeNewLine(temp);
	setAddress(new_emp, temp);

	//BIRTH DATES
	printf("Enter Birth Day: ");
	int day = getInteger(1, 31);
	printf("Enter Birth Month: ");
	int month = getInteger(1, 12);
	printf("Enter Birth Year: ");
	int year = getInteger(1900, 2022);

	struct tm *birth = malloc(sizeof(struct tm));
	if (!birth) {
		printf("Error allocating. exiting.\n\n");
		exit(EXIT_FAILURE);
	}

	memset(birth, 0, sizeof(struct tm));
	birth->tm_mday = day;
	birth->tm_mon = month - 1;
	birth->tm_year = year - 1900;

	time_t birthdate = mktime(birth);
	setBirthday(new_emp, birthdate);

	//PAY
	printf("Enter hourly wage:");
	double wage = getDouble(0, 1000);
	setIncome(new_emp, wage);

	fseek(stdin, 0, SEEK_END);

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

	in->tm_hour = 9;
	in->tm_min = 0;
	in->tm_sec = 0;

	out->tm_hour = 17;
	out->tm_min = 0;
	out->tm_sec = 0;



	time_t inTime = mktime(in);
	time_t outTime = mktime(out);

	for (int i = 0; i < DAYSINWEEK - 2; i++) {
		for (int j = 0; j < WEEKSINMONTH; j++) {
			new_emp->schedule[i][j].punchIn = inTime;
			new_emp->schedule[i][j].punchOut = outTime;
		}
	}

	return new_emp;
}

/// <summary>
/// makeNewManager walks the user through all user input and assignment to create a new PEMPLOYEE node with a manager's permissions.
/// </summary>
/// <param name="">void</param>
/// <returns>newManager</returns>
PEMPLOYEE makeNewManager(void)
{
	PERSONAL p = { 0 };
	TYPE t = { 0 };

	PEMPLOYEE new_emp = createEmployee(p, t);

	char temp[MAX_STRING];
	char temp2[MAX_STRING];

	new_emp->position = MANA;

	//FIRST
	printf("Enter first name: ");
	getString(temp, NAMEMAX);
	removeNewLine(temp);
	setFirstName(new_emp, temp);

	//LAST
	printf("Enter last name: ");
	getString(temp, NAMEMAX);
	removeNewLine(temp);
	setLastName(new_emp, temp);

	//EMPLOYEE NUM GENERATION
	getFirstName(temp, new_emp);
	getLastName(temp2, new_emp);
	int employeeNum = makeEmployeeNumber(temp, temp2);
	setEmployeeNumber(new_emp, employeeNum);

	//SIN
	printf("Enter SIN: ");
	getString(temp, SINMAX);
	removeNewLine(temp);
	setSin(temp, new_emp);

	//ADDRESS
	printf("Enter Address: ");
	getString(temp, ADDRESSMAX);
	removeNewLine(temp);
	setAddress(new_emp, temp);

	//BIRTH DATES
	printf("Enter Birth Day: ");
	int day = getInteger(1, 31);
	printf("Enter Birth Month: ");
	int month = getInteger(1, 12);
	printf("Enter Birth Year: ");
	int year = getInteger(1900, 2022);

	struct tm* birth = malloc(sizeof(struct tm));
	if (!birth) {
		printf("Error allocating. exiting.\n\n");
		exit(EXIT_FAILURE);
	}

	memset(birth, 0, sizeof(struct tm));
	birth->tm_mday = day;
	birth->tm_mon = month - 1;
	birth->tm_year = year - 1900;

	time_t birthdate = mktime(birth);
	setBirthday(new_emp, birthdate);

	//PAY
	printf("Enter salary wage:");
	double wage = getDouble(0, 100000);
	setIncome(new_emp, wage);

	fseek(stdin, 0, SEEK_END);

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

	in->tm_hour = 9;
	in->tm_min = 0;
	in->tm_sec = 0;

	out->tm_hour = 17;
	out->tm_min = 0;
	out->tm_sec = 0;

	time_t inTime = mktime(in);
	time_t outTime = mktime(out);

	for (int i = 0; i < DAYSINWEEK - 2; i++) {
		for (int j = 0; j < WEEKSINMONTH; j++) {
			new_emp->schedule[i][j].punchIn = inTime;
			new_emp->schedule[i][j].punchOut = outTime;
		}
	}

	return new_emp;
}
