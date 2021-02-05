/*
 ******************************************************************************
 * @file    main.c
 * @module  cross module
 * @author  Mohamed Hnezli
 * @version V0.2
 * @date    12-04-2019
 * @brief   main program.
 ******************************************************************************
 * @attention
 *
 * - The present software had been tested only on STM32F3CCTx and may be non
 * functional on other targets.
 *
 * <h2><center>&copy COPYRIGHT 2019 Mohamed Hnezli </center></h2>
 ******************************************************************************
 */

/* include ------------------------------------------------------------------ */
#include <drv/clk.h>                   // clk_sys_conf
#include "stm32f3xx.h"                 // MCU HAL TODO remove test
#include "common/error.h"              // error codes
#include "common/conf.h"               // system configuration
#include "drv/led.h"                   // LED 13
//#include "drv/sx1276/sx1276.h"         // transceiver driver
#include "drv/sx1276/radio.h"          // transceiver driver
#include <string.h>                    // strncmp


/* define ------------------------------------------------------------------- */
#define USE_BAND_868
#define USE_MODEM_LORA
#define TX_OUTPUT_POWER                             14        // dBm
#define RX_TIMEOUT_VALUE                            1000
#define BUFFER_SIZE                                 64 // Define the payload size here

#if defined (USE_BAND_433)
#define RF_FREQUENCY                                434000000 // Hz
#elif defined (USE_BAND_780)
#define RF_FREQUENCY                                780000000 // Hz
#elif defined (USE_BAND_868)
#define RF_FREQUENCY                                868000000 // Hz
#elif defined (USE_BAND_915)
#define RF_FREQUENCY                                915000000 // Hz
#else
    #error "Please define a frequency band in the compiler options."
#endif

#if defined (USE_MODEM_LORA)
#define LORA_BANDWIDTH                              0         // [0: 125 kHz,
                                                              //  1: 250 kHz,
                                                              //  2: 500 kHz,
                                                              //  3: Reserved]
#define LORA_SPREADING_FACTOR                       7         // [SF7..SF12]
#define LORA_CODINGRATE                             1         // [1: 4/5,
                                                              //  2: 4/6,
                                                              //  3: 4/7,
                                                              //  4: 4/8]
#define LORA_PREAMBLE_LENGTH                        8         // Same for Tx and Rx
#define LORA_SYMBOL_TIMEOUT                         5         // Symbols
#define LORA_FIX_LENGTH_PAYLOAD_ON                  false
#define LORA_IQ_INVERSION_ON                        false
#elif defined( USE_MODEM_FSK )
#define FSK_FDEV                                    25e3      // Hz
#define FSK_DATARATE                                50e3      // bps
#define FSK_BANDWIDTH                               50e3      // Hz
#define FSK_AFC_BANDWIDTH                           83.333e3  // Hz
#define FSK_PREAMBLE_LENGTH                         5         // Same for Tx and Rx
#define FSK_FIX_LENGTH_PAYLOAD_ON                   false
#else
    #error "Please define a modem in the compiler options."
#endif


/* typedef ------------------------------------------------------------------ */
typedef enum
{
  LOWPOWER,
  RX,
  RX_TIMEOUT,
  RX_ERROR,
  TX,
  TX_TIMEOUT,
}States_t;


/* variable ----------------------------------------------------------------- */
const uint8_t PingMsg[] = "PING";
const uint8_t PongMsg[] = "PONG";

uint16_t BufferSize = BUFFER_SIZE;
uint8_t Buffer[BUFFER_SIZE];

States_t State = LOWPOWER;

int8_t RssiValue = 0;
int8_t SnrValue = 0;


/* class -------------------------------------------------------------------- */
/*
 * @name:   test
 * @brief:  used to test feature and programing tools.
 * @param:  none.
 * @retval: none.
 * @note:
 */
class test
{
public:
  test (void);
  ~test ();

  int
  get_ok (void)
    {
      return ok;
	}

private:
  int ok;
};


