# arduino-boards

### Requirements

- Arduino IDE 2.3.0 or newer
- Arduino CLI 1.0.4 or newer
- RP2040 core by Earle Philhower

## Install
1. Install RP2040 by Earle Philhower from [https://github.com/earlephilhower/arduino-pico](https://github.com/earlephilhower/arduino-pico?tab=readme-ov-file#installation)
   
3. Open up the Arduino IDE and go to File->Preferences.

4. In the dialog that pops up, enter the following URL in the "Additional Boards Manager URLs" field:

https://github.com/MARS-engineers/arduino-boards/releases/download/global/package_MARS-engineers_boards_index.json
<img width="804" height="533" alt="image" src="https://github.com/user-attachments/assets/421b0eb6-c079-4c88-bd3a-cdc40132c1e2" />

4. Hit OK to close the dialog.

5. Go to Tools->Boards->Board Manager in the IDE

6. Type "mars" in the search box and select "Install":

<img width="264" height="160" alt="image" src="https://github.com/user-attachments/assets/1f8b9d9d-d21a-4c54-819a-fcf7b88d5d6c" />
<img width="213" height="224" alt="image" src="https://github.com/user-attachments/assets/16580d84-5819-4feb-9dd6-0bba550894c9" />



## Attribution

This project includes modified configuration files derived from the
arduino-pico RP2040/RP2350 core by Earle F. Philhower, III.

Original project:
https://github.com/earlephilhower/arduino-pico

All original code remains under the LGPL-2.1-or-later license.
