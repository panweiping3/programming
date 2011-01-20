#include <iostream>
#include <string>

using namespace std;

class A
{
	public:
        A(string a)
	    {
	        cout << "A constructor is called" << endl;	
	    }
        ~A()
        {
	        cout << "A destructor is called" << endl;	
        }
};


void B(const A &a)
{
	cout << "B is called" << endl;	
}
			

int main()
{
	string aaa = "tieto";
	B(aaa);
    
    return 0;
}
