#include "../src/logger/logger.h"
#include "unity.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 256

void setUp(void)
{
    // set stuff up here
}

void tearDown(void)
{
    // clean stuff up here
}

// Test: Logger Initialization
void test_logger_init(void)
{
    struct logger test_logger;
    const char *log_file = "test.log";

    // Initialize
    int result = logger_init(&test_logger, log_file);

    // Assert
    TEST_ASSERT_EQUAL_INT(0, result);
    TEST_ASSERT_NOT_NULL(test_logger.log_file);

    // Clean up
    logger_deinit(&test_logger);
    remove(log_file);
}

// Test: Logger Write
void test_logger_write(void)
{
    struct logger test_logger;
    const char *log_file = "test.log";

    // Initialize
    logger_init(&test_logger, log_file);

    // Act
    const char *log_message = "Test log entry";
    int result = logger_log(&test_logger, log_message);

    // Assert
    TEST_ASSERT_EQUAL_INT(0, result);

    // Verify log file contents
    FILE *file = fopen(log_file, "r");
    TEST_ASSERT_NOT_NULL(file);
    char line[BUFFER_SIZE];
    while (fgets(line, sizeof(line), file) != NULL)
    {
        printf("%s", line);
    }
    TEST_ASSERT_NOT_NULL(line);
    char *found = strstr(line, log_message);

    printf("Line read from file: '%s'\n", line);
    printf("Expected message: '%s'\n", log_message);

    TEST_ASSERT_NOT_NULL(found);
    fclose(file);

    // Clean up
    logger_deinit(&test_logger);
    remove(log_file);
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_logger_init);
    RUN_TEST(test_logger_write);
    return UNITY_END();
}
