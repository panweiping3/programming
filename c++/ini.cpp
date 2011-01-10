#include <iostream>
#include <string>

using namespace std;

class CDemoClass
{
	public:
        CDemoClass(const string &str)
            :data(str) {;}
        CDemoClass(CDemoClass &c)
            :data(c.value()) {;}
   
        string value(void)
        {
            return data;
        }
        void setValue(const string &str)
        {
            data = str;
        }
    private:
        string data;
};


class CInitializationClass
{
    public:
        CInitializationClass(CDemoClass &c);

    private:
        const int const_b;
        CDemoClass cDemoClass;
        CDemoClass &cDemoClassReference;
};

CInitializationClass::CInitializationClass(CDemoClass &c)
    : const_b(100),
      cDemoClass(c),
      cDemoClassReference(c)
{
    
}

int main()
{
    string s = "Tieto";
    CDemoClass tmp(s);
    CInitializationClass b(tmp);

    return 0;
}
/*
请用最高效的方式实现CInitializationClass类的构造函数,
要求：
常量const_b设置成100
成员变量cDemoClass用c的data来初始化；
成员变量cDemoClassReference也用c的data来初始化；
*/

