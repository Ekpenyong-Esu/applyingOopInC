#include "config.h"
#include "monitor.h"
#include <log.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


/**
 * @brief I am truing to understand how i can integrate cmake into my project
 *
 * @param argc
 * @param argv
 * @return
 */


static struct monitor file_monitor;
static int running = 1;

void handle_signal(int sig)
{
    if (sig == SIGINT || sig == SIGTERM)
    {
        printf("\nShutting down...\n");
        monitor_stop(&file_monitor);
        running = 0;
    }
}

int main(int argc, char *argv[])
{

    log_info("Welcome to %s v%s\n", project_name, project_version);

    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s <directory>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *directory = argv[1];

    // Initialize monitor
    if (monitor_init(&file_monitor, directory) != 0)
    {
        fprintf(stderr, "Failed to initialize monitor for directory: %s\n", directory);

        return EXIT_FAILURE;
    }

    // Set up signal handler for graceful shutdown
    signal(SIGINT, handle_signal);
    signal(SIGTERM, handle_signal);

    // Start monitoring
    printf("Monitoring directory: %s\n", directory);
    if (monitor_start(&file_monitor) != 0)
    {
        fprintf(stderr, "Error starting file monitor.\n");
        monitor_deinit(&file_monitor);
        return EXIT_FAILURE;
    }

    // Wait for shutdown signal
    while (running)
    {
        sleep(1);
    }

    // Cleanup
    monitor_deinit(&file_monitor);
    printf("File System Monitor stopped.\n");

    return EXIT_SUCCESS;
}
