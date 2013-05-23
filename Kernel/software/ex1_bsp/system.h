/*
 * system.h - SOPC Builder system and BSP software package information
 *
 * Machine generated for CPU 'nios2_qsys_0' in SOPC Builder design 'qsys_top'
 * SOPC Builder design path: Z:/Valentin/git/concurrence-BA4-2013/Kernel/qsys_top_new.sopcinfo
 *
 * Generated: Thu May 23 21:57:50 CEST 2013
 */

/*
 * DO NOT MODIFY THIS FILE
 *
 * Changing this file will have subtle consequences
 * which will almost certainly lead to a nonfunctioning
 * system. If you do modify this file, be aware that your
 * changes will be overwritten and lost when this file
 * is generated again.
 *
 * DO NOT MODIFY THIS FILE
 */

/*
 * License Agreement
 *
 * Copyright (c) 2008
 * Altera Corporation, San Jose, California, USA.
 * All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 * This agreement shall be governed in all respects by the laws of the State
 * of California and by the laws of the United States of America.
 */

#ifndef __SYSTEM_H_
#define __SYSTEM_H_

/* Include definitions from linker script generator */
#include "linker.h"


/*
 * CPU configuration
 *
 */

#define ALT_CPU_ARCHITECTURE "altera_nios2_qsys"
#define ALT_CPU_BIG_ENDIAN 0
#define ALT_CPU_BREAK_ADDR 0x2004820
#define ALT_CPU_CPU_FREQ 50000000u
#define ALT_CPU_CPU_ID_SIZE 1
#define ALT_CPU_CPU_ID_VALUE 0x00000000
#define ALT_CPU_CPU_IMPLEMENTATION "small"
#define ALT_CPU_DATA_ADDR_WIDTH 0x1a
#define ALT_CPU_DCACHE_LINE_SIZE 0
#define ALT_CPU_DCACHE_LINE_SIZE_LOG2 0
#define ALT_CPU_DCACHE_SIZE 0
#define ALT_CPU_EXCEPTION_ADDR 0x2000020
#define ALT_CPU_FLUSHDA_SUPPORTED
#define ALT_CPU_FREQ 50000000
#define ALT_CPU_HARDWARE_DIVIDE_PRESENT 0
#define ALT_CPU_HARDWARE_MULTIPLY_PRESENT 1
#define ALT_CPU_HARDWARE_MULX_PRESENT 0
#define ALT_CPU_HAS_DEBUG_CORE 1
#define ALT_CPU_HAS_DEBUG_STUB
#define ALT_CPU_HAS_JMPI_INSTRUCTION
#define ALT_CPU_ICACHE_LINE_SIZE 32
#define ALT_CPU_ICACHE_LINE_SIZE_LOG2 5
#define ALT_CPU_ICACHE_SIZE 4096
#define ALT_CPU_INST_ADDR_WIDTH 0x1a
#define ALT_CPU_NAME "nios2_qsys_0"
#define ALT_CPU_RESET_ADDR 0x2000000


/*
 * CPU configuration (with legacy prefix - don't use these anymore)
 *
 */

#define NIOS2_BIG_ENDIAN 0
#define NIOS2_BREAK_ADDR 0x2004820
#define NIOS2_CPU_FREQ 50000000u
#define NIOS2_CPU_ID_SIZE 1
#define NIOS2_CPU_ID_VALUE 0x00000000
#define NIOS2_CPU_IMPLEMENTATION "small"
#define NIOS2_DATA_ADDR_WIDTH 0x1a
#define NIOS2_DCACHE_LINE_SIZE 0
#define NIOS2_DCACHE_LINE_SIZE_LOG2 0
#define NIOS2_DCACHE_SIZE 0
#define NIOS2_EXCEPTION_ADDR 0x2000020
#define NIOS2_FLUSHDA_SUPPORTED
#define NIOS2_HARDWARE_DIVIDE_PRESENT 0
#define NIOS2_HARDWARE_MULTIPLY_PRESENT 1
#define NIOS2_HARDWARE_MULX_PRESENT 0
#define NIOS2_HAS_DEBUG_CORE 1
#define NIOS2_HAS_DEBUG_STUB
#define NIOS2_HAS_JMPI_INSTRUCTION
#define NIOS2_ICACHE_LINE_SIZE 32
#define NIOS2_ICACHE_LINE_SIZE_LOG2 5
#define NIOS2_ICACHE_SIZE 4096
#define NIOS2_INST_ADDR_WIDTH 0x1a
#define NIOS2_RESET_ADDR 0x2000000


/*
 * Define for each module class mastered by the CPU
 *
 */

