#include <stdio.h>
#include "ulog/ulog.h"

int backend_dummy_init(void* arg)
{
    (void)arg;
    return 0;
}

int backend_dummy_tx(uint8_t const* data, size_t size)
{
    #if 1
        fwrite(data, 1, size, stdout);
    #else
        for (size_t i = 0; i < size; i++)
        {
            printf("%02X", data[i]);
        }
        printf("\n");
    #endif

    return size;
}

void backend_dummy_deinit(void)
{
    return;
}

static ulog_backend_t backend_dummy = {
    .init = backend_dummy_init,
    .tx = backend_dummy_tx,
    .deinit = backend_dummy_deinit,
};

int main(int argc, char const *argv[])
{
    (void)argc;
    (void)argv;

    ulog_init(&(ulog_config_t){
                .buffer = (uint8_t[256]){0},
                .size = 256,
              },
              &backend_dummy,
              NULL);

    void* ptr = (void*)0xAABBCCDD;
    ULOG_DBG("Pointer = %p", ptr);
    ULOG_INF("Hello World");
    ULOG_DBG("%s %s %d", "Hello", "World", 0x7E);
    ULOG_WRN("Bad number %d", 42);
    ULOG_ERR("Bad char %c", '!');

    char const exmpl_buffer[] = "AAAAAAAAAAAAAAAAAAAAAA";
    ULOG_HEXDUMP_DBG(exmpl_buffer, sizeof(exmpl_buffer), "This is very important data");

    ulog_deinit();
    return 0;
}
