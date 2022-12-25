#include <cs50.h>
#include <stdio.h>

int main(int argc, string argv[])
{
    //check command line - no. of characters
   int i = 0;
   int l = 0;
   string s = argv[1];
   //printf("%s\n", s);
   while(s[i] != '\0')
   {
        l++;
        i++;
   }
   if (l != 26)
   {
    printf("Key must contain 26 characters.\n");
    return 1;
   }
}