#define _CRT_SECURE_NO_WARNINGS

#include "UserInput.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/// <summary>
/// getCharInput receives userInput limited between 'a' and a max character.
/// </summary>
/// <param name="max"></param>
/// <returns>userInput</returns>
char getCharInput(char max)
{
	char userInput;

	do {
		printf("Please enter a menu entry between a and %c:", max);
		do {
			userInput = getchar();
		} while (userInput == '\n');
		

		fseek(stdin, 0, SEEK_END);
	} while (userInput > max);

	

	return userInput;
}

/// <summary>
/// getString takes a passed in pointer to a userInput string and receives user input for any string type.
/// </summary>
/// <param name="userInput"></param>
void getString(char* userInput, int max_size)
{
	bool valid = true;

	do {
		if (fgets(userInput, max_size - 1, stdin) == NULL) {
			printf("Invalid input, please retry: ");
			valid = false;
		}
		else
			valid = true;


		fseek(stdin, 0, SEEK_END);

	} while (!valid);
}

/// <summary>
/// getInteger gets user input as an integer between a min and a max parameter.
/// </summary>
/// <param name="min"></param>
/// <param name="max"></param>
/// <returns></returns>
int getInteger(int min, int max)
{
	int userInput;
	bool valid = true;

	do {
		if (scanf("%d", &userInput) != 1 || userInput < min || userInput > max) {
			printf("Invalid input, please retry: ");
			valid = false;
		}
		else
			valid = true;

		fseek(stdin, 0, SEEK_END);

	} while (!valid);

	return userInput;
}

/// <summary>
/// getDigitLimitedString receives a # of digits as a parameter and gets user input as a string, limiting it to the number of specifed
/// digits. It then returns a string holding the digit limited string.
/// </summary>
/// <param name="digits"></param>
/// <returns></returns>
void getDigitLimitedString(char* userInput, int digits)
{
	//bool valid;
	//int i;
	//valid = true;

	//do {
	//	valid = true;

	//
	//	i = scanf_s("%s", *userInput, digits);
	//	if (i != 1) {
	//		printf("Invalid input, please retry.\n");
	//		valid = false;
	//	}

	//	fseek(stdin, 0, SEEK_END);

	//	if (valid == true) {
	//		int length = (int)strlen(userInput);

	//		//check length
	//		if (length != digits)
	//			valid = false;
	//		else
	//			valid = true;

	//		//check for non-digits
	//		for (int i = 0; i < length; i++) {
	//			if (!isdigit(userInput[i]))
	//				valid = false;
	//		}

	//	}

	//} while (!valid);

	
}

/// <summary>
/// getDouble gets user input as an double between a min and a max parameter.
/// </summary>
/// <param name="min"></param>
/// <param name="max"></param>
/// <returns></returns>
double getDouble(double min, double max)
{
	double userInput;
	bool valid;

	do {

		fseek(stdin, 0, SEEK_END);

		if (scanf("%lf", &userInput) != 1 || userInput < min || userInput > max) {
			printf("Invalid input, please retry.\n");
			valid = false;
		}
		else
			valid = true;

	} while (!valid);

	return userInput;
}

void removeNewLine(char* strn)
{
	for (int i = 0; i < (int)strlen(strn); i++) {
		if (strn[i] == '\n')
			strn[i] = '\0';
	}
}
