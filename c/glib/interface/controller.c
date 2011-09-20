#include "icontroller.h"
#include "controller.h"

static void foo_controller_class_init(FooControllerClass *class)
{
	
}

static void foo_controller_init(FooController *self)
{
	
}

static void
foo_controller_interface_init(gpointer iface, gpointer iface_data);

FooController *foo_controller_new(void)
{
	return (FooController *)g_object_new(FOO_TYPE_CONTROLLER, NULL);	
}


GType
foo_controller_get_type(void)
{
    static GType type = 0;
    static const GTypeInfo info = {
	sizeof(FooControllerClass),
	NULL,
	NULL,
	(GClassInitFunc)foo_controller_class_init,
	NULL,
	NULL,
	sizeof(FooController),
	0,
	(GInstanceInitFunc)foo_controller_init
    };
    static const GTypeFundamentalInfo finfo = {
	G_TYPE_FLAG_CLASSED | G_TYPE_FLAG_INSTANTIATABLE |
	G_TYPE_FLAG_DERIVABLE | G_TYPE_FLAG_DEEP_DERIVABLE
    };
    static const GInterfaceInfo iinfo = {
	(GInterfaceInitFunc)foo_controller_interface_init,
	NULL,
	NULL
    };

    if(type == 0) {
	type = g_type_register_fundamental(FOO_TYPE_CONTROLLER,
					   (const gchar *)"ControllerType",
					   &info,
					   &finfo,
					   0);
	g_type_add_interface_static(type, FOO_TYPE_ICONTROLLER, &iinfo);
    }

    return type;
}

static void
imp_foo_controller_next(FooIController *self)
{
    FooController *controller = FOO_CONTROLLER(self);

    if(controller->on) {
	controller->channel++;
	if(controller->channel > 99)
	    controller->channel = 1;
	printf("Channel %d\n", controller->channel);
    }
}

static void
imp_foo_controller_prev(FooIController *self)
{
    FooController *controller = FOO_CONTROLLER(self);

    if(controller->on) {
	controller->channel--;
	if(controller->channel < 1)
	    controller->channel = 99;
	printf("Channel %d\n", controller->channel);
    }
}

static void
imp_foo_controller_power(FooIController *self)
{
    FooController *controller = FOO_CONTROLLER(self);

    controller->on = controller->on ^ 1;
    if(controller->on)
	printf("power on\n");
    else
	printf("power off\n");
}

static void
foo_controller_interface_init(gpointer iface, gpointer iface_data)
{
    FooIControllerInterface *_iface = (FooIControllerInterface *)iface;

    _iface->next = imp_foo_controller_next;
    _iface->prev = imp_foo_controller_prev;
    _iface->power = imp_foo_controller_power;
}
