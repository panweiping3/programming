#include <stdio.h>

int main(int argc, char *argv[])
{
    register unsigned long current_stack_pointer1 asm("esp");
    printf("esp 0x%x\n", current_stack_pointer1);
    
    int i;
    register unsigned long current_stack_pointer2 asm("esp");
    printf("esp 0x%x\n", current_stack_pointer2);

    int j;
    register unsigned long current_stack_pointer3 asm("esp");
    printf("esp 0x%x\n", current_stack_pointer3);

    int k;
    register unsigned long current_stack_pointer4 asm("esp");
    printf("esp 0x%x\n", current_stack_pointer4);
    return 0;
}
