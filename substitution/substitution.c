#include <cs50.h>
#include <stdio.h>
#include <ctype.h>

int check_no_char_command(string key);
int check_char_command(string key);
int check_repeat_char(int no_char, string key);
char encrypt(char c, int map[]);

int main(int argc, string argv[])
{
    //check command line - no. of command line
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    else
    {
        //check command line - no. of characters
        int no_char = check_no_char_command(argv[1]);
        //printf("no_char: %i\n", no_char);
        int char_valid = check_char_command(argv[1]);
        //printf("valid %i\n", char_valid);
        int repeat = check_repeat_char(no_char, argv[1]);
        if (no_char != 26)
        {
            printf("Key must contain 26 characters.\n");
            return 1;
        }
        if (char_valid == 0)
        {
            if (repeat == 1)
            {
                printf("The key cannot cotain repeated characters.\n");
                return 1;
            }
            else
            {
            }
        }
        else
        {
            printf("The key should only cotain alphabetic characters.\n");
            return 1;
        }
    }
    //printf("a\n");

    //convert the key to lowercase
    char key_lower[25];
    string s_temp = argv[1];
    for(int i = 0; i <= 25; i++)
    {
        key_lower[i] = tolower(s_temp[i]);
    }

    //assgin original map
    char ori[25];
    for (int i = 0; i <= 25; i++)
    {
        ori[i] = 97 + i;
    }

    //mapping the key
    int map[25];
    for (int i = 0; i <= 25; i++)
    {
        map[i] = key_lower[i] - ori [i];
    }

    //ask user to input the plaintext
    string plain = get_string("Plaintext: ");

    //do encrypt
    int j = 0;
    char cipher[check_no_char_command(plain)];
    printf("ciphertext: ");
    while(plain[j] != '\0')
    {
        cipher[j]= encrypt(plain[j], map);
        printf("%c",cipher[j]);
        j++;
    }
    printf("\n");
}

int check_no_char_command(string key)
{
    int i = 0;
    int l = 0;
   while(key[i] != '\0')
   {
        l++;
        i++;
   }
   return l;
}

int check_char_command(string key)
{
    int i = 0;
    int valid = 0;
    while(key[i] != '\0')
    {
        if ((key[i] >= 'a' && key[i] <= 'z') || (key[i] >= 'A' && key[i] <= 'Z'))
        {
        }
        else
        {
            valid = 1;
            break;
        }
        i++;
    }
    return valid;
}

int check_repeat_char(int no_char, string key)
{
    for (int j = 0; j <= no_char-1; j++)
    {
        char temp = key[j];
        for (int i = 0; i <= no_char-1; i++)
        {
            if (i != j)
            {
                if (temp == key[i])
                {
                    return 1;
                    break;
                }
            }
        }
    }
    return 0;
}

char encrypt(char c, int map[])
{
    char c_out;
    int temp;
    if ((c >= 'a') && (c <= 'z'))
    {
        temp = c - 96;
        c_out = c - map[temp];
    }
    else
    {
        if ((c >= 'A') && (c >= 'Z'))
        {
            temp = c - 64;
            c_out = c - map[temp];
        }
        else
        {
            c_out = c;
        }
    }
    return c_out;
}