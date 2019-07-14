#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <memory.h>
#define START 3
#include "structs.h"
#include "help_functions.h"
#include "products.h"

int main()
{
    handle national_products = {NULL, START, 0, 0};

    printf("Dynamic Product Memorizer 1.1 \n");
    choose(&national_products);
}
