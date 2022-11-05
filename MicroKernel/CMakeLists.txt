project(kernel)

cmake_minimum_required(VERSION 3.22)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(ARCH "x86_64")

add_compile_options($<$<C_COMPILER_ID:Clang>:-fcolor-diagnostics>)

include_directories(include)
include_directories(hal/include)

if("${ARCH}" STREQUAL "x86_64")
	enable_language(ASM_NASM)
	if(NOT CMAKE_ASM_NASM_COMPILER_LOADED)
		message(FATAL_ERROR "Failed to find NASM assembler!")
	endif()
	set(CMAKE_ASM_NASM_COMPILE_OBJECT "<CMAKE_ASM_NASM_COMPILER> -i${CMAKE_CURRENT_SOURCE_DIR}/hal/arch/x86_64 \
        -felf64 -w+gnu-elf-extensions -o <OBJECT> <SOURCE>")
else()
	message(FATAL_ERROR "Unsupported architecture ${ARCH}")
endif()

add_compile_options(-Wall -Wextra -fno-exceptions -fno-rtti)
add_compile_options(-Wno-write-strings -Wno-unused-parameter -Wno-sign-compare -Wno-deprecated-volatile -Wno-non-c-typedef-for-linkage)
add_compile_options(-ffreestanding -nostdlib)
add_compile_options(-mno-mmx -mno-sse -mno-sse2)
add_compile_options(-mcmodel=large -mno-red-zone -fno-pic)

# Inline functions even with O0
add_compile_options(-O0)
add_compile_options(-fno-builtin -finline-functions)
add_compile_options(-g)

set(KERNEL_SRC
	src/kernel.cpp
)

set(HAL_SRC_x86_64
	hal/arch/x86_64/entry.asm
)

add_link_options(-z max-page-size=0x1000 -ffreestanding -nostdlib)

add_executable(kernel.elf ${KERNEL_SRC} ${HAL_SRC_${ARCH}})
target_link_options(kernel.elf PRIVATE -T ${CMAKE_CURRENT_SOURCE_DIR}/linkscript-${ARCH}.ld)
