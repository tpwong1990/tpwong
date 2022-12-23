#include <cs50.h>
#include <stdio.h>
#include <math.h>


int digit_no_checking(long card_no_1);
void type_checking(long card_no_1,int no_digit);

int main(void)
{
    // ask user to input credit card number
    long card_no = get_long("Number: ");
// AE: 34 or 37
//Master: 51-55
//Visa:4
    int j = digit_no_checking(card_no);
    printf("%i\n",j);
    type_checking(card_no,j);

}

// function for no of digit checking
int digit_no_checking(long card_no_1)
{   int check_digit = 0;
    int i = 15.0;
    do
    {
        //printf("%i\n",i);
        if (card_no_1 /(long)pow(10.0,i)>0)
            {
                check_digit = 1;
            }
        i--;
    }
    while(check_digit==0);
    return i+2;
}

// check type of card
void type_checking(long card_no_1,int no_digit)
{
     // get first 2 digit
     int first_2 = card_no_1 / (long)pow(10.0,no_digit-2);
     printf("%i\n",first_2);
    //if (no_digit ==16)
}