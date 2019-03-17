#include <iostream> //do not include anything other than this

using namespace std;

bool multiply(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len);
bool checkOverflowMult(int num1, int num2);
bool checkOverflowAdd(int num1, int num2);
bool testMultiply();


int main()
{
    if(testMultiply())
    {
        cout << 'y' << endl;
    }
    else
    {
        cout << 'n' << endl;
    }
    
    return 0;
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

bool testMultiply() {
	cout << "Start Testing" << endl;
	char result[13];

	// These values should all work
	// Characteristics: -10 through 10
	// Numerators: 0 through 10
	// Denominators: 1 through 10
	for (int c1 = -10; c1 < 11; c1++)
	{
		for (int c2 = -10; c2 < 11; c2++)
		{
			for (int n1 = 0; n1 < 11; n1++)
			{
				for (int n2 = 0; n2 < 11; n2++)
				{
					for (int d1 = 1; d1 < 11; d1++)
					{
						for (int d2 = 1; d2 < 11; d2++)
						{
							if (multiply(c1, n1, d1, c2, n2, d2, result, 12) == false)
							{
								return false;
							}
						}
					}
				}
			}
		}
	}

	// These should all pass (negative / negative = positive)
	// Characteristics: constant
	// Numerators: -10 through -1
	// Denominators: -10 through -1
	for (int n1 = -10; n1 < 0; n1++)
	{
		for (int n2 = -10; n2 < 0; n2++)
		{
			for (int d1 = -10; d1 < 0; d1++)
			{
				for (int d2 = -10; d2 < 0; d2++)
				{
					if (multiply(5, n1, d1, 6, n2, d2, result, 12) == false)
					{
						return false;
					}
				}
			}
		}
	}

	// DIVIDE BY 0 FAILURES
	if (multiply(4, 5, 0, 7, 8, 9, result, 12) == true)
	{
		return false;
	}
	if (multiply(4, 5, 6, 7, 8, 0, result, 12) == true)
	{
		return false;
	}
	if (multiply(4, 5, 0, 7, 8, 0, result, 12) == true)
	{
		return false;
	}

	// NEGATIVE FRACTIONS
	if (multiply(4, -5, 6, 7, 8, 9, result, 12) == true)
	{
		return false;
	}
	if (multiply(4, 5, -6, 7, 8, 9, result, 12) == true)
	{
		return false;
	}
	if (multiply(4, 5, 6, 7, -8, 9, result, 12) == true)
	{
		return false;
	}
	if (multiply(4, 5, 6, 7, 8, -9, result, 12) == true)
	{
		return false;
	}
	if (multiply(4, -5, 6, 7, -8, 9, result, 12) == true)
	{
		return false;
	}
	if (multiply(4, 5, -6, 7, 8, -9, result, 12) == true)
	{
		return false;
	}
	if (multiply(4, -5, 6, 7, 8, -9, result, 12) == true)
	{
		return false;
	}
	if (multiply(4, 5, -6, 7, -8, 9, result, 12) == true)
	{
		return false;
	}

	// Overflow
	if (multiply(5000, 11, 13, 7000, 6, 9, result, 12) == true)
	{
		return false;
	}
	// This one is just under INT_MAX
	if (multiply(5000, 6, 9, 7000, 1, 6, result, 12) == false)
	{
		return false;
	}
	if (multiply(7, 500, 9, 4, INT_MAX, 7, result, 12) == true)
	{
		return false;
	}
	if (multiply(7, 8, INT_MAX, 4, 5, 7, result, 12) == true)
	{
		return false;
	}

	// Checking for correct answer

	multiply(1, 1, 2, 3, 0, 2, result, 12);
	char answer[] = { '4', '.', '5', '\0' };
	cout << result << ' ' << '=' << '=' << ' ' << answer << endl;

	multiply(-5, 3, 4, 6, 7, 9, result, 12);
	char ans[] = { '-', '3', '8', '.', '9', '7', '2', '2', '2', '2', '2', '\0' };
	cout << result << ' ' << '=' << '=' << ' ' << ans << endl;

	multiply(0, 0, 5, INT_MAX, 3, 6, result, 12);
	char ans2[] = { '0' , '\0'};
	cout << result << ' ' << '=' << '=' << ' ' << ans2 << endl;

	multiply(-17, 3, 4, -6, 7, 9, result, 12);
	char ans3[] = { '1', '2', '0', '.', '3', '0', '5', '5', '5', '5', '\0' };
	cout << result << ' ' << '=' << '=' << ' ' << ans3 << endl;

	return true;
}
