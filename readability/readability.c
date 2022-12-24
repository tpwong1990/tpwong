#include <cs50.h>
#include <stdio.h>
#include <math.h>

int count_letters(string text);
int count_words(string text);
int count_sent(string text);
string coleman_liau(int l, int w, int s);

int main(void)
{
    string s = get_string("Text: ");
    int letter_c = count_letters(s);
    int word_c = count_words(s);
    int sent_c = count_sent(s);
    //printf("%i\n", letter_c);
    //printf("%i\n", word_c);
    //printf("%i\n", sent_c);
    string c_l_index = coleman_liau(letter_c, word_c, sent_c);
    printf("Grade %s\n", c_l_index);
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
            if (((text[i-1] == '!' || text[i-1] == '?') || (text[i-1] == ',' || text[i-1] == '.'))&& i > 1)
            {

            }
            else
            {
                count++;
            }
        }
        else
        if ((text[i] == '!' || text[i] == '?') || (text[i] == ',' || text[i] == '.'))
        {
            count++;
        }
        i++;
    }
    return count;
}

int count_sent(string text)
{
    int i = 0;
    int count = 0;
    while (text[i] != '\0')
    {
        if (((text[i] == '!' || text[i] == '?') || text[i] == '.'))
        {
            count++;
        }
        i++;
    }
    return count;
}

string coleman_liau(int l, int w, int s)
{
    double ave_l = (double) l / w * 100.0;
    double ave_s = (double) s / w * 100.0;
    long index = 0.0588 * ave_l - 0.296 * ave_s -15.8;
    int x = round(index);
    if (x >= 16 )
    {
        string temp = "16+";
    }
    else
    {
        string temp = x;
    }
    return temp;
}