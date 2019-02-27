#include <iostream> //do not include anything other than this

using namespace std;

bool subtract(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len); 
//bool isNumber(int n);

int main()
{
	cout << "why isnt anything working!" << endl;
    const int len = 10;
    char answer[len];
    int c1, n1, d1;
    int c2, n2, d2;
    
    c1 = 1;
    n1 = 1;
    d1 = 2;
    
    c2 = 2;
    n2 = 2;
    d2 = 3; 
    
    //if the C string could hold at least the characteristic
    if (subtract(c1, n1, d1, c2, n2, d2, answer, len))
    {

        //display string with answer
    }
    else
    {
        cout << "answer is too big to display." << endl;
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
        int newNumerator = numOne - numTwo;
        float answer = newNumerator/newD;
        float temp = answer;
        float temp2 = answer;
        int decCounter = 0;
        int wholeCounter = 0;
        // while (temp % 1 != 0)
        // {
        //     decCounter ++;
        //     temp = temp*10;
        // }
        while (temp2 > 1)
        {
            wholeCounter++;
            temp2/10;
        }

        if (len - wholeCounter < 0)
        {   
            return false;
        }
        else
        {
            int placesLeft = len-wholeCounter;
            int divisor = 1;
            for (int i = placesLeft; i > 0; i --)
            {
                divisor = divisor * 10;
            }
            answer = answer * divisor;

            int almostFinalAnswer = answer;
            float finalAnswer = almostFinalAnswer / divisor;
            
            
            
        }
        

        int sizeOfNumber = decCounter + wholeCounter;

        
        // int newN = temp % newD;
        // int newC = temp/newD;
        // float decimal = newN/newD;
        // float tempAnswer = newC + decimal;
        // cout << tempAnswer;
          
}
// bool isNumber(int n)
// {
//     char* p;
//     strtol(n.c_str(), &p, 10);
//     return *p == 0;
// }
//
//
