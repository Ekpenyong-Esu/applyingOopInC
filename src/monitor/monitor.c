#include "monitor.h"
#include "../logger/logger.h"
#include "config.h"
#include <signal.h>
#include <string.h>
#include <sys/inotify.h>
#include <unistd.h>


volatile sig_atomic_t terminate_flag = 0; // Global flag to signal termination

/**
 * Async-safe signal handler for SIGINT
 */
static void handle_sigint(int sig)
{
    terminate_flag = 1;
    const char msg[] = "Received SIGINT. Gracefully shutting down...\n";
    write(STDOUT_FILENO, msg, sizeof(msg) - 1);
}


int monitor_init(struct monitor *self, const char *path)
{
    if (!self || !path)
    {
        return -1;
    }
    memset(self, 0, sizeof(struct monitor));

    strncpy(self->directory, path, sizeof(self->directory) - 1);
    self->is_active = 0;
    return 0;
}

int monitor_start(struct monitor *self)
{
    if (!self || self->is_active)
    {
        return -1;
    }
    self->is_active = 1;

    // Register signal handler for SIGINT (Ctrl+C)
    signal(SIGINT, handle_sigint);

    int inotify_fd = inotify_init();
    if (inotify_fd < 0)
    {
        return -1;
    }

    int word = inotify_add_watch(inotify_fd, self->directory, IN_CREATE | IN_DELETE | IN_MODIFY);
    if (word < 0)
    {
        return -1;
    }

    struct logger log = {0};
    if (logger_init(&log, DEFAULT_LOG_FILE) != 0)
    {
        return -1;
    }

    char buffer[BUFFER_SIZE];
    while (self->is_active && !terminate_flag)
    {

        ssize_t length = read(inotify_fd, buffer, sizeof(buffer));

        if (length < 0)
        {
            break;
        }

        struct inotify_event *event = (struct inotify_event *)buffer;
        if (event->len)
        {
            if (event->mask & IN_CREATE)
            {
                logger_log(&log, "File created");
            }
            else if (event->mask & IN_DELETE)
            {
                logger_log(&log, "File deleted");
            }
            else if (event->mask & IN_MODIFY)
            {
                logger_log(&log, "File modified");
            }
        }
    }

    logger_deinit(&log);
    close(inotify_fd);
    return 0;
}

int monitor_stop(struct monitor *self)
{
    if (!self || !self->is_active)
    {
        return -1;
    }
    self->is_active = 0;
    return 0;
}

int monitor_deinit(struct monitor *self)
{
    if (!self)
    {
        return -1;
    }
    memset(self, 0, sizeof(*self));
    return 0;
}
