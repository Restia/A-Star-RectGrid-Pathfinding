#include "Misc.h"

char* int2String(int num)
{
	static char str[10];
	int minus = 0;
	if (num < 0) 
	{
		num = -num;
		minus = 1;
	}
	for (int i = 0; i < 10; i++) str[i] = 0;
	int tmp, count;
	count = 0;
	if (num == 0)
	{
		str[0] = '0';
		str[1] = '\0';
		return str;
	}
	while (num != 0)
	{
		tmp = num % 10;
		num = num / 10;
		str[count] = tmp + '0';
		count++;
	}

	for (int i = 0; i < count / 2; i++)
	{
		swap(str[i], str[count - i - 1]);
	}
	str[count + 1] = '\0';
	if (minus == 1)
	{
		char tmp[10];
		strcpy(tmp, "-");
		strcat(tmp, str);
		strcpy(str, tmp);
	}
	return str;
};

