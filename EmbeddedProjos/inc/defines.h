/*
 * defines.h
 *
 *  Created on: Dec 13, 2016
 *      Author: salsiederja
 */

#ifndef DEFINES_H_
#define DEFINES_H_
#include "inttypes.h"

#define _registerPtr (volatile uint32_t*)
#define _offset (uint8_t)

#define true 1
#define false 0


/*	TOC
 *
 * Section		LINE Start
 * GPIOS  		29
 * RCC			322
 * ADC			346
 *
 */

/*
 * GPIO'S
 */
#define GPIOA (uint32_t) 0x40020000
#define GPIOB (uint32_t) 0x40020400
#define GPIOC (uint32_t) 0x40020800
#define GPIOD (uint32_t) 0x40020C00
#define GPIOE (uint32_t) 0x40021000
#define GPIOF (uint32_t) 0x40021400
#define GPIOG (uint32_t) 0x40021800
#define GPIOH (uint32_t) 0x40021C00

#define GPIO_MODER _offset 0x0
#define GPIO_OTYPER _offset 0x04
#define GPIO_OSPEEDR _offset 0x08
#define GPIO_PUPDR _offset 0x0c
#define GPIO_IDR _offset 0x10
#define GPIO_ODR _offset 0x14
#define GPIO_BSRR _offset 0x18
#define GPIO_LCKR _offset 0x1c
#define GPIO_AFRL _offset 0x20
#define GPIO_AFRH _offset 0x24

#define GPIOA_MODER _registerPtr 0x40020000
#define GPIOB_MODER _registerPtr 0x40020400
#define GPIOC_MODER _registerPtr 0x40020800
#define GPIOD_MODER _registerPtr 0x40020c00
#define GPIOE_MODER _registerPtr 0x40021000
#define GPIOF_MODER _registerPtr 0x40021400
#define GPIOG_MODER _registerPtr 0x40021800
#define GPIOH_MODER _registerPtr 0x40021c00

	#define MODER_0_BF _offset 0x0
	#define MODER_1_BF _offset 0x2
	#define MODER_2_BF _offset 0x4
	#define MODER_3_BF _offset 0x6
	#define MODER_4_BF _offset 0x8
	#define MODER_5_BF _offset 0xA
	#define MODER_6_BF _offset 0xC
	#define MODER_7_BF _offset 0xE
	#define MODER_8_BF _offset 0x10
	#define MODER_9_BF _offset 0x12
	#define MODER_10_BF _offset 0x14
	#define MODER_11_BF _offset 0x16
	#define MODER_12_BF _offset 0x18
	#define MODER_13_BF _offset 0x1A
	#define MODER_14_BF _offset 0x1C
	#define MODER_15_BF _offset 0x1E

		#define GPIO_INPUT 0
		#define GPIO_OUTPUT 1
		#define GPIO_ALTERNATE_FUNCTION 2
		#define GPIO_ANALOG 3

#define GPIOA_OTYPER _registerPtr 0x40020004
#define GPIOB_OTYPER _registerPtr 0x40020404
#define GPIOC_OTYPER _registerPtr 0x40020804
#define GPIOD_OTYPER _registerPtr 0x40020c04
#define GPIOE_OTYPER _registerPtr 0x40021004
#define GPIOF_OTYPER _registerPtr 0x40021404
#define GPIOG_OTYPER _registerPtr 0x40021804
#define GPIOH_OTYPER _registerPtr 0x40021c04

	#define OTYPER_0_BF _offset 0x0
	#define OTYPER_1_BF _offset 0x1
	#define OTYPER_2_BF _offset 0x2
	#define OTYPER_3_BF _offset 0x3
	#define OTYPER_4_BF _offset 0x4
	#define OTYPER_5_BF _offset 0x5
	#define OTYPER_6_BF _offset 0x6
	#define OTYPER_7_BF _offset 0x7
	#define OTYPER_8_BF _offset 0x8
	#define OTYPER_9_BF _offset 0x9
	#define OTYPER_10_BF _offset 0xA
	#define OTYPER_11_BF _offset 0xB
	#define OTYPER_12_BF _offset 0xC
	#define OTYPER_13_BF _offset 0xD
	#define OTYPER_14_BF _offset 0xE
	#define OTYPER_15_BF _offset 0xF