#define __ALTERA_AVALON_JTAG_UART
#define __ALTERA_AVALON_NEW_SDRAM_CONTROLLER
#define __ALTERA_AVALON_ONCHIP_MEMORY2
#define __ALTERA_AVALON_PIO
#define __ALTERA_AVALON_SYSID_QSYS
#define __ALTERA_AVALON_TIMER
#define __ALTERA_NIOS2_QSYS


/*
 * LED_0 configuration
 *
 */

#define ALT_MODULE_CLASS_LED_0 altera_avalon_pio
#define LED_0_BASE 0x2005020
#define LED_0_BIT_CLEARING_EDGE_REGISTER 0
#define LED_0_BIT_MODIFYING_OUTPUT_REGISTER 1
#define LED_0_CAPTURE 0
#define LED_0_DATA_WIDTH 32
#define LED_0_DO_TEST_BENCH_WIRING 0
#define LED_0_DRIVEN_SIM_VALUE 0x0
#define LED_0_EDGE_TYPE "NONE"
#define LED_0_FREQ 50000000u
#define LED_0_HAS_IN 0
#define LED_0_HAS_OUT 1
#define LED_0_HAS_TRI 0
#define LED_0_IRQ -1
#define LED_0_IRQ_INTERRUPT_CONTROLLER_ID -1
#define LED_0_IRQ_TYPE "NONE"
#define LED_0_NAME "/dev/LED_0"
#define LED_0_RESET_VALUE 0x0
#define LED_0_SPAN 32
#define LED_0_TYPE "altera_avalon_pio"


/*
 * LED_1 configuration
 *
 */

#define ALT_MODULE_CLASS_LED_1 altera_avalon_pio
#define LED_1_BASE 0x2005060
#define LED_1_BIT_CLEARING_EDGE_REGISTER 0
#define LED_1_BIT_MODIFYING_OUTPUT_REGISTER 1
#define LED_1_CAPTURE 0
#define LED_1_DATA_WIDTH 32
#define LED_1_DO_TEST_BENCH_WIRING 0
#define LED_1_DRIVEN_SIM_VALUE 0x0
#define LED_1_EDGE_TYPE "NONE"
#define LED_1_FREQ 50000000u
#define LED_1_HAS_IN 0
#define LED_1_HAS_OUT 1
#define LED_1_HAS_TRI 0
#define LED_1_IRQ -1
#define LED_1_IRQ_INTERRUPT_CONTROLLER_ID -1
#define LED_1_IRQ_TYPE "NONE"
#define LED_1_NAME "/dev/LED_1"
#define LED_1_RESET_VALUE 0x0
#define LED_1_SPAN 32
#define LED_1_TYPE "altera_avalon_pio"


/*
 * LED_2 configuration
 *
 */

#define ALT_MODULE_CLASS_LED_2 altera_avalon_pio
#define LED_2_BASE 0x2005040
#define LED_2_BIT_CLEARING_EDGE_REGISTER 0
#define LED_2_BIT_MODIFYING_OUTPUT_REGISTER 1
#define LED_2_CAPTURE 0
#define LED_2_DATA_WIDTH 32
#define LED_2_DO_TEST_BENCH_WIRING 0
#define LED_2_DRIVEN_SIM_VALUE 0x0
#define LED_2_EDGE_TYPE "NONE"
#define LED_2_FREQ 50000000u
#define LED_2_HAS_IN 0
#define LED_2_HAS_OUT 1
#define LED_2_HAS_TRI 0
#define LED_2_IRQ -1
#define LED_2_IRQ_INTERRUPT_CONTROLLER_ID -1
#define LED_2_IRQ_TYPE "NONE"
#define LED_2_NAME "/dev/LED_2"
#define LED_2_RESET_VALUE 0x0
#define LED_2_SPAN 32
#define LED_2_TYPE "altera_avalon_pio"


/*
 * LED_color configuration
 *
 */

#define ALT_MODULE_CLASS_LED_color altera_avalon_pio
#define LED_COLOR_BASE 0x20050f0
#define LED_COLOR_BIT_CLEARING_EDGE_REGISTER 0
#define LED_COLOR_BIT_MODIFYING_OUTPUT_REGISTER 0
#define LED_COLOR_CAPTURE 0
#define LED_COLOR_DATA_WIDTH 24
#define LED_COLOR_DO_TEST_BENCH_WIRING 0
#define LED_COLOR_DRIVEN_SIM_VALUE 0x0
#define LED_COLOR_EDGE_TYPE "NONE"
#define LED_COLOR_FREQ 50000000u
#define LED_COLOR_HAS_IN 0
#define LED_COLOR_HAS_OUT 1
#define LED_COLOR_HAS_TRI 0
#define LED_COLOR_IRQ -1
#define LED_COLOR_IRQ_INTERRUPT_CONTROLLER_ID -1
#define LED_COLOR_IRQ_TYPE "NONE"
#define LED_COLOR_NAME "/dev/LED_color"
#define LED_COLOR_RESET_VALUE 0xff0000
#define LED_COLOR_SPAN 16
#define LED_COLOR_TYPE "altera_avalon_pio"