/* method ------------------------------------------------------------------- */
/* function ----------------------------------------------------------------- */
/*!
 * Radio events function pointer
 */
static RadioEvents_t RadioEvents;

/*!
 * \brief Function to be executed on Radio Tx Done event
 */
void OnTxDone (void)
{
  Radio.Sleep ();
  State = TX;
}

/*!
 * \brief Function to be executed on Radio Rx Done event
 */
void OnRxDone (uint8_t *payload, uint16_t size, int16_t rssi, int8_t snr)
{
  Radio.Sleep( );
  BufferSize = size;
  memcpy( Buffer, payload, BufferSize );
  RssiValue = rssi;
  SnrValue = snr;
  State = RX;
}


/*!
 * \brief Function executed on Radio Tx Timeout event
 */
void OnTxTimeout( void )
{
  Radio.Sleep( );
  State = TX_TIMEOUT;
}

/*!
 * \brief Function executed on Radio Rx Timeout event
 */
void OnRxTimeout( void )
{
  Radio.Sleep( );
  State = RX_TIMEOUT;
}

/*!
 * \brief Function executed on Radio Rx Error event
 */
void OnRxError( void )
{
  Radio.Sleep( );
  State = RX_ERROR;
}

/*
 * @name:   main.
 * @brief:  program start point.
 * @param:  none.
 * @retval: none.
 */
