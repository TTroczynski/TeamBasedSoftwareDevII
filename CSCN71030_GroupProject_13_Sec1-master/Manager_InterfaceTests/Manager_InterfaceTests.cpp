#include "pch.h"
#include "CppUnitTest.h"

#define _CRT_SECURE_NO_WARNINGS

extern "C" {
#include "Manager.h"
#include "Interface.h"
#include "Employee.h"
}

//WORKING CURRENTLY

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Manager_InterfaceTests
{

	TEST_CLASS(Manager_Tests)
	{
		PEMPLOYEE testWorker = createTestWorker();
		PEMPLOYEE testManager = createTestManager();

	public:

		// addEmployee_emptyList
		// Adds a new employee node to an empty list, ensures head node is set properly to new node.
		// Will compare head node with expected head node.
		TEST_METHOD(addEmployee_emptyList)
		{
			NODE head_node = { 0 };
			NODE expectedHead = { 0 };

			expectedHead.employee = createTestWorker();

			bool success = false;
			bool goodAdd;

			goodAdd = addEmployee(&head_node, testWorker);

			if (head_node.employee) {
				if (head_node.employee->employeeNumber == expectedHead.employee->employeeNumber && goodAdd == true)
					success = true;

				else {
					success = false;
				}

				Assert::IsTrue(success);
			}
		}
		// addEmployee_duplicateEmployee
		// Adds a new employee node to a list with one employee with a duplicated employeeNumber.
		// Will compare head node with expected head node to ensure that employees with the same # will not be added.
		TEST_METHOD(addEmployee_duplicateEmployee)
		{
			NODE head_node = { 0 };
			NODE expectedHead = { 0 };

			expectedHead.employee = createTestWorker();	//ID of 12345678

			bool success = false;
			bool goodAdd;

			goodAdd = addEmployee(&head_node, testWorker);
			goodAdd = addEmployee(&head_node, expectedHead.employee);

			if (head_node.employee != NULL) {
				if (head_node.next == NULL && goodAdd == false)
					success = true;
			}
			else {
				success = false;
			}

			Assert::IsTrue(success);
		}

		// addEmployee_standardAdd
		// Adds a new employee node to a list with one current employee.
		// Will ensure that no employee IDs are duplicated, and add the new employee to the end of the list.
		TEST_METHOD(addEmployee_standardAdd)
		{
			NODE head_node = { 0 };
			NODE toAdd = { 0 };


			toAdd.employee = createTestWorker();	//ID of 12345678
			toAdd.employee->employeeNumber = 22222222;

			bool success = false;
			bool goodAdd;

			goodAdd = addEmployee(&head_node, testWorker);
			goodAdd = addEmployee(&head_node, toAdd.employee);

			if (head_node.employee) {

				if (head_node.next->employee->employeeNumber == 22222222) {
					success = true;
				}
				else {
					success = false;
				}

				Assert::IsTrue(success);

			}
		}

		// editEmployee_standardEdit
		// Edits a employee in the list and finds it by searching for an employee with a matching ID
		// Will ensure that if an employee with a matching ID is found, it will be properly edited
		TEST_METHOD(editEmployee_standardEdit)
		{
			NODE head_node = { 0 };
			NODE toEdit = { 0 };

			char* newName = "benjamin";

			toEdit.employee = createTestWorker();	//ID of 12345678
			toEdit.employee->employeeNumber = 12345678;
			strcpy(toEdit.employee->details.fName, newName);

			bool success = false;
			bool goodAdd, goodEdit;

			goodAdd = addEmployee(&head_node, testWorker);
			goodEdit = editEmployee(&head_node, toEdit.employee);

			if(head_node.employee) {
				if (strcmp(head_node.employee->details.fName, newName) == 0 && goodEdit == true) {
					success = true;
				}
			}
			else {
				success = false;
			}

			Assert::IsTrue(success);
		}

		// editEmployee_notFound
		// Refuses to edit an employee if no employee with matching ID is found.
		// Will ensure that if an employee with no matching ID is found, we retry the request.
		TEST_METHOD(editEmployee_notFound)
		{
			PNODE head_node = (PNODE)malloc(sizeof(NODE));
			if (!head_node)
				exit(EXIT_FAILURE);

			head_node->employee = createTestWorker();
			head_node->next = NULL;

			PEMPLOYEE temp = createTestWorker();
			temp->employeeNumber = 22222222;

			bool goodEdit = editEmployee(head_node, temp);

			bool test = false;

			if (goodEdit == false)
				test = true;

			free(head_node);

			Assert::IsTrue(test);
		}

		// editEmployee_emptyList
		// Refuses to edit an employee if the list is empty
		// Will ensure that if an employee with no matching ID is found, we retry the request.
		TEST_METHOD(editEmployee_emptyList)
		{
			PNODE head_node = (PNODE)malloc(sizeof(NODE));
			if (!head_node)
				exit(EXIT_FAILURE);

			head_node = NULL;

			PEMPLOYEE temp = createTestWorker();
			bool goodEdit = editEmployee(head_node, temp);

			bool test = false;

			if (goodEdit == false && head_node == NULL)
				test = true;

			free(head_node);

			Assert::IsTrue(test);
		}

		// removeEmployee_standardRemove
		// Will find an employee in the list with a matchingID, and remove it from the list.
		// Will ensure that only employee's with matching IDs will be removed.
		TEST_METHOD(removeEmployee_standardRemove)
		{
			NODE head_node = { 0 };

			bool goodAdd = addEmployee(&head_node, testWorker);

			PEMPLOYEE temp = createTestWorker();

			bool goodRemove = removeEmployee(&head_node, temp->employeeNumber);

			bool test = false;

			if (goodRemove == true && goodAdd == true)
				test = true;

			Assert::IsTrue(test);
		}

		// removeEmployee_emptyList
		// Refuses to make any edits if the list is empty.
		// Will ensure that if a list is empty, no edits are made and false is returned.
		TEST_METHOD(removeEmployee_emptyList)
		{
			PNODE head_node = (PNODE)malloc(sizeof(NODE));
			if (!head_node)
				exit(EXIT_FAILURE);

			head_node = NULL; //EMPTY LIST

			bool goodRemove = removeEmployee(head_node, 12345678);

			bool test = false;

			if (goodRemove == false && head_node == NULL)
				test = true;

			Assert::IsTrue(test);
		}

		// removeEmployee_notFound
		// Refuses to remove an employee if no employee with matching ID is found.
		// Will ensure that if an employee with no matching ID is found, we retry the request and false is returned.
		TEST_METHOD(removeEmployee_notFound)
		{
			NODE head_node = { 0 };

			bool goodAdd = addEmployee(&head_node, testWorker);

			PEMPLOYEE temp = createTestManager();

			bool goodRemove = removeEmployee(&head_node, temp->employeeNumber);

			bool test = false;

			if (goodRemove == false && head_node.employee != NULL)
				test = true;

			Assert::IsTrue(test);
		}
	};



	TEST_CLASS(Interface_Tests)
	{
	public:

		// logIn_validID
		// Logs in an employee with a valid ID.
		// This test will confirm that the ID will find the correct employee "log them in" and save 
		// their information, including permissions, into the interface to hold who is logged in..
		TEST_METHOD(logIn_validID) {

			PNODE head_node = (PNODE)malloc(sizeof(NODE));
			if (!head_node)
				exit(EXIT_FAILURE);

			head_node->employee = createTestManager();
			head_node->next = NULL;

			int mockEmployeeID = 22222222;

			PNODE employeeReturned = logIn(head_node, mockEmployeeID);

			bool test = false;

			if (mockEmployeeID == employeeReturned->employee->employeeNumber)
				test = true;

			free(head_node);
			Assert::IsTrue(test);
		}

		// logIn_invalidID
		// Attempts to log in with an invalidID
		// This test will confirm that the program will search all employees for a matching ID, and if 
		// none is found, the user will not be logged in.
		TEST_METHOD(logIn_invalidID) {

			PNODE head_node = (PNODE)malloc(sizeof(NODE));
			if (!head_node)
				exit(EXIT_FAILURE);

			head_node->employee = createTestManager();
			head_node->next = NULL;

			int mockEmployeeID = 12345679;

			PNODE employeeReturned = logIn(head_node, mockEmployeeID);

			bool test = false;

			if (employeeReturned == NULL)
				test = true;

			free(head_node);
			Assert::IsTrue(test);
		}

		// logOut_goodLogOut
		// Log out simply clears the employee whose permissions it was storing, and resets back to the log in screen.
		// User is logged out with a simple button press, nothing to test, no input will change where it could breakk it.
		TEST_METHOD(logOut_goodLogOut) {

			PEMPLOYEE stored_employee = createTestManager();
			NODE temp = { 0 };

			temp.employee = stored_employee;

			logOut(&temp);

			bool test = false;
			if (temp.employee == NULL && temp.next == NULL)
				test = true;

			Assert::IsTrue(test);
		}

		// punchIn_nowPunchedOut
		// This test should confirm that a user will be able to punch in if they are currently punched out.
		// It will iterate through the list, find the employee and return true or false based on if it can punch the employee out.
		TEST_METHOD(punchIn_nowPunchedOut)
		{
			PNODE head_node = (PNODE)malloc(sizeof(NODE));
			if (!head_node)
				exit(EXIT_FAILURE);

			head_node->employee = createTestWorker(); //id # of 12345678
			head_node->employee->schedule[0][0].working = false;

			bool success = false;

			success = punchIn(head_node, 12345678);

			bool test = false;

			if (success == true && head_node->employee->schedule[0][0].working == true)
				test = true;

			Assert::IsTrue(success);
		}

		// punchIn_notPunchedOut
		// This test should confirm that a user will not be allowed to punch in after they have already punched in before punching out.
		// If they could it would effectively let them change their times unnecessarrily. It will iterate through the list, find the employee and return true or false based
		// on if it can punch the employee out.
		TEST_METHOD(punchIn_notPunchedOut)
		{
			PNODE head_node = (PNODE)malloc(sizeof(NODE));
			if (!head_node)
				exit(EXIT_FAILURE);

			head_node->employee = createTestWorker(); //id # of 12345678
			head_node->employee->schedule[0][0].working = true;

			bool success = true;

			success = punchIn(head_node, 12345678);

			bool test = false;

			if (success == false && head_node->employee->schedule[0][0].working == true)
				test = true;

			Assert::IsTrue(test);
		}

		// punchOut_nowPunchedIn
		// This test should confirm that a user will allowed to punch out if they are already punched in.
		// It will iterate through the list, find the employee and return true or false based on if it can punch the employee out.
		TEST_METHOD(punchOut_nowPunchedIn)
		{
			PNODE head_node = (PNODE)malloc(sizeof(NODE));
			if (!head_node)
				exit(EXIT_FAILURE);

			head_node->employee = createTestWorker(); //id # of 12345678
			head_node->employee->schedule[0][0].working = true;

			bool success = false;

			success = punchOut(head_node, 12345678);

			bool test = false;

			if (success == true && head_node->employee->schedule[0][0].working == false)
				test = true;

			Assert::IsTrue(success);
		}

		// punchOut_notPunchedIn
		// This test should confirm that a user will not be allowed to punch out if they are not already punched in/ they already punched out.
		// It will iterate through the list, find the employee and return true or false based on if it can punch the employee out.
		TEST_METHOD(punchOut_notPunchedIn)
		{
			PNODE head_node = (PNODE)malloc(sizeof(NODE));
			if (!head_node)
				exit(EXIT_FAILURE);

			head_node->employee = createTestWorker(); //id # of 12345678
			head_node->employee->schedule[0][0].working = false;

			bool success = false;

			success = punchOut(head_node, 12345678);

			bool test = false;

			if (success == false && head_node->employee->schedule[0][0].working == false)
				test = true;

			Assert::IsTrue(test);
		}


		//EXIT INTERFACE TEST METHODS
		TEST_METHOD(exitInterface_sample) {
			Assert::IsTrue(1);
		}

		//DISPLAY MENU TEST METHODS
		TEST_METHOD(displayMenu_sample) {
			Assert::IsTrue(1);
		}
	};
}
