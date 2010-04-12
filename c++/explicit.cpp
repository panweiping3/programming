#include <iostream>
#include <string>

using namespace std;

class A
{
	public:
	//explicit A(string a) // cann't compile if adding explicit 
    A(string a)
		{
			cout << "A constructor is called" << endl;	
		}
};


void B(A a)
{
	cout << "B func is called" << endl;	
}
			

int main()
{
	string aaa = "panweiping";
	B(aaa);

}
