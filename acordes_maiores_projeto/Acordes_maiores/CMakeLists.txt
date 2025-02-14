cmake_minimum_required(VERSION 3.13)

# Adiciona esta linha para exportar o compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Inicializa o SDK do Raspberry Pi Pico
include(pico_sdk_import.cmake)

# Define a placa como Raspberry Pi Pico W (opcional)
set(PICO_BOARD pico CACHE STRING "Board type")

# Define o nome do projeto
project(blink C CXX ASM)

# Inicializa o SDK do Raspberry Pi Pico
pico_sdk_init()

# Adiciona o diretório de bibliotecas (Adafruit SSD1306 e Adafruit GFX)
add_subdirectory(lib/Adafruit-GFX-Library)
add_subdirectory(lib/Adafruit_SSD1306)

# Adiciona o arquivo executável
add_executable(blink
    blink.c  # Seu código principal aqui
)

# Vincula as bibliotecas padrão do Pico
target_link_libraries(blink pico_stdlib)

# Vincula as bibliotecas externas ao executável
target_link_libraries(blink
    Adafruit_GFX
    Adafruit_SSD1306
)

# Inclui os diretórios de cabeçalhos das bibliotecas
target_include_directories(blink PUBLIC
    ${CMAKE_SOURCE_DIR}/lib/Adafruit-GFX-Library
    ${CMAKE_SOURCE_DIR}/lib/Adafruit_SSD1306
)

# Gera arquivos adicionais (hex, map, etc.)
pico_add_extra_outputs(blink)
