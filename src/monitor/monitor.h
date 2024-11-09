#ifndef MONITOR_H
#define MONITOR_H


#define DIRECTORY_SIZE 256
#define BUFFER_SIZE 1024

struct monitor
{
    char directory[DIRECTORY_SIZE]; // Directory path
    int is_active;                  // Monitoring status
};

int monitor_init(struct monitor *self, const char *path);
int monitor_start(struct monitor *self);
int monitor_stop(struct monitor *self);
int monitor_deinit(struct monitor *self);

#endif // MONITOR_H
