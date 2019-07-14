#ifndef PRODUCTS_H_INCLUDED
#define PRODUCTS_H_INCLUDED

void enter(handle *dh, int *pos)
{
    printf("Enter Product Name: ");
    scanf(" %s", dh->product[*pos].product_name);
    unique_product_id(dh, pos);
    printf("Enter product weight: ");
    scanf(" %lf", &dh->product[*pos].weight);
    printf("Enter your product stock: ");
    scanf(" %u", &dh->product[*pos].stock);
    printf("\nProduct with ID %d added.\n", dh->product[*pos].id);
}

void print(handle *dh)
{
    for(int i=0; i<dh->count; i++)
    {
        printf("\nMemory of product list at position %d\n", i+1);
        printf("Product Name = %s \n", dh->product[i].product_name);
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

void save_data(handle *dh, FILE *fp)
{
    int counting, i = 0;

    fp = fopen("Output.txt", "at+");

    if (fp == NULL)
        printf("Error creating File\n");

    for (i = dh->save_counter; i < dh->count; i++)
    {
        counting = fprintf(fp, "%s;%d;%.2lf;%u\n", dh->product[i].product_name, dh->product[i].id, dh->product[i].weight, dh->product[i].stock);
        if (counting == -1)
            printf("Error writing content");
    }

    dh->save_counter = i;

    fclose(fp);
}

int read_data(handle *dh, FILE *fp)
{
    char choice;
    int n = 0;

    fp = fopen("Output.txt", "r+");
    if (fp == NULL)
        return 0;

    printf("Do you want to import a file? Y/N: ");
    scanf(" %c", &choice);
    test_choose(&choice);

    if(choice == 'Y')
    {
        while(!feof(fp))
        {
            allocate_mem(dh);
            n = fscanf(fp, " %[^;];%d;%lf;%u", dh->product[dh->count].product_name, &dh->product[dh->count].id, &dh->product[dh->count].weight, &dh->product[dh->count].stock);

            if (n == -1)
            {
                break;
            }

            if (n != 4)
            {
                printf("Error importing file. Please check line %d. Renaming your input file and continue...\n\n", dh->count+1);
                fclose(fp);
                if (rename("Output.txt", "Output_error.txt"))
                    printf("Error renaming \n");
                return 0;
            }
            dh->count++;
        }
        fclose(fp);
        dh->save_counter = dh->count;
        return dh->count;
    }

    fclose(fp);
    return 0;
}

void choose(handle *dh)
{
    char choice;
    FILE *fp = NULL;

    read_data(dh, fp);
    void rewind(FILE *fp);

    do{
    printf("[E]nter, [D]elete, [P]rint, [C]hange [Q]uit [S]ave: ");
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

    case 'P':
        print(dh);
    break;

    case 'D':
        delete_entries(dh);
    break;

    case 'C':
        change_entries(dh);
    break;

    case 'S':
        save_data(dh, fp);
    break;
    }

    }
    while(choice != 'Q');
    free(dh->product);
}

#endif
