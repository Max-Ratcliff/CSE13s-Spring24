#include "item.h"
#include <string.h>
#include <stdio.h>


// implementation of the cmp() function on items, for when items are ints
bool cmp(item *i1, item *i2)
{
	return !strcmp(i1->key, i2-> key);

}
