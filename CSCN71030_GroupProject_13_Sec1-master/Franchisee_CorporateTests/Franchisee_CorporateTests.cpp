#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

extern "C"
{
#include "Franchisee.h"
#include "Corporate.h"
#include <stdbool.h>
}
namespace FranchiseeCorporateTests
{
	TEST_CLASS(FranchiseeTests)
	{
		char firstTest[NAMEMAX] = "Test First";
		char lastTest[NAMEMAX] = "Test Last";
		char password[DIGITMAX + 2] = "12345678";
		FRANCHISEE test_franchisee = {"Test First", "Test Last", "12345678", true};
		PEMPLOYEE test_manager = makeTestManager();
	public:
		
		TEST_METHOD(TF001_createFranchisee_FirstNameLastNamePassword_ReturnsAFranchisee)
		{
			FRANCHISEE new_franchisee = createFranchisee(firstTest, lastTest, password, true);
			bool areSame = compareFranchisees(new_franchisee, test_franchisee);

			Assert::IsTrue(areSame);
		}

		TEST_METHOD(TF002_setFranchiseeFName_FranchiseeWithFirstName_FirstNameIsAssigned)
		{
			Franchisee new_franchisee;

			setFranchiseeFName(&new_franchisee, firstTest);

			bool firstWasAssigned = false;

			if (!strcmp(new_franchisee.fName, firstTest))
				firstWasAssigned = true;

			Assert::IsTrue(firstWasAssigned);
		}

		TEST_METHOD(TF003_setFranchiseeLName_FranchiseeWithLastName_LastNameIsAssigned)
		{
			Franchisee new_franchisee;

			setFranchiseeLName(&new_franchisee, lastTest);

			bool lastWasAssigned = false;

			if (!strcmp(new_franchisee.lName, lastTest))
				lastWasAssigned = true;

			Assert::IsTrue(lastWasAssigned);
		}

		TEST_METHOD(TF004_setFranchiseePassword_FranchiseeWithPassword_PasswordIsAssigned)
		{
			Franchisee new_franchisee;

			setFranchiseePassword(&new_franchisee, password);

			bool passwordWasAssigned = false;

			if (!strcmp(new_franchisee.password, password))
				passwordWasAssigned = true;

			Assert::IsTrue(passwordWasAssigned);
		}

		TEST_METHOD(TF005_getFranchiseeFName_Franchisee_ReturnsFirstName)
		{
			char* result = getFranchiseeFName(&test_franchisee);
			
			bool firstNameReturned = false;
			if (!strcmp(result, test_franchisee.fName))
				firstNameReturned = true;
			
			Assert::IsTrue(firstNameReturned);
		}

		TEST_METHOD(TF006_getFranchiseeLName_Franchisee_ReturnsLastName)
		{
			char* result = getFranchiseeLName(&test_franchisee);
			
			bool lastNameReturned = false;
			if (!strcmp(result, test_franchisee.lName))
				lastNameReturned = true;

			Assert::IsTrue(lastNameReturned);
		}

		TEST_METHOD(TF007_getFranchiseePassword_Franchisee_ReturnsPassword)
		{
			char* result = getFranchiseePassword(&test_franchisee);

			bool passwordReturned = false;
			if (!strcmp(result, test_franchisee.password))
				passwordReturned = true;

			Assert::IsTrue(passwordReturned);
		}

		TEST_METHOD(TF008_addManager_emptyList_ManagerIsHeadNode)
		{
			NODE head_node = { 0 };

			PNODE expected = (PNODE)malloc(sizeof(NODE));
			if (!expected)
				exit(EXIT_FAILURE);

			expected->employee = makeTestManager();

			bool correctlyAdded = addManager(&head_node, test_manager);

			bool sameEmployeeNumber = false;
			if (head_node.employee)
			{
				if (head_node.employee->employeeNumber == expected->employee->employeeNumber)
					sameEmployeeNumber = true;
			}
			
			free(expected);

			Assert::IsTrue(correctlyAdded == sameEmployeeNumber == true);
		}

		TEST_METHOD(TF009_addManager_duplicateManager_NoOperationsDone)
		{
			NODE head_node = *createNode(test_manager);
			
			bool correctlyAdded = addManager(&head_node, test_manager);

			bool nextIsNull = false;
			if (head_node.next == NULL)
				nextIsNull = true;

			Assert::IsTrue(nextIsNull && correctlyAdded == false);
		}

		TEST_METHOD(TF010_addManager_noDuplicates_ManagerIsAddedToTheEnd)
		{
			NODE head_node = *createNode(test_manager);

			PNODE expected = (PNODE)malloc(sizeof(NODE));
			if (!expected)
				exit(EXIT_FAILURE);

			PEMPLOYEE new_test = makeTestManager();
			new_test->employeeNumber = 12345678;

			expected = createNode(new_test);

			bool correctlyAdded = addManager(&head_node, new_test);

			bool nextIsExpected = false;
			if (head_node.next->employee == expected->employee)
				nextIsExpected = true;

			free(expected);
			Assert::IsTrue(nextIsExpected == correctlyAdded == true);
		}

		TEST_METHOD(TF011_removeManager_existingManager_ManagerIsRemoved)
		{
			NODE head_node = *createNode(test_manager);

			bool correctlyRemoved = removeManager(&head_node, 22222222);

			bool headNodeIsNull = false;
			if (!head_node.employee)
				headNodeIsNull = true;

			Assert::IsTrue(correctlyRemoved = headNodeIsNull == true);
		}

		TEST_METHOD(TF012_removeManager_emptyList_noChanges)
		{
			PNODE head_node = (PNODE)malloc(sizeof(NODE));
			if (!head_node)
				exit(EXIT_FAILURE);

			head_node = NULL;

			bool correctlyRemoved = removeManager(head_node, 12345678);

			bool headIsNotCorrupted = false;
			if (head_node == NULL)
				headIsNotCorrupted = true;

			free(head_node);
			Assert::IsTrue(correctlyRemoved == false && headIsNotCorrupted);
		}

		TEST_METHOD(TF013_removeManager_managerDoesntExist_noChanges)
		{
			NODE head_node = *createNode(test_manager);

			PNODE expected = (PNODE)malloc(sizeof(NODE));
			if (!expected)
				exit(EXIT_FAILURE);

			expected = &head_node;

			bool correctlyRemoved = removeManager(&head_node, 12345678);
			
			bool headIsExpected = false;
			if (head_node.employee == expected->employee)
				headIsExpected = true;

			Assert::IsTrue(headIsExpected && correctlyRemoved == false);
		}

		TEST_METHOD(TF014_modifyManager_emptyList_noEdits)
		{
			PNODE head_node = (PNODE)malloc(sizeof(NODE));
			if (!head_node)
				exit(EXIT_FAILURE);

			head_node = NULL;

			bool correctlyEdited = editManager(head_node, test_manager);

			bool headIsNull = false;
			if (head_node == NULL)
				headIsNull = true;

			free(head_node);
			Assert::IsTrue(correctlyEdited == false && headIsNull);
		}
	
	};

