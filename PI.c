/**
  Section: Included Files
 */

#include <xc.h>
#include "mcc_generated_files/mcc.h"
#include "PI.h"

/**
  Section: PI Module APIs
 */

static uint8_t sensorHeight = 0;
static uint8_t setpoint = 80; 
static int error = 0;
static float integral = 0;
static float ki = 0.000;
static float kp = 50;
static int dutycycle;

uint8_t PI_GetSensorHeight(void) {
    return sensorHeight;
}

void PI_SetSetpoint(uint8_t value) {
    setpoint = value;
}
uint8_t PI_GetSetPoint(void) {
    return setpoint;
}


int PI_GetDutycycle(void) {
    return dutycycle;
}

void PI_SetKp(float value) {
    kp = value;
}
float PI_GetKp(void) {
    return kp;
}

void PI_SetKi(float value) {
    ki = value;
}
float PI_GetKi(void) {
    return ki;
}

void PI(void) {
    sensorHeight = (uint8_t) (ADC_GetConversionResult() >> 2); //resultaat van ADC (8 bit )

    //Hier dient jullie code toegevoegd te worden
    error = setpoint - sensorHeight;
    
    integral += error;
    
    dutycycle = kp*error; // + ki*integral;
    
    if (dutycycle > 100) {
        dutycycle = 100;
    }
    if (dutycycle < 0 ) {
        dutycycle = 0;
    }
    
    dutycycle=0;

            

    PWM5_LoadDutyValue( (uint16_t) 10); // output pwm signaal voor hoogte 10 bit (van 0 tot 0x3FF)
}

/**
 End of File
 */