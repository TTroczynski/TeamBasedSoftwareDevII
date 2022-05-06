#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>

#define NAMEMAX 15
#define SINMAX 10
#define DAYSINWEEK 7
#define WEEKSINMONTH 4
#define ADDRESSMAX 50
#define DATETIMEMAX 30
#define MINUTESINHOUR 60
#define DIGITMAX 8
#define KEY 1993

typedef enum type { WORK, MANA, FRAN, CORP }TYPE;

typedef struct personal {
	char fName[NAMEMAX];
	char lName[NAMEMAX];
	char sinNumber[SINMAX];
	char address[ADDRESSMAX];
	time_t dateOfBirth;
}PERSONAL;

typedef struct schedule {
	time_t punchIn;
	time_t punchOut;
	bool working;
	bool late;
	bool absent;
}SCHEDULE;

typedef union income {
	double salary;
	double wage;
}INCOME;

typedef struct employee {
	PERSONAL details;
	SCHEDULE schedule[DAYSINWEEK][WEEKSINMONTH];
	INCOME income;
	TYPE position;
	int employeeNumber;
}EMPLOYEE, * PEMPLOYEE;

typedef struct listNode {
	PEMPLOYEE employee;
	struct listNode* next;
}NODE, *PNODE;


SCHEDULE* getSchedule(PEMPLOYEE employee);

//Purpose: To retrieve an employees schedule for a specific day of the planned 4 week schedule
//Returns : returns a schedule ADT containing employee schedule information
//Parameters : An Employee(ADT) pointer

SCHEDULE* getNextWeekSchedule(SCHEDULE* employeeSchedule);

//Purpose: To retrieve the next weeks schedule.
//Returns : Returns a schedule(ADT) pointer.This function indexes to the next element in the multidimensional schedule array
//Parameters : a schedule(ADT) pointer

SCHEDULE createSchedule(time_t punchIn, time_t punchOut);

//Purpose: to create a schedule in the appropriate format
//Returns: a schedule type containing the employees schedule data
//Parameters: time_t type holding the employees scheduled punch in time, and a time_t holding the employees scheduled punch out time

void setSchedule(PEMPLOYEE, SCHEDULE, int dayOfWeek, int weekOfMonth);
//Purpose: to set the schedule of an employee on a particular day of a week, of 4 available weeks
//Returns: nothing. The function sets a value and no returns are made within.
//Parameters: A schedule to set, an empoyee to set of the schedule for, an integer representing the day of the week and an integer representing the week of the month.

SCHEDULE* getPrevWeekSchedule(SCHEDULE* employeeSchedule);

//Purpose: To retrieve the previous weeks schedule.
//Returns : Returns a schedule(ADT) pointer.This function indexes to the previous element in the multidimensional schedule array
//Parameters : a schedule(ADT) pointer

void displaySchedule(PEMPLOYEE employee);

//Purpose: to display the employees schedule
//Returns : No return.
//Parameters : An Employee(ADT) pointer

void displayPersonalInfo(PEMPLOYEE employee);

//Purpose: To display the personal information of an employee
//Returns: Nothing. It displays information passed to it
//Parameters: An employee pointer


void displayIncome(PEMPLOYEE employee);

//Purpose: to display the employees wage or salary.This will depend on the type of the employee.The type is stored as an enum named �type�.Workers are paid a wage and managers are paid a salary.
//Returns : No return.
//Parameters : An Employee(ADT) pointer

void setSin(char*, PEMPLOYEE employee);

//Purpose: To set the employees Social Insurance Number
//Returns : nothing.The passed char pointer is the source of the  Social Insurance Number
//Parameters : A char pointer containing the Social Insurance Number to set for an employeeand an Employee(ADT) pointer.

void setIncome(PEMPLOYEE employee, double income);

//Purpose: to set the employees income.This will be either a wage or salary.The employees income is stored within the employee node addressed by the Employee pointer passed to this function.
//Returns : No return.
//Parameters : An Employee(ADT) pointer that stores all the employee's data. Income is stored with each employee. A double containing the new income of the employee. 

int getEmployeeNumber(PEMPLOYEE employee);

//Purpose: to retrieve an employees employee number stored within the employee node the Employee pointer passed to this function points to.
//Returns : an integer containing the employee number
//Parameters : An Employee(ADT) pointer that stores all the employee's data 

