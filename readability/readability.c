#include <cs50.h>
#include <stdio.h>

int count_letters(string text);
int main(void)
{
    string s = get_string("Text: ");
    int letter_c = count_letters(s);
    printf("%i\n", letter_c);
}

int count_letters(string text)
{
    int i = 0;
    int count = 0;
    while (text[i] != '\0')
    {
        if ((text[i] >= 'A' && text[i] <= 'Z') || (text[i] >= 'a' && text[i] <= 'z'))
        {
            count++;
        }
        i++;
    }
    return count;
}