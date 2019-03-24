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

int main()
{
	int SHORT_ARRAY_LENGTH = 5;
	char shortArray[SHORT_ARRAY_LENGTH];

	int MEDIUM_ARRAY_LENGTH = 10;
	char mediumArray[MEDIUM_ARRAY_LENGTH];

	int LARGE_ARRAY_LENGTH = 20;
	char largeArray[LARGE_ARRAY_LENGTH];

	//should not be enough space in the array for the result
	if (add(INT8_MAX, 0, 10, INT8_MAX, 0, 10, shortArray, SHORT_ARRAY_LENGTH))
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

//new functions go here