	TEST_CLASS(CorporateTests)
	{
		char firstTest[NAMEMAX] = "Test First";
		char lastTest[NAMEMAX] = "Test Last";
		char password[NAMEMAX] = "Test Password";
		CORPORATE test_corporate = { "Test First", "Test Last", "Test Password" };
	public:

		TEST_METHOD(TC001_createCorporate_FirstNameLastNamePassword_ReturnsACorporate)
		{
			CORPORATE new_corporate = createCorporate(firstTest, lastTest, password);
			bool areSame = compareCorporates(new_corporate, test_corporate);

			Assert::IsTrue(areSame);
		}

		TEST_METHOD(TC002_setCorporateFName_CorporateWithFirstName_FirstNameIsAssigned)
		{
			CORPORATE new_corporate;
			
			setCorporateFName(&new_corporate, firstTest);

			bool firstWasAssigned = false;
			if (!strcmp(new_corporate.fName, firstTest))
				firstWasAssigned = true;

			Assert::IsTrue(firstWasAssigned);
		}

		TEST_METHOD(TC003_setCorporateLName_CorporateWithLastName_LastNameIsAssigned)
		{
			CORPORATE new_corporate;

			setCorporateLName(&new_corporate, lastTest);

			bool lastWasAssigned = false;
			if (!strcmp(new_corporate.lName, lastTest))
				lastWasAssigned = true;

			Assert::IsTrue(lastWasAssigned);
		}

		TEST_METHOD(TC004_setCorporatePassword_CorporateWithPassword_PasswordIsAssigned)
		{
			CORPORATE new_corporate;

			setCorporatePassword(&new_corporate, password);

			bool passwordWasAssigned = false;
			if (!strcmp(new_corporate.password, password))
				passwordWasAssigned = true;

			Assert::IsTrue(passwordWasAssigned);
		}

		TEST_METHOD(TC005_getCorporateFName_Corporate_ReturnsFirstName)
		{
			char* result = getCorporateFName(&test_corporate);

			bool firstNameReturned = false;
			if (!strcmp(result, firstTest))
				firstNameReturned = true;

			Assert::IsTrue(firstNameReturned);
		}

		TEST_METHOD(TC006_getCorporateLName_Corporate_ReturnsLastName)
		{
			char* result = getCorporateLName(&test_corporate);

			bool lastNameReturned = false;
			if (!strcmp(result, lastTest))
				lastNameReturned = true;

			Assert::IsTrue(lastNameReturned);
		}

		TEST_METHOD(TC007_getCorporatePassword_Corporate_ReturnsPassword)
		{
			char* result = getCorporatePassword(&test_corporate);

			bool passwordReturned = false;
			if (!strcmp(result, password))
				passwordReturned = true;

			Assert::IsTrue(passwordReturned);
		}
	};
}
