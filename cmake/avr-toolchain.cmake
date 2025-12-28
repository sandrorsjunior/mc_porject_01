# Define que é um sistema "Generic" (Bare metal)
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR avr)

# Tenta encontrar os compiladores automaticamente (deve ter avr-gcc no PATH)
find_program(AVR_CC avr-gcc)
find_program(AVR_CXX avr-g++)
find_program(AVR_OBJCOPY avr-objcopy)
find_program(AVR_SIZE avr-size)

set(CMAKE_C_COMPILER ${AVR_CC})
set(CMAKE_CXX_COMPILER ${AVR_CXX})

# Configurações padrão do compilador para reduzir tamanho e otimizar
set(CMAKE_C_FLAGS "-Os -Wall -fno-exceptions -ffunction-sections -fdata-sections -mmcu=atmega328p" CACHE INTERNAL "C Compiler options")
set(CMAKE_EXE_LINKER_FLAGS "-Wl,--gc-sections -mmcu=atmega328p" CACHE INTERNAL "Linker options")

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)