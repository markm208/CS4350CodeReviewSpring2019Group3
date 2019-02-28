#include <iostream> //do not include anything other than this

using namespace std;

bool divide(int c1, int n1, int d1, int c2, int n2, int d2, char answer[], int length);
void addToArray(int num, int pos, char answer[]);


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
        //create 'new' numbers to keep track of
        int newNumerator1;
		int newNumerator2;

        //improper fractions for the new numerators
		newNumerator1 = (c1 * d1) + n1;
		newNumerator2 = (c2 * d2) + n2;

        //divide and first num to array
		int num = newNumerator1 / newNumerator2;
		addToArray(num, 0, answer);

    }

    return retVal;
}

void addToArray(int num, int pos, char answer[])
{
    //cast to char and fix offset
    char numToInsert = (char)num + 48;

    //insert into array
	answer[pos] = numToInsert;
}