#define GPIOA_OSPEEDR _registerPtr 0x40020008
#define GPIOB_OSPEEDR _registerPtr 0x40020408
#define GPIOC_OSPEEDR _registerPtr 0x40020808
#define GPIOD_OSPEEDR _registerPtr 0x40020c08
#define GPIOE_OSPEEDR _registerPtr 0x40021008
#define GPIOF_OSPEEDR _registerPtr 0x40021408
#define GPIOG_OSPEEDR _registerPtr 0x40021808
#define GPIOH_OSPEEDR _registerPtr 0x40021c08

	#define OSPEEDR_0_BF _offset 0x0
	#define OSPEEDR_1_BF _offset 0x2
	#define OSPEEDR_2_BF _offset 0x4
	#define OSPEEDR_3_BF _offset 0x6
	#define OSPEEDR_4_BF _offset 0x8
	#define OSPEEDR_5_BF _offset 0xA
	#define OSPEEDR_6_BF _offset 0xC
	#define OSPEEDR_7_BF _offset 0xE
	#define OSPEEDR_8_BF _offset 0x10
	#define OSPEEDR_9_BF _offset 0x12
	#define OSPEEDR_10_BF _offset 0x14
	#define OSPEEDR_11_BF _offset 0x16
	#define OSPEEDR_12_BF _offset 0x18
	#define OSPEEDR_13_BF _offset 0x1A
	#define OSPEEDR_14_BF _offset 0x1C
	#define OSPEEDR_15_BF _offset 0x1E

#define GPIOA_PUPDR _registerPtr 0x4002000c
#define GPIOB_PUPDR _registerPtr 0x4002040c
#define GPIOC_PUPDR _registerPtr 0x4002080c
#define GPIOD_PUPDR _registerPtr 0x40020c0c
#define GPIOE_PUPDR _registerPtr 0x4002100c
#define GPIOF_PUPDR _registerPtr 0x4002140c
#define GPIOG_PUPDR _registerPtr 0x4002180c
#define GPIOH_PUPDR _registerPtr 0x40021c0c

	#define PUPDR_0_BF _offset 0x0
	#define PUPDR_1_BF _offset 0x2
	#define PUPDR_2_BF _offset 0x4
	#define PUPDR_3_BF _offset 0x6
	#define PUPDR_4_BF _offset 0x8
	#define PUPDR_5_BF _offset 0xA
	#define PUPDR_6_BF _offset 0xC
	#define PUPDR_7_BF _offset 0xE
	#define PUPDR_8_BF _offset 0x10
	#define PUPDR_9_BF _offset 0x12
	#define PUPDR_10_BF _offset 0x14
	#define PUPDR_11_BF _offset 0x16
	#define PUPDR_12_BF _offset 0x18
	#define PUPDR_13_BF _offset 0x1A
	#define PUPDR_14_BF _offset 0x1C
	#define PUPDR_15_BF _offset 0x1E

	#define GPIO_NO_PULL 0
	#define GPIO_PULLUP 1
	#define GPIO_PULLDOWN 2

