#include <iostream> //do not include anything other than this

using namespace std;

const int ASCII_ZERO = 48;
const int ASCII_NINE = 57;

bool ValidateAndGetMantissaLength(char numString[], int& startOfMantissaPosition, int& length);
bool mantissa(char numString[], int& numerator, int& denominator);
void testCharacteristicAndMantissa();
void shouldConvert(const char number[], int expectedCharacteristic, int expectedNumerator, int expectedDenominator);
void shouldNotConvert(const char number[]);

bool characteristic(const char numString[], int&c);
int TenToThePower(int exponent);
int LastWholeNumIndex(const char numString[], bool& decimal_found);
int LastIntegerFound(const char numString[]);

int main()
{
	//characteristic and mantissa test
	testCharacteristicAndMantissa();
  
	//math function tests
	//testMath();

	return 0;
}

void testCharacteristicAndMantissa()
{
	shouldConvert("123.456", 123, 456, 1000);
	shouldConvert("    123.456", 123, 456, 1000);
	shouldConvert("123.456    ", 123, 456, 1000);
	shouldConvert("    123.456    ", 123, 456, 1000);

	shouldConvert("+123.456", 123, 456, 1000);
	shouldConvert("   +123.456", 123, 456, 1000);
	shouldConvert("+123.456   ", 123, 456, 1000);
	shouldConvert("   +123.456   ", 123, 456, 1000);

	shouldConvert("-123.456", -123, 456, 1000);
	shouldConvert("   -123.456", -123, 456, 1000);
	shouldConvert("-123.456   ", -123, 456, 1000);
	shouldConvert("    -123.456   ", -123, 456, 1000);

	shouldConvert("0.456", 0, 456, 1000);
	shouldConvert("   0.456", 0, 456, 1000);
	shouldConvert("0.456   ", 0, 456, 1000);
	shouldConvert("   0.456   ", 0, 456, 1000);

	shouldConvert("-0.456", 0, -456, 1000);
	shouldConvert("   -0.456", 0, -456, 1000);
	shouldConvert("-0.456   ", 0, -456, 1000);
	shouldConvert("   -0.456   ", 0, -456, 1000);

	shouldConvert(".456", 0, 456, 1000);
	shouldConvert("    .456", 0, 456, 1000);
	shouldConvert(".456   ", 0, 456, 1000);
	shouldConvert("   .456   ", 0, 456, 1000);

	shouldConvert("-.456", 0, -456, 1000);
	shouldConvert("    -.456", 0, -456, 1000);
	shouldConvert("-.456   ", 0, -456, 1000);
	shouldConvert("   -.456   ", 0, -456, 1000);

	shouldConvert("000123.456", 123, 456, 1000);
	shouldConvert("123.45600000", 123, 456, 1000);
	shouldConvert("00000123.45600000", 123, 456, 1000);

	shouldConvert("-000123.456", -123, 456, 1000);
	shouldConvert("-123.45600000", -123, 456, 1000);
	shouldConvert("-00000123.45600000", -123, 456, 1000);

	shouldConvert("123.00000456", 123, 456, 100000000);
	shouldConvert("-123.00000456", -123, 456, 100000000);
}
//--
void shouldConvert(const char number[], int expectedCharacteristic, int expectedNumerator, int expectedDenominator)
{
	int c, n, d;

	//if the conversion from C string to integers can take place
	if (characteristic(number, c) && mantissa(number, n, d))
	{
		if (c == expectedCharacteristic && n == expectedNumerator && d == expectedDenominator)
		{
			//test passes, do not print anything on a successful test
		}
		else
		{
			cout << "Test failed: '" << number << "' "
				<< "was parsed but did not produce the expected results" << endl;


			if (expectedCharacteristic != c)
			{
				cout << "expected characteristic: " << expectedCharacteristic << " "
					<< "actual characteristic: " << c << endl;
			}
			/*
			if (expectedNumerator != n)
			{
				cout << "expected numerator: " << expectedNumerator << " "
					<< "actual numerator: " << n << endl;

			}

			if (expectedDenominator != d)
			{
				cout << "expected denominator: " << expectedDenominator << " "
					<< "actual denominator: " << d << endl;
			}
			*/
		}
	}
	else
	{
		cout << "Test failed: '" << number << "' "
			<< "was NOT parsed when it should have been." << endl;
	}
}
//--
void shouldNotConvert(const char number[])
{
	int c, n, d;

	//if the conversion from C string to integers can take place
	if (characteristic(number, c) && mantissa(number, n, d))
	{
		cout << "Test failed: '" << number << "' "
			<< "was parsed when it should NOT have been." << endl;
	}
}

