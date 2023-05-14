#include <math.h>
#include <Wire.h>
#include <SeeedOLED.h>

#define CURRENT_SENSOR A0
#define VOLTAGE_SENSOR A1
#define WATER_SENSOR A2
#define SAMPLE_TIME_MS 1000

float getRMSValue(int sensor_pin);
float getWaterConsumption(int sensor_pin);

void setup()
{
    Serial.begin(9600);
    pinMode(CURRENT_SENSOR, INPUT);
    pinMode(VOLTAGE_SENSOR, INPUT);
    pinMode(WATER_SENSOR, INPUT);

    Wire.begin();
    SeeedOLED.init();

    SeeedOLED.clearDisplay();
    SeeedOLED.setNormalDisplay();
    SeeedOLED.setPageMode();
}

void loop()
{
    float current_rms = getRMSValue(CURRENT_SENSOR);
    float voltage_rms = getRMSValue(VOLTAGE_SENSOR);
    float power = current_rms * voltage_rms;
    float energy = power * (SAMPLE_TIME_MS / 1000.0) / 3600.0; // convert to Wh

    float water_consumption = getWaterConsumption(WATER_SENSOR);
    float water_gallons = water_consumption / 7.481; // convert to gallons

    SeeedOLED.setTextXY(0, 0);
    SeeedOLED.putString("Electricity (Wh): ");
    SeeedOLED.putFloat(energy, 2);
    SeeedOLED.setTextXY(2, 0);
    SeeedOLED.putString("Water (gal): ");
    SeeedOLED.putFloat(water_gallons, 2);

    delay(SAMPLE_TIME_MS);
}

float getRMSValue(int sensor_pin)
{
    int sensor_value;
    long sum = 0;
    uint32_t start_time = millis();
    while((millis() - start_time) < SAMPLE_TIME_MS)
    {
        sensor_value = analogRead(sensor_pin);
        sum += (sensor_value * sensor_value);
        delayMicroseconds(1000);
    }
    float rms = sqrt(sum / SAMPLE_TIME_MS);
    return rms;
}

float getWaterConsumption(int sensor_pin)
{
    int sensor_value;
    float flow_rate;
    float consumption = 0.0;
    uint32_t start_time = millis();
    while((millis() - start_time) < SAMPLE_TIME_MS)
    {
        sensor_value = analogRead(sensor_pin);
        flow_rate = sensor_value / 5.0; // 5 L/min per pulse
        consumption += flow_rate * (SAMPLE_TIME_MS / 1000.0) / 60.0; // convert to liters
        delay(1000);
    }
    return consumption;
}
