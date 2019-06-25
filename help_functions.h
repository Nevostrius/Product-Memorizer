#ifndef HELP_FUNCTIONS_H_INCLUDED
#define HELP_FUNCTIONS_H_INCLUDED

int test_choose(char *choice)
{
    *choice = toupper(*choice);
    return (*choice);
}

void unique_product_id(handle *dh)
{
    printf("Enter unique product ID Number: ");
    scanf(" %d", &dh->product[dh->count].id);

    for (int i=0; i < dh->count;i++)
    {
        if(dh->product[i].id == dh->product[dh->count].id)
        {
            printf("Your product ID is not Unique. Please try again.\n");
            unique_product_id(dh);
        }
    }
}


#endif // HELP_FUNCTIONS_H_INCLUDED
