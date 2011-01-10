#include <iostream>
#include <string.h>
using namespace std; 

class Internet 
{ 
        public: 
                Internet(const char*name, const char*address) 
                { 
                        cout<<"载入构造函数"<strcpy(Internet::name,name); 
                        strcpy(Internet::address,address); 
                        cname=new char[strlen(name)+1]; 
                        if(cname!=NULL) 
                        { 
                                strcpy(Internet::cname,name); 
                        } 
                } 
                Internet(Internet &temp) 
                { 
                        cout<<"载入COPY构造函数"<strcpy(Internet::name,temp.name); 
                        strcpy(Internet::address,temp.address); 
                        cname=new char[strlen(name)+1];//这里注意,深拷贝的体现! 
                        if(cname!=NULL) 
                        { 
                                strcpy(Internet::cname,name); 
                        } 
                } 
                ~Internet() 
                { 
                        cout<<"载入析构函数!"; 
                        delete[] cname; 
                        cin.get(); 
                } 
                void show(); 
        protected: 
                char name[20]; 
                char address[30]; 
                char *cname; 
}; 
void Internet::show() 
{ 
        cout<<"载入show函数"<< endl;
}
void test(Internet ts) 
{ 
        cout<<"载入test函数"<< endl;
} 

int main() 
{ 
        Internet a("中国软件开发实验室","www.cndev-lab.com"); 
        Internet b =a; 
        b.show(); 
        test(b); 

        return 0;
}
