#include <pico/stdio.h>
#include <storage/StorageDevice.hpp>

int main()
{
    stdio_init_all();

    StorageDevice* dev;

    auto file = dev->OpenFile(".config", READ | WRITE);

    auto& fstream = file->GetStream();
    fstream << "hi";
}