#define GPIOA_IDR _registerPtr 0x40020010
#define GPIOB_IDR _registerPtr 0x40020410
#define GPIOC_IDR _registerPtr 0x40020810
#define GPIOD_IDR _registerPtr 0x40020c10
#define GPIOE_IDR _registerPtr 0x40021010
#define GPIOF_IDR _registerPtr 0x40021410
#define GPIOG_IDR _registerPtr 0x40021810
#define GPIOH_IDR _registerPtr 0x40021c10

	#define IDR_0_BF _offset 0x0
	#define IDR_1_BF _offset 0x1
	#define IDR_2_BF _offset 0x2
	#define IDR_3_BF _offset 0x3
	#define IDR_4_BF _offset 0x4
	#define IDR_5_BF _offset 0x5
	#define IDR_6_BF _offset 0x6
	#define IDR_7_BF _offset 0x7
	#define IDR_8_BF _offset 0x8
	#define IDR_9_BF _offset 0x9
	#define IDR_10_BF _offset 0xA
	#define IDR_11_BF _offset 0xB
	#define IDR_12_BF _offset 0xC
	#define IDR_13_BF _offset 0xD
	#define IDR_14_BF _offset 0xE
	#define IDR_15_BF _offset 0xF

#define GPIOA_ODR _registerPtr 0x40020014
#define GPIOB_ODR _registerPtr 0x40020414
#define GPIOC_ODR _registerPtr 0x40020814
#define GPIOD_ODR _registerPtr 0x40020c14
#define GPIOE_ODR _registerPtr 0x40021014
#define GPIOF_ODR _registerPtr 0x40021414
#define GPIOG_ODR _registerPtr 0x40021814
#define GPIOH_ODR _registerPtr 0x40021c14

	#define ODR_0_BF _offset 0x0
	#define ODR_1_BF _offset 0x1
	#define ODR_2_BF _offset 0x2
	#define ODR_3_BF _offset 0x3
	#define ODR_4_BF _offset 0x4
	#define ODR_5_BF _offset 0x5
	#define ODR_6_BF _offset 0x6
	#define ODR_7_BF _offset 0x7
	#define ODR_8_BF _offset 0x8
	#define ODR_9_BF _offset 0x9
	#define ODR_10_BF _offset 0xA
	#define ODR_11_BF _offset 0xB
	#define ODR_12_BF _offset 0xC
	#define ODR_13_BF _offset 0xD
	#define ODR_14_BF _offset 0xE
	#define ODR_15_BF _offset 0xF

#define GPIOA_BSRR _registerPtr 0x40020018
#define GPIOB_BSRR _registerPtr 0x40020418
#define GPIOC_BSRR _registerPtr 0x40020818
#define GPIOD_BSRR _registerPtr 0x40020c18
#define GPIOE_BSRR _registerPtr 0x40021018
#define GPIOF_BSRR _registerPtr 0x40021418
#define GPIOG_BSRR _registerPtr 0x40021818
#define GPIOH_BSRR _registerPtr 0x40021c18

	#define BSRR_S_0_BF _offset 0x0
	#define BSRR_S_1_BF _offset 0x1
	#define BSRR_S_2_BF _offset 0x2
	#define BSRR_S_3_BF _offset 0x3
	#define BSRR_S_4_BF _offset 0x4
	#define BSRR_S_5_BF _offset 0x5
	#define BSRR_S_6_BF _offset 0x6
	#define BSRR_S_7_BF _offset 0x7
	#define BSRR_S_8_BF _offset 0x8
	#define BSRR_S_9_BF _offset 0x9
	#define BSRR_S_10_BF _offset 0xA
	#define BSRR_S_11_BF _offset 0xB
	#define BSRR_S_12_BF _offset 0xC
	#define BSRR_S_13_BF _offset 0xD
	#define BSRR_S_14_BF _offset 0xE
	#define BSRR_S_15_BF _offset 0xF
	#define BSRR_R_0_BF _offset 0x10
	#define BSRR_R_1_BF _offset 0x11
	#define BSRR_R_2_BF _offset 0x12
	#define BSRR_R_3_BF _offset 0x13
	#define BSRR_R_4_BF _offset 0x14
	#define BSRR_R_5_BF _offset 0x15
	#define BSRR_R_6_BF _offset 0x16
	#define BSRR_R_7_BF _offset 0x17
	#define BSRR_R_8_BF _offset 0x18
	#define BSRR_R_9_BF _offset 0x19
	#define BSRR_R_10_BF _offset 0x1A
	#define BSRR_R_11_BF _offset 0x1B
	#define BSRR_R_12_BF _offset 0x1C
	#define BSRR_R_13_BF _offset 0x1D
	#define BSRR_R_14_BF _offset 0x1E
	#define BSRR_R_15_BF _offset 0x1F

