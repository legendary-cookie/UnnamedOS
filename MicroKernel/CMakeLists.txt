project(kernel)

cmake_minimum_required(VERSION 3.22)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(ARCH "x86_64")

add_compile_options($<$<C_COMPILER_ID:Clang>:-fcolor-diagnostics>)

include_directories(include)
include_directories(libk++/include)
include_directories(deps/cxxshim/stage2/include)
include_directories(deps/frigg/include)
include_directories(hal/include)
include_directories(hal/arch/${ARCH}/include)

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

add_compile_options(-Wall -Wextra -fno-exceptions -fno-rtti -fno-stack-protector -O2)
add_compile_options(-Wno-unused-parameter)
add_compile_options(-ffreestanding -nostdlib)
add_compile_options(-mno-mmx -mno-sse -mno-sse2 -mno-3dnow)
add_compile_options(-mcmodel=kernel -mno-red-zone -fno-pic -fno-pie)

# Inline functions even with O0
add_compile_options(-O0)
add_compile_options(-fno-builtin -finline-functions)
add_compile_options(-g)

set(KERNEL_SRC
	src/kernel.cpp
	src/logger.cpp
)

set(LIBK_SRC
	libk++/cstring.cpp
	libk++/fmt.cpp
)

set(HAL_ARCH "hal/arch/${ARCH}")

set(HAL_SRC_x86_64
	${HAL_ARCH}/arch.cpp
	${HAL_ARCH}/IDT.cpp
	${HAL_ARCH}/IDT.asm
	${HAL_ARCH}/GDT.cpp
	${HAL_ARCH}/GDT.asm
	${HAL_ARCH}/CPU.cpp
	${HAL_ARCH}/io.cpp
)

add_link_options(-static -z max-page-size=0x1000 -nostdlib)

add_executable(kernel.elf ${LIBK_SRC} ${HAL_SRC_${ARCH}} ${KERNEL_SRC})
target_link_options(kernel.elf PRIVATE -T ${CMAKE_CURRENT_SOURCE_DIR}/linkscript-${ARCH}.ld)
