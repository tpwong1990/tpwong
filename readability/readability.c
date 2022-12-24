#include <cs50.h>
#include <stdio.h>

int count_letters(string text);
int count_words(string text);
int count_sent(string text);

int main(void)
{
    string s = get_string("Text: ");
    int letter_c = count_letters(s);
    int word_c = count_words(s);
    printf("%i\n", letter_c);
    printf("%i\n", word_c);
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

int count_words(string text)
{
    int i = 0;
    int count = 0;
    while (text[i] != '\0')
    {
        if(text[i] == ' ')
        {
            if ((text[i] == '!' || text[i] == '?') || (text[i] == ',' || text[i] == '.'))
        }
        else
        if ((text[i] == '!' || text[i] == '?') || (text[i] == ',' || text[i] == '.'))
        {


        }


    }
    return count;
}