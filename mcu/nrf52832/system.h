/*
 * Part of the Conic project - robot arm controller
 *
 * NRF52832 common system functions
 *
 * See LICENSE.md for licensing information
 * Roman Luitko, 2020
 */

#ifndef MCU_NRF52832_SYSTEM_H
#define MCU_NRF52832_SYSTEM_H

#define NRF_TEMP_BASE	0x4000C000
#define NRF_CLOCK_BASE	0x40000000

/* Chip temperature */
struct nrf_temp_reg {
	volatile uint32_t TASKS_START;
	volatile uint32_t TASKS_STOP;
	volatile uint32_t __reserved_0[62];
	volatile uint32_t EVENTS_DATARDY;
	volatile uint32_t __reserved_1[128];
	volatile uint32_t INTENSET;
	volatile uint32_t INTENCLR;
	volatile uint32_t __reserved_2[127];
	volatile int32_t  TEMP;
	volatile uint32_t __reserved_3[5];
	volatile uint32_t A0;
	volatile uint32_t A1;
	volatile uint32_t A2;
	volatile uint32_t A3;
	volatile uint32_t A4;
	volatile uint32_t A5;
	volatile uint32_t __reserved_4[2];
	volatile uint32_t B0;
	volatile uint32_t B1;
	volatile uint32_t B2;
	volatile uint32_t B3;
	volatile uint32_t B4;
	volatile uint32_t B5;
	volatile uint32_t __reserved_5[2];
	volatile uint32_t T0;
	volatile uint32_t T1;
	volatile uint32_t T2;
	volatile uint32_t T3;
	volatile uint32_t T4;
};

struct nrf_clock_reg {
	volatile uint32_t TASKS_HFCLKSTART;
	volatile uint32_t TASKS_HFCLKSTOP;
	volatile uint32_t TASKS_LFCLKSTART;
	volatile uint32_t TASKS_LFCLKSTOP;
	volatile uint32_t TASKS_CAL;
	volatile uint32_t TASKS_CTSTART;
	volatile uint32_t TASKS_CTSTOP;
	volatile uint32_t __reserved_0[57];
	volatile uint32_t EVENTS_HFCLKSTARTED;
	volatile uint32_t EVENTS_LFCLKSTARTED;
	volatile uint32_t __reserved_1;
	volatile uint32_t EVENTS_DONE;
	volatile uint32_t EVENTS_CTTO;
	volatile uint32_t __reserved_2[124];
	volatile uint32_t INTENSET;
	volatile uint32_t INTENCLR;
	volatile uint32_t __reserved_3[63];
	volatile uint32_t HFCLKRUN;
	volatile uint32_t HFCLKSTAT;
	volatile uint32_t __reserved_4;
	volatile uint32_t LFCLKRUN;
	volatile uint32_t LFCLKSTAT;
	volatile uint32_t LFCLKSRCCOPY;
	volatile uint32_t __reserved_5[62];
	volatile uint32_t LFCLKSRC;
	volatile uint32_t __reserved_6[7];
	volatile uint32_t CTIV;
	volatile uint32_t __reserved_7[8];
	volatile uint32_t TRACECONFIG;
};

#define NRF_TEMP	((struct nrf_temp_reg*)NRF_TEMP_BASE)
#define NRF_CLOCK	((struct nrf_clock_reg*)NRF_CLOCK_BASE)

int system_temperature(void);
void system_ext_crystal_on(void);

#endif