/*
 * SWITCH_0 configuration
 *
 */

#define ALT_MODULE_CLASS_SWITCH_0 altera_avalon_pio
#define SWITCH_0_BASE 0x2005080
#define SWITCH_0_BIT_CLEARING_EDGE_REGISTER 0
#define SWITCH_0_BIT_MODIFYING_OUTPUT_REGISTER 1
#define SWITCH_0_CAPTURE 0
#define SWITCH_0_DATA_WIDTH 8
#define SWITCH_0_DO_TEST_BENCH_WIRING 0
#define SWITCH_0_DRIVEN_SIM_VALUE 0x0
#define SWITCH_0_EDGE_TYPE "NONE"
#define SWITCH_0_FREQ 50000000u
#define SWITCH_0_HAS_IN 0
#define SWITCH_0_HAS_OUT 0
#define SWITCH_0_HAS_TRI 1
#define SWITCH_0_IRQ -1
#define SWITCH_0_IRQ_INTERRUPT_CONTROLLER_ID -1
#define SWITCH_0_IRQ_TYPE "NONE"
#define SWITCH_0_NAME "/dev/SWITCH_0"
#define SWITCH_0_RESET_VALUE 0x0
#define SWITCH_0_SPAN 32
#define SWITCH_0_TYPE "altera_avalon_pio"


/*
 * SWITCH_1 configuration
 *
 */

#define ALT_MODULE_CLASS_SWITCH_1 altera_avalon_pio
#define SWITCH_1_BASE 0x20050e0
#define SWITCH_1_BIT_CLEARING_EDGE_REGISTER 0
#define SWITCH_1_BIT_MODIFYING_OUTPUT_REGISTER 0
#define SWITCH_1_CAPTURE 0
#define SWITCH_1_DATA_WIDTH 8
#define SWITCH_1_DO_TEST_BENCH_WIRING 0
#define SWITCH_1_DRIVEN_SIM_VALUE 0x0
#define SWITCH_1_EDGE_TYPE "NONE"
#define SWITCH_1_FREQ 50000000u
#define SWITCH_1_HAS_IN 0
#define SWITCH_1_HAS_OUT 0
#define SWITCH_1_HAS_TRI 1
#define SWITCH_1_IRQ -1
#define SWITCH_1_IRQ_INTERRUPT_CONTROLLER_ID -1
#define SWITCH_1_IRQ_TYPE "NONE"
#define SWITCH_1_NAME "/dev/SWITCH_1"
#define SWITCH_1_RESET_VALUE 0x0
#define SWITCH_1_SPAN 16
#define SWITCH_1_TYPE "altera_avalon_pio"


/*
 * System configuration
 *
 */

#define ALT_DEVICE_FAMILY "Cyclone II"
#define ALT_ENHANCED_INTERRUPT_API_PRESENT
#define ALT_IRQ_BASE NULL
#define ALT_LOG_PORT "/dev/null"
#define ALT_LOG_PORT_BASE 0x0
#define ALT_LOG_PORT_DEV null
#define ALT_LOG_PORT_TYPE ""
#define ALT_NUM_EXTERNAL_INTERRUPT_CONTROLLERS 0
#define ALT_NUM_INTERNAL_INTERRUPT_CONTROLLERS 1
#define ALT_NUM_INTERRUPT_CONTROLLERS 1
#define ALT_STDERR "/dev/jtag_uart_0"
#define ALT_STDERR_BASE 0x2005100
#define ALT_STDERR_DEV jtag_uart_0
#define ALT_STDERR_IS_JTAG_UART
#define ALT_STDERR_PRESENT
#define ALT_STDERR_TYPE "altera_avalon_jtag_uart"
#define ALT_STDIN "/dev/jtag_uart_0"
#define ALT_STDIN_BASE 0x2005100
#define ALT_STDIN_DEV jtag_uart_0
#define ALT_STDIN_IS_JTAG_UART
#define ALT_STDIN_PRESENT
#define ALT_STDIN_TYPE "altera_avalon_jtag_uart"
#define ALT_STDOUT "/dev/jtag_uart_0"
#define ALT_STDOUT_BASE 0x2005100
#define ALT_STDOUT_DEV jtag_uart_0
#define ALT_STDOUT_IS_JTAG_UART
#define ALT_STDOUT_PRESENT
#define ALT_STDOUT_TYPE "altera_avalon_jtag_uart"
#define ALT_SYSTEM_NAME "qsys_top"