//This function will go through the numString and check to see if there are any
//invalid chracters, it will store where the mantissa starts in the numString, and
//it will store the length of the mantissa
bool ValidateAndGetMantissaLength(char numString[], int& startOfMantissaPosition, int& mantissaLength, bool& isNegative)
{
    const int decimalVal = '.';

    bool retval = true;

    //We will use current element to keep track of where we are in the numString
    int currentElement = 0;

    //When looking for the mantissa, we only want to store numbers that come after the decimal
    //therefore we will ignore everyting until we find a decimal value
    while(numString[currentElement] != decimalVal)
    {
        if(isNegative == true)
        {
            if(numString[currentElement] == '0')
            {
                isNegative = true;
            }
            else
            {
                isNegative = false;
            }
            
        }

        //If we get to \0 we know there is no matissa in numString so we will set retval to false
        if(numString[currentElement] == '\0')
        {
            retval = false;
            break;
        }
        else if(numString[currentElement] == '-')
        {
            isNegative = true;
        }

        currentElement++;
    }

    //Only enter this if statement if we did find a decimal
    if(!numString[currentElement] == '\0')
    {
        //Need to add one to the index or we will start with the decimal
        currentElement = currentElement + 1;
        startOfMantissaPosition = currentElement;

        //Counter to see how many extra zeros numString may have
        int numOfZeros = 0;

        //This while loop will go through the rest of numString and make sure
        //all the elements are in fact numbers and it will keep track of extra zeros
        while(numString[currentElement] != '\0')
        {
            //Checks to see if the element is 0-9 and if it's not set retval to false for invalid numString
            if((numString[currentElement] < ASCII_ZERO || numString[currentElement] > ASCII_NINE) && numString[currentElement] != ' ')
            {
                retval = false;
                break;
            }
            //If we find a zero we need to keep track of how many zeros we have found to make sure
            //that if it's only zeros at the end we need to cut them off the mantissa
            else if(numString[currentElement] == ASCII_ZERO || numString[currentElement] == ' ')
            {
                numOfZeros++;
            }
            //If we found a number 1-9 reset the zero count
            else
            {
                numOfZeros = 0;
            }

            //continue to next element
            currentElement++;
        }

        //The overal mantissa length will be how long numString is minus the startOfMantissaPosition
        //Also note we add numOfZeros due to the fact we do not want extra zeros to be part of our mantissaLength
        mantissaLength = currentElement - (startOfMantissaPosition + numOfZeros);

		if (mantissaLength >= 13)
		{
			retval = false;
		}
    }
    
    return retval;
}

bool mantissa(char numString[], int& numerator, int& denominator)
{
    bool retval = false;

    //This variable will be passed to numStringCheck to store the initial index of the mantissa
    int startOfMantissaPosition = 0;

    //This variable will be passed to numStringCheck to store the length of the mantissa
    int mantissaLength = 0;

    bool isNegative = false;

    //ValidateAndGetMantissaLength returns whether or not we have a valid numString so we will only
    //build the mantissa if it is valid
    if(ValidateAndGetMantissaLength(numString, startOfMantissaPosition, mantissaLength, isNegative))
    {
        retval = true;

        numerator = 0;
        
        //Denominator is base 10 so we can multiple 1 by 10 however many times to get the correct denominator
        denominator = 1;

        //We will start from the back due to the fact if the mantissa was 321 we build 321 with ints by adding
        //1 + 20 + 300 and we can do that by multiple the numerator by the current denominator
        for(int i = startOfMantissaPosition + mantissaLength - 1; i >= startOfMantissaPosition; i--)
        {
            numerator += (numString[i] - ASCII_ZERO) * denominator;

            //Go up by a base of ten for every element
            denominator = denominator * 10;
        }

        //In case the mantissa is empty, we want the denominator to be 10
        if(denominator == 1)
        {
            denominator = 10;
        }

        if(isNegative == true)
        {
            numerator = numerator * -1;
        }
    }
    else
    {
        numerator = 0;
        denominator = 10;
    }
    

    return retval;
}

