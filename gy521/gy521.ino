#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

Adafruit_MPU6050 mpu;

void setup()
{
    Serial.begin(115200);

    if (!mpu.begin())
    {
        Serial.println("Sensor init failed");
        while (1)
            yield();
    }

    delay(500);
}

void loop()
{
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);

    Serial.print("Accelerometer ");
    Serial.print("X: ");
    Serial.print(a.acceleration.x, 6);
    Serial.print(" m/s^2, ");
    Serial.print("Y: ");
    Serial.print(a.acceleration.y, 6);
    Serial.print(" m/s^2, ");
    Serial.print("Z: ");
    Serial.print(a.acceleration.z, 6);
    Serial.println(" m/s^2");

    Serial.print("Gyroscope ");
    Serial.print("X: ");
    Serial.print(g.gyro.x, 6);
    Serial.print(" rps, ");
    Serial.print("Y: ");
    Serial.print(g.gyro.y, 6);
    Serial.print(" rps, ");
    Serial.print("Z: ");
    Serial.print(g.gyro.z, 6);
    Serial.println(" rps");

    delay(10);
}
