#include "pch.h"
#include "CppUnitTest.h"

#define CURRENTYEAR 2022

extern "C" {
#include "Employee.h"
}

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace EmployeeTests
{
	TEST_CLASS(EmployeeTests)
	{
		int verifyAge = 21;
		struct tm testDob;
		EMPLOYEE testEmployee;
		PERSONAL testPersonal;
		int testYear = 2000;
		int testMonth = 11;
		int testDay = 5;
		double testWage = 23.50;
		int testEmployeeNumber = 12345678;
		char testFirstName[NAMEMAX] = { 'B','i','l','l' };
		char testLastName[NAMEMAX] = { 'O','x','f','o','r','d' };
		char testSocialIN[SINMAX] = { '1', '2', '3', '4', '5', '6', '7', '8', '9' };
		char testAddress[ADDRESSMAX] = { '9','3',' ', 'A','b','b','e','y',' ','l','a','n','e' };
		time_t testDateOfBirth;
		TYPE testPosition = WORK;
		public:

		TEST_METHOD(CreateNewEmployee_ReturnsPointerToNode)
		{
			PEMPLOYEE verify = (PEMPLOYEE)malloc(sizeof(EMPLOYEE));
			bool testPass = true;
			testDob.tm_year = testYear;
			testDob.tm_mon = testMonth;
			testDob.tm_mday = testDay;
			testDateOfBirth = mktime(&testDob);

			strncpy(testPersonal.fName, testFirstName, NAMEMAX);
			strncpy(testPersonal.lName, testLastName, NAMEMAX);
			strncpy(testPersonal.sinNumber, testSocialIN, SINMAX);
			strncpy(testPersonal.address, testAddress, ADDRESSMAX);
			testPersonal.dateOfBirth = testDateOfBirth;

			testEmployee.details = testPersonal;
			testEmployee.position = WORK;
			testEmployee.details.dateOfBirth = testDateOfBirth;


			verify = createEmployee(testPersonal, testPosition);

			if (strcmp(verify->details.address, testEmployee.details.address)) {
				testPass = false;
			}
			if (verify->details.dateOfBirth != testEmployee.details.dateOfBirth) {
				testPass = false;
			}
			if (strcmp(verify->details.fName, testEmployee.details.fName)) {
				testPass = false;
			}
			if (strcmp(verify->details.lName, testEmployee.details.lName)) {
				testPass = false;
			}
			if (strcmp(verify->details.sinNumber, testEmployee.details.sinNumber)) {
				testPass = false;
			}

			Assert::IsTrue(testPass);
		}

		TEST_METHOD(GetNextNode_ReturnsPointerToNextNode)
		{
			PNODE testNode1 = (PNODE)malloc(sizeof(NODE));
			PNODE check = NULL;
			PNODE verify = (PNODE)malloc(sizeof(NODE));
			bool testPass = true;

			if (verify && testNode1) {
				testDob.tm_year = testYear;
				testDob.tm_mday = testMonth;
				testDob.tm_mday = testDay;
				testDateOfBirth = mktime(&testDob);

				strncpy(testEmployee.details.fName, testFirstName, NAMEMAX);
				strncpy(testEmployee.details.lName, testLastName, NAMEMAX);
				strncpy(testEmployee.details.sinNumber, testSocialIN, SINMAX);
				strncpy(testEmployee.details.address, testAddress, ADDRESSMAX);
				testEmployee.details.dateOfBirth = testDateOfBirth;
				testEmployee.position = testPosition;
				testEmployee.employeeNumber = testEmployeeNumber;

				verify->employee = &testEmployee;
				verify->next = NULL;

				testNode1->next = verify;

				check = getNextNode(testNode1);
				Assert::AreEqual(check->employee->employeeNumber, verify->employee->employeeNumber);
			}	
		}
		TEST_METHOD(AddAnEmployeeToList_EmployeeBecomesLastNode)
		{
			PNODE testNode1 = (PNODE)malloc(sizeof(NODE));
			PNODE testList = NULL;
			PEMPLOYEE verify = (PEMPLOYEE)malloc(sizeof(EMPLOYEE));
			bool testPass = true;


			if (testNode1 && testList && verify) {

				testList->employee = NULL;
				testList->next = NULL;

				testDob.tm_year = testYear;
				testDob.tm_mday = testMonth;
				testDob.tm_mday = testDay;
				testDateOfBirth = mktime(&testDob);

				strncpy(testEmployee.details.fName, testFirstName, NAMEMAX);
				strncpy(testEmployee.details.lName, testLastName, NAMEMAX);
				strncpy(testEmployee.details.sinNumber, testSocialIN, SINMAX);
				strncpy(testEmployee.details.address, testAddress, ADDRESSMAX);
				testEmployee.details.dateOfBirth = testDateOfBirth;
				testEmployee.position = testPosition;
				testEmployee.employeeNumber = 123456789;

				testNode1->employee = &testEmployee;
				addNode(testList, testNode1);

				if (testList->next || testList->employee) {
					Assert::AreEqual(testList->next->employee->employeeNumber, testEmployee.employeeNumber);
				}
				else {
					Assert::IsFalse(testPass);
				}
				
			}
			
		}

		TEST_METHOD(RemoveEmployeeFromList_PreviousNextEqualsRemovedNext)
		{
			PEMPLOYEE testEmployee2 = (PEMPLOYEE)malloc(sizeof(EMPLOYEE));
			PNODE check = NULL;
			PNODE testList = (PNODE)malloc(sizeof(NODE));
			PNODE testNode2 = (PNODE)malloc(sizeof(NODE));
			bool testPass = true;

			if (testList && testNode2 && testEmployee2) {
				bool testPass = true;
				testDob.tm_year = testYear;
				testDob.tm_mday = testMonth;
				testDob.tm_mday = testDay;
				testDateOfBirth = mktime(&testDob);

				strncpy(testEmployee.details.fName, testFirstName, NAMEMAX);
				strncpy(testEmployee.details.lName, testLastName, NAMEMAX);
				strncpy(testEmployee.details.sinNumber, testSocialIN, SINMAX);
				strncpy(testEmployee.details.address, testAddress, ADDRESSMAX);
				testEmployee.details.dateOfBirth = testDateOfBirth;
				testEmployee.position = testPosition;

				testNode2->employee = testEmployee2;
				testNode2->next = NULL;

				testList->employee = &testEmployee;
				testList->next = testNode2;

				int returnValue = removeNode(testList, testNode2);
				check = testList->next;

				if (check) {
					testPass = false;
				}

				testList->employee = NULL;

				free(testList);

				Assert::IsTrue(testPass);
			}
		}

		TEST_METHOD(RetrieveAgeOfEmployee_AgeIsReturned)
		{


			bool testPass = true;
			testDob.tm_year = testYear - 1900;
			testDob.tm_mday = testMonth;
			testDob.tm_mday = testDay;
			testDateOfBirth = mktime(&testDob);
			time_t now = time(0);
			int age;
			tm* dateNow;

			strncpy(testEmployee.details.fName, testFirstName, NAMEMAX);
			strncpy(testEmployee.details.lName, testLastName, NAMEMAX);
			strncpy(testEmployee.details.sinNumber, testSocialIN, SINMAX);
			strncpy(testEmployee.details.address, testAddress, ADDRESSMAX);
			testEmployee.details.dateOfBirth = testDateOfBirth;
			testEmployee.position = testPosition;

			dateNow = localtime(&now);

			age = dateNow->tm_year - testDob.tm_year;

			int testAge = getAge(&testEmployee);

			Assert::AreEqual(testAge, age);
		}

		TEST_METHOD(findingSpecifiedNode_returnFoundNode)
		{
			int test;
			int check;
			bool testPass = true;
			PEMPLOYEE tempEmployee = (PEMPLOYEE)malloc(sizeof(EMPLOYEE));
			PNODE testList = (PNODE)malloc(sizeof(NODE));
			PNODE testNode = (PNODE)malloc(sizeof(NODE));
			PNODE testFound = NULL;

			if (testList && testNode && tempEmployee) {
				bool testPass = true;
				testDob.tm_year = testYear;
				testDob.tm_mday = testMonth;
				testDob.tm_mday = testDay;
				testDateOfBirth = mktime(&testDob);

				strncpy(testEmployee.details.fName, testFirstName, NAMEMAX);
				strncpy(testEmployee.details.lName, testLastName, NAMEMAX);
				strncpy(testEmployee.details.sinNumber, testSocialIN, SINMAX);
				strncpy(testEmployee.details.address, testAddress, ADDRESSMAX);
				testEmployee.details.dateOfBirth = testDateOfBirth;
				testEmployee.position = testPosition;


				testEmployee.employeeNumber = 123456789;
				testNode->employee = &testEmployee;
				testNode->next = NULL;

				tempEmployee->employeeNumber = 333333333;
				testList->employee = tempEmployee;
				testList->next = testNode;

				check = 123456789;

				testFound = findNode(testList, 123456789);
				test = testFound->employee->employeeNumber;

				if (test != check) {
					testPass = false;
				}

				Assert::IsTrue(testPass);

				free(tempEmployee);
				free(testList);
				free(testNode);

			}
			
		}

		TEST_METHOD(ReplacingSpecifiedNode_NodeIsReplaced)
		{

			PEMPLOYEE testEmployee1 = (PEMPLOYEE)malloc(sizeof(EMPLOYEE));
			PEMPLOYEE testEmployee2 = (PEMPLOYEE)malloc(sizeof(EMPLOYEE));
			PNODE testList = (PNODE)malloc(sizeof(NODE));
			PNODE testNode = (PNODE)malloc(sizeof(NODE));
			PNODE testNodeToReplace = (PNODE)malloc(sizeof(NODE));
			if (testEmployee1 && testEmployee2 && testList && testNode && testNodeToReplace) {

				bool testPass = true;
				testDob.tm_year = testYear;
				testDob.tm_mday = testMonth;
				testDob.tm_mday = testDay;
				testDateOfBirth = mktime(&testDob);

				strncpy(testEmployee.details.fName, testFirstName, NAMEMAX);
				strncpy(testEmployee.details.lName, testLastName, NAMEMAX);
				strncpy(testEmployee.details.sinNumber, testSocialIN, SINMAX);
				strncpy(testEmployee.details.address, testAddress, ADDRESSMAX);
				testEmployee.details.dateOfBirth = testDateOfBirth;
				testEmployee.position = testPosition;
				testEmployee.employeeNumber = 123456789;

				testNode->employee = &testEmployee;
				testNode->next = NULL;
				testList->next = testNode;

				testEmployee2->employeeNumber = 987654321;
				testList->employee = testEmployee2;
				
				testEmployee1->employeeNumber = 555555555;
				testNodeToReplace->employee = testEmployee1;

				replaceNode(testList, testNodeToReplace, 555555555);

				Assert::AreEqual(testList->employee->employeeNumber, 987654321);

				free(testEmployee1);
				free(testEmployee2);
				free(testList);
				free(testNode);
				free(testNodeToReplace);
			}
			
		}

		TEST_METHOD(CheckEmployeeNumber_NumberNotValid)
		{

			PEMPLOYEE testEmployee2 = (PEMPLOYEE)malloc(sizeof(EMPLOYEE));;
			PNODE testList = (PNODE)malloc(sizeof(NODE));
			bool testPass = true;
			testDob.tm_year = testYear;
			testDob.tm_mday = testMonth;
			testDob.tm_mday = testDay;
			testDateOfBirth = mktime(&testDob);

			strncpy(testEmployee.details.fName, testFirstName, NAMEMAX);
			strncpy(testEmployee.details.lName, testLastName, NAMEMAX);
			strncpy(testEmployee.details.sinNumber, testSocialIN, SINMAX);
			strncpy(testEmployee.details.address, testAddress, ADDRESSMAX);
			testEmployee.details.dateOfBirth = testDateOfBirth;
			testEmployee.position = testPosition;
			testEmployee.employeeNumber = 123456789;

			testPass = checkEmployeeNumber(&testEmployee);

			Assert::IsFalse(testPass);
		}

		TEST_METHOD(MakeEmployeeNumber_NumberIsValid)
		{
			time_t now;
			srand(time(&now));

			const int MAXVALUE = 99999999;
			const int MINVALUE = 10000000;
			int newNumber = 100000000;

			int testPass = false;
			int checkValid = false;
			testDob.tm_year = testYear;
			testDob.tm_mday = testMonth;
			testDob.tm_mday = testDay;
			testDateOfBirth = mktime(&testDob);

			strncpy(testEmployee.details.fName, testFirstName, NAMEMAX);
			strncpy(testEmployee.details.lName, testLastName, NAMEMAX);
			strncpy(testEmployee.details.sinNumber, testSocialIN, SINMAX);
			strncpy(testEmployee.details.address, testAddress, ADDRESSMAX);
			testEmployee.details.dateOfBirth = testDateOfBirth;
			testEmployee.position = testPosition;

			for (int i = 0; i < DIGITMAX; i++) {
				newNumber ^= (testLastName[i] << i);
				newNumber ^= (testFirstName[i] >> i);
			}
			newNumber = newNumber % (MAXVALUE - MINVALUE) + MINVALUE;
			newNumber ^= KEY;

			testPass = newNumber;

			checkValid = makeEmployeeNumber(testEmployee.details.fName, testEmployee.details.lName);

			Assert::AreEqual(testPass, checkValid);
		}

		TEST_METHOD(GetEmployeeBirthday_BirthdayIsRetrieved)
		{

			time_t testBirthday;
			time_t verify;
			bool testPass = true;
			testDob.tm_year = testYear;
			testDob.tm_mday = testMonth;
			testDob.tm_mday = testDay;
			testDateOfBirth = mktime(&testDob);

			strncpy(testEmployee.details.fName, testFirstName, NAMEMAX);
			strncpy(testEmployee.details.lName, testLastName, NAMEMAX);
			strncpy(testEmployee.details.sinNumber, testSocialIN, SINMAX);
			strncpy(testEmployee.details.address, testAddress, ADDRESSMAX);
			testEmployee.details.dateOfBirth = testDateOfBirth;
			testEmployee.position = testPosition;
			testEmployee.employeeNumber = 123456789;

			testBirthday = getBirthday(&testEmployee);
			verify = testEmployee.details.dateOfBirth;

			Assert::AreEqual(testBirthday, verify);
		}

		TEST_METHOD(GetEmployeeSIN_SINIsRetrieved)
		{

			char testSIN[SINMAX] = { 0 };
			char verifySIN[SINMAX] = { 0 };
			bool testPass = true;
			testDob.tm_year = testYear;
			testDob.tm_mday = testMonth;
			testDob.tm_mday = testDay;
			testDateOfBirth = mktime(&testDob);

			strncpy(testEmployee.details.fName, testFirstName, NAMEMAX);
			strncpy(testEmployee.details.lName, testLastName, NAMEMAX);
			strncpy(testEmployee.details.sinNumber, testSocialIN, SINMAX);
			strncpy(testEmployee.details.address, testAddress, ADDRESSMAX);
			testEmployee.details.dateOfBirth = testDateOfBirth;
			testEmployee.position = testPosition;
			testEmployee.employeeNumber = 123456789;

			getSin(testSIN, &testEmployee);
			strncpy_s(verifySIN, testEmployee.details.sinNumber, SINMAX);

			Assert::AreEqual(testSIN, verifySIN);
		}

		TEST_METHOD(GetEmployeeAddress_AddressIsRetrieved)
		{
			char verifyAddress[ADDRESSMAX] = { 0 };
			bool testPass = true;
			testDob.tm_year = testYear;
			testDob.tm_mday = testMonth;
			testDob.tm_mday = testDay;
			testDateOfBirth = mktime(&testDob);

			strncpy(testEmployee.details.fName, testFirstName, NAMEMAX);
			strncpy(testEmployee.details.lName, testLastName, NAMEMAX);
			strncpy(testEmployee.details.sinNumber, testSocialIN, SINMAX);
			strncpy(testEmployee.details.address, testAddress, ADDRESSMAX);
			testEmployee.details.dateOfBirth = testDateOfBirth;
			testEmployee.position = testPosition;
			testEmployee.employeeNumber = 123456789;

			getAddress(verifyAddress, &testEmployee);

			Assert::AreEqual(testAddress, verifyAddress);
		}

		TEST_METHOD(GetEmployeeLastName_LastNameIsRetrieved)
		{
			char verifyLastName[NAMEMAX] = { 0 };
			bool testPass = true;
			testDob.tm_year = testYear;
			testDob.tm_mday = testMonth;
			testDob.tm_mday = testDay;
			testDateOfBirth = mktime(&testDob);

			strncpy(testEmployee.details.fName, testFirstName, NAMEMAX);
			strncpy(testEmployee.details.lName, testLastName, NAMEMAX);
			strncpy(testEmployee.details.sinNumber, testSocialIN, SINMAX);
			strncpy(testEmployee.details.address, testAddress, ADDRESSMAX);
			testEmployee.details.dateOfBirth = testDateOfBirth;
			testEmployee.position = testPosition;
			testEmployee.employeeNumber = 123456789;

			getLastName(verifyLastName, &testEmployee);

			Assert::AreEqual(testLastName, verifyLastName);
		}


		TEST_METHOD(GetEmployeeFirstName_FirstNameIsRetrieved)
		{

			char verifyFirstName[NAMEMAX] = { 0 };
			bool testPass = true;
			testDob.tm_year = testYear;
			testDob.tm_mday = testMonth;
			testDob.tm_mday = testDay;
			testDateOfBirth = mktime(&testDob);

			strncpy(testEmployee.details.fName, testFirstName, NAMEMAX);
			strncpy(testEmployee.details.lName, testLastName, NAMEMAX);
			strncpy(testEmployee.details.sinNumber, testSocialIN, SINMAX);
			strncpy(testEmployee.details.address, testAddress, ADDRESSMAX);
			testEmployee.details.dateOfBirth = testDateOfBirth;
			testEmployee.position = testPosition;
			testEmployee.employeeNumber = 123456789;

			getFirstName(verifyFirstName, &testEmployee);

			Assert::AreEqual(testFirstName, verifyFirstName);
		}

		TEST_METHOD(SetEmployeeBirthday_EmployeesBirthdayMatches)
		{
			time_t timeNow = time(0);
			tm* dateTimeNow = localtime(&timeNow);

			time_t testBirthday;
			time_t verifyBirthday = 0;
			bool testPass = true;

			strncpy(testEmployee.details.fName, testFirstName, NAMEMAX);
			strncpy(testEmployee.details.lName, testLastName, NAMEMAX);
			strncpy(testEmployee.details.sinNumber, testSocialIN, SINMAX);
			strncpy(testEmployee.details.address, testAddress, ADDRESSMAX);
			testEmployee.position = testPosition;
			testEmployee.employeeNumber = 123456789;
			testEmployee.details.dateOfBirth = -1;

			testDob.tm_year = testYear - 1900;
			testDob.tm_mon = testMonth;
			testDob.tm_mday = testDay;
			testBirthday = mktime(&testDob);

			setBirthday(&testEmployee, testBirthday);
			verifyBirthday = testEmployee.details.dateOfBirth;

			Assert::AreEqual(testBirthday, verifyBirthday);
		}

		TEST_METHOD(SetEmployeeAddress_EmployeesAddressMatches)
		{

			char verifyAddress[ADDRESSMAX];
			bool testPass = true;
			testDob.tm_year = testYear;
			testDob.tm_mday = testMonth;
			testDob.tm_mday = testDay;
			testDateOfBirth = mktime(&testDob);

			strncpy(testEmployee.details.fName, testFirstName, NAMEMAX);
			strncpy(testEmployee.details.lName, testLastName, NAMEMAX);
			strncpy(testEmployee.details.sinNumber, testSocialIN, SINMAX);

			testEmployee.details.dateOfBirth = testDateOfBirth;
			testEmployee.position = testPosition;
			testEmployee.employeeNumber = 123456789;

			setAddress(&testEmployee, testAddress);
			strncpy(verifyAddress, testEmployee.details.address, ADDRESSMAX);

			Assert::AreEqual(verifyAddress, testAddress);
		}


		TEST_METHOD(GetEmployeeAgeAsString_ReturnsMatchingAgeAsString)
		{
			time_t timeNow = time(0);

			bool testPass = true;
			testDob.tm_year = testYear - 1900;
			testDob.tm_mday = testMonth - 1;
			testDob.tm_mday = testDay;
			testDateOfBirth = mktime(&testDob);

			tm* timeNowDMYFormat = localtime(&timeNow);

			int testAge = timeNowDMYFormat->tm_year - (testYear - 1900);
			char testAgeStr[4] = { 0 };
			_itoa(testAge, testAgeStr, 10);

			char verify[4] = { 0 };

			strncpy(testEmployee.details.fName, testFirstName, NAMEMAX);
			strncpy(testEmployee.details.lName, testLastName, NAMEMAX);
			strncpy(testEmployee.details.sinNumber, testSocialIN, SINMAX);
			strncpy(testEmployee.details.address, testAddress, ADDRESSMAX);
			testEmployee.details.dateOfBirth = testDateOfBirth;
			testEmployee.position = testPosition;
			testEmployee.employeeNumber = 123456789;

			getAgeString(&testEmployee, verify);



			Assert::AreEqual(testAgeStr, verify);
		}

		TEST_METHOD(GetEmployeeAgeAsNumber_ReturnsMatchingAgeAsNumber)
		{
			int verify = 0;
			int testAge = 0;
			

			time_t timeNow;
			time_t birthday;

			time(&timeNow);

			struct tm* dobDT = (struct tm*)malloc(sizeof(struct tm));

			dobDT = localtime(&timeNow);

			testAge = dobDT->tm_year - (testYear - 1900);
			dobDT->tm_year = testYear - 1900;
			dobDT->tm_mday = testMonth - 1;
			dobDT->tm_mday = testDay;

		

			birthday = mktime(dobDT);

			strncpy(testEmployee.details.fName, testFirstName, NAMEMAX);
			strncpy(testEmployee.details.lName, testLastName, NAMEMAX);
			strncpy(testEmployee.details.sinNumber, testSocialIN, SINMAX);
			strncpy(testEmployee.details.address, testAddress, ADDRESSMAX);
			testEmployee.details.dateOfBirth = birthday;
			testEmployee.position = testPosition;
			testEmployee.employeeNumber = 123456789;

			verify = getAge(&testEmployee);

			Assert::AreEqual(testAge, verify);
		}

		TEST_METHOD(SetEmployeesLastName_EmployeesLastNameMatches)
		{

			char verify[NAMEMAX] = { 0 };
			char* check = NULL;

			testDob.tm_year = testYear;
			testDob.tm_mday = testMonth;
			testDob.tm_mday = testDay;
			testDateOfBirth = mktime(&testDob);

			strncpy(testEmployee.details.fName, testFirstName, NAMEMAX);

			strncpy(verify, testLastName, NAMEMAX);

			strncpy(testEmployee.details.sinNumber, testSocialIN, SINMAX);
			strncpy(testEmployee.details.address, testAddress, ADDRESSMAX);
			testEmployee.details.dateOfBirth = testDateOfBirth;
			testEmployee.position = testPosition;
			testEmployee.employeeNumber = 123456789;

			setLastName(&testEmployee, testLastName);
			check = testEmployee.details.lName;

			Assert::AreEqual(check, verify);
		}

		TEST_METHOD(SetEmployeesFirstName_EmployeesFirstNameMatches)
		{
			char verify[NAMEMAX] = { 0 };
			char* check = NULL;

			testDob.tm_year = testYear;
			testDob.tm_mday = testMonth;
			testDob.tm_mday = testDay;
			testDateOfBirth = mktime(&testDob);

			strncpy(verify, testFirstName, NAMEMAX);

			strncpy(testEmployee.details.lName, testLastName, NAMEMAX);
			strncpy(testEmployee.details.sinNumber, testSocialIN, SINMAX);
			strncpy(testEmployee.details.address, testAddress, ADDRESSMAX);
			testEmployee.details.dateOfBirth = testDateOfBirth;
			testEmployee.position = testPosition;
			testEmployee.employeeNumber = 123456789;

			setFirstName(&testEmployee, testFirstName);
			check = testEmployee.details.fName;

			Assert::AreEqual(check, verify);
		}

		TEST_METHOD(SetEmployeeInListNode_ListNodeContainsEmployee)
		{
			PNODE list = (PNODE)malloc(sizeof(NODE));
			int testEmployeeID = 0;
			int verify = 0;

			testDob.tm_year = testYear;
			testDob.tm_mday = testMonth;
			testDob.tm_mday = testDay;
			testDateOfBirth = mktime(&testDob);

			strncpy(testEmployee.details.fName, testFirstName, NAMEMAX);
			strncpy(testEmployee.details.lName, testLastName, NAMEMAX);
			strncpy(testEmployee.details.sinNumber, testSocialIN, SINMAX);
			strncpy(testEmployee.details.address, testAddress, ADDRESSMAX);
			testEmployee.details.dateOfBirth = testDateOfBirth;
			testEmployee.position = testPosition;
			testEmployee.employeeNumber = 123456789;

			if (list) {
				*list = { 0 };
				setEmployee(list, &testEmployee);
				testEmployeeID = testEmployee.employeeNumber;
				verify = list->employee->employeeNumber;
			}
			
			Assert::AreEqual(testEmployeeID, verify);

		}

		TEST_METHOD(GetEmployeePersonalInfo_RetrievedInfoMatches)
		{
			PNODE list = (PNODE)malloc(sizeof(NODE));
			PNODE testNode = (PNODE)malloc(sizeof(NODE));
			PERSONAL verify;

			testDob.tm_year = testYear;
			testDob.tm_mday = testMonth;
			testDob.tm_mday = testDay;
			testDateOfBirth = mktime(&testDob);

			strncpy(testEmployee.details.fName, testFirstName, NAMEMAX);
			strncpy(testEmployee.details.lName, testLastName, NAMEMAX);
			strncpy(testEmployee.details.sinNumber, testSocialIN, SINMAX);
			strncpy(testEmployee.details.address, testAddress, ADDRESSMAX);
			testEmployee.details.dateOfBirth = testDateOfBirth;
			testEmployee.position = testPosition;
			testEmployee.employeeNumber = 123456789;

			if (list && testNode) {
				testNode->employee = &testEmployee;
				verify = getPersonalInfo(testNode->employee);
				Assert::AreEqual(testNode->employee->details.address, verify.address);
			}

		}

		TEST_METHOD(SetEmployeePersonalInfo_SetInfoMatches)
		{
			PNODE list = (PNODE)malloc(sizeof(NODE));
			PEMPLOYEE newTestEmployee = (PEMPLOYEE)malloc(sizeof(EMPLOYEE));
			PERSONAL verify;

			testDob.tm_year = testYear;
			testDob.tm_mday = testMonth;
			testDob.tm_mday = testDay;
			testDateOfBirth = mktime(&testDob);

			strncpy(verify.fName, testFirstName, NAMEMAX);
			strncpy(verify.lName, testLastName, NAMEMAX);
			strncpy(verify.sinNumber, testSocialIN, SINMAX);
			strncpy(verify.address, testAddress, ADDRESSMAX);
			verify.dateOfBirth = testDateOfBirth;

			if (list && newTestEmployee) {
				setPersonalInfo(newTestEmployee,verify);
				Assert::AreEqual(newTestEmployee->details.address, verify.address);

			}
			free(newTestEmployee);
		}

		TEST_METHOD(GetEmployeeFromNode_RetrievesEmployyeFromListNode)
		{
			PEMPLOYEE verify = (PEMPLOYEE)malloc(sizeof(EMPLOYEE));
			PNODE testNode = (PNODE)malloc(sizeof(NODE));
			double test = 0;

			testDob.tm_year = testYear;
			testDob.tm_mday = testMonth;
			testDob.tm_mday = testDay;
			testDateOfBirth = mktime(&testDob);

			strncpy(testEmployee.details.fName, testFirstName, NAMEMAX);
			strncpy(testEmployee.details.lName, testLastName, NAMEMAX);
			strncpy(testEmployee.details.sinNumber, testSocialIN, SINMAX);
			strncpy(testEmployee.details.address, testAddress, ADDRESSMAX);
			testEmployee.details.dateOfBirth = testDateOfBirth;
			testEmployee.employeeNumber = 123456789;
			testEmployee.income.wage = testWage;

			if (testNode && verify) {
				testNode->employee = &testEmployee;
				verify = getEmployee(testNode);
				Assert::AreEqual(verify->employeeNumber, testNode->employee->employeeNumber);
			}

		}

		TEST_METHOD(GetEmployeeNumber_RetrievesEmployeeNumberFromEmployee)
		{
			PEMPLOYEE verify = (PEMPLOYEE)malloc(sizeof(EMPLOYEE));
			PNODE testNode = (PNODE)malloc(sizeof(NODE));
			double test = 0;

			testDob.tm_year = testYear;
			testDob.tm_mday = testMonth;
			testDob.tm_mday = testDay;
			testDateOfBirth = mktime(&testDob);

			strncpy(testEmployee.details.fName, testFirstName, NAMEMAX);
			strncpy(testEmployee.details.lName, testLastName, NAMEMAX);
			strncpy(testEmployee.details.sinNumber, testSocialIN, SINMAX);
			strncpy(testEmployee.details.address, testAddress, ADDRESSMAX);
			testEmployee.details.dateOfBirth = testDateOfBirth;
			testEmployee.employeeNumber = 123456789;
			testEmployee.income.wage = testWage;

			if (testNode && verify) {
				testNode->employee = &testEmployee;

				verify = getEmployee(testNode);


				Assert::AreEqual(verify->employeeNumber, testNode->employee->employeeNumber);

			}


		}

		TEST_METHOD(SetEmployeeIncome_SetEmployeeWageMatches)
		{

			testDob.tm_year = testYear;
			testDob.tm_mday = testMonth;
			testDob.tm_mday = testDay;
			testDateOfBirth = mktime(&testDob);

			strncpy(testEmployee.details.fName, testFirstName, NAMEMAX);
			strncpy(testEmployee.details.lName, testLastName, NAMEMAX);
			strncpy(testEmployee.details.sinNumber, testSocialIN, SINMAX);
			strncpy(testEmployee.details.address, testAddress, ADDRESSMAX);
			testEmployee.details.dateOfBirth = testDateOfBirth;
			testEmployee.employeeNumber = 123456789;
			testEmployee.position = WORK;

			setIncome(&testEmployee, testWage);

			Assert::AreEqual(testEmployee.income.wage, testWage);

		}


		TEST_METHOD(SetEmployeeSIN_EmployeeSINMatches)
		{
			PEMPLOYEE verify = (PEMPLOYEE)malloc(sizeof(EMPLOYEE));
			double test = 0;

			testDob.tm_year = testYear;
			testDob.tm_mday = testMonth;
			testDob.tm_mday = testDay;
			testDateOfBirth = mktime(&testDob);

			strncpy(testEmployee.details.fName, testFirstName, NAMEMAX);
			strncpy(testEmployee.details.lName, testLastName, NAMEMAX);
			
			strncpy(testEmployee.details.address, testAddress, ADDRESSMAX);
			testEmployee.details.dateOfBirth = testDateOfBirth;
			testEmployee.employeeNumber = 123456789;

			if (verify) {
				setSin(testSocialIN, verify);


				Assert::AreEqual(verify->details.sinNumber, testSocialIN);
			}
		}

		TEST_METHOD(GetPreviousWeekSchedule_PreviousWeekScheduleReturned)
		{
			bool testPass = true;

			time_t now = time(0);
			tm* dateTimeCurrent = (tm*)malloc(sizeof(tm));
			tm* dateTimePrev = (tm*)malloc(sizeof(tm));
			int day;
			int week;

			time_t punchInPrev;
			time_t punchOutPrev;

			SCHEDULE* test = NULL;
			SCHEDULE* verify = NULL;

			if (dateTimeCurrent && dateTimePrev) {


				dateTimeCurrent = localtime(&now);
				*dateTimePrev = *dateTimeCurrent;

				dateTimePrev->tm_mday = dateTimePrev->tm_mday - 7;
				punchInPrev = mktime(dateTimePrev);
				dateTimePrev->tm_hour = dateTimePrev->tm_hour + 8;
				punchOutPrev = mktime(dateTimePrev);

				testDob.tm_year = testYear;
				testDob.tm_mday = testMonth;
				testDob.tm_mday = testDay;
				testDateOfBirth = mktime(&testDob);

				strncpy(testEmployee.details.fName, testFirstName, NAMEMAX);
				strncpy(testEmployee.details.lName, testLastName, NAMEMAX);
				strncpy(testEmployee.details.sinNumber, testSocialIN, SINMAX);
				strncpy(testEmployee.details.address, testAddress, ADDRESSMAX);
				testEmployee.details.dateOfBirth = testDateOfBirth;
				testEmployee.employeeNumber = 123456789;


				week = (dateTimeCurrent->tm_mday / DAYSINWEEK) - 1;
				day = dateTimeCurrent->tm_mday % DAYSINWEEK;

				if (week >= WEEKSINMONTH) {
					week = 0;
				}

				testEmployee.schedule[day][week].absent = false;
				testEmployee.schedule[day][week].late = false;
				testEmployee.schedule[day][week].working = false;
				testEmployee.schedule[day][week].punchIn = punchInPrev;
				testEmployee.schedule[day][week].punchOut = punchOutPrev;

				test = &testEmployee.schedule[day][week];
				//week+1 sets the index back to current. it was -1 for setting the 'week' to a previous (from current) index
				verify = getPrevWeekSchedule(&testEmployee.schedule[day][week + 1]);

				if ((day + ((week + 1) * DAYSINWEEK)) >= 0) {

					if (test->absent != verify->absent) {
						testPass = false;
					}
					else if (test->late != verify->late) {
						testPass = false;
					}
					else if (test->punchIn != verify->punchIn) {
						testPass = false;
					}
					else if (test->punchOut != verify->punchOut) {
						testPass = false;
					}
					else if (test->working != verify->working) {
						testPass = false;
					}
				}
				else if ((verify == NULL) && (day + ((week + 1) * DAYSINWEEK)) >= 0) {
					testPass = true;
				}
				else {
					testPass = false;
				}
				

				Assert::IsTrue(testPass);
			}
		}

		TEST_METHOD(SetEmployeeSchedule_EmployeesScheduleMatches)
		{
			bool testPass = true;
			SCHEDULE next;

			time_t now = time(0);
			tm* dateTimePrev = (tm*)malloc(sizeof(tm));
			tm* dateTimeCurrent = (tm*)malloc(sizeof(tm));
			tm* dateTimeNext = (tm*)malloc(sizeof(tm));

			time_t punchInPrev;
			time_t punchOutPrev;
			time_t punchInCurrent;
			time_t punchOutCurrent;
			time_t punchInNext;
			time_t punchOutNext;

			SCHEDULE* test;

			if (dateTimeCurrent && dateTimeNext && dateTimePrev) {

				dateTimeCurrent = localtime(&now);

				dateTimeNext->tm_mday = dateTimeCurrent->tm_mday + 1;
				dateTimeNext->tm_year = dateTimeCurrent->tm_year;
				dateTimeNext->tm_mon = dateTimeCurrent->tm_mon;
				dateTimeNext->tm_hour = 8;
				dateTimeNext->tm_min = 0;

				dateTimePrev->tm_mday = dateTimeCurrent->tm_mday - 1;
				dateTimePrev->tm_year = dateTimeCurrent->tm_year;
				dateTimePrev->tm_mon = dateTimeCurrent->tm_mon;
				dateTimePrev->tm_hour = 8;
				dateTimePrev->tm_min = 0;

				dateTimeCurrent->tm_hour = dateTimeCurrent->tm_hour + 2;

				punchInPrev = mktime(dateTimePrev);
				dateTimePrev->tm_hour += 8;
				punchOutPrev = mktime(dateTimePrev);

				punchInCurrent = mktime(dateTimeCurrent);
				dateTimeCurrent->tm_hour += 8;
				punchOutCurrent = mktime(dateTimeCurrent);

				punchInNext = mktime(dateTimeNext);
				dateTimeNext->tm_hour += 8;
				punchOutNext = mktime(dateTimeNext);

				testDob.tm_year = testYear;
				testDob.tm_mday = testMonth;
				testDob.tm_mday = testDay;
				testDateOfBirth = mktime(&testDob);

				strncpy(testEmployee.details.fName, testFirstName, NAMEMAX);
				strncpy(testEmployee.details.lName, testLastName, NAMEMAX);
				strncpy(testEmployee.details.sinNumber, testSocialIN, SINMAX);
				strncpy(testEmployee.details.address, testAddress, ADDRESSMAX);
				testEmployee.details.dateOfBirth = testDateOfBirth;
				testEmployee.employeeNumber = 123456789;
				testEmployee.schedule[0][0].absent = false;
				testEmployee.schedule[0][0].late = false;
				testEmployee.schedule[0][0].working = false;
				testEmployee.schedule[0][0].punchIn = punchInPrev;
				testEmployee.schedule[0][0].punchOut = punchOutPrev;
				testEmployee.schedule[0][1].absent = false;
				testEmployee.schedule[0][1].late = false;
				testEmployee.schedule[0][1].working = false;
				testEmployee.schedule[0][1].punchIn = punchInCurrent;
				testEmployee.schedule[0][1].punchOut = punchOutCurrent;

				next.absent = false;
				next.late = false;
				next.punchIn = punchInNext;
				next.punchOut = punchOutNext;
				next.working = false;

				setSchedule(&testEmployee, next, (dateTimeCurrent->tm_mday % DAYSINWEEK), (dateTimeCurrent->tm_mday / DAYSINWEEK)-1);
				test = &testEmployee.schedule[dateTimeCurrent->tm_mday % DAYSINWEEK][(dateTimeCurrent->tm_mday / DAYSINWEEK) - 1];


				if (test->absent != next.absent) {
					testPass = false;
				}
				else if (test->late != next.late) {
					testPass = false;
				}
				else if (test->punchIn != next.punchIn) {
					testPass = false;
				}
				else if (test->punchOut != next.punchOut) {
					testPass = false;
				}
				else if (test->working != next.working) {
					testPass = false;
				}


				Assert::IsTrue(testPass);
			}

		}

		TEST_METHOD(CreateASchedule_ScheduleDetailsMatch)
		{
			bool testPass = true;
			SCHEDULE test = {};
			SCHEDULE verify = {};
			time_t punchIn;
			time_t punchOut;
			tm* punchInDT = (tm*)malloc(sizeof(tm));
			tm* punchOutDT = (tm*)malloc(sizeof(tm));
			time_t now;
			tm* dateTimeNow = (tm*)malloc(sizeof(tm));

			now = time(0);

			if (punchInDT && punchOutDT && dateTimeNow) {

				dateTimeNow = localtime(&now);

				punchInDT->tm_year = dateTimeNow->tm_year;
				punchInDT->tm_mon = dateTimeNow->tm_mon;
				punchInDT->tm_mday = dateTimeNow->tm_mday;
				punchInDT->tm_hour = dateTimeNow->tm_hour;
				punchInDT->tm_min = dateTimeNow->tm_min;

				punchIn = mktime(punchInDT);

				punchOutDT = punchInDT;
				punchOutDT->tm_hour = punchOutDT->tm_hour + 8;

				punchOut = mktime(punchOutDT);

				test.absent = false;
				test.late = false;
				test.punchIn = punchIn;
				test.punchOut = punchOut;

				verify = createSchedule(punchIn, punchOut);

				if (verify.absent != test.absent) {
					testPass = false;
				}
				else if (verify.late != test.late) {
					testPass = false;
				}
				else if (verify.working != test.working) {
					testPass = false;
				}
				else if (verify.punchIn != test.punchIn) {
					testPass = false;
				}
				else if (verify.punchOut != test.punchOut) {
					testPass = false;
				}

				Assert::IsTrue(testPass);

			}
			
		}

		TEST_METHOD(GetNextWeekSchedule_NextWeekScheduleReturned)
		{
			bool testPass = true;

			time_t now = time(0);
			tm* dateTimeCurrent = (tm*)malloc(sizeof(tm));
			tm* dateTimeNext = (tm*)malloc(sizeof(tm));
			int day = 0;
			int week = 0;

			//time_t punchInPrev;
			//time_t punchOutPrev;
			//time_t punchInCurrent;
			//time_t punchOutCurrent;
			time_t punchInNext;
			time_t punchOutNext;

			SCHEDULE* test = NULL;
			SCHEDULE* verify = NULL;

			if (dateTimeCurrent && dateTimeNext) {


				dateTimeCurrent = localtime(&now);
				*dateTimeNext = *dateTimeCurrent;

				dateTimeNext->tm_mday = dateTimeNext->tm_mday + 7;
				punchInNext = mktime(dateTimeNext);
				dateTimeNext->tm_hour = dateTimeNext->tm_hour + 8;
				punchOutNext = mktime(dateTimeNext);
				
				testDob.tm_year = testYear;
				testDob.tm_mday = testMonth;
				testDob.tm_mday = testDay;
				testDateOfBirth = mktime(&testDob);

				strncpy(testEmployee.details.fName, testFirstName, NAMEMAX);
				strncpy(testEmployee.details.lName, testLastName, NAMEMAX);
				strncpy(testEmployee.details.sinNumber, testSocialIN, SINMAX);
				strncpy(testEmployee.details.address, testAddress, ADDRESSMAX);
				testEmployee.details.dateOfBirth = testDateOfBirth;
				testEmployee.employeeNumber = 123456789;


				week = (dateTimeCurrent->tm_mday / DAYSINWEEK) + 1;
				day = dateTimeCurrent->tm_mday % DAYSINWEEK;

				if (week >= WEEKSINMONTH) {
					week = 3;
				}

				testEmployee.schedule[day][week].absent = false;
				testEmployee.schedule[day][week].late = false;
				testEmployee.schedule[day][week].working = false;
				testEmployee.schedule[day][week].punchIn = punchInNext;
				testEmployee.schedule[day][week].punchOut = punchOutNext;
				

				test = &testEmployee.schedule[day][week];
				verify = getNextWeekSchedule(&testEmployee.schedule[day][week - 1]);
				
				//if day current day count is less than the max value that can be used to get the next schedule (MAX index - 7, to get the schedule 7 days from current)
				if ((day + ((week + 1)*DAYSINWEEK)) < ((WEEKSINMONTH * DAYSINWEEK) - DAYSINWEEK)) {
				

					if (test->absent != verify->absent) {
						testPass = false;
					}
					else if (test->late != verify->late) {
						testPass = false;
					}
					else if (test->punchIn != verify->punchIn) {
						testPass = false;
					}
					else if (test->punchOut != verify->punchOut) {
						testPass = false;
					}
					else if (test->working != verify->working) {
						testPass = false;
					}
					
				}
				else if ((verify == NULL) && (day + ((week + 1) * DAYSINWEEK)) >= ((WEEKSINMONTH * DAYSINWEEK) - DAYSINWEEK)) {
					testPass = true;
				}
				else {
					testPass = false;
				}

				Assert::IsTrue(testPass);
			}
		}

		TEST_METHOD(GetEmployeesSchedule_RetrievedScheduleMatches) {

			bool testPass = true;
			int weeks = 0;
			int days = 0;
			int error = 0;
			time_t now = time(0);
			tm* dateTimeCurrent = (tm*)malloc(sizeof(tm));
			time_t punchInCurrent;
			time_t punchOutCurrent;
			SCHEDULE* test;
			SCHEDULE* verify;

			if (dateTimeCurrent) {

				error = localtime_s(dateTimeCurrent, &now);

				if (error) {

					free(dateTimeCurrent);
					exit(EXIT_FAILURE);
				}
				weeks = (dateTimeCurrent->tm_mday / DAYSINWEEK) - 1;
				days = dateTimeCurrent->tm_mday % DAYSINWEEK;

				punchInCurrent = mktime(dateTimeCurrent);
				dateTimeCurrent->tm_hour = dateTimeCurrent->tm_hour + 8;
				punchOutCurrent = mktime(dateTimeCurrent);

				testDob.tm_year = testYear;
				testDob.tm_mday = testMonth;
				testDob.tm_mday = testDay;
				testDateOfBirth = mktime(&testDob);

				strncpy(testEmployee.details.fName, testFirstName, NAMEMAX);
				strncpy(testEmployee.details.lName, testLastName, NAMEMAX);
				strncpy(testEmployee.details.sinNumber, testSocialIN, SINMAX);
				strncpy(testEmployee.details.address, testAddress, ADDRESSMAX);
				testEmployee.details.dateOfBirth = testDateOfBirth;
				testEmployee.employeeNumber = 123456789;

				testEmployee.schedule[days][weeks].absent = false;
				testEmployee.schedule[days][weeks].late = false;
				testEmployee.schedule[days][weeks].working = false;
				testEmployee.schedule[days][weeks].punchIn = punchInCurrent;
				testEmployee.schedule[days][weeks].punchOut = punchOutCurrent;

				test = getSchedule(&testEmployee);
				verify = &testEmployee.schedule[days][weeks];

				if (test->absent != verify->absent) {
					testPass = false;
				}
				else if (test->late != verify->late) {
					testPass = false;
				}
				else if (test->punchIn != verify->punchIn) {
					testPass = false;
				}
				else if (test->punchOut != verify->punchOut) {
					testPass = false;
				}
				else if (test->working != verify->working) {
					testPass = false;
				}

				Assert::IsTrue(testPass);

			}	
		}

		TEST_METHOD(GetEmployeeIncome) {

			double testIncome = 18.76;
			double verify = 0;

			strncpy(testEmployee.details.fName, testFirstName, NAMEMAX);
			strncpy(testEmployee.details.lName, testLastName, NAMEMAX);
			strncpy(testEmployee.details.sinNumber, testSocialIN, SINMAX);
			strncpy(testEmployee.details.address, testAddress, ADDRESSMAX);
			testEmployee.details.dateOfBirth = testDateOfBirth;
			testEmployee.employeeNumber = 123456789;
			testEmployee.income.wage = testIncome;

			verify = getIncome(&testEmployee);

			Assert::AreEqual(verify, testIncome);
		}

		TEST_METHOD(GetEarningsOfAShift_ReturnsEarningsAsDouble) {

			bool testPass = true;
			int day;
			int week;
			double testIncome;
			double verifyIncome;
			int hourOffset;

			time_t now;
			tm* dateTimeCurrent = (tm*)malloc(sizeof(tm));

			time_t punchInCurrent;
			time_t punchOutCurrent;

			//SCHEDULE* test;
			//SCHEDULE* verify;

			if (dateTimeCurrent) {

				time(&now);
				dateTimeCurrent = localtime(&now);

				punchInCurrent = mktime(dateTimeCurrent);
				hourOffset = dateTimeCurrent->tm_hour;
				dateTimeCurrent->tm_hour = hourOffset + 8;
				punchOutCurrent = mktime(dateTimeCurrent);

				day = dateTimeCurrent->tm_mday % DAYSINWEEK;
				week = dateTimeCurrent->tm_mday / DAYSINWEEK;

				testDob.tm_year = testYear;
				testDob.tm_mday = testMonth;
				testDob.tm_mday = testDay;
				testDateOfBirth = mktime(&testDob);

				strncpy(testEmployee.details.fName, testFirstName, NAMEMAX);
				strncpy(testEmployee.details.lName, testLastName, NAMEMAX);
				strncpy(testEmployee.details.sinNumber, testSocialIN, SINMAX);
				strncpy(testEmployee.details.address, testAddress, ADDRESSMAX);
				testEmployee.details.dateOfBirth = testDateOfBirth;
				testEmployee.position = WORK;
				testEmployee.income.wage = 18.67;
				testEmployee.employeeNumber = 123456789;
				testEmployee.schedule[day][week].absent = false;
				testEmployee.schedule[day][week].late = false;
				testEmployee.schedule[day][week].working = false;
				testEmployee.schedule[day][week].punchIn = punchInCurrent;
				testEmployee.schedule[day][week].punchOut = punchOutCurrent;

				testIncome = getDayEarnings(&testEmployee, week, day);
				verifyIncome = 8 * testEmployee.income.wage;

				Assert::AreEqual(verifyIncome, testIncome);


			}
		}

		TEST_METHOD(SetEmployeeId_EmployeesIDMatches) {


		}

		TEST_METHOD(CreateList_ListWithSingleNULLEmployeeReturned) {


		}

		TEST_METHOD(CreateNode_NewNodeWithSpecifiedEmployeeReturned) {


		}
	};

}
