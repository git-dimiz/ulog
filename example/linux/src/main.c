#include <stdio.h>
#include "ulog/ulog.h"

int backend_dummy_init(void* arg)
{
    (void)arg;
    return 0;
}

int backend_dummy_tx(uint8_t const* data, size_t size)
{
    fwrite(data, 1, size, stdout);
    // for (size_t i = 0; i < size; i++)
    // {
    //     printf("%02X", data[i]);
    // }
    // printf("\n");

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

    ulog("%s %s %d\n", "Hello", "World", 0x7E);
    ulog("Hello World\n");
    ulog("Hell Boy\n");
    ulog("Hell Girl\n");
    ulog("Hell IT\n");

    ulog_deinit();
    return 0;
}
