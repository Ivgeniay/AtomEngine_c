#include "logger.h"
#include "asserts.h"
#include "platform/platform.h"

// TODO: temporary
#include <stdio.h>
#include <string.h>
#include <stdarg.h>


b8 initialize_logging() {
    // TODO: create log file
    return TRUE;
}

void shutdown_logging() {
    // TODO: clean up logging/writte queued entries.
}

void log_output(log_level level, const char* message, ...) {
    const char* level_string[6] = {
        "[FATL]",
        "[ERRR]",
        "[WARN]",
        "[INFO]",
        "[DEBG]",
        "[TRCE]"
    };
    
    b8 is_error = level < LOG_LEVEL_WARN;

    const i32 msg_length = 32000;

    // Technically imposes a 32k character limit on a single log entry, but...
    char out_message[msg_length];
    memset(out_message, 0, sizeof(out_message));

    // Transplatform arguments pointer (va_list throws error)
    __builtin_va_list arg_ptr;
    va_start(arg_ptr, message);
    vsnprintf(out_message, sizeof(out_message), message, arg_ptr);
    va_end(arg_ptr);

    char out_message2[msg_length];
    sprintf(out_message2, "%s:\t%s\n", level_string[level], out_message);

    // Platform specific output
    if (is_error) {
        platform_console_write_error(out_message, level);
    } else {
        platform_console_write(out_message, level);
    }
}

void report_assertion_failure(const char* expression, const char* message, const char* file, i32 line) {
    log_output(LOG_LEVEL_FATAL, "Assertion failed: %s,\nMessage: %s,\nFile: %s,\nLine: %d.\n\n", expression, message, file, line);
}
