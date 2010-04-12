#include <iostream>

using namespace std;

#define __u16 unsigned short

__u16 htons(__u16 x)
{
    cout << "low" << (((__u16)(x) & (__u16)0x00ff) << 8) << endl; 
    cout << "hig" << (((__u16)(x) & (__u16)0xff00) >> 8) << endl;
    cout << "or " << ((((__u16)(x) & (__u16)0x00ff) << 8) | (((__u16)(x) & (__u16)0xff00) >> 8)) << endl;
    return ((__u16)(
                (((__u16)(x) & (__u16)0x00ff) << 8) 
                | (((__u16)(x) & (__u16)0xff00) >> 8) ));
}

int main()
{
   __u16 i = 1234;

   cout << "i  " << i << endl;
   __u16 j = htons(i);
   cout << "htons (i)" << i << endl; 
   cout << "j  " << j << endl; 
    
    return 0;
}
