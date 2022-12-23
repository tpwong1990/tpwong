#include <cs50.h>
#include <stdio.h>
#include <math.h>


int digit_no_checking(long card_no);
int type_checking(long card_no, int no_digit);
int Luhn_check(long card_no, int no_digit);
int extract_digit(long number, int no_digit, int target_digit);

int main(void)
{
    // ask user to input credit card number
    long card_no = get_long("Number: ");

    // check no of digit
    int j = digit_no_checking(card_no);
    //printf("j: %i\n",j);

    // check the type
    int card_result = type_checking(card_no, j);
    if (card_result == 0)
    {
        printf("INVALID\n");
    }
    if (card_result == 1)
    {
        printf("AMEX\n");
    }
    if (card_result == 2)
    {
        printf("MASTERCARD\n");
    }
    if (card_result == 3)
    {
        printf("VISA\n");
    }
}

// No. of digit checking
int digit_no_checking(long card_no)
{
    int check_digit = 0;
    int i = 15.0;
    do
    {
        //printf("%i\n",i);
        if (card_no / (long)pow(10.0, i) > 0)
        {
            check_digit = 1;
        }
        i--;
    }
    while (check_digit == 0);
    return i + 2;
}

// Check type of card
int type_checking(long card_no, int no_digit)
{
    // 0 = Invalid
    // 1 = AE
    // 2 = Master
    // 3 = Visa
    int type = 0;
    int card_valid = Luhn_check(card_no, no_digit);
    if (card_valid == 1)
    {
        // get first 2 digit
        int first_2 = card_no / (long)pow(10.0, no_digit - 2);
        //printf("first 2 digit: %i\n",first_2);

        //AE or Master or Visa check
        if ((first_2 == 34 || first_2 == 37) && no_digit == 15)
        {
            type = 1;
        }
        if ((first_2 >= 51 && first_2 <= 55) && no_digit == 16)
        {
            type = 2;
        }
        if ((first_2 >= 40 && first_2 <= 49) && (no_digit == 13 || (no_digit == 16)))
        {
            type = 3;
        }
    }
    return type;
}

int Luhn_check(long card_no, int no_digit)
{
    int valid;
    int digit_temp = 0;

    {
        // add digits which is multiplied by 2
        for (int i = 2; i <= no_digit; i = i + 2)
        {
            //printf("%i %i\n", i, extract_digit(card_no, no_digit, i));
            int temp = extract_digit(card_no, no_digit, i) * 2;
            if (temp >= 10)
            {
                int temp1 = temp / 10;
                int temp2 = temp % 10;
                digit_temp = digit_temp + temp1 + temp2;
            }
            else
            {
                digit_temp = digit_temp + temp;
            }
        }
        // add the other digits
        for (int i = 1; i <= no_digit; i = i + 2)
        {
            digit_temp = digit_temp + extract_digit(card_no, no_digit, i);
        }
        if (digit_temp % 10 == 0)
        {
            return valid = 1;
        }
        else
        {
            return valid = 0;
        }
    }
}

int extract_digit(long number, int no_digit, int target_digit)
{
    long temp = number;
    int digit;
    for (int i = 1; i <= no_digit; i++)
    {
        digit = temp % 10;
        temp = temp / 10;
        //printf("%i %i\n",i, target_digit);
        if (i == target_digit)
        {
            //printf("digit %i %i\n", i, digit);
            break;
        }
    }
    return digit;
}
