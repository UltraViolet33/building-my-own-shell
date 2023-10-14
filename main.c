#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

#define RL_BUFSIZE 1024
#define TOK_BUFSIZE 64
#define TOK_DELIM " \t\r\n\a"

void main_loop(void);
char *read_line(void);
char **split_line(char *line);
int launch(char **args);

int main(int argc, char **argv)
{
    main_loop();

    return EXIT_SUCCESS;
}

void main_loop(void)
{
    char *line;
    char **args;

    line = read_line();

    args = split_line(line);

    launch(args);

    // for (int i = 0; i < 5; i++)
    // {
    //     printf("%s", args[i]);
    // }
}

char **split_line(char *line)
{
    int bufsize = TOK_BUFSIZE;
    char *token;
    char **tokens = malloc(sizeof(char *) * bufsize);
    int position = 0;

    if (!tokens)
    {
        fprintf(stderr, "Allocation error\n");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, TOK_DELIM);

    while (token != NULL)
    {
        tokens[position] = token;
        position++;

        if (position >= bufsize)
        {
            bufsize += TOK_BUFSIZE;
            tokens = realloc(tokens, bufsize * sizeof(char *));

            if (!tokens)
            {
                fprintf(stderr, "Allocation error\n");
                exit(EXIT_FAILURE);
            }
        }

        token = strtok(NULL, TOK_DELIM);
    }

    tokens[position] = NULL;

    return tokens;
}

char *read_line(void)
{
    int buffer_size = RL_BUFSIZE;
    int position = 0;
    char c;

    char *buffer = malloc(sizeof(char) * buffer_size);

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
            return buffer;
        }
        else
        {
            buffer[position] = c;
        }

        position++;

        if (position >= buffer_size)
        {
            buffer_size += RL_BUFSIZE;
            buffer = realloc(buffer, buffer_size);

            if (buffer == NULL)
            {
                fprintf(stderr, "lsh: allocation error\n");
                exit(EXIT_FAILURE);
            }
        }
    }
}

int launch(char **args)
{
    pid_t pid, wpid;
    int status;

    pid = fork();

    if (pid == 0)
    {
        // Child process
        if (execvp(args[0], args) == -1)
        {
            perror("lsh");
        }

        exit(EXIT_FAILURE);
    }
    else if (pid < 0)
    {
        // Error forking
        perror("lsh");
    }
    else
    {
        // Parent process
        do
        {
            wpid = waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }

    return 1;
}