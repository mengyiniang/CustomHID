#THIS FILE IS AUTO GENERATED FROM THE TEMPLATE! DO NOT CHANGE!
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_VERSION 1)
cmake_minimum_required(VERSION 3.21)

set(PROJECT_NAME CustomHID)

set(CMAKE_SYSTEM_PROCESSOR cortex-m0plus)

set(CMAKE_C_COMPILER C:/Keil_v5/ARM/ARMCLANG/bin/armclang.exe)
set(CMAKE_C_COMPILER_WORKS TRUE)
set(CMAKE_CXX_COMPILER C:/Keil_v5/ARM/ARMCLANG/bin/armclang.exe)
set(CMAKE_CXX_COMPILER_WORKS TRUE)
#set(CMAKE_ASM_COMPILER C:/Keil_v5/ARM/ARMCLANG/bin/armclang.exe)
set(CMAKE_ASM_COMPILER C:/Keil_v5/ARM/ARMCLANG/bin/armasm.exe)     # 指明 ASM 编译器，配合 第二种 CMAKE_ASM_FLAGS_INIT 方式使用
set(CMAKE_ASM_COMPILER_WORKS TRUE)

#设置链接器
set(CMAKE_C_LINK_EXECUTABLE C:/Keil_v5/ARM/ARMCLANG/bin/armlink.exe)
set(CMAKE_ASM_LINK_EXECUTABLE C:/Keil_v5/ARM/ARMCLANG/bin/armlink.exe)
set(CMAKE_CXX_LINK_EXECUTABLE C:/Keil_v5/ARM/ARMCLANG/bin/armlink.exe)

set(SECTIONS_SCRIPT_PATH ${CMAKE_HOME_DIRECTORY}/MDK-ARM/${PROJECT_NAME}/${PROJECT_NAME}.sct)

set(C_TARGET_FLAG --target=arm-arm-none-eabi)               # MDK 的 link 分页中的配置
set(ASM_TARGET_FLAG --target=arm-arm-none-eabi)             # MDK 的 link 分页中的配置(不支持显示指定 ASM 编译器的方式)
set(LINKER_TARGET_FLAG --cpu=${CMAKE_SYSTEM_PROCESSOR})     # MDK 的 link 分页中的配置

set(COMPILE_RULE_FLAG "-mcpu=${CMAKE_SYSTEM_PROCESSOR}")

# 优化选项 -O 有 1~3   -Os 是平衡  -Oz 是最小体积
set(CMAKE_C_FLAGS_INIT "${C_TARGET_FLAG} ${COMPILE_RULE_FLAG} \
    -xc -std=c99 -fno-rtti -funsigned-char -fshort-enums -fshort-wchar \
    -gdwarf-3 -Oz -ffunction-sections")

# 设置 C++ 编译器选项(没有用到 c++ 所以不用配置)
#set(CMAKE_CXX_FLAGS_INIT ${CMAKE_C_FLAGS_INIT})

# 设置ASM编译器选项
# 注意： -masm=auto 选项是 MDK 的 link 分页里没有的参数，需要加上  -g 是debug 用的加不加都行
set(CMAKE_ASM_FLAGS_INIT "${ASM_TARGET_FLAG} ${COMPILE_RULE_FLAG} \
        -masm=auto -c -gdwarf-3 ")
# 第二种方式 配套显示执行 armasm.exe 为 ASM 编译器的方法，看上起更清晰一些
#set(CMAKE_ASM_FLAGS_INIT "${ASM_TARGET_FLAG} --cpu=Cortex-M3")

set(CMAKE_EXE_LINKER_FLAGS_INIT  " \
            ${LINKER_TARGET_FLAG} \
            --strict \
            --scatter ${SECTIONS_SCRIPT_PATH} \
            --info sizes --info totals --info unused --info veneers \
            --summary_stderr \
            --info summarysizes"
        )

# project settings
project(CustomHID C CXX ASM)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_C_STANDARD 99)

include_directories(USB_DEVICE/App USB_DEVICE/Target Core/Inc Drivers/STM32L0xx_HAL_Driver/Inc Drivers/STM32L0xx_HAL_Driver/Inc/Legacy Middlewares/ST/STM32_USB_Device_Library/Core/Inc Drivers/CMSIS/Device/ST/STM32L0xx/Include Drivers/CMSIS/Include Middlewares/ST/STM32_USB_Device_Library/Class/CustomHID/Inc)
file(GLOB_RECURSE SOURCES "Core/*.*" "Middlewares/*.*" "Drivers/*.*" "Drivers/App/usb_device.c" "USB_DEVICE/*.*")
add_definitions(-DDEBUG -DUSE_FULL_LL_DRIVER -DUSE_HAL_DRIVER -DSTM32L053xx)
add_definitions(--target=arm-arm-none-eabi)

#file(GLOB_RECURSE SOURCES "startup/*.*" "RT-Thread/*.*" "Middlewares/*.*" "Drivers/*.*" "Core/*.*" App)
# 对于混合兼容的环境，需要屏蔽各种编译环境引起的文件“干扰”,通过 list(REMOVE_ITEM) 命令移除不同编译环境下的干扰文件
# 在原来 CubeMX 自动生成的 gcc 编译环境目录上,附加 ARMCC 编译需要的文件
file(GLOB_RECURSE SOURCES ${SOURCES} "MDK-ARM/startup_stm32l053xx.s")
# 将由 CubeMX 生成的 GCC 编译环境中的会干扰ARMCC环境的文件，放在 EXCLUDE_SRCS 自定义列表中
#file(GLOB_RECURSE EXCLUDE_SRCS
#        "STM32L053R8TX_FLASH.ld"
#        )
# 从源文件列表(SOURCES)中剔除干扰文件(EXCLUDE_SRCS)
list(REMOVE_ITEM SOURCES ${EXCLUDE_SRCS})


add_executable(${PROJECT_NAME} ${SOURCES} ${LINKER_SCRIPT})

set(HEX_FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.hex)
set(BIN_FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.bin)
set(ELF_FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.elf)

set(ARMCC_fromelf fromelf.exe)