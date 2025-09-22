#include "revert_string.h"
#include <string.h>

void RevertString(char *str)
{
	int l = strlen(str);
	char sv;
	for (int i = 0; i < l / 2; i++)
	{
		sv = str[i];
		str[i] = str[l- i - 1];
		str[l- i - 1] = sv;
	}
}