#define GPIOA_LCKR _registerPtr 0x4002001c
#define GPIOB_LCKR _registerPtr 0x4002041c
#define GPIOC_LCKR _registerPtr 0x4002081c
#define GPIOD_LCKR _registerPtr 0x40020c1c
#define GPIOE_LCKR _registerPtr 0x4002101c
#define GPIOF_LCKR _registerPtr 0x4002141c
#define GPIOG_LCKR _registerPtr 0x4002181c
#define GPIOH_LCKR _registerPtr 0x40021c1c

	#define LCKR_0_BF _offset 0x0
	#define LCKR_1_BF _offset 0x1
	#define LCKR_2_BF _offset 0x2
	#define LCKR_3_BF _offset 0x3
	#define LCKR_4_BF _offset 0x4
	#define LCKR_5_BF _offset 0x5
	#define LCKR_6_BF _offset 0x6
	#define LCKR_7_BF _offset 0x7
	#define LCKR_8_BF _offset 0x8
	#define LCKR_9_BF _offset 0x9
	#define LCKR_10_BF _offset 0xA
	#define LCKR_11_BF _offset 0xB
	#define LCKR_12_BF _offset 0xC
	#define LCKR_13_BF _offset 0xD
	#define LCKR_14_BF _offset 0xE
	#define LCKR_15_BF _offset 0xF
	#define LCKR_LCKK_BF _offset 0x10

#define GPIOA_AFRL _registerPtr 0x40020020
#define GPIOB_AFRL _registerPtr 0x40020420
#define GPIOC_AFRL _registerPtr 0x40020820
#define GPIOD_AFRL _registerPtr 0x40020c20
#define GPIOE_AFRL _registerPtr 0x40021020
#define GPIOF_AFRL _registerPtr 0x40021420
#define GPIOG_AFRL _registerPtr 0x40021820
#define GPIOH_AFRL _registerPtr 0x40021c20

	#define AFRL_0_BF _offset 0x0
	#define AFRL_1_BF _offset 0x4
	#define AFRL_2_BF _offset 0x8
	#define AFRL_3_BF _offset 0xC
	#define AFRL_4_BF _offset 0x10
	#define AFRL_5_BF _offset 0x14
	#define AFRL_6_BF _offset 0x18
	#define AFRL_7_BF _offset 0x1c

#define GPIOA_AFRH _registerPtr 0x40020024
#define GPIOB_AFRH _registerPtr 0x40020424
#define GPIOC_AFRH _registerPtr 0x40020824
#define GPIOD_AFRH _registerPtr 0x40020c24
#define GPIOE_AFRH _registerPtr 0x40021024
#define GPIOF_AFRH _registerPtr 0x40021424
#define GPIOG_AFRH _registerPtr 0x40021824
#define GPIOH_AFRH _registerPtr 0x40021c24

	#define AFRH_8_BF _offset 0x0
	#define AFRH_9_BF _offset 0x4
	#define AFRH_10_BF _offset 0x8
	#define AFRH_11_BF _offset 0xC
	#define AFRH_12_BF _offset 0x10
	#define AFRH_13_BF _offset 0x14
	#define AFRH_14_BF _offset 0x18
	#define AFRH_15_BF _offset 0x1c

/*
 * RCC Registers
 */