//Returns true if all of the characters in an array are digits, +, - or leading spaces. Once a decimal place is found (if there is one), this function will stop checking for proper number syntax and for valid characters.
//If the function returns true, the integer passed in will be updated.
bool characteristic(const char numString[], int& c)
{
	bool still_true = true;
	int whole_num = 0;

	//used to make sure that if there are only mantissa values and a decimal place, the characteristic doesn't return false, but instead returns 0
	bool decimal_found = false;

	int last_digit_pos = LastWholeNumIndex(numString, decimal_found);

	//if there is no decimal found, the for loop will only check until the last digit placement, spaces are allowed after characteristics
	if (!decimal_found)
	{
		last_digit_pos = LastIntegerFound(numString);
	}
	bool positive_value = true;
	bool before_digits = true;

	for (int i = 0; i <= last_digit_pos; i++)
	{
		if (isdigit(numString[i])) //If the character value is a digit, the integer will no longer accept spaces, +, or -, as well as other characters that are not digits as well
		{
			before_digits = false;
			int place_value = TenToThePower(last_digit_pos - i); //Decimal place value for specific char array value

			//char array value being added to whole_num cannot exceed the maximum integer value - also checks if the place value exceeds the INT_MAX in TenToThePower, extra case checked for billions place since 1 & 2 billion can be used
			if (place_value == -1 || (place_value == 1000000000 && (numString[i] - '0') >= 3) || ((numString[i] - '0') * place_value > 2147483647 - whole_num))
			{
				still_true = false;
				break;
			}

			//numString[i] - '0' subtracts the ASCII value of 0 from the numString[i] digit to get the int value
			whole_num += (numString[i] - '0') * place_value; //adds to the whole number and adds the character array value at its correct place value, ex: 1234 would add 1000, 200, 30, and then 4.
		}
		else if ((numString[i] == '+' || numString[i] == ' ') && before_digits) //accepts + or leading spaces before the integer begins
		{
			continue;
		}
		else if (numString[i] == '-' && before_digits) //accepts - before integer begins, set integer to negative after loop
		{
			positive_value = false;
		}
		else
		{
			still_true = false;
			break;
		}
	}

	if (!decimal_found && before_digits) //checks if only spaces, +, -, or nothing was added to the char array
		still_true = false;

	if (!positive_value && still_true) //Changes integer to a negative if there was a minus symbol, made outside of loop to avoid changing whole number value when creating the whole number
		whole_num = whole_num * (-1);

	if (still_true)
		c = whole_num;

	return still_true;
}

//Finds the decimal place in the character array if there is one and returns the position right before the decimal. Used to only find the whole number integer values
int LastWholeNumIndex(const char numString[], bool& decimal_found)
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

//Added another function so that spaces could be included after the characteristic, when first reading through the assignment, I thought that would be invalid.
int LastIntegerFound(const char numString[])
{
	int pos = 0;
	bool before_digits = true;
	for (pos; numString[pos] != '\0'; pos++)
	{
		if (isdigit(numString[pos]))
		{
			before_digits = false;
		}
		else if (!isdigit(numString[pos]) && before_digits)
		{
			continue;
		}
		else if (!isdigit(numString[pos] && !before_digits))
		{
			break;
		}
	}
	return pos - 1;
}

//Works similar to the pow function, but only returns 10 to the power of the parameter (used for place values)
int TenToThePower(int exponent)
{
	if (exponent < 0)
		return -1;

	int result = 1;
	for (int i = 0; i < exponent; i++)
	{
		if (2147483647 / 10 < result)
			return -1;
		result *= 10;
	}

	return result;
}