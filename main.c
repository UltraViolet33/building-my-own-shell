#include <stdio.h>
#include <stdlib.h>

#define LSH_RL_BUFSIZE 1024

void lsh_loop(void);
char *readline(void);

int main(int argc, char **argv)
{
    lsh_loop();

    return EXIT_SUCCESS;
}


void lsh_loop(void)
{
    char *line;

    line = readline();

    for (int i = 0; i < 5; i++)
    {
        printf("%c", line[i]);
    }

}


char *readline(void)
{
    int buffer_size = LSH_RL_BUFSIZE;
    int position = 0;
    char c;

    char *buffer = malloc(sizeof(char) * buffer_size);

    printf("%d", buffer_size);

    if (buffer == NULL)
    {
        fprintf(stderr, "lsh: allocation error\n");
        exit(EXIT_FAILURE);
    }

    while (1)
    {
        c = getchar();

        if (c == EOF || c == '\n')
        {
            buffer[position] = '\0';
            printf("terminated");
            return buffer;
        }
        else
        {
            buffer[position] = c;
        }

        position++;

        if (position >= buffer_size)
        {
            buffer_size += LSH_RL_BUFSIZE;
            buffer = realloc(buffer, buffer_size);

            if (buffer == NULL)
            {
                fprintf(stderr, "lsh: allocation error\n");
                exit(EXIT_FAILURE);
            }
        }
    }
}