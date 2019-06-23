#ifndef PRODUCTS_H_INCLUDED
#define PRODUCTS_H_INCLUDED

int test_choose(char *choice)
{
    *choice = toupper(*choice);
    return (*choice);
}

void enter(handle *dh)
{

    if(dh->product == NULL)
    {
        printf("No memory allocated, allocating memory... \n");
        dh->product = (article *) malloc(dh->allocation * sizeof(article));
        if(dh->product == NULL){printf("Error allocating memory. Exit program\n"); exit(EXIT_FAILURE);}
        printf("Memory in the size %d allocated... you may add products to memory\n\n", dh->allocation);
    }

    if(dh->count+1 > dh->allocation)
    {
        printf("\nResizing memory necessary...\n");
        dh->product = (article*) realloc(dh->product, (dh->allocation+1) * sizeof(article));
        if(dh->product == NULL){printf("Error allocating memory. Exit program\n"); exit(EXIT_FAILURE);}
        dh->allocation++;
        printf("Memory successfully reallocated. Memory can currently hold %d items\n", dh->allocation);
    }

    printf("Enter product ID Number: ");
    scanf(" %d", &dh->product[dh->count].id);
    printf("Enter product weight: ");
    scanf(" %lf", &dh->product[dh->count].weight);
    printf("\nProduct ID: %d Weight: %.2lf added.\n", dh->product[dh->count].id, dh->product[dh->count].weight);
    dh->count++;
    printf("%d Elements in memory\n\n", dh->count);
}

void show(handle *dh)
{
    for(int i=0; i<dh->count; i++)
    {
        printf("\nMemory of at position %d\n", i+1);
        printf("Product ID %d \n", dh->product[i].id);
        printf("Product Weight %.2lf \n\n", dh->product[i].weight);
    }
}

void delete_entries(handle *dh)
{
    int what_to_delete = 0;
    char security_check;
    int id, j = -1;

    printf("Delete single element [1] or whole array? [2] (every other number to abort process): ");
    scanf(" %d", &what_to_delete);

    switch(what_to_delete)
    {
    case 1:
            printf("\nEnter the ID you want to delete: ");
            scanf(" %d", &id);

            for(int i=0; i<dh->count; i++)
            {
                if (id == dh->product[i].id)
                {
                    printf("Entered ID found at position %d\n", i+1);
                    j = i;
                    break;
                }
            }

            if (j>=0)
            {
                for(int i=j; i<dh->count; i++)
                {
                dh->product[i] = dh->product[i+1];
                }

            dh->count--;
            }

            if(dh->count < dh->allocation && dh->count >= START)
            {
                printf("\nReallocating memory...\n");
                dh->product = (article *) realloc(dh->product, (dh->allocation-1) * sizeof(article));
                dh->allocation--;
                printf("Allocated memory is %d\n", dh->allocation);
            }

    break;

    case 2:
            printf("Are you sure to delete everything Y/N?: ");
            scanf(" %c", &security_check);
            test_choose(&security_check);
            if(security_check == 'Y')
            {
            free(dh->product);
            dh->product = NULL;
            dh->count = 0;
            printf("Elements deleted and memory freed.\n\n");
            }
            else
            {
            printf("Elements won't be deleted.\n");
            }
    break;
    }
}


void choose(handle *dh)
{
    char choice;

    printf("Dynamic Product Memorizer 1.0 \n");
    do{
    printf("[E]nter, [D]elete, [S]how, [Q]uit: ");
    scanf(" %c", &choice);
    test_choose(&choice);

    switch(choice)
    {
    case 'E':
             enter(dh);
             break;

    case 'S':
             show(dh);
             break;
    case 'D':
             delete_entries(dh);
             break;
    }
    }
    while(choice != 'Q');

    free(dh->product);
}

#endif
