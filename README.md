# The Entry Monitor System :seedling:
- A system to keep track time when a user enters or leaves a premises
- it also controls who is allowed to enter a premise using RFID tags 
<br/>

## Testing & Setup
- all the tests done are based on the `Olimex ESP32-PoE-ISO`
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
- In the same folder you will also get a libraries folder, please unzip that and paste on those files in your directory documents/Arduino/libraries 
- Now you are set with all the libraries used in the development of this code


## INITIAL SYSTEM SETUP
For a freshly obtained/programmed device with the code 


## Time  & Date Test Results  
Time from npt tested as works fine! :)

<br/>

<img width="950" alt="Screenshot 2022-04-23 at 22 19 44" src="https://user-images.githubusercontent.com/20322653/164943339-f7193448-2e5c-46d1-b948-bade2411159c.png">

## RFID Tags Reading 
RFID Tags read and confirmed to be working fine as well! :) 

<br/>

<img width="950" alt="Screenshot 2022-04-23 at 22 19 00" src="https://user-images.githubusercontent.com/20322653/164943413-b7b41c24-f95c-4d92-8668-9ac0a0bc4f4f.png">
