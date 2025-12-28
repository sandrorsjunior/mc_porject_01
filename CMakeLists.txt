cmake_minimum_required(VERSION 3.10)

# Define o nome do projeto
project(mc_porject_01)

# Define a frequência da CPU (16MHz é padrão para Arduino Uno/Nano)
add_definitions(-DF_CPU=16000000UL)

# Inclui a pasta de cabeçalhos (.h)
include_directories(include)

# Encontra todos os arquivos .c na pasta src/
file(GLOB_RECURSE SOURCES "src/*.c")

# Cria o executável (.elf)
add_executable(${PROJECT_NAME}.elf ${SOURCES})

# Comandos Pós-Compilação (Essenciais para AVR)
# 1. Gera o arquivo .hex (necessário para gravar no chip)
add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
    COMMAND ${AVR_OBJCOPY} -O ihex -R .eeprom ${PROJECT_NAME}.elf ${PROJECT_NAME}.hex
    COMMENT "Gerando arquivo .hex para gravação..."
)

# 2. Mostra o tamanho do binário no terminal (Memória Flash e RAM usada)
add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
    COMMAND ${AVR_SIZE} -A ${PROJECT_NAME}.elf
    COMMENT "Verificando tamanho do binário..."
)