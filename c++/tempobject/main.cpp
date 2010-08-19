/*
 * temporaty B object is deconstructed after calling BBto()
 *
 * /

#include <iostream>
using namespace std;
class B {
	public:
		B() 
		{
			cerr << __FILE__ << __LINE__ << __func__ << "B constructor" << endl;
		}

		~B() 
		{
			cerr << __FILE__ << __LINE__ << __func__ << "B deconstructor" << endl;
		}

		void BBto(void)
		{
			cerr << __FILE__ << __LINE__ << __func__ << "B:to" << endl;
		}
};

class A {
	public:
		A() 
		{
			cerr << __FILE__ << __LINE__ << __func__ << "A constructor" << endl;
		}

		~A() 
		{
			cerr << __FILE__ << __LINE__ << __func__ << "A deconstructor" << endl;
		}

		class B AAto(void)
		{
			class B b;
			cerr << __FILE__ << __LINE__ << __func__ << "A:to" << endl;
			return b;
		}
};


int main(int argc, char *argv[])
{
	class A a;
	a.AAto().BBto();

	sleep(10);
	
	char *ch = (char *)&a;
	return 0;
}
