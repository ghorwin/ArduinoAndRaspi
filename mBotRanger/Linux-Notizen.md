# Programmierung des mBot Ranger von MakeBlock mit der Arduino IDE unter Linux

## System und Vorbereitung

- Arduino-IDE installieren, entweder als AppImage oder als zip, ggfs. benötigte deb-Pakete nachinstallieren
  (in der Kommandozeile starten und bei Fehlern das entsprechende Paket nachinstallieren)
- nach dem ersten Start in Settings die Sprache in Deutsch ändern

### brttly
  
Beim Anschließend des Boards an den USB-Port wird die Verbindung mit /dev/ttyUSB0 kurz hergestellt und gleich wieder unterbrochen.
Ausgabe von 'sudo dmesg' ist ähnlich wie:

```
[  284.973894] usb 3-4.2: ch34x converter now attached to ttyUSB0
[  285.019333] usb 3-4.2: usbfs: interface 0 claimed by ch34x while 'brltty' sets config #1
[  285.019883] ch34x ttyUSB0: ch34x converter now disconnected from ttyUSB0
[  285.019895] ch34x 3-4.2:1.0: device disconnected
```

Den brltty Dienst (Assistenzdienst für Sehbehinderte/Blinde) abschalten:

```
# Systemdienste deaktivieren
sudo systemctl mask brltty.path
sudo systemctl mask brltty.service

# udev Regeln ausschalten
for f in /usr/lib/udev/rules.d/*brltty*.rules; do
    sudo ln -s /dev/null "/etc/udev/rules.d/$(basename "$f")"
done
sudo udevadm control --reload-rules
```

Nun kann man das Board verbinden und sollte folgende Ausgabe sehen:

```
[ 2378.903385] usb 3-2: new full-speed USB device number 3 using xhci_hcd
[ 2379.075714] usb 3-2: New USB device found, idVendor=1a86, idProduct=7523, bcdDevice= 2.64
[ 2379.075733] usb 3-2: New USB device strings: Mfr=0, Product=2, SerialNumber=0
[ 2379.075739] usb 3-2: Product: USB Serial
[ 2379.085854] ch341 3-2:1.0: ch341-uart converter detected
[ 2379.100209] usb 3-2: ch341-uart converter now attached to ttyUSB0
```


### Firmaware und Bibliotheken installieren

-> Download der Bibliotheken von der github-Seite: https://github.com/Makeblock-official/Makeblock-Libraries

Download des Archives: https://codeload.github.com/Makeblock-official/Makeblock-Libraries/zip/master

Dann in der Arduino-IDE: 

- Sketch->Include Library->Add .ZIB Library...
- die heruntergeladene master.zip auswählen


## Grundlegendes zur Programmierung des Roboters

### Board in Arduino-IDE auswählen

Der mBot Ranger hat ein "Auriga"-Board, welches den Prozessor 
"Arduino Mega 2560" und zahlreiche Sensoren und Controller hat.

Ausgewählt wird das Board in der Arduino-IDE:

Tools->Board->Arduino AVR Boards->Arduino Mega or Mega 2560
Tools->Port->/dev/ttyUSB0


### Originales Programm (die "Firmware")

Als Teil der Bibliotheken gibt es in der Arduino-IDE unter
Datei->Beispiele->MakeBlockDrive->Firmware_for_Auriga 
das originale Programm. Wenn man dieses aufspielt, funktioniert
auch die Bluetooth-Verbindung mit der App wieder und man kann wie gewohnt
das Gerät steuern.


### Andere Beispielprogramme

Für alle möglichen verbauten Komponenten gibt es Beispielprogramme.
Bei diesen Programmen muss man ggfs. den eingebundenen Bibliotheksheader
in 

`#include <MeAuriga.h>`

ändern. 



