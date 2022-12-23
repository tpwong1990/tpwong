#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // ask user to input credit card number
    long card_no = get_long("Number: ");
// AE: 34 or 37
//Master: 51-55
//Visa:4
int check_digit=0;
double i = 15.0;
    do
    {
        if (card_no % pow(10.0,i)==1)
            {
                check_digit = 1
            }
        i--
    }
    while(check_digit==0)
}