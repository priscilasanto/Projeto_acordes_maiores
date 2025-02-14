cmake_minimum_required(VERSION 3.13)

# Adiciona esta linha para exportar o compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Inicializa o SDK do Raspberry Pi Pico
include(pico_sdk_import.cmake)

# Define o nome do projeto
project(acordes_maiores_projeto C CXX ASM)

# Inicializa o SDK do Raspberry Pi Pico
pico_sdk_init()

# Adiciona o diretório de bibliotecas (Adafruit SSD1306, Adafruit GFX e DHT)
add_subdirectory(lib/Adafruit-GFX-Library)
add_subdirectory(lib/Adafruit_SSD1306)
add_subdirectory(lib/DHT-sensor-library)  # Adicione esta linha

# Adiciona o arquivo executável
add_executable(acordes_maiores
    Acordes_maiores.c  # Seu código principal aqui
)

# Vincula as bibliotecas padrão do Pico
target_link_libraries(acordes_maiores pico_stdlib hardware_i2c)