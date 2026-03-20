#ifndef LOG_H
#define LOG_H

int log_init();
int log_info(const char *msg);
int log_warn(const char *msg);
int log_error(const char *msg);
int log_close();

#endif
