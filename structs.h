#ifndef STRUCTS_H_INCLUDED
#define STRUCTS_H_INCLUDED

typedef struct
{
    char product_name[20];
    int id;
    double weight;
    unsigned int stock;
}article;

typedef struct
{
    article *product;
    int allocation;
    int count;
    int save_counter;
}handle;


#endif
