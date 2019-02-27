#include <iostream> //do not include anything other than this

using namespace std;

bool subtract(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len); 
//bool isNumber(int n);

int main()
{
	cout << "why isnt anything working!" << endl;
    char answer[10];
    int c1, n1, d1;
    int c2, n2, d2;
    
    c1 = 1;
    n1 = 1;
    d1 = 2;
    
    c2 = 2;
    n2 = 2;
    d2 = 3; 
    
    //if the C string could hold at least the characteristic
    if (subtract(c1, n1, d1, c2, n2, d2, answer, 10))
    {

        //display string with answer
    }
    else
    {
        //display error message
    }
    return 0;
}

//new functions go here
bool subtract(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len)
{
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
        int temp = numOne - numTwo;
        int newN = temp % newD;
        int newC = temp/newD;
        float decimal = newN/newD;
        float tempAnswer = newC + decimal;
        cout << tempAnswer;
          
}
// bool isNumber(int n)
// {
//     char* p;
//     strtol(n.c_str(), &p, 10);
//     return *p == 0;
// }
//
//
