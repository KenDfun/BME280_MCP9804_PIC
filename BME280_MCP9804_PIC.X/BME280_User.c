#include <xc.h>
#include <stdio.h>
#include "./BME280_driver/bme280.h"
#include "./BME280_User.h"



void print_sensor_data(struct bme280_data *comp_data);
int8_t set_sensor_data_mode(void);

void debug_error(void);
void user_delay_ms(uint32_t period);

static struct bme280_dev BME280Dev;

void Bme280_UserInit(void)
{
    int8_t rslt = BME280_OK;

    BME280Dev.dev_id = BME280_I2C_ADDR_PRIM;
    BME280Dev.intf = BME280_I2C_INTF;
    BME280Dev.read = user_i2c_read;
    BME280Dev.write = user_i2c_write;
    BME280Dev.delay_ms = user_delay_ms;

    rslt = bme280_init(&BME280Dev);  
    
    if(rslt!=BME280_OK){
        debug_error();
    }
    
    set_sensor_data_mode();
    
}


#ifdef FORCED_MODE
int8_t set_sensor_data_mode(void)
{
    int8_t rslt;
    uint8_t settings_sel;
 
    /* Recommended mode of operation: Indoor navigation */
    BME280Dev.settings.osr_h = BME280_OVERSAMPLING_1X;
    BME280Dev.settings.osr_p = BME280_OVERSAMPLING_16X;
    BME280Dev.settings.osr_t = BME280_OVERSAMPLING_2X;
    BME280Dev.settings.filter = BME280_FILTER_COEFF_16;
 
    settings_sel = BME280_OSR_PRESS_SEL | BME280_OSR_TEMP_SEL | BME280_OSR_HUM_SEL | BME280_FILTER_SEL;
 
    rslt = bme280_set_sensor_settings(settings_sel, &BME280Dev);
 
//    printf("Temperature, Pressure, Humidity by forced mode.\r\n");
    
    return rslt;

}

int8_t BME280_Data(void)
{
    int8_t rslt;
    struct bme280_data comp_data;
    
    rslt = bme280_set_sensor_mode(BME280_FORCED_MODE, &BME280Dev);
    /* Wait for the measurement to complete and print data @25Hz */
    user_delay_ms(40);
    rslt = bme280_get_sensor_data(BME280_ALL, &comp_data, &BME280Dev);
    print_sensor_data(&comp_data);    
    
    return rslt;
}

#else

int8_t set_sensor_data_mode(void)
{
    int8_t rslt;
    uint8_t settings_sel;

    /* Recommended mode of operation: Indoor navigation */
    BME280Dev.settings.osr_h = BME280_OVERSAMPLING_1X;
    BME280Dev.settings.osr_p = BME280_OVERSAMPLING_16X;
    BME280Dev.settings.osr_t = BME280_OVERSAMPLING_2X;
    BME280Dev.settings.filter = BME280_FILTER_COEFF_16;
    BME280Dev.settings.standby_time = BME280_STANDBY_TIME_62_5_MS;

    settings_sel = BME280_OSR_PRESS_SEL;
    settings_sel |= BME280_OSR_TEMP_SEL;
    settings_sel |= BME280_OSR_HUM_SEL;
    settings_sel |= BME280_STANDBY_SEL;
    settings_sel |= BME280_FILTER_SEL;
    rslt = bme280_set_sensor_settings(settings_sel, &BME280Dev);
    rslt = bme280_set_sensor_mode(BME280_NORMAL_MODE, &BME280Dev);

//    printf("Temperature, Pressure, Humidity by normal mode.\r\n");

    return rslt;
}
int8_t BME280_Data(void)
{
    int8_t rslt;
    struct bme280_data comp_data;
    
    /* Delay while the sensor completes a measurement */
    //        BME280Dev.delay_ms(70);
    rslt = bme280_get_sensor_data(BME280_ALL, &comp_data, &BME280Dev);
    print_sensor_data(&comp_data);
    
    return rslt;
}
#endif

void print_sensor_data(struct bme280_data *comp_data)
{
        printf("BME280 : %ld.%02ld[C], %ld.%02ld[hPa], %ld.%03ld[%%]\r\n",   comp_data->temperature/100,comp_data->temperature%100,
                                                        comp_data->pressure/100,comp_data->pressure%100,
                                                        comp_data->humidity/1000,comp_data->humidity%1000);
}


