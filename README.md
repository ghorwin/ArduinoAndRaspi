# ArduinoAndRaspi
Mein kleines Testrepo, um meine Programme zum Ausprobieren des Arduino und Raspi verfügbar zu halten



## Debugging-Notizen


Serial-Plotter parst Werte aus einzeligen Serial.print() und Serial.println() Statements, wie:

Sensor_1:20.3,Sensor2_:34.1


Wenn die Arduino-IDE geschlossen ist, kann man auch direkt auf dem Seriellen Port lauschen:

`cat /dev/ttyACM0`

mit der zuletzt eingestellten Baud-Rate. Oder

`screen /dev/ttyACM0 115200`


(Ctrl+A d für detach oder Ctrl+A K für kill)

