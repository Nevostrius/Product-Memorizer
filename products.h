#ifndef PRODUCTS_H_INCLUDED
#define PRODUCTS_H_INCLUDED

void enter(handle *dh, int *pos)
{
    printf("Enter Product Name: ");
    fgets(dh->product[*pos].product_name, 20, stdin);
    fflush(stdin);
    unique_product_id(dh, pos);
    printf("Enter product weight: ");
    scanf(" %lf", &dh->product[*pos].weight);
    printf("Enter your product stock: ");
    scanf(" %u", &dh->product[*pos].stock);
    printf("\nProduct with ID %d added.\n", dh->product[*pos].id);
}

void show(handle *dh)
{
    for(int i=0; i<dh->count; i++)
    {
        printf("\nMemory of product list at position %d\n", i+1);
        printf("Product Name = %s", dh->product[i].product_name);
        printf("Product ID %d \n", dh->product[i].id);
        printf("Product Weight %.2lf \n", dh->product[i].weight);
        printf("Product stock %u\n\n", dh->product[i].stock);
    }
}

handle *delete_entries(handle *dh)
{
    int what_to_delete = 0;
    char security_check;
    int id, j = -1;

    printf("Delete single element [1] or whole array? [2] (every other number to abort process): ");
    scanf(" %d", &what_to_delete);

    //Decide what should be deleted
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
                for(int i = j; i < dh->count; i++)
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

    return dh;
}

void change_entries(handle *dh)
{
    int id;

    printf("Type in the ID of the product you want to change:");
    scanf(" %d", &id);
    fflush(stdin);

    for(int i = 0; i < dh->count; i++)
    {
        if (dh->product[i].id == id)
        {
            enter(dh, &i);
        }
    }
}

void choose(handle *dh)
{
    char choice;

    do{
    printf("[E]nter, [D]elete, [S]how, [C]hange [Q]uit: ");
    scanf(" %c", &choice);
    test_choose(&choice);
    fflush(stdin);

    switch(choice)
    {
    case 'E':
        allocate_mem(dh);
        enter(dh, &dh->count);
        dh->count++;
        printf("%d Elements in memory\n\n", dh->count);
    break;

    case 'S':
        show(dh);
    break;

    case 'D':
        delete_entries(dh);
    break;

    case 'C':
        change_entries(dh);
    break;
    }

    }
    while(choice != 'Q');
    free(dh->product);
}

#endif
