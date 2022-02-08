#include <stdio.h>
#include <string.h>

int main(){
    char *s="59b997fa";
    // for(int i=strlen(s)-1;i>=0;i--)
    //     printf("%x ",(int)s[i]);
    for(int i=0;i<strlen(s);i++)
        printf("%x ",(int)s[i]);
    return 0;
}