/*
 * buttons configuration
 *
 */

#define ALT_MODULE_CLASS_buttons altera_avalon_pio
#define BUTTONS_BASE 0x2005000
#define BUTTONS_BIT_CLEARING_EDGE_REGISTER 1
#define BUTTONS_BIT_MODIFYING_OUTPUT_REGISTER 1
#define BUTTONS_CAPTURE 1
#define BUTTONS_DATA_WIDTH 4
#define BUTTONS_DO_TEST_BENCH_WIRING 0
#define BUTTONS_DRIVEN_SIM_VALUE 0x0
#define BUTTONS_EDGE_TYPE "FALLING"
#define BUTTONS_FREQ 50000000u
#define BUTTONS_HAS_IN 1
#define BUTTONS_HAS_OUT 1
#define BUTTONS_HAS_TRI 0
#define BUTTONS_IRQ 2
#define BUTTONS_IRQ_INTERRUPT_CONTROLLER_ID 0
#define BUTTONS_IRQ_TYPE "EDGE"
#define BUTTONS_NAME "/dev/buttons"
#define BUTTONS_RESET_VALUE 0x0
#define BUTTONS_SPAN 32
#define BUTTONS_TYPE "altera_avalon_pio"


/*
 * hal configuration
 *
 */

#define ALT_MAX_FD 32
#define ALT_SYS_CLK TIMER
#define ALT_TIMESTAMP_CLK none


/*
 * jtag_uart_0 configuration
 *
 */

#define ALT_MODULE_CLASS_jtag_uart_0 altera_avalon_jtag_uart
#define JTAG_UART_0_BASE 0x2005100
#define JTAG_UART_0_IRQ 3
#define JTAG_UART_0_IRQ_INTERRUPT_CONTROLLER_ID 0
#define JTAG_UART_0_NAME "/dev/jtag_uart_0"
#define JTAG_UART_0_READ_DEPTH 64
#define JTAG_UART_0_READ_THRESHOLD 8
#define JTAG_UART_0_SPAN 8
#define JTAG_UART_0_TYPE "altera_avalon_jtag_uart"
#define JTAG_UART_0_WRITE_DEPTH 64
#define JTAG_UART_0_WRITE_THRESHOLD 8


/*
 * onchip_mem configuration
 *
 */

#define ALT_MODULE_CLASS_onchip_mem altera_avalon_onchip_memory2
#define ONCHIP_MEM_ALLOW_IN_SYSTEM_MEMORY_CONTENT_EDITOR 0
#define ONCHIP_MEM_ALLOW_MRAM_SIM_CONTENTS_ONLY_FILE 0
#define ONCHIP_MEM_BASE 0x2000000
#define ONCHIP_MEM_CONTENTS_INFO ""
#define ONCHIP_MEM_DUAL_PORT 0
#define ONCHIP_MEM_GUI_RAM_BLOCK_TYPE "Automatic"
#define ONCHIP_MEM_INIT_CONTENTS_FILE "onchip_mem"
#define ONCHIP_MEM_INIT_MEM_CONTENT 1
#define ONCHIP_MEM_INSTANCE_ID "NONE"
#define ONCHIP_MEM_IRQ -1
#define ONCHIP_MEM_IRQ_INTERRUPT_CONTROLLER_ID -1
#define ONCHIP_MEM_NAME "/dev/onchip_mem"
#define ONCHIP_MEM_NON_DEFAULT_INIT_FILE_ENABLED 0
#define ONCHIP_MEM_RAM_BLOCK_TYPE "Auto"
#define ONCHIP_MEM_READ_DURING_WRITE_MODE "DONT_CARE"
#define ONCHIP_MEM_SINGLE_CLOCK_OP 0
#define ONCHIP_MEM_SIZE_MULTIPLE 1
#define ONCHIP_MEM_SIZE_VALUE 16384u
#define ONCHIP_MEM_SPAN 16384
#define ONCHIP_MEM_TYPE "altera_avalon_onchip_memory2"
#define ONCHIP_MEM_WRITABLE 1


/*
 * sdram configuration
 *
 */

