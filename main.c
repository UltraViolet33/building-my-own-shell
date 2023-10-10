#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define LSH_RL_BUFSIZE 1024
#define LSH_TOK_BUFSIZE 64
#define LSH_TOK_DELIM " \t\r\n\a"

void lsh_loop(void);
char *readline(void);

char **splitline(char *line);

int main(int argc, char **argv)
{
    lsh_loop();

    return EXIT_SUCCESS;
}


char **splitline(char *line)
{
    char *token;
    char **tokens = malloc(sizeof(char *) * BUFSIZ);

    int position = 0;

    token = strtok(line, LSH_TOK_DELIM);

    while(token != NULL)
    {
        printf("%s\n", token);
        tokens[position] = token;
        token = strtok (NULL, LSH_TOK_DELIM);
        position++;
    }

    return tokens;
}


void lsh_loop(void)
{
    char *line;
    char **args;

    line = readline();
    
    args = splitline(line);

    for (int i = 0; i < 5; i++)
    {
        // printf("%c", args[i]);
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