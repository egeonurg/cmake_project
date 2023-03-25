cmake_minimum_required (VERSION 3.0)

include(xmc4500.cmake)

# set the build type
if(NOT CMAKE_BUILD_TYPE) 
    set(CMAKE_BUILD_TYPE Release)
endif(NOT CMAKE_BUILD_TYPE)

if(CMAKE_BUILD_TYPE MATCHES Debug)
  message("Debug build.")
elseif(CMAKE_BUILD_TYPE MATCHES Release)
  message("Release build.")
endif()

# Project specific settings
set(application_name "xmc4500")

project (${application_name} C CXX ASM)

# STM32-specific settings
set(XMC4500_F100x1024 1)

# Used linker file (just for testing)
get_filename_component(LINKER_SCRIPT xmc4500.ld ABSOLUTE)

include_directories(    
	Libraries/CMSIS/Include/
	Libraries/CMSIS/Infineon/XMC4500_series/Include/
	Libraries/XMCLib/inc/	
)

set(sources
        main.c
	Startup/startup_XMC4500.s
	Startup/system_XMC4500.c
	Libraries/Newlib/syscalls.c
	Libraries/XMCLib/src/xmc4_eru.c
	Libraries/XMCLib/src/xmc4_flash.c
	Libraries/XMCLib/src/xmc4_gpio.c
	Libraries/XMCLib/src/xmc4_rtc.c
	Libraries/XMCLib/src/xmc4_scu.c
	Libraries/XMCLib/src/xmc_can.c
	Libraries/XMCLib/src/xmc_ccu4.c
	Libraries/XMCLib/src/xmc_ccu8.c
	Libraries/XMCLib/src/xmc_common.c
	Libraries/XMCLib/src/xmc_dac.c
	Libraries/XMCLib/src/xmc_dma.c
	Libraries/XMCLib/src/xmc_dsd.c
	Libraries/XMCLib/src/xmc_ebu.c
	Libraries/XMCLib/src/xmc_ecat.c
	Libraries/XMCLib/src/xmc_eru.c
	Libraries/XMCLib/src/xmc_eth_mac.c
	Libraries/XMCLib/src/xmc_eth_phy_dp83848.c
	Libraries/XMCLib/src/xmc_eth_phy_ksz8031rnl.c
	Libraries/XMCLib/src/xmc_eth_phy_ksz8081rnb.c
	Libraries/XMCLib/src/xmc_fce.c
	Libraries/XMCLib/src/xmc_gpio.c
	Libraries/XMCLib/src/xmc_hrpwm.c
	Libraries/XMCLib/src/xmc_i2c.c
	Libraries/XMCLib/src/xmc_i2s.c
	Libraries/XMCLib/src/xmc_ledts.c
	Libraries/XMCLib/src/xmc_posif.c
	Libraries/XMCLib/src/xmc_rtc.c
	Libraries/XMCLib/src/xmc_sdmmc.c
	Libraries/XMCLib/src/xmc_spi.c
	Libraries/XMCLib/src/xmc_uart.c
	Libraries/XMCLib/src/xmc_usbd.c
	Libraries/XMCLib/src/xmc_usbh.c
	Libraries/XMCLib/src/xmc_usic.c
	Libraries/XMCLib/src/xmc_vadc.c
	Libraries/XMCLib/src/xmc_wdt.c
)

# GCC optimization level: use -O0 in debug build, otherwise -O2
set(opt_level -O0)

# set some project constants
set(elf_file ${application_name}.elf)
set(bin_file ${application_name}.bin)
set(hex_file ${application_name}.hex)
set(map_file ${application_name}.map)
set(lss_file ${application_name}.lss)

# add sources to elf file
add_executable(${elf_file} ${sources})

# set additional for compiler and linker: optimization and generate map file
set(additional_compiler_flags ${opt_level})
set(additional_linker_flags -Wl,-Map=${map_file},--cref,--no-warn-mismatch)
target_compile_options(${elf_file} PRIVATE ${additional_compiler_flags})
target_link_libraries(${elf_file} PRIVATE ${additional_linker_flags})

# remove unused sections
target_link_libraries(${elf_file} PUBLIC "-g -Wl,--gc-sections")

# link with linker file
target_link_libraries(${elf_file} PUBLIC -T${LINKER_SCRIPT})

# show size of resulting firmware image
add_custom_target(${elf_file}-size DEPENDS ${elf_file} COMMAND ${ARM_SIZE_EXECUTABLE} -B ${elf_file})

# generate extended listing
add_custom_target(${lss_file} DEPENDS ${elf_file} COMMAND ${ARM_OBJDUMP_EXECUTABLE} -S ${elf_file} > ${lss_file})

# create binary and hex files
add_custom_target(${hex_file} DEPENDS ${elf_file} COMMAND ${ARM_OBJCOPY_EXECUTABLE} -Oihex ${elf_file} ${hex_file})
add_custom_target(${bin_file} DEPENDS ${elf_file} COMMAND ${ARM_OBJCOPY_EXECUTABLE} -Obinary ${elf_file} ${bin_file})
add_custom_target(${application_name} ALL DEPENDS ${elf_file}-size ${bin_file} ${hex_file} ${lss_file})