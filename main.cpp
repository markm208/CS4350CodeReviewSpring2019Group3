#include <iostream>

using namespace std;

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
char* translate_to_string(int integer)
{
    int converter=1;
    int length=0;
    while(converter<=integer)
    {
        length++;
        converter=converter*10;
    }
    //convert int to char array
    char result[length];
    for(int i = length;i>0;i--)
    {
        int local_int=0;
        while(integer>=converter)
        {
            local_int=local_int+1;
            integer=integer-converter;
        }
        if(converter!=1)
        {
            converter=converter/10;
        }
        result[length-i]=(char)(local_int+48);
    }
    //convert to pointer
    char* pointer = result;
    return pointer;    
}
bool add(int c1,int n1, int d1,int c2,int n2, int d2, char result[],int len)
{
    if(c2<0)
    {
        n2=-n2;
    }
    //set up answer devisor and set up numerator as well
    int d3 = divisor(d1,d2,n1,n2);

    //add numerators
    int n3=n1+n2;
    //add integers
    int c3=c1+c2;
    cout<<"c3"<<endl;
    cout<<c3<<endl;
    cout<<c1<<endl;
    cout<<c2<<endl;
    cout<<"end of c3"<<endl;
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
    cout<<c3<<endl;
    cout<<n3<<endl;
    cout<<d3<<endl;
    char* char_c3=translate_to_string(c3);
    char* char_n3=translate_to_string(n3);
    char* char_d3=translate_to_string(d3);

    //loop to add to length
    for(int i =0;i<sizeof(&char_c3);i++)
    {
        cout<< &char_c3[i];
    }
}

int main()
{
    char result[3];
    add(599,6,10,-2,7,10,result,3);
    return 0;
}

//new functions go here