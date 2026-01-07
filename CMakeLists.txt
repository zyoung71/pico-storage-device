if (NOT TARGET pico-storage-device)

    add_library(pico-storage-device STATIC
        src/storage/StorageDevice.cpp
        src/storage/FileContentsMap.cpp
    )

    add_subdirectory(lib/pico-util)

    target_include_directories(pico-storage-device PUBLIC
        include
    )

    target_link_libraries(pico-storage-device
        pico-util
    )

endif()