#define RCC_AHB1ENR _registerPtr 0x40023830
	#define GPIOAEN_BF 0
	#define GPIOBEN_BF 1
	#define GPIOCEN_BF 2
	#define GPIODEN_BF 3
	#define GPIOEEN_BF 4
	#define GPIOFEN_BF 5
	#define GPIOGEN_BF 6
	#define GPIOHEN_BF 7

#define RCC_APB2ENR _registerPtr 0x40023844
	#define USART1EN_BF _offset 0x4
	#define ADC1EN_BF _offset 0x8
	#define ADC2EN_BF _offset 0x9
	#define ADC3EN_BF _offset 0xA

#define RCC_APB1ENR _registerPtr 0x40023840






/*
 * ADC1 REGISTERS
 */

#define ADC1_SR _registerPtr 0x40012000
	#define ADC_SR_AWD_BF _offset 0x0
	#define ADC_SR_EOC_BF _offset 0x1
	#define ADC_SR_JEOC_BF _offset 0x2
	#define ADC_SR_JSTRT_BF _offset 0x3
	#define ADC_SR_STRT_BF _offset 0x4
	#define ADC_SR_OVR_BF _offset 0x5


#define ADC1_CR1 _registerPtr 0x40012004
	#define ADC_CR1_OVRIE_BF _offset 0x1A
	#define ADC_CR1_RES_BF _offset 0x18
	#define ADC_CR1_AWDEN_BF _offset 0x17
	#define ADC_CR1_JAWDEN_BF _offset 0x16
	#define ADC_CR1_DISCNUM_BF _offset 0xF
	#define ADC_CR1_JDISCEN_BF _offset 0xC
	#define ADC_CR1_DISCEN_BF _offset 0xB
	#define ADC_CR1_JAUTO_BF _offset 0xA
	#define ADC_CR1_AWDSGL_BF _offset 0x9
	#define ADC_CR1_SCAN_BF _offset 0x8
	#define ADC_CR1_JEOCIE_BF _offset 0x7
	#define ADC_CR1_AWDIE_BF _offset 0x6
	#define ADC_CR1_EOCIE_BF _offset 0x5
	#define ADC_CR1_AWDCH_BF _offset 0x0


#define ADC1_CR2 _registerPtr 0x40012008
	#define ADC_CR2_SWSTART_BF _offset 0x1e
	#define ADC_CR2_EXTEN_BF _offset 0x1d
	#define ADC_CR2_EXTSEL_BF _offset 0x1b
	#define ADC_CR2_JSWSTART_BF _offset 0x16
	#define ADC_CR2_JEXTEN_BF _offset 0x15
	#define ADC_CR2_JEXTSEL_BF _offset 0x13
	#define ADC_CR2_ALIGN_BF _offset 0xb
	#define ADC_CR2_EOCS_BF _offset 0xa
	#define ADC_CR2_DDS_BF _offset 0x9
	#define ADC_CR2_DMA_BF _offset 0x8
	#define ADC_CR2_CONT_BF _offset 0x1
	#define ADC_CR2_ADON_BF _offset 0x0

#define ADC1_SMPR1 _registerPtr 0x4001200c

#define ADC1_SMPR2 _registerPtr 0x40012010

#define ADC1_JOFR1 _registerPtr 0x40012014

#define ADC1_JOFR2 _registerPtr 0x40012018

#define ADC1_JOFR3 _registerPtr 0x4001201c

#define ADC1_JOFR4 _registerPtr 0x40012020

#define ADC1_HTR _registerPtr 0x40012024

#define ADC1_LTR _registerPtr 0x40012028

#define ADC1_SQR1 _registerPtr 0x4001202c
	#define ADC_SQR1_L_BF _offset 0x14
	#define ADC_SQR1_SQ16_BF _offset 0xf
	#define ADC_SQR1_SQ15_BF _offset 0xa
	#define ADC_SQR1_SQ14_BF _offset 0x5
	#define ADC_SQR1_SQ13_BF _offset 0x0


