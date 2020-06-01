/* library MPU6050 */
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BusIO_Register.h>
#include <Adafruit_I2CDevice.h>

/* library blynk */
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

/* config MPU6050 */
Adafruit_MPU6050 mpu;

/* config blink */

char auth[] = "";
#define gyroValueX V0
#define gyroValueY V1
#define gyroValueZ V2
#define accellValueX V3
#define accellValueY V4
#define accellValueZ V5
#define virtualLCD V6
WidgetLCD lcd(virtualLCD);

/* config wifi */
char ssid[] = "";
char pass[] = "";

void setup(void)
{
    Serial.begin(115200);

    Blynk.begin(auth, ssid, pass); // Give us access!

    while (Blynk.connect() == false)
    { // Be patient.
        // Wait for Blynk to come online
    }
    // Notify immediately on startup
    Blynk.notify("Device Started");

    while (!Serial)
        delay(10); // will pause Zero, Leonardo, etc until serial console opens

    Serial.println("Adafruit MPU6050 test!");

    // Try to initialize!
    if (!mpu.begin())
    {
        Serial.println("Failed to find MPU6050 chip");
        while (1)
        {
            delay(10);
        }
    }
    Blynk.notify("MPU6050 Found!");
    Serial.println("MPU6050 Found!");

    // change param (enum values) functions if necessary
    setConfigAccelScale(MPU6050_RANGE_2_G, true);
    setConfigGyroScale(MPU6050_RANGE_250_DEG, true);
    setConfigFilterBandwidth(MPU6050_BAND_260_HZ, true);

    // Print a splash screen:
    lcd.clear();
    lcd.print(0, 0, "   GY521 MPU   ");
    lcd.print(0, 1, " MONITOR THING ");
    delay(100);
}

void loop()
{
    Blynk.run();

    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);
 
    Serial.print("Accelerometer ");
    Serial.print("X: ");
    Serial.print(a.acceleration.x, 2);
    Serial.print(" m/s^2, ");
    Serial.print("Y: ");
    Serial.print(a.acceleration.y, 2);
    Serial.print(" m/s^2, ");
    Serial.print("Z: ");
    Serial.print(a.acceleration.z, 2);
    Serial.println(" m/s^2");

    Serial.print("Gyroscope ");
    Serial.print("X: ");
    Serial.print(g.gyro.x, 2);
    Serial.print(" rps, ");
    Serial.print("Y: ");
    Serial.print(g.gyro.y, 2);
    Serial.print(" rps, ");
    Serial.print("Z: ");
    Serial.print(g.gyro.z, 2);
    Serial.println(" rps");

    // Write the values to Blynk:
    Blynk.virtualWrite(gyroValueX, a.acceleration.x);
    Blynk.virtualWrite(gyroValueY, a.acceleration.y);
    Blynk.virtualWrite(gyroValueZ, a.acceleration.z);
    Blynk.virtualWrite(accellValueX, g.gyro.x);
    Blynk.virtualWrite(accellValueY, g.gyro.y);
    Blynk.virtualWrite(accellValueZ, g.gyro.z);

    delay(10);
}

void setConfigAccelScale(mpu6050_accel_range_t range_accel, bool print)
{
    mpu.setAccelerometerRange(range_accel);
    if (print)
        getConfigAccelScale();
}

void setConfigGyroScale(mpu6050_gyro_range_t range_gyro, bool print)
{
    mpu.setGyroRange(range_gyro);
    if (print)
        getConfigGyroScale();
}

void setConfigFilterBandwidth(mpu6050_bandwidth_t range_bandwidth, bool print)
{
    mpu.setFilterBandwidth(range_bandwidth);

    if (print)
        getConfigFilterBandwidth();
}

void getConfigAccelScale()
{
    Serial.print("Accelerometer range set to: ");
    switch (mpu.getAccelerometerRange())
    {
    case MPU6050_RANGE_2_G:
        Serial.println("+-2G");
        break;
    case MPU6050_RANGE_4_G:
        Serial.println("+-4G");
        break;
    case MPU6050_RANGE_8_G:
        Serial.println("+-8G");
        break;
    case MPU6050_RANGE_16_G:
        Serial.println("+-16G");
        break;
    }
}

void getConfigGyroScale()
{
    Serial.print("Gyro range set to: ");
    switch (mpu.getGyroRange())
    {
    case MPU6050_RANGE_250_DEG:
        Serial.println("+- 250 deg/s");
        break;
    case MPU6050_RANGE_500_DEG:
        Serial.println("+- 500 deg/s");
        break;
    case MPU6050_RANGE_1000_DEG:
        Serial.println("+- 1000 deg/s");
        break;
    case MPU6050_RANGE_2000_DEG:
        Serial.println("+- 2000 deg/s");
        break;
    }
}

void getConfigFilterBandwidth()
{
    Serial.print("Filter bandwidth set to: ");
    switch (mpu.getFilterBandwidth())
    {
    case MPU6050_BAND_260_HZ:
        Serial.println("260 Hz");
        break;
    case MPU6050_BAND_184_HZ:
        Serial.println("184 Hz");
        break;
    case MPU6050_BAND_94_HZ:
        Serial.println("94 Hz");
        break;
    case MPU6050_BAND_44_HZ:
        Serial.println("44 Hz");
        break;
    case MPU6050_BAND_21_HZ:
        Serial.println("21 Hz");
        break;
    case MPU6050_BAND_10_HZ:
        Serial.println("10 Hz");
        break;
    case MPU6050_BAND_5_HZ:
        Serial.println("5 Hz");
        break;
    }
}