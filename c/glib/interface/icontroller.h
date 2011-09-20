#ifndef __ICONTROLLER_H_
#define __ICONTROLLER_H_

#include <glib-object.h>

#define FOO_TYPE_ICONTROLLER (foo_icontroller_get_type())
#define FOO_ICONTROLLER(obj)					\
    (G_TYPE_CHECK_INSTANCE_CAST((obj), FOO_TYPE_ICONTROLLER, FooIController))
#define FOO_IS_ICONTROLLER(obj)					\
    (G_TYPE_CHECK_INSTANCE_TYPE((obj), FOO_TYPE_ICONTROLLER))
#define FOO_ICONTROLLER_GET_INTERFACE(obj)				\
    (G_TYPE_INSTANCE_GET_INTERFACE((obj), FOO_TYPE_ICONTROLLER,		\
				   FooIControllerInterface))

typedef struct _FooIController FooIController;
typedef struct _FooIControllerInterface FooIControllerInterface;

struct _FooIControllerInterface {
    GTypeInterface parent;

    void (*next)(FooIController *self);
    void (*prev)(FooIController *self);
    void (*power)(FooIController *self);
};

GType foo_icontroller_get_type(void);

void foo_icontroller_next(FooIController *self);
void foo_icontroller_prev(FooIController *self);
void foo_icontroller_power(FooIController *self);

#endif /* __ICONTROLLER_H_ */
