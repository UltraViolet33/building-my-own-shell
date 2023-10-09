#include <stdio.h>
#include <stdlib.h>

void lsh_loop(void);



int main(int argc, char **argv)
{
    // load config files

    lsh_loop();

    return EXIT_SUCCESS;
}


void lsh_loop(void)
{
    printf("loop");
}