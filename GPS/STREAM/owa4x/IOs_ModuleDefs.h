 #ifndef __IOS_MODULEDEFS_H
  
    #define __IOS_MODULEDEFS_H
  
    #ifdef __cplusplus
     extern "C"{
    #endif
  
    typedef struct {
       unsigned char InputNumber;
       unsigned char InputValue;
    } input_int_t;
  
    typedef struct {
       char scale;
       double x_axis;
       double y_axis;
       double z_axis;
    } move_int_t;
  
    #define MUX_MODE0       0x00
    #define MUX_MODE1       0x01
    #define MUX_MODE2       0x02
    #define MUX_MODE3       0x03
    #define MUX_MODE4       0x04
    #define MUX_MODE5       0x05
    #define MUX_MODE6       0x06
    #define MUX_MODE7       0x07
  
    #define PULL_DISABLE    (1 << 3)
    #define PULL_UP         (1 << 4)
    #define INPUT_EN        (1 << 5)
    #define SLEWCTRL_SLOW   (1 << 6)
    #define SLEWCTRL_FAST   0
  
    #define PIN_OUTPUT            (PULL_DISABLE)
    #define PIN_OUTPUT_PULLUP     (PULL_UP)
    #define PIN_OUTPUT_PULLDOWN   0
    #define PIN_INPUT             (INPUT_EN | PULL_DISABLE)
    #define PIN_INPUT_PULLUP      (INPUT_EN | PULL_UP)
    #define PIN_INPUT_PULLDOWN    (INPUT_EN)
  
    //Digital Inputs
    #define  DIGITAL_INPUT_0   0 
    #define  DIGITAL_INPUT_1   1 
    #define  DIGITAL_INPUT_2   2 
    #define  DIGITAL_INPUT_3   3 
    #define  DIGITAL_INPUT_4   4 
    #define  DIGITAL_INPUT_5   5 
    #define  DIGITAL_INPUT_6   6 
    #define  DIGITAL_INPUT_7   7 
    #define  DIGITAL_INPUT_8   8 
    #define  DIGITAL_INPUT_9   9 
    #define  OUT8_FAULT        12 
    #define  OUT9_FAULT        13 
    #define  PWR_FAIL          14 
    #define  DIGITAL_INPUT_10  22 
    #define  DIGITAL_INPUT_11  23 
    #define  DIGITAL_INPUT_12  24 
    #define  FALLING_EDGE         0
    #define  RISING_EDGE          1
    #define  BOTH_EDGE            2
  
    //Digital Outputs
    #define  DIGITAL_OUTPUT_0   0
    #define  DIGITAL_OUTPUT_1   1
    #define  DIGITAL_OUTPUT_2   2
    #define  DIGITAL_OUTPUT_3   3
    #define  DIGITAL_OUTPUT_4   4
    #define  DIGITAL_OUTPUT_5   5
    #define  DIGITAL_OUTPUT_6   6
    #define  DIGITAL_OUTPUT_7   7
    #define  DIGITAL_OUTPUT_8   8
    #define  DIGITAL_OUTPUT_9   9
  
    //CAN TX Modes
    #define FAST_TX_MODE       0
    #define DISABLE_TX_MODE    1
    #define SLOW_TX_MODE       2
  
    //KLINE Thershold
    #define LOW_THRESHOLD      0
    #define HIGH_THRESHOLD     1
  
    int IO_Initialize( void );
  
    int IO_Start( void);
  
    int IO_Finalize( void);
  
    int IO_IsActive( int *wActive);
  
    int IO_GetVersion( char *wVersion);
  
    int DIGIO_Set_LED_SW0( unsigned char wValue );
  
    int DIGIO_Get_LED_SW0( unsigned char *wValue );
  
    int DIGIO_Set_LED_SW0_Output( void );
  
    int DIGIO_Set_LED_SW0_Input( void );
  
    int DIGIO_Set_PPS_GPS( unsigned char wValue );
  
    int DIGIO_Get_PPS_GPS( unsigned char *wValue );
  
    int DIGIO_Set_PPS_GPS_Output( void );
  
    int DIGIO_Set_PPS_GPS_Input( void );
  
    int DIGIO_Set_LED_SW1( unsigned char wValue );
  
    int DIGIO_Get_LED_SW1( unsigned char *wValue );
  
    int DIGIO_Set_LED_SW2( unsigned char wValue );
  
    int DIGIO_Get_LED_SW2( unsigned char *wValue );
  
    int DIGIO_Set_DOUT( unsigned char wOutput, unsigned char wValue );
  
    int DIGIO_Set_All_DOUT( unsigned short int wOutput, unsigned short int wValue );
  
    int DIGIO_Switch_GSM_ON_OFF( unsigned char wValue );
    
    int DIGIO_Get_PWR_IND( unsigned char *wValue );
  
    int DIGIO_Enable_Wifi(unsigned char wValue);
  
    int DIGIO_Enable_Bluetooth(unsigned char wValue);
  
    int DIGIO_Enable_RS485( char wValue );
  
    int DIGIO_Enable_KLINE(unsigned char wValue);
  
    int DIGIO_Set_KLINE1_Threshold( char wValue );
  
   int DIGIO_Set_KLINE2_Threshold( char wValue );
  
    int DIGIO_Get_DIN( unsigned char wInput, unsigned char *wValue );
  
    int DIGIO_Get_All_DIN( unsigned short int *wValue );
  
    int DIGIO_ConfigureInterruptService( unsigned char wInput, unsigned char wEdge, void(*wHandler)(input_int_t), unsigned short int wNumInts);
  
    int DIGIO_GetNumberOfInterrupts( unsigned char wInput, unsigned long *pTotal);
  
    int DIGIO_RemoveInterruptService( unsigned char wInput);
  
    int DIGIO_Set_VOUT( unsigned char wValue );
  
    int DIGIO_Get_VOUT_STATUS( unsigned char *wValue );
  
    int DIGIO_Set_ADC_RANGE( unsigned char wRange, unsigned char wValue );
  
    int ANAGIO_GetAnalogIn( int anag_nbr, int *value );
  
    int DIGIO_Get_PWR_FAIL( unsigned char *wValue );
  
    int DIGIO_Select_Power_Supply_Internal_Battery( unsigned char wValue );
  
    int DIGIO_Set_Audio_Path( unsigned char wValue );
  
    int DIGIO_Enable_Can( char wValue);
  
    int DIGIO_Set_ETH_ON( unsigned char wValue );
  
    // iButton
    int IBUTTON_Reset( void);
  
    int IBUTTON_ReadByte( unsigned char *pData);
  
    int IBUTTON_ReadData(unsigned short int wAddress, unsigned short int wSize, char *pData);
  
    int IBUTTON_WriteByte( unsigned char Data);
  
    int IBUTTON_ReadID( unsigned char *pData);
  
    int IBUTTON_CfgInt( void(*wHandler)(unsigned char *));
  
    int IBUTTON_RemoveInt( void);
  
    int OW_Discover(OneWireTable_t **OneWireROMList, unsigned char *OneWireROMListSize);
  
    int OW_SetUpdate(void(*wHandler)(OneWireTable_t *, unsigned char, int), unsigned char time);
  
    int OW_ResetUpdate( void);
  
      int DIGIO_Enable_Uart5( unsigned char wValue );
  
      int DIGIO_Set_SD_Card( unsigned char wValue );
  
      int DIGIO_Get_USB_A( unsigned char *wValue );
  
    int DIGIO_Set_CAN1_TX_Mode( char wValue );
  
    int DIGIO_Set_CAN2_TX_Mode( char wValue );
  
    int DIGIO_Set_CAN3_TX_Mode( char wValue );
  
    int DIGIO_Set_CAN4_TX_Mode( char wValue );
  
    int DIGIO_Switch_GPS_ON_OFF( unsigned char wValue );
  
    
    int DIGIO_Set_SIM_SEL( unsigned char wValue );
  
    #ifdef __cplusplus
     }
    #endif
  
 #endif /* __IOS_MODULEDEFS_H */