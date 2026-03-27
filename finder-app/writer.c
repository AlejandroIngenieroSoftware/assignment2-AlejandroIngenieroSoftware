#include <stdio.h>
#include <stdlib.h>
#include <syslog.h>

int main(int argc, char *argv[]) {
    openlog("writer", LOG_PID, LOG_USER);

    if (argc != 3) {
        syslog(LOG_ERR, "Uso incorrecto: %s <archivo> <texto>", argv[0]);
        return 1;
    }

    const char *file = argv[1];
    const char *text = argv[2];

    FILE *f = fopen(file, "w");
    if (!f) {
        syslog(LOG_ERR, "Error al abrir archivo %s", file);
        return 1;
    }

    syslog(LOG_DEBUG, "Escribiendo %s en %s", text, file);

    if (fprintf(f, "%s", text) < 0) {
        syslog(LOG_ERR, "Error al escribir en archivo");
        fclose(f);
        return 1;
    }

    fclose(f);
    closelog();
    return 0;
}
