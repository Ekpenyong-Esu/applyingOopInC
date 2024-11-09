#include "logger.h"
#include <string.h>
#include <time.h>

int logger_init(struct logger *self, const char *log_path)
{
    if (!self || !log_path)
    {
        return -1;
    }

    // Close existing log file if already open
    if (self->log_file)
    {
        fclose(self->log_file);
        self->log_file = NULL;
    }

    memset(self, 0, sizeof(struct logger));

    self->log_file = fopen(log_path, "a");

    if (!self->log_file)
    {
        return -1; // Failed to open file
    }

    return 0;
}

int logger_log(struct logger *self, const char *message)
{
    if (!self || !self->log_file || !message)
    {
        return -1;
    }

    //memset(self, 0, sizeof(struct logger));

    time_t now = time(NULL);
    fprintf(self->log_file, "[%s] %s", ctime(&now), message);
    fflush(self->log_file);
    return 0;
}

int logger_deinit(struct logger *self)
{
    if (!self || !self->log_file)
    {
        return -1;
    }
    fclose(self->log_file);
    self->log_file = NULL;
    return 0;
}
