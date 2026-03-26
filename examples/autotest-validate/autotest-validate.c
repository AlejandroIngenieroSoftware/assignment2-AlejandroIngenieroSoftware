#include <string.h>
#include <ctype.h>

/* ===== FUNCIONES QUE FALTABAN ===== */

int this_function_returns_true()
{
    return 1;
}

int this_function_returns_false()
{
    return 0;
}

/* ===== TU FUNCIÓN ===== */

int validate_username(const char *username)
{
    if (username == NULL || strlen(username) == 0)
        return 0;

    for (int i = 0; username[i] != '\0'; i++)
    {
        if (!isalnum(username[i]))
            return 0;
    }

    return 1;
}
