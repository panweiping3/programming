#include <stdio.h>
#include <string.h>

bool WildSearch(char *source, int s_length, char *pattern, int p_length, bool full, char pre_char)
{
   if (s_length == 0 && p_length != 0)
   {
       if (p_length == 1 && pattern[0] == '*')
           return true;
       else
           return false;
   }
   else if (s_length != 0 && p_length == 0)
   {
       if (full)
           return false;
       else
           return true;
   }
   else if (s_length == 0 && p_length == 0)
       return true;

   if (pattern[0] == '*')
   {
       pattern++;
       p_length--;

       if (p_length == 0)
       {
           return true;
       }

       return WildSearch(source, s_length, pattern, p_length, full, '*');
   }
   else if (pattern[0] == '?')
   {
       source++;
       s_length--;
       pattern++;
       p_length--;

       return WildSearch(source, s_length, pattern, p_length, full, '?');
   }
   else
   {
       char *psz_star_pos = strchr(pattern, '*');
       char *psz_question_pos = strchr(pattern, '?');
       int n_len_to_star = (psz_star_pos == NULL) ? (int)strlen(pattern) : (int)(psz_star_pos - pattern);
       int n_len_to_question = (psz_question_pos == NULL) ? (int)strlen(pattern) : (int)(psz_question_pos - pattern);

       int n_compare_len = n_len_to_question > n_len_to_star ? n_len_to_star : n_len_to_question;

       if (strncmp(source, pattern, n_compare_len) == 0)
       {
           pre_char = pattern[0];
           source++;
           s_length--;
           pattern++;
           p_length--;

           return WildSearch(source, s_length, pattern, p_length, full, pre_char);
       }
       else
       {
           if (pre_char != '*')
               return false;

           source++;
           s_length--;

           return WildSearch(source, s_length, pattern, p_length, full, pre_char);
       }
   }

   return true;
}

int main(int argc, char** argv)
{
   	char source[]= "abbb";
   	char pattern[] = "*ab";

   	bool result = WildSearch(source, (int)strlen(source), pattern, (int)strlen(pattern), false, ' ');

	if (result == true)
	   	printf("match\n");
	else
		printf("don't match\n");

 	return 0;
}
