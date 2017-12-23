
typedef void(*debug_callback_t)(char *src);

void RegisterDebugCallback(debug_callback_t cb);

void DebugPrint(char *Format, ...);

