/* A subclass of GObject with a property. */

#include "signal.h" 

GType get_my_typeid()
{
    static my_type_id = 0;
    if(my_type_id==0) {
        GTypeInfo my_type_info = {
            sizeof(MyClass),  //class_size;

            NULL,               //base_init;
            NULL,               //base_finalize;

            /* classed types, instantiated types */
            (GClassInitFunc)my_class_init_func, //class_init;
            NULL,               //class_finalize;
            NULL,               //class_data;

            /* instantiated types */
            sizeof(MyObject),//instance_size;
            0,                  //n_preallocs;
            (GInstanceInitFunc)my_instance_init_func, //instance_init;

            /* value handling */
            NULL,               //value_table;
        };

        my_type_id = g_type_register_static(
                G_TYPE_OBJECT,
                "MyClass",
                &my_type_info,
                0
                );
    }
    return my_type_id;
}

void my_instance_init_func(MyObject *instance, gpointer data)
{
    instance->name = "MyObjectInstance";
}

void my_class_init_func(MyClass* klass, gpointer data)
{
    int signal_id = g_signal_new(
            "my-signal",
            get_my_typeid(),
            G_SIGNAL_RUN_LAST,
            0,
            NULL,
            NULL,
            g_cclosure_marshal_VOID__STRING,
            G_TYPE_NONE,
            1,
            G_TYPE_STRING,
            NULL
            );
}

void hello(GObject *sender, char* name, gpointer data)
{
    printf("Hello world, [%s]!\n",name);
}

void goodbye(GObject *sender, char* name, gpointer data)
{
    MyObject *instance = G_TYPE_CHECK_INSTANCE_CAST(
            sender,get_my_typeid(),MyObject);
    printf("Goodbye world, [%s]! Message from [%s]. data is [%d]\n",
            name, instance->name, *(int*)data);
}
