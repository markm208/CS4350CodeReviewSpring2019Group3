#include <iostream> //do not include anything other than this

using namespace std;

bool multiply(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len);
bool checkOverflowMult(int num1, int num2);
bool checkOverflowAdd(int num1, int num2);

void testCharacteristicAndMantissa();
void shouldConvert(char number[], int expectedCharacteristic, int expectedNumerator, int expectedDenominator);
void shouldNotConvert(char number[]);

void testMath();
void testAdd();
void testSubtract();
void testMultiply();
void testDivide();

int main()
{
	//characteristic and mantissa test
	testCharacteristicAndMantissa();
	
	//math function tests
	testMath();

    return 0;
}

//--
void shouldConvert(char number[], int expectedCharacteristic, int expectedNumerator, int expectedDenominator)
{
	int c, n, d;

	cout << "Test failed: '" << number << "' "
			<< "was NOT parsed when it should have been." << endl;
}
//--
void shouldNotConvert(char number[])
{
	int c, n, d;
}
//--
void testMath()
{
	//add
	testAdd();
	testSubtract();
	testMultiply();
	testDivide();
}
//--
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

// multiply returns a boolean: true if the provided numbers can by multiplied and false if they cannot.
bool multiply(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len)
{
	// Convert numbers into just numerator and denominator and multiply to get multiplication answer

	// denominator can never be zero
	if (d1 == 0 || d2==0)
	{
		return false;
	}

	// Make sure fractions aren't negative
	if ((n1 < 0 && d1 > 0) || (n2 < 0 &&  d2 > 0) || (n1 > 0 && d1 < 0) || (n2 > 0 && d2 < 0))
	{
		return false;
	}

	if((c1 == 0 && n1 == 0) || (c2 == 0 && n2 == 0))
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
	if(c1 < 0 && c2 < 0)
	{
		c1*=-1;
		c2*=-1;
	}
	// If one of them is negative the result is negative.
	else if(c1 < 0 || c2 < 0)
	{
		c1 = abs(c1);
		c2 = abs(c2);
		result[pos] = '-';
		pos++;
	}

	int numerator1 = c1*d1 + n1;
	int numerator2 = c2*d2 + n2;
	// checking if overflow for numerator1*numerator2
	if (checkOverflowMult(numerator1, numerator2) == true)
	{
		return false;
	}
	int n = numerator1*numerator2;
	int d = d1*d2;

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
	for (unsigned int i = 0; i < characteristicNumberDigits; i++) {
		int nextDigit = characteristic / magnitudeCharacteristic;
		// The character '0' is represented as an ASCII number and 
		//  adding the nextDigit to '0' increases the ASCII number so 1 becomes '1', 2 becomes '2', etc.
		result[pos] = nextDigit + '0';
		pos++;
		characteristic -= (nextDigit*magnitudeCharacteristic);
		magnitudeCharacteristic /= 10;
	}



	// FIND DIGITS IN DECIMAL PLACE

	int remaining = n%d;
	// If there is a decimal place...
	if (remaining != 0)
	{
		// Place decimal point as character into result
		result[pos] = '.';
		pos++;

		// If there is no remaining then there is nothing left for the decimal place except zeros
		while(remaining != 0)
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
	if(INT_MAX - abs(num1) < abs(num2))
	{
		retVal = true;
	}
	return retVal;
}
