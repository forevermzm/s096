#include <stdio.h> 
int main(void){ 
    FILE *input = fopen("floating.txt", "r" ); 
    if (!input)perror("fopen"); 
    fclose( input ); 
    return 0; 
}
