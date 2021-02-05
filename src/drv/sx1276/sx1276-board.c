/*
 / _____)             _              | |
( (____  _____ ____ _| |_ _____  ____| |__
 \____ \| ___ |    (_   _) ___ |/ ___)  _ \
 _____) ) ____| | | || |_| ____( (___| | | |
(______/|_____)_|_|_| \__)_____)\____)_| |_|
    (C)2013 Semtech

Description: SX1276 driver specific target board functions implementation

License: Revised BSD License, see LICENSE.TXT file include in the project

Maintainer: Miguel Luis and Gregory Cristian
*/
#include "drv/sx1276/radio.h"
#include "drv/sx1276/sx1276.h"
#include "drv/sx1276/sx1276-board.h"
#include "common/conf.h"               // system configuration
#include "stm32f3xx.h"                 // peripheral drivers


//#include "board.h"

/*!
 * Flag used to set the RF switch control pins in low power mode when the radio is not active.
 */
static bool RadioIsActive = false;

/*!
 * Radio driver structure initialization
 */
const struct Radio_s Radio =
{
  SX1276Init,
  SX1276GetStatus,
  SX1276SetModem,
  SX1276SetChannel,
  SX1276IsChannelFree,
  SX1276Random,
  SX1276SetRxConfig,
  SX1276SetTxConfig,
  SX1276CheckRfFrequency,
  SX1276GetTimeOnAir,
  SX1276Send,
  SX1276SetSleep,
  SX1276SetStby,
  SX1276SetRx,
  SX1276StartCad,
  SX1276ReadRssi,
  SX1276Write,
  SX1276Read,
  SX1276WriteBuffer,
  SX1276ReadBuffer,
  SX1276SetMaxPayloadLength
};

/*!
 * Antenna switch GPIO pins objects
 */
#if 0
Gpio_t AntSwitchLf;
Gpio_t AntSwitchHf;
#endif // 0 TODO wait for porting

void SX1276IoInit (void)
{
  HAL_GPIO_WritePin(CONF_GPIO_SX1276_SPI, CONF_PIN_SX1276_NSS, GPIO_PIN_SET);

  HAL_GPIO_WritePin(CONF_GPIO_SX1276_DIO0, CONF_PIN_SX1276_DIO0, GPIO_PIN_RESET);
#if 0  // unused pins
  HAL_GPIO_WritePin(CONF_GPIO_SX1276_DIO1, CONF_PIN_SX1276_DIO1, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(CONF_GPIO_SX1276_DIO2, CONF_PIN_SX1276_DIO2, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(CONF_GPIO_SX1276_DIO3, CONF_PIN_SX1276_DIO3, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(CONF_GPIO_SX1276_DIO4, CONF_PIN_SX1276_DIO4, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(CONF_GPIO_SX1276_DIO5, CONF_PIN_SX1276_DIO5, GPIO_PIN_RESET);
#endif   // 0 unused pins

  return;
}

void SX1276IoIrqInit (DioIrqHandler **irqHandlers)
{
  extern void (*sx1276_dio0_isr) (void);

  sx1276_dio0_isr = irqHandlers[0];

#if 0
  GpioSetInterrupt( &SX1276.DIO1, IRQ_RISING_EDGE, IRQ_HIGH_PRIORITY, irqHandlers[1]);
  GpioSetInterrupt( &SX1276.DIO2, IRQ_RISING_EDGE, IRQ_HIGH_PRIORITY, irqHandlers[2]);
  GpioSetInterrupt( &SX1276.DIO3, IRQ_RISING_EDGE, IRQ_HIGH_PRIORITY, irqHandlers[3]);
  GpioSetInterrupt( &SX1276.DIO4, IRQ_RISING_EDGE, IRQ_HIGH_PRIORITY, irqHandlers[4]);
  GpioSetInterrupt( &SX1276.DIO5, IRQ_RISING_EDGE, IRQ_HIGH_PRIORITY, irqHandlers[5]);
#endif // 0 TODO wait for porting

  return;
}

void SX1276IoDeInit (void)
{
#if 0
    GpioInit( &SX1276.Spi.Nss, RADIO_NSS, PIN_OUTPUT, PIN_PUSH_PULL, PIN_NO_PULL, 1 );

    GpioInit( &SX1276.DIO0, RADIO_DIO_0, PIN_INPUT, PIN_PUSH_PULL, PIN_NO_PULL, 0 );
    GpioInit( &SX1276.DIO1, RADIO_DIO_1, PIN_INPUT, PIN_PUSH_PULL, PIN_NO_PULL, 0 );
    GpioInit( &SX1276.DIO2, RADIO_DIO_2, PIN_INPUT, PIN_PUSH_PULL, PIN_NO_PULL, 0 );
    GpioInit( &SX1276.DIO3, RADIO_DIO_3, PIN_INPUT, PIN_PUSH_PULL, PIN_NO_PULL, 0 );
    GpioInit( &SX1276.DIO4, RADIO_DIO_4, PIN_INPUT, PIN_PUSH_PULL, PIN_NO_PULL, 0 );
    GpioInit( &SX1276.DIO5, RADIO_DIO_5, PIN_INPUT, PIN_PUSH_PULL, PIN_NO_PULL, 0 );
#endif // 0 TODO wait for porting

  return;
}

uint8_t SX1276GetPaSelect( uint32_t channel )
{
    if( channel < RF_MID_BAND_THRESH )
    {
        return RF_PACONFIG_PASELECT_PABOOST;
    }
    else
    {
        return RF_PACONFIG_PASELECT_RFO;
    }
}

void SX1276SetAntSwLowPower( bool status )
{
  if( RadioIsActive != status )
    {
      RadioIsActive = status;
    
      if( status == false )
        {
          SX1276AntSwInit( );
        }
      else
        {
          SX1276AntSwDeInit( );
        }
    }
}

void SX1276AntSwInit( void )
{
#if  0
  GpioInit( &AntSwitchLf, RADIO_ANT_SWITCH_LF, PIN_OUTPUT, PIN_PUSH_PULL, PIN_PULL_UP, 1 );
  GpioInit( &AntSwitchHf, RADIO_ANT_SWITCH_HF, PIN_OUTPUT, PIN_PUSH_PULL, PIN_PULL_UP, 0 );
#endif // 0 TODO wait for porting
}

void SX1276AntSwDeInit( void )
{
#if 0
  GpioInit( &AntSwitchLf, RADIO_ANT_SWITCH_LF, PIN_OUTPUT, PIN_OPEN_DRAIN, PIN_NO_PULL, 0 );
  GpioInit( &AntSwitchHf, RADIO_ANT_SWITCH_HF, PIN_OUTPUT, PIN_OPEN_DRAIN, PIN_NO_PULL, 0 );
#endif // 0 TODO wait for porting
}

void SX1276SetAntSw( uint8_t rxTx )
{
  if( rxTx != 0 ) // 1: TX, 0: RX
    {
#if 0
      GpioWrite( &AntSwitchLf, 0 );
      GpioWrite( &AntSwitchHf, 1 );
#endif // 0 TODO wait for porting
    }
  else
    {
#if 0
      GpioWrite( &AntSwitchLf, 1 );
      GpioWrite( &AntSwitchHf, 0 );
#endif // 0 TODO wait for porting
    }
}

bool SX1276CheckRfFrequency( uint32_t frequency )
{
  // Implement check. Currently all frequencies are supported
  return true;
}
