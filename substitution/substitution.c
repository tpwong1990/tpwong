#include <cs50.h>
#include <stdio.h>

int check_no_char_command(string key);

int main(int argc, string argv[])
{
    //check command line - no. of command line
    if (argc != 1)
    {
        printf("Usage: ./substitution key\n");
    }
    //check command line - no. of characters
    int no_char = check_no_char_command(argv[1]);
   if (no_char != 26)
   {
    printf("Key must contain 26 characters.\n");
    return 1;
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