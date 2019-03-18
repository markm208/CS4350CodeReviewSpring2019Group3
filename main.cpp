#include <iostream> //do not include anything other than this

using namespace std;

//void testCharacteristicAndMantissa();
void shouldConvert(char number[], int expectedCharacteristic, int expectedNumerator, int expectedDenominator);
void shouldNotConvert(char number[]);

void testMath();
void testSubtract();

int main()
{
	//math function tests
	testMath();
    return 0;
}

void shouldConvert(char number[], int expectedCharacteristic, int expectedNumerator, int expectedDenominator)
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
void shouldNotConvert(char number[])
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
	subtract(0, 0, 10, 0, 0, 10, shortArray, SHORT_ARRAY_LENGTH);
	shouldConvert(shortArray, 0, 0, 10);
	subtract(0, 0, 10, 0, 0, 10, mediumArray, MEDIUM_ARRAY_LENGTH);
	shouldConvert(mediumArray, 0, 0, 10);
	subtract(0, 0, 10, 0, 0, 10, largeArray, LARGE_ARRAY_LENGTH);
	shouldConvert(largeArray, 0, 0, 10);

	//2 - 1 = "1"
	subtract(2, 0, 10, 1, 0, 10, shortArray, SHORT_ARRAY_LENGTH);
	shouldConvert(shortArray, 1, 0, 10);
	subtract(2, 0, 10, 1, 0, 10, mediumArray, MEDIUM_ARRAY_LENGTH);
	shouldConvert(mediumArray, 1, 0, 10);
	subtract(2, 0, 10, 1, 0, 10, largeArray, LARGE_ARRAY_LENGTH);
	shouldConvert(largeArray, 1, 0, 10);

	//1 - -1.5 = "2.5"
	subtract(1, 0, 10, -1, 1, 2, shortArray, SHORT_ARRAY_LENGTH);
	shouldConvert(shortArray, 2, 5, 10);
	subtract(1, 0, 10, -1, 1, 2, mediumArray, MEDIUM_ARRAY_LENGTH);
	shouldConvert(mediumArray, 2, 5, 10);
	subtract(1, 0, 10, -1, 1, 2, largeArray, LARGE_ARRAY_LENGTH);
	shouldConvert(largeArray, 2, 5, 10);

	//1.125 - 1.6R = "-.54"
	subtract(1, 1, 8, 1, 2, 3, shortArray, SHORT_ARRAY_LENGTH);
	shouldConvert(shortArray, 0, -54, 100);

	//1.125 - 1.6R = "-.5416666"
	subtract(1, 1, 8, 1, 2, 3, mediumArray, MEDIUM_ARRAY_LENGTH);
	shouldConvert(mediumArray, 0, -5416666, 10000000);

	//1.125 - 1.6R = "-.54166666666666666"
	subtract(1, 1, 8, 1, 2, 3, largeArray, LARGE_ARRAY_LENGTH);
	//can't use the convert function because the num/denom would overflow
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
	bool isNegative = false;//used at the end to add the negative
	int swapVal = 0;
	bool retVal = true;
	//turn the two fractions into improper fractions
    int numOne = c1*d1 + n1;
    int numTwo = c2*d2 + n2;
	int charCounter = 0;
	
    int newD;
	//if we don't have common denominators
    if (d1 != d2)
    {
        numOne = numOne*d2;
        numTwo = numTwo*d1;
        newD = d1*d2;
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
    int characteristic = newNumerator/newD;
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
				result[i - 1] = char('0'+remainder);
				temp = temp / 10;

			}
			charCounter++;
		}
		//determine how many spaces I have left to work with
		digitsLeft = len - (charCounter);
	}
	//create a multiplier digit that we will use later on line 131
	int multiplier = 1;
	temp = digitsLeft;
	while (temp != 0)
	{
		multiplier = multiplier * 10;
		temp--;
	}
	//redo initial calculation
    if ((newNumerator * multiplier)/newD > INT_MAX)
    {
        return false;
    }
	unsigned long mantissa = (newNumerator * multiplier)/newD;
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

	if (isNegative)
	{
		/*I was having trouble with the - sign being overridden
		so I moved this part to the end to make sure that doesn't happen.*/
		result[0] = '-';
	}
	return retVal;
}
