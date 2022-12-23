#include <cs50.h>
#include <stdio.h>

void create_space(int space_no)
{
    for (int j = 0; j < space_no; j++)
    {
        printf(" ");
    }
}
void create_hash(int hash_no)
{
    for (int i = 0; i < hash_no; i++)
    {
        printf("#");
    }
}

int main(void)
{
    //ask user to input the height of the pyramids
    int n;
    do
    {
        n = get_int("Height: ");
    }
    while (n < 1 || n > 8);

    for (wget https://cdn.cs50.net/2021/fall/psets/1/credit.zipint line = 1; line < n + 1; line++)
    {
        // print # to build the left side of pyramids
        create_space(n - line);
        create_hash(line);

        // print space to the middle
        printf("  ");

        // print # build the right side of pyramids
        create_hash(line);
        //create_space(n-line);
        // switch to next line
        printf("\n");
    }
}