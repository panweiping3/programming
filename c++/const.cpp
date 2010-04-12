#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    const int i = 100;
    int *p = (int *)&i;
    *p = 200;
    cout << i << endl;
    cout << *p << endl;
    return 0;
        
}
