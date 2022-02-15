#define ERROR_HANLER 1

#include <iostream>
using namespace std;

const char const*alphabetA="0123456789abcdefghijklmnopqrstuvwxyz";
const char const*alphabetB="j2n3yzkgucrv7e9d0ho1xlps68iwmtb45fqa";
const char const*alphabetC="9sie2m63u4zq0y7cwogk1fnblh8arvp5dxtj";

inline const unsigned char retNum(const char symb,const char const*alphabet)
{
    for(const char*p=alphabet;*p;p++)
    {
        if(symb==*p)
            return (unsigned char)(p-alphabet);
    }

    return 255;
}

inline bool code(char*line,const char const*alphabetA,const char const*alphabetB)
{
    register unsigned char i=0;

    for(char*p=line;*p;p++,i++)
    #ifdef ERROR_HANLER
    {
        const unsigned char n=retNum(*p,alphabetA);
        if(!(unsigned char)(~n))return false;
        *p=alphabetB[(n+3*i+2)%36];
    }
    #else
        *p=alphabetB[(retNum(*p,alphabetA)+3*i+2)%36];
    #endif

    return true;
}

inline bool decode(char*line,const char const*alphabetA,const char const*alphabetB)
{
    register unsigned char i=0;

    for(char*p=line;*p;p++,i++)
    #ifdef ERROR_HANLER
    {
        const unsigned char n=retNum(*p,alphabetB);
        if(!(unsigned char)(~n))return false;
        *p=alphabetA[(n-3*i-2+36)%36];
    }
    #else
        *p=alphabetA[(retNum(*p,alphabetB)-3*i-2+36)%36];
    #endif

    return true;
}

char line[255]={0};

int main()
{
    setlocale(0,"");
    
    cout<<"Введите шифруемую строку: ";
    cin.getline(line,255,'\n');

    if(!code(line,alphabetA,alphabetB))goto error;
    cout<<"Зашифрованная строка: "<<line<<endl;

    if(!decode(line,alphabetA,alphabetB))goto error;
    cout<<"Расшифрованная строка: "<<line<<endl;

    return 0;

error:
    cout<<"Можно использовать только символы латинского алфавита и цифры!\n";
    cerr<<"Можно использовать только символы латинского алфавита и цифры!\n";
    return 1;
}