PEMPLOYEE getEmployee(PNODE listNode);

//Purpose: to retrieve an employee from the listNode container.
//Returns : a employee(ADT) pointer to an employee
//Parameters : An listNode (ADT) ponter to a node containing the empoyees data. 

double getIncome(PEMPLOYEE employee);

//Purpose: to retrieve the employees wage or salary stored within the employee node the Employee pointer passed to this function points to.
//Returns : a double type representing the employee's income. 
//Parameters : An Employee(ADT) pointer containing all the employee's data. 

double getDayEarnings(PEMPLOYEE employee, int weekOfMonth, int dayOfWeek);
//Purpose: To retrieve a specified shifts earnings
//Returns: a double containing the earned income of a particular day
//Parameters: An employee (ADT) pointer representing the employee, an integer specifying the week, and integer specifying the day of the week.

void setPersonalInfo(PEMPLOYEE employee, PERSONAL personalInfo);

//Purpose: To set the personal information of an employee stored within the employee node the Employee pointer passed to this function points to.
//Returns : nothing.
//Parameters : An employee pointerand a Personal(ADT) type.

PERSONAL getPersonalInfo(PEMPLOYEE employee);

//Purpose: To retrieve the personal information stored within the employee node the Employee pointer passed to this function points to.
//Returns : a Personal(ADT) type
//Parameters : An employee pointer to an employee(ADT) type.

void setEmployee(PNODE listNode, PEMPLOYEE employee);

//Purpose: to set an employees data into a node container that can be added to a list.
//Returns : a employee(ADT) pointer to an employee
//Parameters : An listNode (ADT) ponter to a node containing the empoyees data.

void setFirstName(PEMPLOYEE employee, char* fName_Source);

//Purpose: To set the first name of the employee.The first name is stored within the employee node the Employee pointer passed to this function points to.
//Returns : none
//Parameters : An Employee(ADT) pointerand a char pointer containing the employees first name

void setLastName(PEMPLOYEE employee, char* lName_Source);

//Purpose: To set the last name of the employee.The last name is stored within the employee node the Employee pointer passed to this function points to.
//Returns : none
//Parameters : An Employee(ADT) pointerand a char pointer containing the employee's last name 

int getAge(PEMPLOYEE employee);

//Purpose: To get the age of the employee in a time_t type.The age is stored within the employee node the Employee pointer passed to this function points to.
//Returns : int type containing the number of years of age
//Parameters : An Employee(ADT) pointerand a char pointer containing the employee's age  

void getAgeString(PEMPLOYEE employee, char* age_Destination);

//Purpose: To get the age of the employee in a char[] type.The age is stored within the employee node the Employee pointer passed to this function points to. The destination for output is the char* parameter.
//Returns : none
//Parameters : An Employee(ADT) pointerand a char pointer containing the employee's age  

void setAddress(PEMPLOYEE employee, char* address_Source);

//Purpose: To set the address of the employee.The address is stored within the employee node the Employee pointer passed to this function points to.
//Returns : none
//Parameters : An Employee(ADT) pointerand a char pointer containing the address

void setBirthday(PEMPLOYEE employee, time_t birthday);

//Purpose: To set the date of birth of the employee.The date of birth is stored within the employee node the Employee pointer passed to this function points to.
//Returns : none
//Parameters : An Employee(ADT) pointerand a time_t value containing a date of birth

void getFirstName(char* fName_Destination, PEMPLOYEE employee);

//Purpose: To retrieve the employees first name stored within the employee node the Employee pointer passed to this function points to.
//Returns : nothing.The passed char pointer will be the destination of the retrieved first name.
//Parameters : a char pointer where the first name will be storedand Employee(ADT) pointer

void getLastName(char* lName_Destination, PEMPLOYEE employee);

//Purpose: To retrieve the employee�s last name stored within the employee node the Employee pointer passed to this function points to.
//Returns : nothing.The passed char pointer will be the destination of the retrieved last name.
//Parameters : a char pointer where the last name will be storedand Employee(ADT) pointer

void getAddress(char* address_Destination, PEMPLOYEE employee);

//Purpose: To retrieve the employee's address stored within the employee node the Employee pointer passed to this function points to. 
//Returns : Nothing.The passed char pointer is the destination of the retrieved address
//Parameters : a char pointer where the address will be stored and an Employee(ADT) pointer

void getSin(char* sin_Destination, PEMPLOYEE employee);

