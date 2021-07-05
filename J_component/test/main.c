#include <stdio.h>
#include <string.h>

void file_write(char* str)
{
   FILE *fp;
   fp = fopen("data.cs", "a");
   fprintf(fp, "\n%s",str);
   printf("Your message is appended in data.txt file.");
   fclose(fp);
}


int main()
{
   char str[100];
   scanf("%s",str);
   file_write(str);
   return 0;
}
