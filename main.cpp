#include <iostream> //do not include anything other than this

using namespace std;

bool subtract(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len); 
//bool isNumber(int n);

int main()
{
    const int len = 10;
    char answer[len];
    int c1, n1, d1;
    int c2, n2, d2;
    
    c1 = 2;
    n1 = 1;
    d1 = 2;
    
    c2 = 1;
    n2 = 1;
    d2 = 4; 
    
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
	bool isNegative = false;
	int swapVal = 0;
	bool retVal = true;
    int numOne = c1*d1 + n1;
    int numTwo = c2*d2 + n2;
	int charCounter = 0;
	
    int newD;
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
	if (charCounter + 2 > len)//account for null terminator and period
	{
		return false;
	}
	else
	{
		temp = characteristic;
		if (charCounter == 0)
		{
			result[charCounter] = '0';
			result[charCounter + 1] = '.';
			charCounter += 2;
		}
		else
		{
			result[charCounter] = '.';
			
			for (int i = charCounter; i > 0; i--)
			{
				int remainder = temp % 10;
				result[i - 1] = char('0'+remainder);
				temp = temp / 10;

			}
			charCounter++;
		}
		
		digitsLeft = len - (charCounter);
	}
	int multiplier = 1;
	temp = digitsLeft;
	while (temp != 0)
	{
		multiplier = multiplier * 10;
		temp--;
	}
	//redo initial calculation
	characteristic = (newNumerator * multiplier) / newD;//this will give us the correct number of decimals
	//now we extract the decimal numbers by recounting the numbers then pulling from the end
	temp = characteristic;
	//charCounter = 0;
	/*
	while (temp != 0)
	{
		charCounter++;
		temp = temp / 10;
	}
	*/
	//result[len - 1] = '\0';
	temp = characteristic;
	for (int i = 0; i < len - charCounter; i++)
	{
		int remainder = temp % 10;
		result[len - i - 1] = char('0' + remainder);
		temp = temp / 10;
	}

	if (isNegative)
	{
		result[0] = '-';
	}
	return retVal;
}
