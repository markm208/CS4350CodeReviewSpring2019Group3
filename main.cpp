#include <iostream> //do not include anything other than this

using namespace std;

int main()
{
    testMultiply();
    return 0;
}

// multiply returns a boolean: true if the provided numbers can by multiplied and false if they cannot.
// NEED TO FIND OUT IF CUSTOMER WOULD LIKE TO TRUNCATE, ROUND UP, ROUND DOWN, ETC
//  IF THE NUMBER HAS MORE DIGITS THAN THE ARRAY CAN STORE.
// NEED TO FIND OUT IF CUSTOMER WANTS SOMETHING TO HAPPEN OTHER THAN RETURN FALSE IF MULTIPLICATION CANNOT BE PERFORMED.
bool multiply(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len)
{
	// Convert numbers into just numerator and denominator and multiply to get multiplication answer
	int numerator1 = c1*d1 + n1;
	int numerator2 = c2*d2 + n2;
	int n = numerator1*numerator2;
	int d = d1*d2;

    // At this point n/d would be the correct answer except the decimal place would be lost because they are integers

    // Check to make sure valid input. Only invalid integer is if the denominator is zero.
	if (d == 0)
	{
        // Not in specs, here for debugging and can be easily removed if needed
		cout << "Error: Cannot Divide By Zero" << endl;
		return false;
	}

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

	// Put digits from characteristics into result
	for (unsigned int i = 0; i < characteristicNumberDigits; i++) {
		// **Need to find out from customer exactly what they would like when characteristic is too big for the array**
        if (i == len - 1)
		{
			result[len] = '\0';
			return true;
		}
		int nextDigit = characteristic / magnitudeCharacteristic;
        // The character '0' is represented as an ASCII number and 
        //  adding the nextDigit to '0' increases the ASCII number so 1 becomes '1', 2 becomes '2', etc.
        result[i] = nextDigit + '0';
		characteristic -= (nextDigit*magnitudeCharacteristic);
		magnitudeCharacteristic /= 10;
	}



	// FIND DIGITS IN DECIMAL PLACE

    // If there is a decimal place...
	if (n%d != 0)
	{
		// Place decimal point as character into result
		result[characteristicNumberDigits] = '.';

		int numerator = n%d;
		for (unsigned int i = characteristicNumberDigits + 1; i < len; i++)
		{
            // To access the next decimal point I multiply the numerator by ten then divide by d
            // Because numerator and d are integers it will only provide the characteristic
			numerator *= 10;
			result[i] = numerator / d + '0';
            // By replacing the numerator with numerator%d it removes the characteristic
			numerator %= d;

            // If the numerator at this point is equal to 0 the decimal point has ended.
			if (numerator == 0)
			{
                // Can't have string end only at end of array because
                //  there would be garbage after the product before the string ends
				result[i + 1] = '\0';
				break;
			}
        }
	}
    // If the product has no decimal place
	else
	{
        // Can't have string end only at end of array because
        //  there would be garbage after the product before the string ends
		result[characteristicNumberDigits] = '\0';
	}
    
    // This is here so that the result always has the end string at the end
	result[len] = '\0';

	return true;
}

bool testMultiply() {
	cout << "Beginning Testing of multiply(c1, n1, d1, c2, n2, d2, result[], len)" << endl << endl;
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
								cout << "FAILURED WHEN IT SHOULD HAVE PASSED" << endl;
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
						cout << "FAILED ON NEGATIVE OVER NEGATIVE (PASS)" << endl;
						cout << "N1: " << n1 << endl;
						cout << "D1: " << d1 << endl;
						cout << "N2: " << n2 << endl;
						cout << "D2: " << d2 << endl;
						return false;
					}
				}
			}
		}
	}

	// DIVIDE BY 0 FAILURES
	cout << "Should get 3 divide by zero errors below:" << endl;
	if (multiply(4, 5, 0, 7, 8, 9, result, 12) == true )
	{
		cout << "FAILED ON FIRST NUMBER DIVIDE BY 0" << endl;
		return false;
	}
	if (multiply(4, 5, 6, 7, 8, 0, result, 12) == true)
	{
		cout << "FAILED ON SECOND NUMBER DIVIDE BY 0" << endl;
		return false;
	}
	if (multiply(4, 5, 0, 7, 8, 0, result, 12) == true)
	{
		cout << "FAILED ON BOTH NUMBERS DIVIDE BY 0" << endl;
		return false;
	}

	// NEGATIVE FRACTIONS
	cout << endl << "Should get 8 negative fraction errors below:" << endl;
	if (multiply(4, -5, 6, 7, 8, 9, result, 12) == true)
	{
		cout << "FAILED ON FIRST NUMERATOR NEGATIVE" << endl;
		return false;
	}
	if (multiply(4, 5, -6, 7, 8, 9, result, 12) == true)
	{
		cout << "FAILED ON FIRST DENOMINATOR NEGATIVE" << endl;
		return false;
	}
	if (multiply(4, 5, 6, 7, -8, 9, result, 12) == true)
	{
		cout << "FAILED ON SECOND NUMERATOR NEGATIVE" << endl;
		return false;
	}
	if (multiply(4, 5, 6, 7, 8, -9, result, 12) == true)
	{
		cout << "FAILED ON SECOND DENOMINATOR NEGATIVE" << endl;
		return false;
	}
	if (multiply(4, -5, 6, 7, -8, 9, result, 12) == true)
	{
		cout << "FAILED ON BOTH NUMERATOR NEGATIVE" << endl;
		return false;
	}
	if (multiply(4, 5, -6, 7, 8, -9, result, 12) == true)
	{
		cout << "FAILED ON BOTH DENOMINATOR NEGATIVE" << endl;
		return false;
	}
	if (multiply(4, -5, 6, 7, 8, -9, result, 12) == true)
	{
		cout << "FAILED ON FIRST NUMERATOR, SECOND DENOMINATOR NEGATIVE" << endl;
		return false;
	}
	if (multiply(4, 5, -6, 7, -8, 9, result, 12) == true)
	{
		cout << "FAILED ON SECOND NUMERATOR, FIRST DENOMINATOR NEGATIVE" << endl;
		return false;
	}

	// Characterisitcs, Numerators, and Denominators all ran through every integer from -10 through 10

	cout << endl << "SUCCESS" << endl;
	return true;
}
