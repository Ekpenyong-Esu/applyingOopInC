#include "../monitor/monitor.h"
#include "unity.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>


void setUp(void)
{
    // set stuff up here
}

void tearDown(void)
{
    // clean stuff up here
}

// Test: Monitor Initialization with Valid Path
void test_monitor_init_valid_path(void)
{
    struct monitor test_monitor;

    // Initialize
    const char *valid_path = "/tmp";

    // Act
    int result = monitor_init(&test_monitor, valid_path);

    // Assert
    TEST_ASSERT_EQUAL_INT(0, result);
    TEST_ASSERT_EQUAL_STRING(valid_path, test_monitor.directory);
    TEST_ASSERT_EQUAL_INT(0, test_monitor.is_active);

    monitor_deinit(&test_monitor);
}

// Test: Monitor Initialization with Null Path
void test_monitor_init_null_path(void)
{
    struct monitor test_monitor;

    // Initialize
    const char *null_path = NULL;

    // Act
    int result = monitor_init(&test_monitor, null_path);

    // Assert
    TEST_ASSERT_EQUAL_INT(-1, result);
}

// Test: Monitor Start and Stop
void test_monitor_start_and_stop(void)
{
    struct monitor test_monitor;

    // Initialize
    monitor_init(&test_monitor, "/tmp");

    // Act
    int start_result = monitor_start(&test_monitor);
    int stop_result = monitor_stop(&test_monitor);

    // Assert
    TEST_ASSERT_EQUAL_INT(0, start_result);
    TEST_ASSERT_EQUAL_INT(1, test_monitor.is_active); // Active after start
    TEST_ASSERT_EQUAL_INT(0, stop_result);
    TEST_ASSERT_EQUAL_INT(0, test_monitor.is_active); // Inactive after stop

    monitor_deinit(&test_monitor);
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_monitor_init_valid_path);
    RUN_TEST(test_monitor_init_null_path);
    RUN_TEST(test_monitor_start_and_stop);
    return UNITY_END();
}
