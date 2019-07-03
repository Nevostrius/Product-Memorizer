#ifndef HELP_FUNCTIONS_H_INCLUDED
#define HELP_FUNCTIONS_H_INCLUDED

int test_choose(char *choice)
{
    *choice = toupper(*choice);
    return (*choice);
}

void unique_product_id(handle *dh, int *pos)
{
    printf("Enter unique product ID Number: ");
    scanf(" %d", &dh->product[*pos].id);

    for (int i=0; i < dh->count; i++)
    {
        if(dh->product[i].id == dh->product[*pos].id && i != *pos)
        {
            printf("Your product ID is not Unique. Please try again.\n");
            unique_product_id(dh, pos);
        }
    }
}

void allocate_mem(handle *dh)
{
    //Allocate Memory to Array product
    if(dh->product == NULL)
    {
        printf("No memory allocated, allocating memory... \n");
        dh->product = (article *) malloc(dh->allocation * sizeof(article));
        if(dh->product == NULL){printf("Error allocating memory. Exit program\n"); exit(EXIT_FAILURE);}
        printf("Memory in the size %d allocated... you may add products to memory\n\n", dh->allocation);
    }

    //Reallocate Memory for Array product if necessary
    if(dh->count+1 > dh->allocation)
    {
        printf("\nResizing memory necessary...\n");
        dh->product = (article*) realloc(dh->product, (dh->allocation+1) * sizeof(article));
        if(dh->product == NULL){printf("Error allocating memory. Exit program\n"); exit(EXIT_FAILURE);}
        dh->allocation++;
        printf("Memory successfully reallocated. Memory can currently hold %d items\n", dh->allocation);
    }
}

#endif // HELP_FUNCTIONS_H_INCLUDED