int
main (void)
{
  bool isMaster = true;
  int32_t idx = 0;

  /* configure system clock */
  clk_sysconf ();

  /* configure modules */
  clk_conf_led ();
  led blue_led (CONF_GPIO_LED, (uint32_t)CONF_PIN_LED);

  RadioEvents.TxDone = OnTxDone;
  RadioEvents.RxDone = OnRxDone;
  RadioEvents.TxTimeout = OnTxTimeout;
  RadioEvents.RxTimeout = OnRxTimeout;
  RadioEvents.RxError = OnRxError;

  Radio.Init( &RadioEvents );

  Radio.SetChannel( RF_FREQUENCY );

#if defined( USE_MODEM_LORA )
  Radio.SetTxConfig( MODEM_LORA, TX_OUTPUT_POWER, 0, LORA_BANDWIDTH,
                                 LORA_SPREADING_FACTOR, LORA_CODINGRATE,
                                 LORA_PREAMBLE_LENGTH, LORA_FIX_LENGTH_PAYLOAD_ON,
                                 true, 0, 0, LORA_IQ_INVERSION_ON, 3000 );

  Radio.SetRxConfig( MODEM_LORA, LORA_BANDWIDTH, LORA_SPREADING_FACTOR,
                                 LORA_CODINGRATE, 0, LORA_PREAMBLE_LENGTH,
                                 LORA_SYMBOL_TIMEOUT, LORA_FIX_LENGTH_PAYLOAD_ON,
                                 0, true, 0, 0, LORA_IQ_INVERSION_ON, true );
#elif defined( USE_MODEM_FSK )
  Radio.SetTxConfig( MODEM_FSK, TX_OUTPUT_POWER, FSK_FDEV, 0,
                                FSK_DATARATE, 0,
                                FSK_PREAMBLE_LENGTH, FSK_FIX_LENGTH_PAYLOAD_ON,
                                true, 0, 0, 0, 3000 );

  Radio.SetRxConfig( MODEM_FSK, FSK_BANDWIDTH, FSK_DATARATE,
                                0, FSK_AFC_BANDWIDTH, FSK_PREAMBLE_LENGTH,
                                0, FSK_FIX_LENGTH_PAYLOAD_ON, 0, true,
                                0, 0,false, true );
#else
  #error "Please define a frequency band in the compiler options."
#endif

  while (1)
    {
#if 1
      idx += 1;
      Radio.Send (Buffer, sprintf ((char*)Buffer, "ping %d", idx));
      blue_led.toggle ();
      clk_delay (200);
      blue_led.toggle ();
      clk_delay (200);
      blue_led.toggle ();
      clk_delay (200);
      blue_led.toggle ();
      clk_delay (1400);
#else
      Radio.Rx (3000);
#endif
    }
  Radio.Rx( RX_TIMEOUT_VALUE );

  while (1)
    {
      clk_delay (100);
      blue_led.toggle ();

      switch( State )
      {
      case RX:
        if (isMaster == true)
          {
            if (BufferSize > 0)
              {
                if (strncmp ((const char*)Buffer, (const char*)PongMsg, 4) == 0)
                  {
                    // Indicates on a LED that the received frame is a PONG
                    blue_led.on ();
                    clk_delay (50);
                    blue_led.off ();
                    clk_delay (50);
                    blue_led.off ();
                    clk_delay (50);
                    blue_led.off ();
                    clk_delay (50);

                    // Send the next PING frame
                    Buffer[0] = 'P';
                    Buffer[1] = 'I';
                    Buffer[2] = 'N';
                    Buffer[3] = 'G';
                    // We fill the buffer with numbers for the payload
                    for (idx = 4; idx < BufferSize; idx++)
                      {
                        Buffer[idx] = idx - 4;
                      }
                    clk_delay (1);
                    Radio.Send (Buffer, BufferSize);
                  }
                else if (strncmp((const char*)Buffer, (const char*)PingMsg, 4) == 0)
                  {
                    // A master already exists then become a slave
                    isMaster = false;
                    blue_led.off ();
                    Radio.Rx (RX_TIMEOUT_VALUE);
                  }
                else // valid reception but neither a PING or a PONG message
                  {
                    // Set device as master and start again
                    isMaster = true;
                    Radio.Rx (RX_TIMEOUT_VALUE);
                  }
              }
          }
        else
          {
            if (BufferSize > 0)
              {
                if (strncmp((const char*)Buffer, (const char* )PingMsg, 4) == 0)
                  {
                    // Indicates on a LED that the received frame is a PING
                    blue_led.on ();
                    clk_delay (50);
                    blue_led.off ();
                    clk_delay (50);

                    // Send the reply to the PONG string
                    Buffer[0] = 'P';
                    Buffer[1] = 'O';
                    Buffer[2] = 'N';
                    Buffer[3] = 'G';
                    // We fill the buffer with numbers for the payload
                    for (idx = 4; idx < BufferSize; idx++)
                      {
                        Buffer[idx] = idx - 4;
                      }
                    clk_delay( 1 );
                    Radio.Send( Buffer, BufferSize );
                  }
                else // valid reception but not a PING as expected
                  {
                    // Set device as master and start again
                    isMaster = true;
                    Radio.Rx( RX_TIMEOUT_VALUE );
                  }
              }
          }
        State = LOWPOWER;
        break;
      case TX:
        // Indicates on a LED that we have sent a PING [Master]
        // Indicates on a LED that we have sent a PONG [Slave]
        blue_led.on ();
        clk_delay (50);
        blue_led.off ();
        clk_delay (50);

        Radio.Rx (RX_TIMEOUT_VALUE);
        State = LOWPOWER;
        break;
      case RX_TIMEOUT:
      case RX_ERROR:
        if (isMaster == true)
          {
            // Send the next PING frame
            Buffer[0] = 'P';
            Buffer[1] = 'I';
            Buffer[2] = 'N';
            Buffer[3] = 'G';
            for (idx = 4; idx < BufferSize; idx++)
              {
                Buffer[idx] = idx - 4;
              }
            clk_delay (1);
            Radio.Send( Buffer, BufferSize );
          }
        else
          {
            Radio.Rx( RX_TIMEOUT_VALUE );
          }
        State = LOWPOWER;
        break;
      case TX_TIMEOUT:
        Radio.Rx( RX_TIMEOUT_VALUE );
        State = LOWPOWER;
        break;
      case LOWPOWER:
      default:
        // Set low power
        break;
      }

#if 0
      TimerLowPowerHandler( );
#endif // o TODO wait for porting
    }

  return EUNKNOWN;  // should never get here
}