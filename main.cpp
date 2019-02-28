#include <iostream> //do not include anything other than this

using namespace std;

bool divide(int c1, int n1, int d1, int c2, int n2, int d2, char answer[], int length);
void addToArray(char num, bool convert, int pos, char answer[]);


int main()
{
    const int ANS_LENGTH = 10;
    char answer[ANS_LENGTH];

    int c1, n1, d1;
    int c2, n2, d2;
    c1 = 4;
    n1 = 1;
    d1 = 2;
    
    c2 = 1;
    n2 = 1;
    d2 = 2;

    if(divide(c1, n1, d1, c2, n2, d2, answer, ANS_LENGTH))
    {
        cout << "answer: " << answer << endl;
    }
    else
    {
        cout << "error, could not divide" << endl;
    }

    return 0;
}

//new functions go here
bool divide(int c1, int n1, int d1, int c2, int n2, int d2, char answer[], int length)
{
    bool retVal = true;

    //check to make sure denominators are not 0
	if (d1 == 0 || d2 == 0)
	{
		retVal = false;
	}
    else //otherwise we can continue
    {
        //create 'new' numerators and pos to keep track of array
        int newNumerator1;
		int newNumerator2;
        int endNumer;
        int endDenom;
        int pos = 0;

        //check for negative characteristic and flip to postive numbers
        //and add '-' to answer array
		if (c1 < 0)
		{
			c1 = c1 * -1;
            addToArray('-', false, pos++, answer);
		}
		if (c2 < 0)
		{
			c2 = c2* -1;
            addToArray('-', false, pos++, answer);
		}

        //improper fractions for the new numerators
		newNumerator1 = (c1 * d1) + n1;
		newNumerator2 = (c2 * d2) + n2;

        //cross multiply with new numerators
		endNumer = newNumerator1 * d2;
		endDenom = d1 * newNumerator2;

        //divide first num and add to array
		int num = endNumer / endDenom;
		addToArray(num, true, pos++, answer);
        int remainder = endNumer;

        //add a decimal
		addToArray('.', false, pos++, answer);

        while(pos < length - 1)
        {
            num = num * endDenom; //mutliply denom
			num = remainder - num; //subtract from previous

            //check for 0
            //removed

            num = num * 10; //"move the decimal"
            remainder = num; //save number
            num = num / endDenom; //divide
            addToArray(num, true, pos++, answer); //add to array
        }

        //add null char to end of array
        addToArray('\0', false, pos++, answer);
    }

    return retVal;
}

void addToArray(char c, bool convert, int pos, char answer[])
{   
    if(convert)
    {
        answer[pos] = c + 48;
    }
    else
    {
	    answer[pos] = c;
    }
}