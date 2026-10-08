#include <pico/stdio.h>
#include <storage/StorageDevice.hpp>

int main()
{
    stdio_init_all();

    StorageDevice* dev;
    auto& sds = dev->GetStream();
    sds << "hi";
}