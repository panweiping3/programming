#include "boy.h"

int main(void)
{
	g_type_init();
	Boy *b = boy_new();
	boy_set_name(b, "pwp");
	boy_set_age(b, 28);
	boy_info(b);

	return 0;
}
