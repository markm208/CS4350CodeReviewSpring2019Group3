#include <iostream> //do not include anything other than this

using namespace std;

bool subtract(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len); 
//bool isNumber(int n);

int main()
{
    const int len = 6;
    char answer[len];
    int c1, n1, d1;
    int c2, n2, d2;
    
    c1 = 5;
    n1 = 5;
    d1 = 27;
    
    c2 = 2;
    n2 = 6;
    d2 = 27; 
    
    //if the C string could hold at least the characteristic
    if (subtract(c1, n1, d1, c2, n2, d2, answer, len))
    {

		cout << "The result is: ";
		for (int i = 0; i < len; i++)
		{
			cout << answer[i];
		}
		cout << endl;
        //display string with answer
    }
    else
    {
        cout << "answer is too big to display." << endl;
        //display error message
    }
	system("pause");
    return 0;
}

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
		//the first thing thats being added is the '.'  could have been done later but whatever
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
	long mantissa = (newNumerator * multiplier)/newD;
	/*The above live is the same calculation we did earlier, except the decimal is moved over to
	include the right amount of decimal characters.  It is treated as a whole number, but we know that the 
	extra digits are our missing decimal numbers*/
	
	long mantissaTemp = mantissa;
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
