#include <iostream>

using namespace std;


// add if not base divisable by 10
int adding(int n1,int d1,int n2,int d2)
{
    int n3=0;
    int d3=0;
    d3=d1*d2;
    n3=(n1*d2)+(n2*d2);
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
//set up divisor to hightest divisor
int divisor(int d1,int d2,int &n1,int &n2)
{
    if(d1 == d2)
    {
        return d1;
    }
    else
    {
        while(1)
        {
            if(d1>d2)
            {
                d2=d2*10;
                n2=n2*10;
                if(d1==d2)
                {
                    return d1;
                }
            }
            else
            {
                d1=d1*10;
                n1=n1*10;
                if(d1==d2)
                {
                    return d1;
                }
            }
            
        }
    }
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
    int d3 = divisor(d1,d2,n1,n2);

    //add numerators
    int n3=n1+n2;
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
    //set up char array
    char result[10];
    //add values
    add(0,1,10,0,0,10,result,10);
    int i = 0;
    //print results
    cout<<"your result is :";
    cout<<result<<endl;
    return 0;
}

//new functions go here