#include <iostream> //do not include anything other than this

using namespace std;

bool multiply(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len);
bool subtract(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len);
bool checkOverflowMult(int num1, int num2);
bool checkOverflowAdd(int num1, int num2);

const int ASCII_ZERO = 48;
const int ASCII_NINE = 57;

bool ValidateAndGetMantissaLength(char numString[], int& startOfMantissaPosition, int& mantissaLength, bool& isNegative);
bool mantissa(const char numString[], int& numerator, int& denominator);
void testCharacteristicAndMantissa();
void shouldConvert(const char number[], int expectedCharacteristic, int expectedNumerator, int expectedDenominator);
void shouldNotConvert(const char number[]);

bool characteristic(const char numString[], int&c);
int TenToThePower(int exponent);
int LastWholeNumIndex(const char numString[], bool& decimal_found);
int LastIntegerFound(const char numString[]);

void testSubtract();
void testMath();
void testMultiply();

int main()
{
	//characteristic and mantissa test
	testCharacteristicAndMantissa();

	//math function tests
	testMath();

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

	shouldConvert("123456", 123456, 0, 10);
	shouldConvert("   123456", 123456, 0, 10);
	shouldConvert("123456   ", 123456, 0, 10);
	shouldConvert("   123456   ", 123456, 0, 10);

	shouldConvert("-123456", -123456, 0, 10);
	shouldConvert("   -123456", -123456, 0, 10);
	shouldConvert("-123456   ", -123456, 0, 10);
	shouldConvert("   -123456   ", -123456, 0, 10);

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

//--
void testMath()
{
	//add
	testMultiply();
	testSubtract();
}
//--

//--
void testSubtract()
{
	const int SHORT_ARRAY_LENGTH = 5;
	char shortArray[SHORT_ARRAY_LENGTH];

	const int MEDIUM_ARRAY_LENGTH = 10;
	char mediumArray[MEDIUM_ARRAY_LENGTH];

	const int LARGE_ARRAY_LENGTH = 20;
	char largeArray[LARGE_ARRAY_LENGTH];

	//should not be enough space in the array for the result
	if (subtract(INT_MIN, 0, 10, INT_MAX, 0, 10, shortArray, SHORT_ARRAY_LENGTH))
	{
		cout << "Error: not enough space in array" << endl;
	}

	//0 - 0 = "0"
	/*subtract(0, 0, 10, 0, 0, 10, shortArray, SHORT_ARRAY_LENGTH);
	shouldConvert(shortArray, 0, 0, 10);
	subtract(0, 0, 10, 0, 0, 10, mediumArray, MEDIUM_ARRAY_LENGTH);
	shouldConvert(mediumArray, 0, 0, 10);
	subtract(0, 0, 10, 0, 0, 10, largeArray, LARGE_ARRAY_LENGTH);
	shouldConvert(largeArray, 0, 0, 10);*/

	////2 - 1 = "1"
	subtract(2, 0, 10, 1, 0, 10, shortArray, SHORT_ARRAY_LENGTH);
	shouldConvert(shortArray, 1, 0, 10);
	subtract(2, 0, 10, 1, 0, 10, mediumArray, MEDIUM_ARRAY_LENGTH);
	shouldConvert(mediumArray, 1, 0, 10);
	subtract(2, 0, 10, 1, 0, 10, largeArray, LARGE_ARRAY_LENGTH);
	shouldConvert(largeArray, 1, 0, 10);

	////1 - -1.5 = "2.5"
	subtract(1, 0, 10, -1, 1, 2, shortArray, SHORT_ARRAY_LENGTH);
	shouldConvert(shortArray, 2, 5, 10);
	subtract(1, 0, 10, -1, 1, 2, mediumArray, MEDIUM_ARRAY_LENGTH);
	shouldConvert(mediumArray, 2, 5, 10);
	subtract(1, 0, 10, -1, 1, 2, largeArray, LARGE_ARRAY_LENGTH);
	shouldConvert(largeArray, 2, 5, 10);

	////1.125 - 1.6R = "-.54"
	subtract(1, 1, 8, 1, 2, 3, shortArray, SHORT_ARRAY_LENGTH);
	shouldConvert(shortArray, 0, -54, 100);

	////1.125 - 1.6R = "-.5416666"
	subtract(1, 1, 8, 1, 2, 3, mediumArray, MEDIUM_ARRAY_LENGTH);
	shouldConvert(mediumArray, 0, -5416666, 10000000);

	////1.125 - 1.6R = "-.54166666666666666"
	subtract(1, 1, 8, 1, 2, 3, largeArray, LARGE_ARRAY_LENGTH);
	////can't use the convert function because the num/denom would overflow
	char expectedResult[] = "-.54166666666666666";
	for (int i = 0; i < LARGE_ARRAY_LENGTH; i++)
	{
		if (expectedResult[i] != largeArray[i])
		{
			cout << "Error: mismatch in C strings in subtract()." << endl
				<< "Expected: " << expectedResult << " "
				<< "Actual: " << largeArray
				<< endl;
		}
	}
}
//--



//new functions go here
bool subtract(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len)
{
	if (c1 >= INT_MAX)
	{
		return false;
	}
	if (c1 <= INT_MIN)
	{
		return false;
	}
	bool isNegative = false;//used at the end to add the negative
	int swapVal = 0;
	bool retVal = true;
	//turn the two fractions into improper fractions
	int numOne = c1 * d1 + n1;
	int numTwo = c2 * d2 + n2;
	int charCounter = 0;

	int newD;
	//if we don't have common denominators
	if (d1 != d2)
	{
		numOne = numOne * d2;
		numTwo = numTwo * d1;
		newD = d1 * d2;
	}
	else
	{
		newD = d1;
	}
	//if the result is going to be negative, switch the values and will tack on a negative sign later
	if (numTwo > numOne)
	{
		swapVal = numTwo;
		numTwo = numOne;
		numOne = swapVal;
		swapVal = d1;
		d1 = d2;
		d2 = swapVal;

		isNegative = true;
		charCounter++;
	}


	int newNumerator = numOne - numTwo;
	int characteristic = newNumerator / newD;
	if (characteristic > INT_MAX)
	{
		return false;
	}
	//figure out how many digits the characteristic has
	int temp = characteristic;
	int digitsLeft;
	while (temp != 0)
	{
		charCounter++;
		temp = temp / 10;
	}
	if (charCounter + 2 > len)//check if the array can at least hold the characteristic
	{
		return false;
	}
	else
	{
		temp = characteristic;
		//special case if the characteristic is zero
		if (charCounter == 0)
		{
			result[charCounter] = '0';
			result[charCounter + 1] = '.';
			charCounter += 2;
		}
		//the first thing thats being added is the '.'  could have been done later
		else
		{
			result[charCounter] = '.';

			//add the characteristic digits to the array
			for (int i = charCounter; i > 0; i--)
			{
				int remainder = temp % 10;
				result[i - 1] = char('0' + remainder);
				temp = temp / 10;

			}
			charCounter++;
		}
		//determine how many spaces I have left to work with
		digitsLeft = len - (charCounter);
	}
	//create a multiplier digit that we will use later on line 326
	int multiplier = 1;
	temp = digitsLeft;
	while (temp != 0)
	{
		multiplier = multiplier * 10;
		temp--;
	}
	//redo initial calculation
	if ((newNumerator * multiplier) / newD > INT_MAX)
	{
		return false;
	}
	unsigned long mantissa = (newNumerator * multiplier) / newD;
	/*The above live is the same calculation we did earlier, except the decimal is moved over to
	include the right amount of decimal characters.  It is treated as a whole number, but we know that the
	extra digits are our missing decimal numbers*/

	unsigned long mantissaTemp = mantissa;
	//adds the rest of the digits to the array
	for (int i = 0; i < len - charCounter; i++)
	{
		//gets the right-most digit of our new mantissa integer
		int remainder = mantissaTemp % 10;
		//adds a digit - starting at the end and moving to the left 
		result[len - i - 1] = char('0' + remainder);
		mantissaTemp = mantissaTemp / 10;
	}
	result[len] = char('\0');

	if (isNegative)
	{
		/*I was having trouble with the - sign being overridden
		so I moved this part to the end to make sure that doesn't happen.*/
		result[0] = '-';
	}
	return retVal;
}

void testMultiply()
{
	const int SHORT_ARRAY_LENGTH = 5;
	char shortArray[SHORT_ARRAY_LENGTH];

	const int MEDIUM_ARRAY_LENGTH = 10;
	char mediumArray[MEDIUM_ARRAY_LENGTH];

	const int LARGE_ARRAY_LENGTH = 20;
	char largeArray[LARGE_ARRAY_LENGTH];

	//should not be enough space in the array for the result
	if (multiply(INT_MAX, 0, 10, INT_MAX, 0, 10, shortArray, SHORT_ARRAY_LENGTH))
	{
		cout << "Error: not enough space in array" << endl;
	}

	//0 * 0 = "0"
	multiply(0, 0, 10, 0, 0, 10, shortArray, SHORT_ARRAY_LENGTH);
	shouldConvert(shortArray, 0, 0, 10);
	multiply(0, 0, 10, 0, 0, 10, mediumArray, MEDIUM_ARRAY_LENGTH);
	shouldConvert(mediumArray, 0, 0, 10);
	multiply(0, 0, 10, 0, 0, 10, largeArray, LARGE_ARRAY_LENGTH);
	shouldConvert(largeArray, 0, 0, 10);

	//3 * 2 = "6"
	multiply(3, 0, 10, 2, 0, 10, shortArray, SHORT_ARRAY_LENGTH);
	shouldConvert(shortArray, 6, 0, 10);
	multiply(3, 0, 10, 2, 0, 10, mediumArray, MEDIUM_ARRAY_LENGTH);
	shouldConvert(mediumArray, 6, 0, 10);
	multiply(3, 0, 10, 2, 0, 10, largeArray, LARGE_ARRAY_LENGTH);
	shouldConvert(largeArray, 6, 0, 10);

	//3 * -1.5 = "-4.5"
	multiply(3, 0, 10, -1, 1, 2, shortArray, SHORT_ARRAY_LENGTH);
	shouldConvert(shortArray, -4, 5, 10);
	multiply(3, 0, 10, -1, 1, 2, mediumArray, MEDIUM_ARRAY_LENGTH);
	shouldConvert(mediumArray, -4, 5, 10);
	multiply(3, 0, 10, -1, 1, 2, largeArray, LARGE_ARRAY_LENGTH);
	shouldConvert(largeArray, -4, 5, 10);

	//1.125 * 1.6R = "1.87"
	multiply(1, 1, 8, 1, 2, 3, shortArray, SHORT_ARRAY_LENGTH);
	shouldConvert(shortArray, 1, 87, 100);

	//1.125 * 1.6R = "1.875"
	multiply(1, 1, 8, 1, 2, 3, mediumArray, MEDIUM_ARRAY_LENGTH);
	shouldConvert(mediumArray, 1, 875, 1000);

	//1.125 * 1.6R = "1.875"
	multiply(1, 1, 8, 1, 2, 3, largeArray, LARGE_ARRAY_LENGTH);
	shouldConvert(largeArray, 1, 875, 1000);
}

//This function will go through the numString and check to see if there are any
//invalid chracters, it will store where the mantissa starts in the numString, and
//it will store the length of the mantissa
bool ValidateAndGetMantissaLength(const char numString[], int& startOfMantissaPosition, int& mantissaLength, bool& isNegative)
{
	const int decimalVal = '.';

	bool retval = true;

	//We will use current element to keep track of where we are in the numString
	int currentElement = 0;

	//When looking for the mantissa, we only want to store numbers that come after the decimal
	//therefore we will ignore everyting until we find a decimal value
	while (numString[currentElement] != decimalVal)
	{
		if (isNegative == true)
		{
			if (numString[currentElement] == '0')
			{
				isNegative = true;
			}
			else
			{
				isNegative = false;
			}

		}

		//If we get to \0 we know there is no matissa in numString so we will set retval to false
		if (numString[currentElement] == '\0')
		{
			retval = true;
			break;
		}
		else if (numString[currentElement] == '-')
		{
			isNegative = true;
		}

		currentElement++;
	}

	//Only enter this if statement if we did find a decimal
	if (!numString[currentElement] == '\0')
	{
		//Need to add one to the index or we will start with the decimal
		currentElement = currentElement + 1;
		startOfMantissaPosition = currentElement;

		//Counter to see how many extra zeros numString may have
		int numOfZeros = 0;

		//This while loop will go through the rest of numString and make sure
		//all the elements are in fact numbers and it will keep track of extra zeros
		while (numString[currentElement] != '\0')
		{
			//Checks to see if the element is 0-9 and if it's not set retval to false for invalid numString
			if ((numString[currentElement] < ASCII_ZERO || numString[currentElement] > ASCII_NINE) && numString[currentElement] != ' ')
			{
				retval = false;
				break;
			}
			//If we find a zero we need to keep track of how many zeros we have found to make sure
			//that if it's only zeros at the end we need to cut them off the mantissa
			else if (numString[currentElement] == ASCII_ZERO || numString[currentElement] == ' ')
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

bool mantissa(const char numString[], int& numerator, int& denominator)
{
	bool retval = false;

	//This variable will be passed to numStringCheck to store the initial index of the mantissa
	int startOfMantissaPosition = 0;

	//This variable will be passed to numStringCheck to store the length of the mantissa
	int mantissaLength = 0;

	bool isNegative = false;

	//ValidateAndGetMantissaLength returns whether or not we have a valid numString so we will only
	//build the mantissa if it is valid
	if (ValidateAndGetMantissaLength(numString, startOfMantissaPosition, mantissaLength, isNegative))
	{
		retval = true;

		numerator = 0;

		//Denominator is base 10 so we can multiple 1 by 10 however many times to get the correct denominator
		denominator = 1;

		//We will start from the back due to the fact if the mantissa was 321 we build 321 with ints by adding
		//1 + 20 + 300 and we can do that by multiple the numerator by the current denominator
		for (int i = startOfMantissaPosition + mantissaLength - 1; i >= startOfMantissaPosition; i--)
		{
			numerator += (numString[i] - ASCII_ZERO) * denominator;

			//Go up by a base of ten for every element
			denominator = denominator * 10;
		}

		//In case the mantissa is empty, we want the denominator to be 10
		if (denominator == 1)
		{
			denominator = 10;
		}

		if (isNegative == true)
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

// multiply returns a boolean: true if the provided numbers can by multiplied and false if they cannot.
bool multiply(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len)
{
	len -= 1;
	// Convert numbers into just numerator and denominator and multiply to get multiplication answer

	// denominator can never be zero
	if (d1 == 0 || d2 == 0)
	{
		return false;
	}

	// Make sure fractions aren't negative
	if ((n1 < 0 && d1 > 0) || (n2 < 0 && d2 > 0) || (n1 > 0 && d1 < 0) || (n2 > 0 && d2 < 0))
	{
		return false;
	}

	if ((c1 == 0 && n1 == 0) || (c2 == 0 && n2 == 0))
	{
		result[0] = '0';
		result[1] = '\0';
		return true;
	}

	// checking if overflow for c1*d1, c2*d2, d1*d2, c1*d1+n1, and c2*d2+n2
	if (checkOverflowMult(c1, d1) == true || checkOverflowMult(c2, d2) == true || checkOverflowMult(d1, d2) == true || checkOverflowAdd(c1*d1, n1) == true || checkOverflowAdd(c2*d2, n2) == true)
	{
		return false;
	}

	int pos = 0;

	// If both are negative the negative cancels and the result is positive.
	if (c1 < 0 && c2 < 0)
	{
		c1 *= -1;
		c2 *= -1;
	}
	// If one of them is negative the result is negative.
	else if (c1 < 0 || c2 < 0)
	{
		c1 = abs(c1);
		c2 = abs(c2);
		result[pos] = '-';
		pos++;
	}

	int numerator1 = c1 * d1 + n1;
	int numerator2 = c2 * d2 + n2;
	// checking if overflow for numerator1*numerator2
	if (checkOverflowMult(numerator1, numerator2) == true)
	{
		return false;
	}
	int n = numerator1 * numerator2;
	int d = d1 * d2;

	// At this point n/d would be the correct answer except the decimal place would be lost because they are integers

	// Because n and d are integers, n divided by d will truncate and provide only the characteristic
	int characteristic = n / d;



	// MOVE CHARACTERISITIC INTO RESULT (CHAR ARRAY)

	// Find length of characterisitc (number of digits in characteristic)
	int characteristicNumberDigits = 0;
	int magnitudeCharacteristic = 1;
	while (characteristic / magnitudeCharacteristic != 0)
	{
		magnitudeCharacteristic *= 10;
		characteristicNumberDigits += 1;
	}
	// The magnitude at this point is 10 times larger
	// Dividing by 10 will get the magnitude of the characteristic
	magnitudeCharacteristic /= 10;

	// Characteristic is too large for given array
	if (characteristicNumberDigits > len)
	{
		return false;
	}

	// Put digits from characteristics into result
	for (int i = 0; i < characteristicNumberDigits; i++) {
		int nextDigit = characteristic / magnitudeCharacteristic;
		// The character '0' is represented as an ASCII number and 
		//  adding the nextDigit to '0' increases the ASCII number so 1 becomes '1', 2 becomes '2', etc.
		result[pos] = nextDigit + '0';
		pos++;
		characteristic -= (nextDigit*magnitudeCharacteristic);
		magnitudeCharacteristic /= 10;
	}



	// FIND DIGITS IN DECIMAL PLACE

	int remaining = n % d;
	// If there is a decimal place...
	if (remaining != 0)
	{
		// Place decimal point as character into result
		result[pos] = '.';
		pos++;

		// If there is no remaining then there is nothing left for the decimal place except zeros
		while (remaining != 0)
		{
			// To access the next decimal point I multiply the numerator by ten then divide by d
			// Because numerator and d are integers it will only provide the characteristic
			remaining *= 10;
			result[pos] = remaining / d + '0';
			pos++;
			// By replacing the numerator with numerator%d it removes the characteristic
			remaining %= d;

			// If the numerator at this point is equal to 0 the decimal point has ended.
			if (pos == len)
			{
				// Can't have string end only at end of array because
				//  there would be garbage after the product before the string ends
				break;
			}
		}
	}
	// Can't have string end only at end of array because
	//  there would be garbage after the product before the string ends
	result[pos] = '\0';
	pos++;

	return true;
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


bool checkOverflowMult(int num1, int num2)
{
	bool retVal = false;
	if (num1 != 0 && abs(INT_MAX / num1) <= abs(num2))
	{
		retVal = true;
	}
	return retVal;
}

bool checkOverflowAdd(int num1, int num2)
{
	bool retVal = false;
	if (INT_MAX - abs(num1) < abs(num2))
	{
		retVal = true;
	}
	return retVal;
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
