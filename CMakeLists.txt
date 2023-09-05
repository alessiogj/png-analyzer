cmake_minimum_required(VERSION 3.25)
project(PngAnalyzer C)

set(CMAKE_C_STANDARD 11)

# Aggiungi il file hello.c al progetto
add_executable(PngAnalyzer
        src/analyzer.c
        lib/ihdr_analyzer.h
        src/ihdr_analyzer.c
        lib/types.h
        lib/utils.h
        src/utils.c
        src/idat_analyzer.c
        lib/idat_analyzer.h lib/decompression_algorithm.h src/decompression_algorithm.c lib/image_parsing.h src/image_parsing.c)

# Collega la libreria zlib al tuo target
find_package(ZLIB REQUIRED)
target_link_libraries(PngAnalyzer ZLIB::ZLIB)

# Copia il file hello.png nella directory dell'eseguibile
configure_file(hello.png ${CMAKE_BINARY_DIR}/hello.png COPYONLY)



