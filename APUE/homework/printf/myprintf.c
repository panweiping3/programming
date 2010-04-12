/*
 * only support  'o', 'd', 'x', 'c', 's'
*/

#include<unistd.h>
#include<stdlib.h>
#include<stdarg.h>
#include<string.h>

#define STDOUT 		1
#define LINE_LENGTH 80
#define CMD_NUM 	5 
#define RADIX_8		8 
#define RADIX_10	10 
#define RADIX_16	16 
#define BITS_32		32 

char cmd[CMD_NUM] = {'o', 'd', 'x', 'c', 's'};

int myprintf(const char *format, ...);
void mysprintf(char *buf, int radix, int value);
int analyse_args(char *format_p, char *command, int *n);
int cal_int_length(int value);
void print_int(char **p, int value, int radix, int require_size);
void print_char(char **p, char ch, int require_size);
void print_str(char **d_p, char *s_p, int require_size);

int myprintf(const char *format, ...)
{
	int i = 0;
	char *format_p = NULL;
	va_list pvar;
	char buf[LINE_LENGTH];
	char *buf_p = buf;

	int ch = '\0';
	int  value = 0;
	char *str = NULL;
	int var_length = 0;

	int require_size = 0;
	int format_size = 0;

	format_size = strlen(format);
	format_p = (char *)format;
	va_start(pvar, format);
	memset(buf, ' ', LINE_LENGTH);

	if (format_p == NULL)
		return -1;

	while((format_p != NULL) && (format_size > 0))
	{
		require_size = 0;
		char command = '\0';
		if (*format_p == '%')
		{	
			if (analyse_args(format_p, &command, &require_size ) == 0)
			{
				format_size -= cal_int_length(require_size) + 2;
			
				switch (command)
				{
					case 'o':	value = va_arg(pvar, int);			
								print_int(&buf_p, value, RADIX_8, require_size);
								format_p += cal_int_length(require_size) + 2;
								break;
					case 'd':	value = va_arg(pvar, int);			
								print_int(&buf_p, value, RADIX_10, require_size);
								format_p += cal_int_length(require_size) + 2;
								break;
					case 'x':	value = va_arg(pvar, int);			
								print_int(&buf_p, value, RADIX_16, require_size);
								format_p += cal_int_length(require_size) + 2;
								break;
					case 'c':	value = va_arg(pvar, int);			
								print_char(&buf_p, value, require_size);
								format_p += cal_int_length(require_size) + 2;
								break;
					case 's':	str = va_arg(pvar, char *);			
								print_str(&buf_p, str, require_size);
								format_p += cal_int_length(require_size) + 2;
								break;
					default:
								break;
				}
			}// end if analyse_args
			else 
				return -1;	
		}//end if %
		
		*buf_p++ = *format_p++;
		format_size--;
	}	

	write(STDOUT, buf, LINE_LENGTH);
	write(STDOUT, "\n", 1);

	return 0;
}

int analyse_args(char *format_p, char *command, int *n)
{
	int i;
	char *tmp = format_p + 1;
	char buf[BITS_32] = {'\0'};
	char *p = tmp;

	while(((*p) >= '0') && ((*p) <= '9'))
		p++;

	memcpy((void *)buf, (void *)tmp, p-tmp);
	*n = atoi(buf);

	for(i=0; i<CMD_NUM; i++)
		if ((*p) == cmd[i])
		{
			*command = cmd[i];
			return 0;
		}

	return -1;
}	

int cal_int_length(int value)
{
	int length = 1;
	
	while ((value/RADIX_10) != 0)
	{
		length++;
		value/=RADIX_10;
	}
	
	return length;
}

void print_char(char **p, char ch, int require_size)
{
	if (require_size > 1)
		(*p) += require_size - 1;
	
	**p = ch;
	(*p) += 1;

	return;
}

void print_int(char **p, int value, int radix, int require_size)
{
	char buf[BITS_32];
	int var_size = 0;

	memset(buf, ' ', BITS_32);	
	mysprintf(buf, radix, value);	
	var_size = strlen(buf);

	if (require_size > var_size)
		(*p) += require_size - var_size;
			
	memcpy((*p), buf, var_size);
	(*p) += var_size;

	return;
}

void print_str(char **d_p, char *s_p, int require_size)
{
	char buf[LINE_LENGTH];
	int var_size = 0;
	
	var_size = strlen(s_p);
	memset(buf, ' ', LINE_LENGTH);
	memcpy(buf, s_p, var_size);
 
	if (require_size > var_size)
		(*d_p) += require_size - var_size;

	memcpy((*d_p), buf, var_size);
	(*d_p) += var_size;

	return;
}

void mysprintf(char *buf, int radix, int value)
{
	char num[BITS_32];
	char *p = num;	
	char *buf_p = buf;	
	memset(num, ' ', BITS_32);

	while(value != 0)
	{
		*p = value % radix + '0';
		value /= radix;
		p++;
	}
	
	p--;
	
	while(p != num)
		*buf_p++ = *p--;
	
	*buf_p++ = *p--;
	*buf_p = '\0';	
}

int main()
{
	char ch = 'a';
	char *str = "abcde";
	int i = 12345;
	myprintf("%10s \n %10c \n %10x \n %10o \n %10d \n", str, ch, i, i, i);
}
