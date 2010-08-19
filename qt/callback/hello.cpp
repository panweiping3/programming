#include   <iostream>
using   namespace   std;

class WindowA
{
	public:
		void show(const char *p)
		{
			cout << "WindowA" << p <<endl;
			return;
		}
};


class WindowB
{
	public:
		void show(const char *p)
		{
			cout << "WindowB" << p <<endl;
			return;
		}
};

class Button 
{
	public:
		void click(void (Window::*pf)(const char *))
		{
			Window *p;
			(p->*pf)("hello window !");
			
			return;
		}
};

int main(int argc, char *argv[])
{
	class Button button;
	button.click(&WindowA::show);
	button.click(&WindowB::show);
	return 0;
} 
