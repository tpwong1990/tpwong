#include <cs50.h>
#include <stdio.h>

int check_no_char_command(string key);
int check_char_command(string key);

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
        if (char_valid == 0)
        {
            printf("The key should only cotain alphabetic characters.\n")
            return 1;
        }
        if (char_valid == -1)
        {
            prinft("The key cannot contain )
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