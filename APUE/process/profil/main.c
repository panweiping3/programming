#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

unsigned short buffer[4096];
int start_address;
void f();
void g();
void the_end();

int main()
{
    int end_address, scale, f_address, g_address, text_length;
    
    signal(SIGINT, the_end);

    end_address = (int)the_end;
    start_address = (int)main;

    text_length = (end_address - start_address + sizeof(int) - 1) / sizeof(int);
    printf("start_address 0x%x, end_address 0x%x, text_length 0x%x\n", start_address, end_address, text_length);

    f_address = (int)f;
    g_address = (int)g;
    printf("f_address 0x%x, g_address 0x%x, f_offset %d, g_offset %d\n", f_address, g_address, f_address-start_address, g_address-start_address);
    
    scale = 0xffff;
    profil(buffer, sizeof(unsigned short) * 4096, start_address, scale);

    for(;;) {
        f();
        g();
    }
}

void f()
{}

void g()
{}

void the_end()
{
    int i;
    for (i=0; i<4096; ++i) {
        if (buffer[i]) {
            printf("buf[0x%x]=%d\n", start_address + i * 2, buffer[i]);
        }
    }   
}
