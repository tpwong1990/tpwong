#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    // ask user to input credit card number
    long card_no = get_long("Number: ");
// AE: 34 or 37
//Master: 51-55
//Visa:4
int check_digit=0;
int i = 15.0;
    do
    {
        printf("%i\n",i);
        if (card_no % (long)pow(10.0,i)==1)
            {
                check_digit = 1;
            }
        i--;
    }
    while(check_digit==0);
}