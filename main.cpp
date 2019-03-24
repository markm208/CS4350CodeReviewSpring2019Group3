#include <iostream>

using namespace std;


// add if not base divisable by 10
int adding_d(int n1,int d1,int n2,int d2)
{
    int d3=0;
    d3=d1*d2;
    return d3;
}
int adding_n(int n1,int d1,int n2,int d2)
{
    int n3=0;
    n3=(n1*d2)+(n2*d2);
    return n3;
}
//get the length of an integer.
int lengthof(int integer)
{
    int length=1;
    int converter=10;
    while(converter<=integer)
    {
        converter=converter*10;
        length++;
    }
    return length;
}

//translate integer to char array
void translate_to_string(int integer,char* resultV)
{
    if(integer==0)
    {
        resultV[0]='0';
    }
    else{
    int converter=1;
    int length=0;
    while(integer>=converter)
    {
        length++;
        converter=converter*10;
    }
    //convert int to char array
    char result[length];
    //make converter equal to the power of the integer
    converter=converter/10;
    for(int i = length;i>=0;i--)
    {
        int local_int=0;
        while(integer>=converter-1)
        {
            local_int=local_int+1;
            integer=integer-converter;
        }
        if(converter!=1)
        {
            converter=converter/10;
        }
        //push integer on to array as char
        result[length-i]=(char)(local_int+48);
    }
    //change original array passed in
    for(int i =0;i<length;i++)
    {
        resultV[i]=result[i];
    }
    cout<<resultV<<endl;
    }
}
//add function
bool add(int c1,int n1, int d1,int c2,int n2, int d2, char* result,int len)
{
    //check if either number is negative.
    if(c2<0)
    {
        n2=-n2;
    }
    if(c1<0)
    {
        n1=-n1;
    }
    //set up answer devisor and set up numerator as well
    int d3 = adding_d(n1,d1,n2,d2);

    //add numerators
    int n3=adding_n(n1,d1,n2,d2);
    //add integers
    int c3=c1+c2;
    //add, subtract, or do nothing to characteristic
    if(n3>d3)
    {
        c3=c3+1;
        n3=n3-d3;
    }
    if(n3<0)
    {
        c3=c3-1;
        //because i set the number as a negative,we must add here
        n3=d3+n3;
    }
    //store results
    int len_c3=lengthof(c3);
    int len_n3=lengthof(n3);
    char char_c3[len_c3];
    char char_n3[len_n3];

    translate_to_string(c3,char_c3);
    translate_to_string(n3,char_n3);

    //loop to add to characteristic and numerator to result
    if(lengthof(c3)+lengthof(n3)+1>len)
    {
        return false;
    }
    int i=0;
    while(i!=len_c3)
    {
        result[i]=char_c3[i];
        i++;
    }
    if(i==len)
    {

    }
    else
    {
        result[i]='.';
        i++;
    }
    while(i!=(len_c3+len_n3+1) && i!=len)
    {
        result[i]=char_n3[i-(len_c3+1)];
        i++;
    }
    result[i]='\0';
    return true;
}

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

	//0 + 0 = "0"
	add(0, 0, 10, 0, 0, 10, shortArray, SHORT_ARRAY_LENGTH);
    cout<<shortArray<<endl;
////shouldConvert(shortArray, 0, 0, 10);
	add(0, 0, 10, 0, 0, 10, mediumArray, MEDIUM_ARRAY_LENGTH);
    cout<<mediumArray<<endl;
	//shouldConvert(mediumArray, 0, 0, 10);
	add(0, 0, 10, 0, 0, 10, largeArray, LARGE_ARRAY_LENGTH);
    cout<<mediumArray<<endl;
	//shouldConvert(largeArray, 0, 0, 10);

	//1 + 1 = "2"
	add(1, 0, 10, 1, 0, 10, shortArray, SHORT_ARRAY_LENGTH);
    cout<<shortArray<<endl;
	add(1, 0, 10, 1, 0, 10, mediumArray, MEDIUM_ARRAY_LENGTH);
    cout<<mediumArray<<endl;
	add(1, 0, 10, 1, 0, 10, largeArray, LARGE_ARRAY_LENGTH);
    cout<<largeArray<<endl;
	//1 + -1.5 = "-.5"
    cout<<shortArray<<endl;
	add(1, 0, 10, -1, 1, 2, shortArray, SHORT_ARRAY_LENGTH);
    cout<<shortArray<<endl;
	add(1, 0, 10, -1, 1, 2, mediumArray, MEDIUM_ARRAY_LENGTH);
    cout<<shortArray<<endl;
	add(1, 0, 10, -1, 1, 2, largeArray, LARGE_ARRAY_LENGTH);

	//1.125 + 1.6R = "2.79"
    cout<<shortArray<<endl;
	add(1, 1, 8, 1, 2, 3, shortArray, SHORT_ARRAY_LENGTH);

	//1.125 + 1.6R = "2.7916666"
    cout<<shortArray<<endl;
	add(1, 1, 8, 1, 2, 3, mediumArray, MEDIUM_ARRAY_LENGTH);

	//1.125 + 1.6R = "2.79166666666666666"
    cout<<shortArray<<endl;
	add(1, 1, 8, 1, 2, 3, largeArray, LARGE_ARRAY_LENGTH);
	//can't use the convert function because the num/denom would overflow
	char expectedResult[] = "2.79166666666666666";
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
			cout << "Error: mismatch in C strings in add()." << endl
				<< "Expected: " << expectedResult << " "
				<< "Actual: " << largeArray
				<< endl;
		}
	}
    return 0;
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
