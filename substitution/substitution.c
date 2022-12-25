#include <cs50.h>
#include <stdio.h>

int main(int argc, string argv[])
{
    //check command line - no. of characters
   int i = 0;
   int l = 0;
   while(argv[i] != '\0')
   {
        l++;
   }
   if (l != 26)
   {
    printf("Key must contain 26 characters.\n");
    return 1;
   }
}