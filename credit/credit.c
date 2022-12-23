#include <cs50.h>
#include <stdio.h>
#include <math.h>


int digit_no_checking(long card_no);
void type_checking(long card_no,int no_digit);
int Luhn_check(long card_no, no_digit);

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
int digit_no_checking(long card_no)
{   int check_digit = 0;
    int i = 15.0;
    do
    {
        //printf("%i\n",i);
        if (card_no /(long)pow(10.0,i)>0)
            {
                check_digit = 1;
            }
        i--;
    }
    while(check_digit==0);
    return i+2;
}

// check type of card
int type_checking(long card_no_1,int no_digit)
{
    // 0 = Invalid
    // 1 = AE
    // 2 = Master
    // 3 = Visa
    int type = 0;
    int card_valid = Luhn_check(card_no);

     // get first 2 digit
     int first_2 = card_no / (long)pow(10.0,no_digit-2);
     printf("%i\n",first_2);
}

int Luhn_checking(long card_no, no_digit)
{
    int valid;
    if (no_digit == 15 || no_digit == 13 || no_digit == 16)
    {

    }
    else
    {
        return valid = 0;
    }
}