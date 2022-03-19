#include <stdio.h>

int a=0;

void func(){
    printf("%d",a);
}
int main(int argc, char const *argv[])
{
    a=2;
    func();   
    return 0;
}
