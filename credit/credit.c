#include <cs50.h>
#include <stdio.h>
#include <math.h>


int digit_no_checking(long card_no);
int type_checking(long card_no,int no_digit);
int Luhn_check(long card_no, int no_digit);

int main(void)
{
    // ask user to input credit card number
    long card_no = get_long("Number: ");
// AE: 34 or 37
//Master: 51-55
//Visa:4
    int j = digit_no_checking(card_no);
    int card_result;
    printf("j: %i\n",j);
    card_result = type_checking(card_no,j);
    printf("type: %i\n", card_result);
    card_result = Luhn_check(card_no, j);

}

// No. of digit checking
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

// Check type of card
int type_checking(long card_no,int no_digit)
{
    // 0 = Invalid
    // 1 = AE
    // 2 = Master
    // 3 = Visa
    int type = 0;
    //int card_valid = Luhn_check(card_no);
    int card_valid = 1;
    if (card_valid == 1)
     {
        // get first 2 digit
        int first_2 = card_no / (long)pow(10.0,no_digit-2);
        printf("first 2 digit: %i\n",first_2);

        //AE or Master or Visa check
        if (first_2 == 34 || first_2 ==37)
        {
            type = 1;
        }
        if (first_2 >=51 && first_2 <=55)
        {
            type = 2;
        }
        if (first_2 >= 40 && first_2 <=49)
        {
            type = 3;
        }
     }
     return type;
}

int Luhn_check(long card_no, int no_digit)
{
    int valid;
    if (no_digit == 15 || no_digit == 13 || no_digit == 16)
    {
        //extract the every other digit
        for (int i = 1; i <= no_digit; i = i+2)
        {
            int ex_digit = card_no / (long)pow(10.0,i);
            printf("%i\n", ex_digit);
        }
        return valid = 1;
    }
    else
    {
        return valid = 0;
    }
}