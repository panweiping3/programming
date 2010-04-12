#include <iostream>

using namespace std;

class pwp
{
	public:
		~pwp()
		{
			cout << "pwp destructor" << endl;
		}

		static pwp *instance()
		{
			if ( p == NULL)
			{	
				p = new pwp();
				return p;
			}	
			else
				return p;
		}

	private:
		pwp()
		{
			cout << "pwp constructor" << endl;
		}

	private:
		static pwp *p;
};

pwp *pwp::p = NULL;

int main(int argc, char *argv[])
{
	pwp *b = pwp::instance();
}
