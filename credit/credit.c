#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // ask user to input credit card number
    long card_no;
    do
    {
        card_no = get_long("Number: ");
    } while(card_no >0);
}