include(xmc4500_opt.cmake)

# the name of the target operating system
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_VERSION 1)
set(CMAKE_SYSTEM_PROCESSOR ARM)
set(PREPROCESSORS_FLAGS "-DXMC4500_F100x1024 -D__FPU_PRESENT -D__MPU_PRESENT")
add_compile_definitions(${PREPROCESSORS_FLAGS})

# which compilers to use for C and C++
set(CMAKE_C_COMPILER   arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER arm-none-eabi-g++)
set(CMAKE_ASM_COMPILER arm-none-eabi-gcc)
set(CMAKE_OBJCOPY      arm-none-eabi-objcopy)
set(CMAKE_OBJDUMP      arm-none-eabi-objdump)

set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

# compiler: language specific flags
set(CMAKE_C_STANDARD 99)

set(CMAKE_C_FLAGS "${XMC4500_CCOPT}")
set(CMAKE_C_FLAGS_RELEASE "${XMC4500_CCOPT}")
set(CMAKE_C_FLAGS_DEBUG "${XMC4500_CCOPT}")
set(CMAKE_CXX_FLAGS "${XMC4500_CCXOPT}")
set(CMAKE_CXX_FLAGS_RELEASE "${XMC4500_CCXOPT}")
set(CMAKE_CXX_FLAGS_DEBUG "${XMC4500_CCXOPT}")




set(CMAKE_ASM_FLAGS "${CORE_FLAGS} -g -ggdb3 -D__USES_CXX" CACHE INTERNAL "asm compiler flags")
set(CMAKE_ASM_FLAGS_DEBUG "" CACHE INTERNAL "asm compiler flags: Debug")
set(CMAKE_ASM_FLAGS_RELEASE "" CACHE INTERNAL "asm compiler flags: Release")

# search for programs in the build host directories
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)

# for libraries and headers in the target directories
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

# find additional toolchain executables
find_program(ARM_SIZE_EXECUTABLE arm-none-eabi-size)
find_program(ARM_GDB_EXECUTABLE arm-none-eabi-gdb)
find_program(ARM_OBJCOPY_EXECUTABLE arm-none-eabi-objcopy)
find_program(ARM_OBJDUMP_EXECUTABLE arm-none-eabi-objdump)
