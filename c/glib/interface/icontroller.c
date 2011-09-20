#include "icontroller.h"

static void
foo_icontroller_base_init(gpointer g_class) {
}

GType
foo_icontroller_get_type(void)
{
    static GType type = 0;
    static const GTypeInfo info = {
	sizeof(FooIControllerInterface),
	foo_icontroller_base_init,
	NULL,
	NULL,
	NULL,
	NULL,
	0,
	0,
	NULL
    };

    if(type == 0) {
	type = g_type_register_static(G_TYPE_INTERFACE,
				      (const gchar *)"FooIController",
				      &info,
				      0);
    }

    return type;
}

void
foo_icontroller_next(FooIController *self) 
{
    FooIControllerInterface *iface = FOO_ICONTROLLER_GET_INTERFACE(self);
    iface->next(self);
}

void
foo_icontroller_prev(FooIController *self)
{
    FooIControllerInterface *iface = FOO_ICONTROLLER_GET_INTERFACE(self);
    iface->prev(self);
}

void
foo_icontroller_power(FooIController *self)
{
    FooIControllerInterface *iface = FOO_ICONTROLLER_GET_INTERFACE(self);
    iface->power(self);
}
