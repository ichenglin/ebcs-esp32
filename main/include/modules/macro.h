#ifndef MACRO_MODULE_H
#define MACRO_MODULE_H

#define LOG_RETURN(tag, message) do { ESP_LOGE(tag, "%s", message); return; } while (0)

#endif // MACRO_MODULE_H
