#include <iostream> //do not include anything other than this

using namespace std;

bool divide(int c1, int n1, int d1, int c2, int n2, int d2, char answer[], int length);

int main()
{
    const int ANS_LENGTH = 10;
    char answer[ANS_LENGTH];

    int c1, n1, d1;
    int c2, n2, d2;

    if(divide(c1, n1, d1, c2, n2, d2, answer, ANS_LENGTH))
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
bool divide(int c1, int n1, int d1, int c2, int n2, int d2, char answer[], int length)
{

}