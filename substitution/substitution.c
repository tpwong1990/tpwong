#include <cs50.h>
#include <stdio.h>

int check_no_char_command(string key);
int check_char_command(string key);
int check_repeat_char(string key);

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
        int char_valid = check_char_command(argc[1]);
        if (no_char != 26)
        {
            printf("Key must contain 26 characters.\n");
            return 1;
        }
        if (char_valid == 1)
        {
            printf("The key should only cotain alphabetic characters.\n");
            return 1;
        }
        if (char_valid == -1)
        {
            prinft("The key cannot contain repeated characters.\n");
            return 1;
        }
    }
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
    int repeat = check_repeat_char(key);
    if (repeat = 0)
    {
        while(key[i] != '\0')
        {
            if (key[i] >= 'a' && key[i] <= 'z') || (key[i] >= 'A' && key[i] <= 'Z')
            {
                return valid = 0;
            }
            else
            {
                return valid = 1;
            }
        }
    }
    else
    {
        return valid = -1;
    }
}

int check_repeat_char(string key)
{
    
}