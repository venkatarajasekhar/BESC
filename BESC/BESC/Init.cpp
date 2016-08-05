#include "Init.h"



void Init::PinMux_Init(void)
{
	/* supply clock to ports */
    CLOCK_EnableClock(kCLOCK_PortA);
	CLOCK_EnableClock(kCLOCK_PortB);

	// Set PTA6 as GPIO, LED output
	PORT_SetPinMux(PORTA, 3U, kPORT_MuxAsGpio);
	PORT_SetPinMux(PORTA, 4U, kPORT_MuxAsGpio);
	PORT_SetPinMux(PORTA, 5U, kPORT_MuxAsGpio);
	PORT_SetPinMux(PORTA, 6U, kPORT_MuxAsGpio);

	// Set PTB1 (pin 13) as LPUART_TX, PTB2 (pin 14) as RX
	PORT_SetPinMux(PORTB, 1U, kPORT_MuxAlt2);
	PORT_SetPinMux(PORTB, 2U, kPORT_MuxAlt2);

	// Set PTB10 (pin 9) as TPM0_CH1, PTB11 (pin 10) as TPM0_CH0
	PORT_SetPinMux(PORTB, 10U, kPORT_MuxAlt2);
	PORT_SetPinMux(PORTB, 11U, kPORT_MuxAlt2);
}

void Init::GPIO_Init(void)
{
	/* Define the init structure for the output LED pin*/
	gpio_pin_config_t digitalOut = {
		kGPIO_DigitalOutput, 0,
	};

	GPIO_PinInit(GPIOA, 3U, &digitalOut);
	GPIO_PinInit(GPIOA, 4U, &digitalOut);
	GPIO_PinInit(GPIOA, 5U, &digitalOut);
	GPIO_PinInit(GPIOA, 6U, &digitalOut);
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

	LPUART_Init(LPUART0, &config, CLOCK_GetPeriphClkFreq());
}

status_t Init::TPM0_Init(void)
{
	tpm_config_t tpmInfo;
	uint8_t updatedDutycycle = 0U;
	tpm_chnl_pwm_signal_param_t tpmParam[2];

	/* Configure tpm params with frequency 24kHZ */
	tpmParam[0].chnlNumber = tpm_chnl_t::kTPM_Chnl_0;
	tpmParam[0].level = _tpm_pwm_level_select::kTPM_HighTrue;
	tpmParam[0].dutyCyclePercent = 0U;

	tpmParam[1].chnlNumber = tpm_chnl_t::kTPM_Chnl_1;
	tpmParam[1].level = _tpm_pwm_level_select::kTPM_HighTrue;
	tpmParam[1].dutyCyclePercent = 0U;

	/* Board pin, clock, debug console init */
	//BOARD_InitPins();
	//BOARD_BootClockRUN();
	//BOARD_InitDebugConsole();
	/* Select the clock source for the TPM counter as MCG IRC48M clock */
	CLOCK_SetTpmClock(1U);

	/*
	* tpmInfo.prescale = kTPM_Prescale_Divide_1;
	* tpmInfo.useGlobalTimeBase = false;
	* tpmInfo.enableDoze = false;
	* tpmInfo.enableDebugMode = false;
	* tpmInfo.enableReloadOnTrigger = false;
	* tpmInfo.enableStopOnOverflow = false;
	* tpmInfo.enableStartOnTrigger = false;
	* tpmInfo.enablePauseOnTrigger = false;
	* tpmInfo.triggerSelect = kTPM_Trigger_Select_0;
	* tpmInfo.triggerSource = kTPM_TriggerSource_External;
	*/
	TPM_GetDefaultConfig(&tpmInfo);
	/* Initialize TPM module */
	TPM_Init(TPM0, &tpmInfo);

	auto s = TPM_SetupPwm(TPM0, tpmParam, 2U, tpm_pwm_mode_t::kTPM_CenterAlignedPwm, 24000U, CLOCK_GetPeriphClkFreq());
	if (s != kStatus_Success)
	{
		return s;
	}

	TPM_StartTimer(TPM0, tpm_clock_source_t::kTPM_SystemClock);

	return kStatus_Success;
}

void Init::Clock_init(void)
{
	/*
	* Core clock: 48MHz
	* Bus clock: 24MHz
	*/
    /* MCG_Lite configuration for HIRC mode. */
    mcglite_config_t mcgliteConfig;
	mcgliteConfig.outSrc = mcglite_clkout_src_t::kMCGLITE_ClkSrcHirc;
	mcgliteConfig.irclkEnableMode = _mcglite_irclk_enable_mode::kMCGLITE_IrclkEnable;
	mcgliteConfig.ircs = mcglite_lirc_mode_t::kMCGLITE_Lirc2M;
	mcgliteConfig.fcrdiv = mcglite_lirc_div_t::kMCGLITE_LircDivBy1;
	mcgliteConfig.lircDiv2 = mcglite_lirc_div_t::kMCGLITE_LircDivBy2;
	mcgliteConfig.hircEnableInNotHircMode = false;

	sim_clock_config_t simConfig;
#if (defined(FSL_FEATURE_SIM_OPT_HAS_OSC32K_SELECTION) && FSL_FEATURE_SIM_OPT_HAS_OSC32K_SELECTION)
	simConfig.er32kSrc = 0U; /* SIM_SOPT1[OSC32KSEL]. */
#endif
	simConfig.clkdiv1 = 0x00010000U; /* SIM_CLKDIV1. */

	CLOCK_SetSimSafeDivs();

	CLOCK_SetMcgliteConfig(&mcgliteConfig);

	CLOCK_SetSimConfig(&simConfig);

	SystemCoreClock = 48000000U;
}

