#include "systemcalls.h"
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdarg.h>
#include <stdbool.h>

/**
 * do_system
 */
bool do_system(const char *cmd)
{
    int ret = system(cmd);

    if (ret == -1)
        return false;

    if (WIFEXITED(ret) && WEXITSTATUS(ret) == 0)
        return true;

    return false;
}

/**
 * do_exec
 */
bool do_exec(int count, ...)
{
    va_list args;
    va_start(args, count);

    char *command[count + 1];
    for (int i = 0; i < count; i++)
    {
        command[i] = va_arg(args, char *);
    }
    command[count] = NULL;

    pid_t pid = fork();

    if (pid < 0)
    {
        va_end(args);
        return false;
    }

    if (pid == 0)
    {
        // Proceso hijo
        execv(command[0], command);
        // Si llega aquí, exec falló
        perror("execv");
        exit(EXIT_FAILURE);
    }
    else
    {
        // Proceso padre
        int status;
        if (waitpid(pid, &status, 0) == -1)
        {
            va_end(args);
            return false;
        }

        va_end(args);

        if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
            return true;

        return false;
    }
}

/**
 * do_exec_redirect
 */
bool do_exec_redirect(const char *outputfile, int count, ...)
{
    va_list args;
    va_start(args, count);

    char *command[count + 1];
    for (int i = 0; i < count; i++)
    {
        command[i] = va_arg(args, char *);
    }
    command[count] = NULL;

    pid_t pid = fork();

    if (pid < 0)
    {
        va_end(args);
        return false;
    }

    if (pid == 0)
    {
        // Proceso hijo

        int fd = open(outputfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd < 0)
        {
            perror("open");
            exit(EXIT_FAILURE);
        }

        // Redirigir stdout a archivo
        if (dup2(fd, STDOUT_FILENO) < 0)
        {
            perror("dup2");
            close(fd);
            exit(EXIT_FAILURE);
        }

        close(fd);

        execv(command[0], command);

        // Si falla
        perror("execv");
        exit(EXIT_FAILURE);
    }
    else
    {
        // Padre
        int status;
        if (waitpid(pid, &status, 0) == -1)
        {
            va_end(args);
            return false;
        }

        va_end(args);

        if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
            return true;

        return false;
    }
}