#define ALT_MODULE_CLASS_sdram altera_avalon_new_sdram_controller
#define SDRAM_BASE 0x0
#define SDRAM_CAS_LATENCY 2
#define SDRAM_CONTENTS_INFO ""
#define SDRAM_INIT_NOP_DELAY 0.0
#define SDRAM_INIT_REFRESH_COMMANDS 8
#define SDRAM_IRQ -1
#define SDRAM_IRQ_INTERRUPT_CONTROLLER_ID -1
#define SDRAM_IS_INITIALIZED 1
#define SDRAM_NAME "/dev/sdram"
#define SDRAM_POWERUP_DELAY 200.0
#define SDRAM_REFRESH_PERIOD 0.75
#define SDRAM_REGISTER_DATA_IN 1
#define SDRAM_SDRAM_ADDR_WIDTH 0x18
#define SDRAM_SDRAM_BANK_WIDTH 2
#define SDRAM_SDRAM_COL_WIDTH 9
#define SDRAM_SDRAM_DATA_WIDTH 16
#define SDRAM_SDRAM_NUM_BANKS 4
#define SDRAM_SDRAM_NUM_CHIPSELECTS 1
#define SDRAM_SDRAM_ROW_WIDTH 13
#define SDRAM_SHARED_DATA 0
#define SDRAM_SIM_MODEL_BASE 0
#define SDRAM_SPAN 33554432
#define SDRAM_STARVATION_INDICATOR 0
#define SDRAM_TRISTATE_BRIDGE_SLAVE ""
#define SDRAM_TYPE "altera_avalon_new_sdram_controller"
#define SDRAM_T_AC 6.5
#define SDRAM_T_MRD 3
#define SDRAM_T_RCD 20.0
#define SDRAM_T_RFC 70.0
#define SDRAM_T_RP 20.0
#define SDRAM_T_WR 14.0


/*
 * sysid_qsys_0 configuration
 *
 */

#define ALT_MODULE_CLASS_sysid_qsys_0 altera_avalon_sysid_qsys
#define SYSID_QSYS_0_BASE 0x2005108
#define SYSID_QSYS_0_ID -558907665
#define SYSID_QSYS_0_IRQ -1
#define SYSID_QSYS_0_IRQ_INTERRUPT_CONTROLLER_ID -1
#define SYSID_QSYS_0_NAME "/dev/sysid_qsys_0"
#define SYSID_QSYS_0_SPAN 8
#define SYSID_QSYS_0_TIMESTAMP 1360593110
#define SYSID_QSYS_0_TYPE "altera_avalon_sysid_qsys"


/*
 * timer configuration
 *
 */

#define ALT_MODULE_CLASS_timer altera_avalon_timer
#define TIMER_ALWAYS_RUN 0
#define TIMER_BASE 0x20050a0
#define TIMER_COUNTER_SIZE 32
#define TIMER_FIXED_PERIOD 0
#define TIMER_FREQ 50000000u
#define TIMER_IRQ 0
#define TIMER_IRQ_INTERRUPT_CONTROLLER_ID 0
#define TIMER_LOAD_VALUE 49999ull
#define TIMER_MULT 0.0010
#define TIMER_NAME "/dev/timer"
#define TIMER_PERIOD 1
#define TIMER_PERIOD_UNITS "ms"
#define TIMER_RESET_OUTPUT 0
#define TIMER_SNAPSHOT 1
#define TIMER_SPAN 32
#define TIMER_TICKS_PER_SEC 1000u
#define TIMER_TIMEOUT_PULSE_OUTPUT 0
#define TIMER_TYPE "altera_avalon_timer"


/*
 * timer_1 configuration
 *
 */

#define ALT_MODULE_CLASS_timer_1 altera_avalon_timer
#define TIMER_1_ALWAYS_RUN 0
#define TIMER_1_BASE 0x20050c0
#define TIMER_1_COUNTER_SIZE 32
#define TIMER_1_FIXED_PERIOD 0
#define TIMER_1_FREQ 50000000u
#define TIMER_1_IRQ 1
#define TIMER_1_IRQ_INTERRUPT_CONTROLLER_ID 0
#define TIMER_1_LOAD_VALUE 49999ull
#define TIMER_1_MULT 0.0010
#define TIMER_1_NAME "/dev/timer_1"
#define TIMER_1_PERIOD 1
#define TIMER_1_PERIOD_UNITS "ms"
#define TIMER_1_RESET_OUTPUT 0
#define TIMER_1_SNAPSHOT 1
#define TIMER_1_SPAN 32
#define TIMER_1_TICKS_PER_SEC 1000u
#define TIMER_1_TIMEOUT_PULSE_OUTPUT 0
#define TIMER_1_TYPE "altera_avalon_timer"

#endif /* __SYSTEM_H_ */
