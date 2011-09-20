#ifndef SIGNAL_H
#define SIGNAL_H

/* A subclass of GObject with a property. */

#include <stdio.h>
#include <glib-object.h>

typedef struct {
    GObject something_as_boilerplate;
    char *name;
} MyObject;

typedef struct {
    GObjectClass something_as_boilerplate;
} MyClass;

GType get_my_typeid();
void my_instance_init_func(MyObject *instance, gpointer data);
void my_class_init_func(MyClass* klass, gpointer data);
void hello(GObject *sender, char* name, gpointer data);
void goodbye(GObject *sender, char* name, gpointer data);

#endif
