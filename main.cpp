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
    
    c1 = 20;
    n1 = 2;
    d1 = 5;
    
    c2 = 1;
    n2 = 1;
    d2 = 2; 
    
    //if the C string could hold at least the characteristic
    if (subtract(c1, n1, d1, c2, n2, d2, answer, len))
    {

		cout << "The result is: " << answer << endl;
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
	bool retVal = true;
    int numOne = c1*d1 + n1;
    int numTwo = c2*d2 + n2;
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
    int newNumerator = numOne - numTwo;
    int characteristic = newNumerator/newD;
    int decimalNumber = newNumerator % newD;
	int temp = characteristic;
	int digitCounterRight = 0;
	int digitCounterLeft = 0;
	int  i = 0;
	//checking to see how many whole digits we have
	while (temp != 0)
	{
		temp = temp / 10;
		digitCounterLeft++;
	}
	if (digitCounterLeft > len)
	{
		retVal = false;
	}
	temp = characteristic;
	for (i = digitCounterLeft; i > 0; i--)
	{
		
			int remainder = temp % 10;
			result[i - 1] = '0' + remainder;
			temp = temp / 10;	
	}
	i = digitCounterLeft;
	result[i] = '.';
	i++;
	temp = decimalNumber;
	//checking to see how many decimal numbers we have
	while (temp != 0)
	{
		temp = temp / 10;
		digitCounterRight++;
	}
	if (digitCounterRight > len - i)
	{
		//shit's gettin cut off
	}
	else //can safely add each digit to the cstr
	{
		temp = decimalNumber;
		int j = digitCounterRight + i;
		for (j; j > i; j--)
		{
			int remainder = temp % 10;
			result[j - 1] = '0' + remainder;
			temp = temp / 10;
			if (temp == 0)
			{
				result[digitCounterRight+i] = '\0';
			}	
		}
	}
	return retVal;
}