//Purpose: To retrieve the employees Social Insurance Number stored within the employee node the Employee pointer passed to this function points to.
//Returns : nothing.The passed char pointer is the destination of the retrieved Social Insurance Number
//Parameters : A char pointer where the Social Insurance Number will be storedand an Employee(ADT) pointer

time_t getBirthday(PEMPLOYEE employee);

//Purpose: To get the date of birth of the employee stored within the employee node the Employee pointer passed to this function points to.
//Returns : a time_t type containing the date of birth
//Parameters : An Employee(ADT) pointer

int makeEmployeeNumber(char* fName, char* lName);

//Purpose: To generate a unique employee number in a secure way.A number will be difficult to create by anyone who does not know how they are generated.This is important because employee numbers serve as passwords for punching inand out.
//Returns : an integer value representing the employee�s employee number
//Parameters : a char pointer containing the employees first name, and a char pointer containing the employees' last name.  

bool checkEmployeeNumber(PEMPLOYEE employee);

//Purpose: To validate the employee number was generated by this punch clock
//Returns : true or false. True if the number was created with this punch clock
//Parameters : an employee(ADT) pointer

void setEmployeeNumber(PEMPLOYEE employee, int employeeID);

//Purpose: To set the employee number of the employee
//Returns: Nothing. The employeeId is set in the employee the employee(ADT) pointer points to
//Parameters: An employee(ADT) pointer and an integer containing the employee ID

PEMPLOYEE createEmployee(PERSONAL personalInfo, TYPE position);

//Purpose: To create a new employee
//Returns : a pointer to the new Employee(ADT)
//Parameters : A Personal(ADT) containing the personal information of the employeeand a Type(enum) that represents the new employee's position. 

bool addNode(PNODE listNode, PNODE employeeNode);

//Purpose: To add a new employee to the employee list.The list contains all employees currently working at the establishment.
//Returns : Nothing.The function only reassigns pointers
//Parameters : An listNode(ADT) pointer to add and a listNode(ADT) pointer to the list in which to store the Employee

bool removeNode(PNODE listNode, PNODE node_To_Remove);

//Purpose: To remove an employee from the employee list.The list contains all employees currently working at the establishment.
//Returns : 0 or -1 (integers). 0 if successful, -1 if unsuccessful.
//Parameters : a listNode (ADT) pointer to an employee to remove and listNode(ADT) pointer to the list containing all employees.

PNODE getNextNode(PNODE listNode);

//Purpose: To get the next node in the employee linked list
//Returns : An listNode (ADT) pointer to the next node of the passed employee list
//Parameters : A listNode (ADT) pointer

void replaceNode(PNODE listNode, PNODE, int employeeNumber);

//Purpose: To replace an existing employee with a matching employee id with a different employee
//Returns : nothing.
//Parameters : A listNode (ADT) that will replace a different employee, the listNode(ADT) list containing all employees, and an integer containing the employee ID to identify the employee to replace.

PNODE findNode(PNODE listNode, int employeeNumber);

//Purpose: To retrieve the listNode(ADT) pointer to the node containing the matching employee ID
//Returns : An Employee(ADT) pointer
//Parameters : a listNode(ADT) pointer and an integer containing the employee ID to find

void displayNode(PNODE listNode);

//Purpose: To display an employee�s data
//Returns : nothing.
//Parameters : A listNode(ADT) pointer containing the employee data to be displayed

void displayAll(PNODE listNode);

//Purpose: To display all employees in the employee list.
//Returns : Nothing
//Parameters : An listNode(ADT) list pointer containing the data of all employees

void deleteNode(PNODE listNode);

//Purpose: To free allocated space of the desired employee(ADT) node in the listNode(ADT) list, deleting the employee from the list.
//Returns : nothing.
//Parameters : A listNode(ADT) list pointer containing all employee data.

void deleteList(PNODE listNode);

//Purpose: To free all allocated space of the desired employee(ADT) nodes from the list
//Returns : nothing.
//Parameters : A listNode(ADT) list pointer containing all employee data.

NODE createList();
//Purpose: To create the start of the list and initialize attributes
//Returns : nothing.
//Parameters : none

PNODE createNode(PEMPLOYEE employee);
//Purpose: To create a new node containing the supplied employee data
//Returns : nothing.
//Parameters : a pointer to an employee (ADT)
