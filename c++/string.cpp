#include <iostream>

using namespace std;

int main()
{
	string str1 = "/dev/sda2";
	string str2;
	string str3 = "";

    if (str2.empty() == true) {
        cout << "str2 is empty" << endl;
    }

    if (str3.empty() == true) {
        cout << "str3 is empty" << endl;
    }

    cout << "str2 size:" << str2.size() << " length:" << str2.length() << endl;
    cout << "str3 size:" << str3.size() << " length:" << str3.length() << endl;
}

