#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>

void parse(GHashTable *table, char *str, char *delim, char *subdelim)
{
	char *str1, *str2, *token, *key, *value;
	char *saveptr1, *saveptr2;
	int j;

	if (!table)
		return;

	for (j = 1, str1 = str; ; j++, str1 = NULL) {
		int i;
		token = strtok_r(str1, delim, &saveptr1);
		if (token == NULL)
			break;

		i = 0;
		for (str2 = token; ; str2 = NULL) {
			if (i == 0) {
				key = strtok_r(str2, subdelim, &saveptr2);
				if (key == NULL)
					break;
				i++;
			} else if (i == 1) {
				value = strtok_r(str2, subdelim, &saveptr2);
				if (value == NULL)
					break;
				i = 0;
				g_hash_table_insert(table, key, value);
			}
		}
	}
} 

void iterator(gpointer key, gpointer value ,gpointer user_data)
{
	 printf("key=%d, value=%d\n", strtol((char *)key, NULL, 10), strtol((char *)value, NULL, 10));
}

int main(int argc, char *argv[])
{
	GHashTable *table = NULL;

	if (argc != 4) {
		fprintf(stderr, "Usage: %s string delim subdelim\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	table = g_hash_table_new(g_str_hash, g_str_equal);
	if (table) 
		parse(table, argv[1], argv[2],argv[3]);
	g_hash_table_foreach(table, (GHFunc)iterator, NULL);
	exit(EXIT_SUCCESS);
}
