# The Entry Monitor System :seedling:
- A system to keep track time when a user enters or leaves a premises
- it also controls who is allowed to enter a premise using RFID tags 
<br/>

## Testing & Setup :hammer:
- all the tests done are based on the `Olimex ESP32-PoE-ISO`
<br/>
<img src="https://user-images.githubusercontent.com/20322653/171873462-9ebf9662-89d1-4f0c-ac91-65f4855fcba6.jpeg">

- The programming IDE used is the Arduino IDE grab it [here](https://www.arduino.cc/en/software) if you don't have it already installed, based on your distribution
## IDE setup 
- Once you download and install you need to do one more thing in order to add the ESP32 based boards on the the ide, flow this procedure
  1) In your Arduino IDE, go to File> Preferences
<img width="450" alt="Screenshot 2022-06-03 at 16 11 39" src="https://user-images.githubusercontent.com/20322653/171860733-7a97f782-c27a-4008-83fa-04431a19e978.png">
  2) Enter the following into the “Additional Board Manager URLs” field: `(https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json)` <br/>
  3)  Then, click the “OK” button:
 <img width="450" alt="Screenshot 2022-06-03 at 16 12 28" src="https://user-images.githubusercontent.com/20322653/171860900-2f202f3c-3e56-4b77-9f5a-3482a66ff2a7.png">
  4) Open the Boards Manager. Go to Tools > Board > Boards Manager…
 <img width="450" alt="Screenshot 2022-06-03 at 16 12 51" src="https://user-images.githubusercontent.com/20322653/171860969-b9a0f80c-d90f-4215-ac17-731405129016.png">
  5) Search for ESP32 and press install button for the “ESP32 by Espressif Systems“:
<img width="450" alt="Screenshot 2022-06-03 at 16 13 23" src="https://user-images.githubusercontent.com/20322653/171861059-189619d5-bc2b-47e8-bba1-f6454703be35.png">
  6) That’s it. It should be installed after a few seconds.

## Download the Files :arrow_down_small:
- Download all the files on the `Code`:arrow_down_small: on this platform, In your downloads you will get the a folder :file_folder:  `entry_monitor_system-main`
- In the same folder you will also get a :file_folder: `libraries` folder, please unzip that and paste on those files in your directory documents/Arduino/libraries 
- Now you are set with all the libraries used in the development of this code

## INITIAL SYSTEM SETUP :clock4:
- For a freshly obtained/programmed device with the code, compile it on the ide and upload to your board. 
- on your Arduino Ide make sure to select `OLIMEX ESP32-PoE-ISO` on the boards section under tools, also make sure to select the appropriate port <br/>
<img width="500" alt="Screenshot 2022-06-03 at 16 24 51" src="https://user-images.githubusercontent.com/20322653/171863122-cc39af18-65c3-4f40-b437-06601c73c244.png">

## Hardware Configuration and Connnections :hammer:
Main elements under consideration here were
- RFID Tag Reader
- Relay 
- LEDs & Buzzer

### RFID Tag Reader
- The mapping between the board and the tag reader can be done as follows 
<img src="https://user-images.githubusercontent.com/20322653/171983565-ad7ea00d-4110-49d4-8cf6-43d4556da8be.png" height="400"><img width="300" alt="Screenshot 2022-06-04 at 07 38 24" src="https://user-images.githubusercontent.com/20322653/171983615-d905d1a6-ffad-46f6-a0bb-3a1afcf0d003.png">
### Relay
- The recommended relay module for testing is this type or similar [link](https://www.aliexpress.com/item/1005004032808437.html?spm=a2g0o.productlist.0.0.101c4c05DWJqN3&algo_pvid=08315f6b-de1b-474c-88d6-3aecf38e36be&algo_exp_id=08315f6b-de1b-474c-88d6-3aecf38e36be-6&pdp_ext_f=%7B%22sku_id%22%3A%2212000027806582449%22%7D&pdp_npi=2%40dis%21USD%21%210.61%21%21%21%21%21%400b0a556516543183697484339e86bf%2112000027806582449%21sea)
<img width="400" alt="Screenshot 2022-06-04 at 07 53 25" src="https://user-images.githubusercontent.com/20322653/171983784-dd19e226-ecd3-43e3-b963-0f3ff2617fb9.png">


- Connect the `IN` pin to `16` of the ESP board
- Connect the `VDD` to `5v` on the ESP board 
- Connect the `GND` to and `GND` on the ESP board 

### LEDs & Buzzer
- Connect the leds & the buzzer as follows: 
  - `LED enter` => `Pin 3` on the ESP BOARD 
  - `LED leave` => `Pin 4` on the ESP BOARD 
  - `LED unrecognized` => `Pin 16` on the ESP BOARD 
  - `LED in-operation` => `Pin 1` on the ESP BOARD 
  - `LED setup done` => `Pin 32` on the ESP BOARD 
  - `Buzzer` => `Pin 33` on the ESP BOARD 

## The system had several sections
  1) Setup & Registrations :white_check_mark:
  2) Ethernet setup & Internet access:white_check_mark:
  3) RFID Authorizations:white_check_mark:
  4) Time and Date fetching :white_check_mark:

## Setup & Registration :one:
- Once the powered the system will first launch as an access point as there is no save data on the flash => it actually checks if such data was previously save, if not it will launch an access point with the name `ENTRY MONITOR SYSTEM` <br/>
<img width="393" alt="Screenshot 2022-06-03 at 16 33 35" src="https://user-images.githubusercontent.com/20322653/171864517-a64cd6c6-bb22-4a67-b192-6567910cdc05.png">

- Connect to this network, use the password :unlock: `123456789`
- Then on your favorite browser type the following domain/url `192.168.88.17` and hit enter 
- You should be served with this page <br/>
 <img width="500" alt="Screenshot 2022-06-03 at 16 36 42" src="https://user-images.githubusercontent.com/20322653/171865061-8a596be5-da4c-4873-9506-20a73615cea5.png">
- Fill in your the details as it (for testing, user, test, .....)
- Then hit submit.
- The device restarts and checks if there is any information saved, next it will not launch as an access point rather try to hit the internet 

## Ethernet setup & Internet access :two:
- The systems checks if the information you wrote exists on the flash and trys to connect to the internet so that it can assign you a session/device UID that is hence used to identify the device <br/>
<img width="500" alt="Screenshot 2022-05-26 at 05 03 47" src="https://user-images.githubusercontent.com/20322653/171866288-abeb3754-6908-4472-8d50-a1e4ffc6f766.png">


- In the next request it fetches the `ID` and saves it 
 <img width="500" alt="Screenshot 2022-05-30 at 16 08 17" src="https://user-images.githubusercontent.com/20322653/171866743-716369ae-fbf8-4036-bc75-d8eef02eb4bb.png">
 - From there the device is fully set and registered :crystal_ball: and it can make all requests needed.
 
## RFID Authorizations :three:
- RFID Tags read and confirmed to be working fine as well!

<img width="500" alt="Screenshot 2022-06-03 at 16 50 01" src="https://user-images.githubusercontent.com/20322653/171867339-f682cebc-4446-4772-8949-9e91c5a60285.png">

## Time from npt tested as works fine! :) :four:
<img width="500" alt="Screenshot 2022-04-23 at 22 19 44" src="https://user-images.githubusercontent.com/20322653/164943339-f7193448-2e5c-46d1-b948-bade2411159c.png">
<br/>

