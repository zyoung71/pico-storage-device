#include <pico/stdio.h>
#include <storage/StorageDevice.h>

int main()
{
    stdio_init_all();

    StorageDevice* devUTF8;
    StorageDevice* devUTF16;
    auto& sdsUTF8 = devUTF8->GetStream();
    auto& sdsUTF16 = devUTF16->GetStream();
    sdsUTF8 << "hi";
    sdsUTF16 << u"hi";
}