 #ifndef _FMS_DESF_H
 #define  _FMS_DESF_H
  
 #ifdef __cplusplus
  extern "C"{
 #endif
  
 #ifdef CAN_MAX_DLEN
  #define MAX_TELLTALE_BLOCK_LEN CAN_MAX_DLEN
 #else
  #define MAX_TELLTALE_BLOCK_LEN 8
 #endif
 #define NOF_TELLTALE_BLOCKS 5    
 #define NOF_BUS_DOORS   10       
 #define VI_MAX_LEN      201         
 #define  DI_MAX_LEN     20       
    typedef struct{
       unsigned char  card_present;  
       unsigned char  time_state;    
       unsigned char  working_state; 
    }tacho_driver_t;
  
    typedef struct{ //Tachograph: TCO1 (PGN FE6C)
       time_t         last_change;
       float          engine_speed; 
       unsigned char  direction;    
       unsigned char  performance;  
       unsigned char  handling_info;
       unsigned char  event;        
       tacho_driver_t driver1;
       tacho_driver_t driver2;
       unsigned char  motion;       
       unsigned char  overspeed;    
    }tacho_info_t;
  
    typedef enum{
       FMS_OFF,
       FMS_VEHICLE_STOPPED,
       FMS_VEHICLE_IDLING,
       FMS_VEHICLE_MOVING
    }status_enum_t;
  
    typedef struct{
       unsigned char present;
       time_t        last_change;
    }fms_event_t;
  
    typedef struct{ //FMS-standard Interface: FMS (PGN FDD1)
       time_t        last_change;
       char          v_bus[3];   
       char          v_truck[3]; 
       unsigned char diagnostic; 
       unsigned char request;    
    }fms_std_inter_t;
  
    typedef struct{ //FMS status. Calculated value
       time_t         last_change;
       status_enum_t  status;
    }fms_status_t;
  
    typedef struct{ //FMS ignition. Calculated value
       time_t        last_ignition_change;
       unsigned char ignition_st;  
    }fms_ignition_t;
  
    typedef struct{ //FMS idling status. Calculated value
       time_t        last_idling_change;
       unsigned char idling_st;  
       unsigned long idling_time;
       double        idling_avg_fuel_rate;
    }fms_idling_t;
  
    typedef struct{ //FMS moving status. Calculated value
       time_t        last_moving_change;
       unsigned char moving_st;
    }fms_moving_t;
  
    typedef struct{ //FMS Engine Temperature 1: ET1 (PGN FEEE)
       time_t      last_change;
       signed int  coolant_temp; 
    }fms_eng_temp1_t;
  
    typedef struct{ //FMS Ambient Conditions: AMB (PGN FEF5)
       time_t  last_change;
       float   air_temp; 
    }fms_amb_condit_t;
  
    typedef struct{ //FMS Air Supply Pressure: AIR1 (PGN FEAE)
       time_t       last_change;
       unsigned int air_pressure1; 
       unsigned int air_pressure2; 
    }fms_brake_press_t;
  
    typedef struct{ //FMS Aftertreatment 1 Diesel Exhaust Fluid Tank 1 Information: AT1T1I (PGN FE56)
       time_t last_change;
       float  level;      
    }fms_diesel_t;
  
    typedef struct{ //FMS Electronic Engine Controller #1: EEC1 (PGN EEC1)
       time_t last_change;
       float  engine_rpm;    
       char   actual_engine; 
    }fms_eng_control1_t;
  
    typedef struct{ //FMS High Resolution Vehicle Distance: VDHR (PGN FEC1)
       time_t             last_change;
       unsigned long long distance;     
    }fms_distance_t;
  
    typedef struct{ //FMS High Resolution Fuel Consumption (Liquid): HRLFC (PGN FD09)
       time_t last_change;
       float  hr_total_fuel; 
    }fms_hr_fuel_consum_t;
  
    typedef struct{ //FMS Fuel Consumption: LFC (PGN FEE9)
       time_t last_change;
       float  total_fuel;  
    }fms_fuel_consum_t;
  
    typedef struct{ //FMS Fuel Economy:LFE (PGN FEF2)
       time_t last_change;
       float  fuel_rate;     
       float  inst_fuel_eco; 
    }fms_fuel_eco_t;
  
    typedef struct{ //FMS Engine Hours, Revolutions: HOURS (PGN FEE5)
       time_t last_change;
       float  engine_hours; 
    }fms_eng_hours_t;
  
    typedef struct{ //FMS Dash Display: DD (PGN FEFC)
       time_t last_change;
       float  fuel_level; 
       // @important We cannot add fields to existing structures, or we break backwards compatibility
       //float  fuel_level_2; /**<  Fuel level 2, Ratio of the total volume, % display for secondary tank when two fuel types are used */
    }fms_dash_display_t;
  
    typedef struct{ //FMS Service Information: SERV (PGN FEC0)
       time_t last_change;
       long   service_distance;   
    }fms_serv_inform_t;
  
    typedef struct{ //FMS Electronic Engine Controller #2: EEC2 (PGN EEC2) [Bus only]
       time_t last_change;
       char   engine_load; 
       float  accelerator; 
    }fms_eng_control2_t;
  
    typedef struct{ //FMS Cruise Control/Vehicle Speed: CCVS (PGN FEF1) [Bus only]
       time_t        last_change;
       float         engine_speed;  
       unsigned char brake;         
       unsigned char clutch;        
       unsigned char cruise_control;
       unsigned char parking_brake; 
    }fms_cruise_speed_t;
  
    typedef struct{
       unsigned char  alternator[4]; 
       time_t         last_change;
    }fms_as_t;
  
    typedef struct{
       unsigned char seconds;
       unsigned char minutes;
       unsigned char hours;
       unsigned char month;
       unsigned char day;
       unsigned int  year;
       time_t        epoch_ts;
       time_t last_change;
    }fms_timedate_t;
  
    typedef struct{ //FMS Electronic Transmission Controller 2: ETC2 (PGN F005) [Bus only]
       time_t last_change;
       char   selected_gear; 
       char   current_gear;  
    }fms_etc2_t;
  
    typedef struct{ //FMS Door Control 1: DC1 (PGN FE4E) [Bus only]
       time_t        last_change;
       unsigned char doors_enabled;  
       unsigned char doors_position;    
       unsigned char ramp;           
    }fms_dc1_t;
  
    typedef struct{ //FMS Door Control 2: DC2 (PGN FDA5) [Bus only]
       time_t        last_change;
       struct door_status {
          unsigned char status;   
          unsigned char locked;   
          unsigned char enabled;  
       } door[NOF_BUS_DOORS]; 
    }fms_dc2_t;
  
    typedef struct { // FMS DI information
       unsigned char present;
       char       driverId[DI_MAX_LEN];
       time_t        last_change;
    }fms_driver_info_t;
  
    typedef struct { // FMS tell Tale status 
       unsigned char block[NOF_TELLTALE_BLOCKS][MAX_TELLTALE_BLOCK_LEN]; 
       time_t   last_change;
    }fms_tt_status_t;
  
    typedef struct {
       unsigned char fuel_type;   
       time_t last_change;
    } fms_eng_control14_t;
  
    typedef struct {
       unsigned int cvw; 
       time_t last_change;
    } fms_vehicle_weight_t;
  
    typedef struct {
       unsigned char engaged; 
       time_t last_change;
    } fms_ptode_t;
  
    typedef struct {
       float remaining_charge; 
       time_t last_change;
    } fms_elec_pow_t;
  
    typedef struct {
       float wheel_angle; 
       time_t last_change;
    } fms_dyn_sta_ctr_t;
    
    typedef struct {
       float front_left; 
       float front_right; 
       float rear_left; 
       float rear_right; 
       time_t last_change;
    } fms_air_susp_ctr_t;
  
    typedef struct _fms_data_t{
       time_t               any_change;      
       fms_std_inter_t      std_interface;   
       fms_status_t         status_data;     
       fms_ignition_t       ignition;        
       fms_idling_t         idling;          
       fms_moving_t         moving;          
       fms_event_t          mv_no_throttle;  
       tacho_info_t         tachograph;
       fms_eng_temp1_t      engine_temp;     
       fms_amb_condit_t     ambient_temp;    
       fms_brake_press_t    air_supply_press;
       fms_diesel_t         def_level;       
       fms_eng_control1_t   engine_control1; 
       fms_distance_t       odometer;        
       fms_hr_fuel_consum_t hr_fuel_consum;  
       fms_fuel_consum_t    fuel_consum;     
       fms_fuel_eco_t       fuel_economy;    
       fms_eng_hours_t      total_hours;     
       fms_dash_display_t   dash_display;    
       fms_serv_inform_t    service_inform;  
       fms_eng_control2_t   engine_control2; 
       fms_cruise_speed_t   cruise_speed;    
       fms_etc2_t           gear_control;    
       // P1K / v1.0.6
       char           vin[VI_MAX_LEN+1];   
       char           di_raw[DI_MAX_LEN+4];        
       fms_driver_info_t driver[2];     
       fms_tt_status_t      tell_tale_status;
       fms_dc1_t         doors_control; 
       fms_dc2_t         doors;         
       // P1L / v1.1.0
       fms_eng_control14_t engine_control14; 
       fms_ptode_t       ptode;         
       fms_vehicle_weight_t comb_vehicle_weight; 
       fms_elec_pow_t    electrical_power; 
       fms_dyn_sta_ctr_t dyn_sta_control;  
       fms_air_susp_ctr_t   air_susp_control; 
       // P1M / v1.1.1
       fms_as_t       alternator_status;      
       fms_timedate_t    td;            
       // P1N / v1.1.2
    }fms_data_t;
  
    typedef enum{
       PGN_65484 = 0,
       PGN_65485
    }pgn_type_t;
  
    typedef struct _tire_data_t{
       time_t         last_change;
       pgn_type_t     pgn_number;
       unsigned char  axle_number;
       unsigned char  wheel_position;
       short int      tire_pressure; 
       float       tire_temp;     
       short int      tire_deviation;   
       unsigned char  fault_bitmap;
    }tire_data_t;
  
  
    //Fault Bitmap Values
    #define  SECOND_LEVEL_PRESSURE_FAULT      0x01
    #define  FIRST_LEVEL_LOW_PRESSURE_FAULT   0x02
    #define  FIRST_LEVEL_HIGH_PRESSURE_FAULT  0x04
    #define  HIGH_TEMPERATURE_FAULT        0x08
    #define  SENSOR_FAULT               0x10
    #define  LOW_BATTERY                0x20
  
    #define  MAX_TIRE_NUMBER      20
  
    typedef struct _tpms_data_t{
       tire_data_t    TireData[MAX_TIRE_NUMBER];
    }tpms_data_t;
  
    typedef struct{ //EBS Propriety 1: (PGN FF00)
       time_t             last_change;
       unsigned char      overload;     
       unsigned short int ebs_pressure; 
    }fms_ebsp1_t;
  
    typedef struct{ //FMS(bytes not used) Vehicle Weight: (PGN FEEA)
       time_t        last_change;
       unsigned long boogie_load; 
    }fms_vehicle_w_t;
  
    typedef struct{ //EBS Electronic Brake System #2/1: (PGN 0300)
       time_t        last_change;
       unsigned char rsp_event;   
       unsigned char abs_event;   
    }fms_ebs21_t;
  
    typedef struct{ //EBS Electronic Brake System #2/2: (PGN FEC4)
       time_t        last_change;
       unsigned char red_warning;    
       unsigned char yellow_warning; 
    }fms_ebs22_t;
  
    typedef struct _ebs_data_t{
       fms_distance_t     total_distance; 
       fms_serv_inform_t  service_inform; 
       fms_vehicle_w_t    weight;         
       fms_ebsp1_t        ebsp1_data;     
       fms_ebs21_t        ebs21_data;     
       fms_ebs22_t        ebs22_data;     
    }ebs_data_t;
  
    #define EVENT_NO           0x00
    #define EVENT_YES          0x01
    #define EVENT_ERROR           0x02
    #define EVENT_NOT_AVAILABLE      0x03
  
    #define MIN_BAUDRATE       125000
    #define MAX_BAUDRATE       500000
    #define MIN_IDLING_TIME       30
    #define MAX_IDLING_TIME       3600
  
    typedef struct fms_conf_t_{
       unsigned int      bitrate;            
       char              interface[16];      
       char              enable_log;        
       //char              enable_dump;
  
       unsigned short    time_for_idling;
       unsigned short    eng_temp_threshold;
       short             rpm_threshold;
       unsigned char     x_accelerator_pos;
       unsigned short    time_for_no_throttle;
    }fms_conf_t;
  
      int FMS_Initialize  ( fms_conf_t *pconf );
  
       int FMS_Start       ( void );
  
     int FMS_Finalize    ( void );
  
     int FMS_IsActive    ( int *wActive);
  
     int FMS_GetVersion  ( char *wVersion);
  
     int FMS_GetFMSData  ( void *wData, int wSize);
  
     int FMS_GetTPMSData ( void *wData, int wSize);
  
     int FMS_RemoveTPMSData ( unsigned char axle, unsigned char wheel);
  
     int FMS_GetEBSData  ( void *wData, int wSize);
  
   #ifdef __cplusplus
    }
   #endif
  
 #endif   // _FMS_DESF_H