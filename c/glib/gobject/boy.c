/* boy.c */
#include "boy.h"

enum { BOY_BORN, LAST_SIGNAL };
static gint boy_signals[LAST_SIGNAL] = { 0 };
static void boy_born(void);
static void boy_init(Boy *boy);
static void boy_class_init(BoyClass *boyclass);
enum {
	PROP_0,
	PROP_AGE,
	PROP_NAME,
	LAST_PROP
};

typedef struct {
	gint age;
	gchar *name;
} BoyPrivate;

#define BOY_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), BOY_TYPE, BoyPrivate))

GType boy_get_type(void)
{
	static GType boy_type = 0;
	if(!boy_type)
	{
		static const GTypeInfo boy_info = {
			sizeof(BoyClass),
			NULL,NULL,
			(GClassInitFunc)boy_class_init,
			NULL,NULL,
			sizeof(Boy),
			0,
			(GInstanceInitFunc)boy_init
		};

		boy_type = g_type_register_static(G_TYPE_OBJECT, "Boy", &boy_info, 0);
	}

	return boy_type;
}

static void boy_init(Boy *boy)
{
	BoyPrivate *priv = BOY_GET_PRIVATE (boy);
	priv->age = 0;
	priv->name = "none";
}

static void boy_class_init(BoyClass *boyclass)
{
	GObjectClass *object_class = G_OBJECT_CLASS(boyclass);
	g_type_class_add_private (boyclass, sizeof (BoyPrivate));

	boyclass->boy_born = boy_born;

	boy_signals[BOY_BORN] = g_signal_new("boy_born",
				BOY_TYPE,
				G_SIGNAL_RUN_FIRST,
				G_STRUCT_OFFSET(BoyClass,boy_born),
				NULL,NULL,
				g_cclosure_marshal_VOID__VOID,
				G_TYPE_NONE, 0, NULL);
}

Boy *boy_new(void)
{
	Boy *boy;
	boy = g_object_new(BOY_TYPE, NULL);
	g_signal_emit(boy,boy_signals[BOY_BORN],0);
	return boy;
}

int boy_get_age(Boy *boy)
{
	BoyPrivate *priv = BOY_GET_PRIVATE (boy);
	return priv->age;
}

void boy_set_age(Boy *boy, int age)
{
	BoyPrivate *priv = BOY_GET_PRIVATE (boy);
	priv->age = age;
}

char *boy_get_name(Boy *boy)
{
	BoyPrivate *priv = BOY_GET_PRIVATE (boy);
	return priv->name;
}

void boy_set_name(Boy *boy, char *name)
{
	BoyPrivate *priv = BOY_GET_PRIVATE (boy);
	priv->name = name;
}

Boy*  boy_new_with_name(gchar *name)
{
	Boy* boy;
	boy = boy_new();
	boy_set_name(boy, name);
	return boy;
}

Boy*  boy_new_with_age(gint age)
{
	Boy* boy;
	boy = boy_new();
	boy_set_age(boy, age);
	return boy;
}

Boy *boy_new_with_name_and_age(gchar *name, gint age)
{
	Boy *boy;
	boy = boy_new();
	boy_set_name(boy,name);
	boy_set_age(boy,age);
	return boy;
}

static void boy_born(void)
{
	g_print("Message : A boy was born .\n");
}

void  boy_info(Boy *boy)
{
	g_print("The Boy name is %s\n", boy_get_name(boy));
	g_print("The Boy age is %d\n", boy_get_age(boy));
}

