#include "array_operations.hh"

int greatest_v1(int *itemptr, int size)
{
    int *max = itemptr;

    for ( auto i = itemptr; i < itemptr+size; i++) {

        if (*max < *i ) {
            *max = *i;
        }
    }
    return *max;
}

int greatest_v2(int *itemptr, int *endptr)
{
    int x = *itemptr;
    while( itemptr < endptr ) {
        if ( *itemptr > x ) {
            x = *itemptr;
        }
        itemptr++;
    }
    return x;
}

void copy(int *itemptr, int *endptr, int *targetptr)
{
    while ( itemptr < endptr ) {
        *targetptr = *itemptr;
        itemptr++;
        targetptr++;
    }
}

void reverse(int *leftptr, int *rightptr)
{
    int *pointer = leftptr, *pointer2 = rightptr-1;
    while( pointer < pointer2 ) {

        int temp = *pointer;
        *pointer = *pointer2;
        *pointer2 = temp;

        pointer++;
        pointer2--;
    }




}
