#ifndef __CONTROLLER_H_
#define __CONTROLLER_H_

#include <stdio.h>
#include <glib-object.h>

#define FOO_TYPE_CONTROLLER (foo_controller_get_type())
#define FOO_CONTROLLER(obj)					\
    (G_TYPE_CHECK_INSTANCE_CAST((obj), FOO_TYPE_CONTROLLER, FooController))
#define FOO_IS_CONTROLLER(obj)					\
    (G_TYPE_CHECK_INSTANCE_TYPE((obj), FOO_TYPE_CONTROLLER))
#define FOO_CONTROLLER_CLASS(klass)					\
    (G_TYPE_CHECK_CLASS_CAST(klass), FOO_TYPE_CONTROLLER, FooControllerClass))
#define FOO_IS_CONTROLLER_CLASS(klass)				\
    (G_TYPE_CHECK_CLASS_TYPE((klass), FOO_TYPE_CONTROLLER))
#define FOO_CONTROLLER_GET_CLASS(obj)					\
    (G_TYPE_INSTANCE_GET_CLASS((obj), FOO_TYPE_CONTROLLER, FooControllerClass))

typedef struct _FooController FooController;
typedef struct _FooControllerClass FooControllerClass;

struct _FooController {
    GTypeInstance parent_instance; /* Extent GTypeInstance for inherit
				    * GTypeClass */

    int on;
    int channel;
};

struct _FooControllerClass {
    GTypeClass parent_class;	/* Inherit GTypeClass */
};

GType foo_controller_get_type(void);

#endif /* __CONTROLLER_H_ */
