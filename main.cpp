/*
EW202 Lab 5.1 Calibration
D Evangelista, 2019 
*/

#include "mbed.h"
#include "rtos.h"
#include "stdio.h"

#define NMEAS 10
#define NHTS 20

Serial pc(USBTX,USBRX);
AnalogIn sensor(p20); 
DigitalOut heartbeat(LED1); 

float analog_values[NHTS]; 
float heights[NHTS] = {8.0,9.0,10.0,11.0,12.0,
    13.0,14.0,15.0,16.0,17.0,
    18.0,19.0,20.0,21.0,22.0,
    23.0,24.0,25.0,26.0,27.0};
int i,j; 

int main(void){
    pc.printf("EW202 Lab 5.1 Calibration Program\n");
    pc.printf("D Evangelista, 2019\n");
    
    for(i=0;i<NHTS;i++){
        pc.printf("Raise elevator to %f inches and press any key\n",heights[i]);
        getchar();
        
        // get measurements
        analog_values[i] = 0.0;
        for (j=0; j<NMEAS; j++){
            analog_values[i] += sensor.read();
            wait(0.1); 
            heartbeat = !heartbeat;
            } 
        analog_values[i] = analog_values[i]/(float)NMEAS; 
        pc.printf("Got %f at height %f in\n",analog_values[i],heights[i]);
        
        } // data collection loop
        
        // print results for import into Matlab
        pc.printf("Results for pasting into Matlab:\n\n");
        for (i=0;i<NHTS;i++){
            pc.printf("%f,%f\n",heights[i],analog_values[i]);
            }
        
    } // int main()
