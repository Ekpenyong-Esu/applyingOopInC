#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>


struct logger
{
    FILE *log_file; // File pointer for log file
};

int logger_init(struct logger *self, const char *log_path);
int logger_log(struct logger *self, const char *message);
int logger_deinit(struct logger *self);

#endif // LOGGER_H
