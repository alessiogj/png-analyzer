cmake_minimum_required(VERSION 3.25)
project(PngAnalyzer C)

set(CMAKE_C_STANDARD 11)

# Aggiungi il file hello.c al progetto
add_executable(PngAnalyzer analyzer.c)

# Copia il file hello.png nella directory dell'eseguibile
configure_file(hello.png ${CMAKE_BINARY_DIR}/hello.png COPYONLY)


