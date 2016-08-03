#include "Init.h"

void Init::PinMux_Init(void)
{
	/* supply clock to ports */
    CLOCK_EnableClock(kCLOCK_PortA);
	CLOCK_EnableClock(kCLOCK_PortB);

	// Set PTA6 as GPIO, LED output
	PORT_SetPinMux(PORTA, 6U, kPORT_MuxAsGpio);

	// Set PTB1 (pin 13) as LPUART_TX, PTB2 (pin 14) as RX
	PORT_SetPinMux(PORTB, 1U, kPORT_MuxAlt2);
	PORT_SetPinMux(PORTB, 2U, kPORT_MuxAlt2);
}

void Init::LPUART0_Init(void)
{
	lpuart_config_t config;

	CLOCK_SetLpuart0Clock(0x1U);
	//CLOCK_EnableClock(kCLOCK_Lpuart0);
	/*
	* config.baudRate_Bps = 115200U;
	* config.parityMode = kLPUART_ParityDisabled;
	* config.stopBitCount = kLPUART_OneStopBit;
	* config.txFifoWatermark = 0;
	* config.rxFifoWatermark = 0;
	* config.enableTx = false;
	* config.enableRx = false;
	*/
	LPUART_GetDefaultConfig(&config);
	config.baudRate_Bps = 9600U;
	config.enableTx = true;
	config.enableRx = true;

	LPUART_Init(LPUART0, &config, CLOCK_GetFreq(clock_name_t::kCLOCK_McgPeriphClk));
}

void Init::Clock_init(void)
{
	/*
	* Core clock: 48MHz
	* Bus clock: 24MHz
	*/
    /* MCG_Lite configuration for HIRC mode. */
    mcglite_config_t mcgliteConfig;
	mcgliteConfig.outSrc = kMCGLITE_ClkSrcHirc;
	mcgliteConfig.irclkEnableMode = _mcglite_irclk_enable_mode::kMCGLITE_IrclkEnable | _mcglite_irclk_enable_mode::kMCGLITE_IrclkEnableInStop;
	mcgliteConfig.ircs = kMCGLITE_Lirc2M;
	mcgliteConfig.fcrdiv = kMCGLITE_LircDivBy1;
	mcgliteConfig.lircDiv2 = kMCGLITE_LircDivBy2;
	mcgliteConfig.hircEnableInNotHircMode = false;

	const sim_clock_config_t simConfig =
	{
#if (defined(FSL_FEATURE_SIM_OPT_HAS_OSC32K_SELECTION) && FSL_FEATURE_SIM_OPT_HAS_OSC32K_SELECTION)
		.er32kSrc = 0U, /* SIM_SOPT1[OSC32KSEL]. */
#endif
		.clkdiv1 = 0x00010000U, /* SIM_CLKDIV1. */
	};

	CLOCK_SetSimSafeDivs();

	CLOCK_SetMcgliteConfig(&mcgliteConfig);

	CLOCK_SetSimConfig(&simConfig);

	SystemCoreClock = 48000000U;
}

