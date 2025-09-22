#include "swap.h"

void Swap(char *left, char *right)
{
	char center = *left;
	*left = *right;
	*right = center;
}
