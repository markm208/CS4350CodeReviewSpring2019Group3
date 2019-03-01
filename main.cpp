#include <iostream> //do not include anything other than this

using namespace std;

bool characteristic(char numString[], int&c);
int TenToThePower(int length);
int LastWholeNumIndex(char numString[], bool& decimal_found);

int main()
{
	//Returns true, integer is updated
	char number[] = "123.456";
	int c = 0;
	cout << "True or Not: " << boolalpha << characteristic(number, c) << endl;
	cout << "C value: " << c << endl << endl;
	
	//The rest of char arrays are used for tests and will be deleted upon merge

	//Returns false, integer does not update
	char number2[] = "E12773.456";
	cout << "True or Not: " << boolalpha << characteristic(number2, c) << endl;
	cout << "C value: " << c << endl << endl;

	//Returns true, integer is updated
	char number3[] = "     -1323.456";
	cout << "True or Not: " << boolalpha << characteristic(number3, c) << endl;
	cout << "C value: " << c << endl << endl;

	//Returns false, integer does not update
	char number4[] = "1E23.456";
	cout << "True or Not: " << boolalpha << characteristic(number4, c) << endl;
	cout << "C value: " << c << endl << endl;

	//Returns true, integer is updated
	char number5[] = ".456";
	cout << "True or Not: " << boolalpha << characteristic(number5, c) << endl;
	cout << "C value: " << c << endl << endl;

	//Returns false, integer does not update because integer is too big
	char number6[] = "1111111111111111.456";
	cout << "True or Not: " << boolalpha << characteristic(number6, c) << endl;
	cout << "C value: " << c << endl << endl;

	return 0;
}

//Returns a boolean value if the value in the integer is changed or not, only the characteristic or whole number of the char array is added to c
bool characteristic(char numString[], int& c)
{
	int whole_num = 0;
	bool decimal_found = false; //used to make sure that if there are only mantissa values and a decimal place, the characteristic doesn't return false, but instead returns 0
	int last_digit_pos = LastWholeNumIndex(numString, decimal_found);
	bool positive_value = true;
	bool before_digits = true;

	for (int i = 0; i <= last_digit_pos; i++)
	{
		if (isdigit(numString[i])) //If the character value is a digit, the integer will no longer accept spaces, +, or -, as well as other characters that are not digits as well
		{
			before_digits = false;
			int place_value = TenToThePower(last_digit_pos - i); //Decimal place value for specific char array value

			if ( ((numString[i] - '0') * place_value > INT_MAX - whole_num) || place_value == -1) //char array value being added to whole_num cannot exceed the maximum integer value
			{
				return false;
			}

			//numString[i] - '0' subtracts the ASCII value of 0 from the numString[i] digit to get the int value
			whole_num += (numString[i] - '0') * place_value; //adds to the whole number and adds the character array value at its correct place value, ex: 1234 would add 1000, 200, 30, and then 4.
		}
		else if ((numString[i] == '+' || numString[i] == ' ') && before_digits) //accepts + or leading spaces before the integer begins
		{
			continue;
		}
		else if (numString[i] == '-' && before_digits) //accepts - before integer begins, set integer to negative after loop - What does the customer want to happen for double negative cases? Does --x make it a positive, or does it stay negative?
		{
			positive_value = false;
		}
		else
		{
			return false;
		}
	}

	if (!decimal_found && before_digits) //checks if only spaces, +, -, or nothing was adding to the char array
		return false;

	if (!positive_value) //Changes integer to a negative if there was a minus symbol, made outside of loop to avoid changing whole number value when creating the whole number
		whole_num = whole_num *(-1);

	c = whole_num;

	return true;
}

//Finds the decimal place in the character array if there is one and returns the position right before the decimal. Used to only find the whole number integer values
int LastWholeNumIndex(char numString[], bool& decimal_found)
{
	int pos = 0;

	for (pos; numString[pos] != '\0'; pos++)
	{
		if (numString[pos] == '.')
		{
			decimal_found = true;
			break;
		}
	}

	return pos - 1; 
}

//Works similar to the pow function, but only returns 10 to the power of the parameter (used for place values)
int TenToThePower(int exp)
{
	if (exp < 0)
		return -1;

	int result = 1;
	for (int i = 0; i < exp; i++)
		result *= 10;

	return result;
}