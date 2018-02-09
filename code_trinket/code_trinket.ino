///// For Adafruit Pro Trinket 5V
///////////////////////////////////////////////////

#define READ_SENSORS_INTERVAL 1000
#define SEND_STATES_INTERVAL 30000

#define PUMP_PIN A0
#define WARM_LED_PIN A1
#define COLD_LED_PIN A2

#define TEMP_PIN A4
#define LIGHT_PIN A3
#define WATER_LVL1_PIN 9
#define WATER_LVL2_PIN 10

// https://github.com/schinken/SimpleTimer
#include <SimpleTimer.h>
SimpleTimer timer;

// sensors values
int light, waterLvl;
float temp;

// actuators values
int ledsIntensity = 0,
    pumpIntensity = 0;

// Serial communication
String inputString = "";
int inputStringLength = 0;

void setup() {
    // init actuators pins
    pinMode( PUMP_PIN, OUTPUT );
    setPump( LOW );

    pinMode( COLD_LED_PIN, OUTPUT );
    pinMode( WARM_LED_PIN, OUTPUT );
    setLeds( HIGH );

    // init sensors pins
    pinMode( TEMP_PIN, INPUT );
    pinMode( LIGHT_PIN, INPUT );
    pinMode( WATER_LVL1_PIN, INPUT );
    pinMode( WATER_LVL2_PIN, INPUT );

    // Init Serial communication
    Serial.begin( 9600 );
    // reserve 200 bytes for the inputString
    inputString.reserve( 200 );

    // init timed loops
    timer.setInterval( READ_SENSORS_INTERVAL, readSensors );
    timer.setInterval( SEND_STATES_INTERVAL, sendStates );
}

void loop() {
    timer.run();
}
