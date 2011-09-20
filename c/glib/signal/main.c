#include <stdio.h>

#include "signal.h"

int main(void)
{
    g_type_init();

    printf("Type id: %d\n",get_my_typeid());
    printf("Type name: %s\n",g_type_name(get_my_typeid()));

    GValue *val = g_new0(GValue,1);

    MyObject *instance = (MyObject*)g_object_new(get_my_typeid(),NULL);
    int tmpvar = 42;
    g_signal_connect(instance,"my-signal",G_CALLBACK(hello),NULL);
    g_signal_connect(instance,"my-signal",G_CALLBACK(goodbye),&tmpvar);
    g_signal_emit_by_name(instance,"my-signal","pwp");

    g_object_unref(instance);
    g_free(val);

    return 0;
}
