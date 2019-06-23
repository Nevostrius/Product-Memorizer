#ifndef STRUCTS_H_INCLUDED
#define STRUCTS_H_INCLUDED

typedef struct
{
    int id;
    double weight;
}article;

typedef struct
{
    article *product;
    int allocation;
    int count;
}handle;


#endif
