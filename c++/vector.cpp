#include <iostream>
#include <vector>
#include <string.h>

using namespace std;

class CDemo{
    public:
        CDemo(): str(NULL)
        {
            str = new char[10];
        }

        ~CDemo()
        {
                delete []str;
                str = NULL;
        }
         
        void setData(const char *p)
        {
            strcpy(str, p);
        }
    private:
        char *str;
};

void func(void)
{
    CDemo d;
    d.setData("Tieto");

    vector<CDemo> *v = new vector<CDemo>();
    v->push_back(d);
    delete v;

    return;
}

int main(int argc, char *argv[])
{
    func();

    return 0;
}
