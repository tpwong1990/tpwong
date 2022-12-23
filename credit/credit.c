#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // ask user to input credit card number
    long card_no = get_long("Number: ");
// AE: 34 or 37
//Master: 51-55
//Visa:4
    for(int i = 16; i<0; i--)
    {
        if (card_no % 10)
    }
}