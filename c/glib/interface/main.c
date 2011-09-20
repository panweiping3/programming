#include <stdio.h>
#include "controller.h"

int
main(int argc, const char *argv[])
{
    FooController *controller;
    int i;
    int v;

    g_type_init();
    
    controller = (FooController *)g_type_create_instance(FOO_TYPE_CONTROLLER);
    
    foo_icontroller_power(controller);
    
    for(i = 0; i < 5; i++)
	v = foo_icontroller_next(controller);
    for(i = 0; i < 7; i++)
	v = foo_icontroller_prev(controller);
    
    foo_icontroller_power(controller);
    
    return 0;
}