#define ADC1_SQR2 _registerPtr 0x40012030

#define ADC1_SQR3 _registerPtr 0x40012034

#define ADC1_JSQR _registerPtr 0x40012038

#define ADC1_JDR1 _registerPtr 0x4001203c

#define ADC1_JDR2 _registerPtr 0x40012040

#define ADC1_JDR3 _registerPtr 0x40012044

#define ADC1_JDR4 _registerPtr 0x40012048

#define ADC1_DR _registerPtr 0x4001204c


//Timer Start Addresses

#define TIM1 (uint32_t) 0x40010000
#define TIM8 (uint32_t) 0x40010400

#define TIM2 (uint32_t) 0x40000000
#define TIM3 (uint32_t) 0x40000400
#define TIM4 (uint32_t) 0x40000800
#define TIM5 (uint32_t) 0x40000C00

#define TIM9 (uint32_t) 0x40014000

#define TIM12 (uint32_t) 0x0001800

#define TIM10 (uint32_t) 0x0014400

#define TIM13 (uint32_t) 0x40001C00
#define TIM14 (uint32_t) 0x40002000

#define TIM11 (uint32_t) 0x40014800

#define TIM6 (uint32_t) 0x40001000
#define TIM7 (uint32_t) 0x40001400

/*
 * USART defines
 *
 */



	#define USART1_SR _registerPtr 0x40011000
		#define CTS_BF _offset 9
		#define LBD_BF _offset 8
		#define TXE_BF _offset 7
		#define TC_BF _offset 6
		#define RXNE_BF _offset 5
		#define IDLE_BF _offset 4
		#define ROE_BF _offset 3
		#define NF_BF _offset 2
		#define FE_BF _offset 1
		#define PE_BF _offset 0

	#define USART1_DR _registerPtr 0x40011004

	#define USART1_BRR _registerPtr 0x40011008
		#define MANTISSA_BF _offset 4
		#define FRACTION_BF _offset 0

	#define USART1_CR1 _registerPtr 0x4001100c
		#define  OVER8_BF _offset 0xf
		#define  UE_BF _offset 0xd
		#define  M_BF _offset 0xc
		#define  WAKE_BF _offset 0xb
		#define  PCE_BF _offset 0xa
		#define  PS_BF _offset 9
		#define  PEIE_BF _offset 8
		#define  TXEIE_BF _offset 7
		#define  TCIE_BF _offset 6
		#define  RXNEIE_BF _offset 5
		#define  IDLEIE_BF _offset 4
		#define  TE_BF _offset 3
		#define  RE_BF _offset 2
		#define  RWU_BF _offset 1
		#define  SBK_BF _offset 0

	#define USART1_CR2 _registerPtr 0x40011010
		#define  LINEN_BF _offset 0xe
		#define  STOP_BF _offset 0xc
		#define  CLKEN_BF _offset 0xb
		#define  CPOL_BF _offset 0xa
		#define  CPHA_BF _offset 9
		#define  LBCL_BF _offset 8
		#define  LBDIE_BF _offset 6
		#define  LBDL_BF _offset 5
		#define  ADD_BF _offset 0

	#define USART1_CR3 _registerPtr 0x40011014
		#define ONEBIT_BF _offset 0xb
		#define CTSIE_BF _offset 0xa
		#define CTIE_BF _offset 9
		#define RTSE_BF _offset 8
		#define DMAT_BF _offset 7
		#define DMAR_BF _offset 6
		#define SCEN_BF _offset 5
		#define NACK_BF _offset 4
		#define HDSEL_BF _offset 3
		#define IRLP_BF _offset 2
		#define IREN_BF _offset 1
		#define EIE_BF _offset 0

	#define USART1_GTPR _registerPtr 00x40011018
		#define GT_BF _offset 8
		#define PSC_BF _offset	0

















#endif /* DEFINES_H_ */
