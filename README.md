# enmeraz-Wifi_Lamp

# Introduction
## Description of Project: 
For my final project I wanted to create a LED lamp that could connect to a Wifi network. I will attempt to use a ESP32 to create a wifi network for a web server using Access Points (AP). The following network can be shown below.

Once everything is set up, the user must log into the wifi network that you created. Next the user can go into their favorite web browser and enter 192.168.4.1 (or whatever the device gives out as a IP address) in the web address to begin.  

# Setting up your ESP32 or ESP8266
First we have to add our board entries:
1. Open the Arduino IDE. Make sure that you are at version 1.8 or higher, if not then update your IDE with the latest version.
2. Click on the File menu on the top menu bar.
3. Click on the Preferences menu item. This will open a Preferences dialog box.
4. You should be on the Settings tab in the Preferences dialog box by default.
5. Look for the textbox labeled “Additional Boards Manager URLs”.
6. If there is already text in this box add a coma at the end of it, then follow the next step.
7. Paste the following link into the text box – https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
8. Click the OK button to save the setting.

For ESP32:
1. In your arduino IDE you need tto click on the Tools menu on the top menu bar
2. Scroll down to the Board: entry (i.e. Board: Arduino/Genuino Uno).
3. A submenu will open when you highlight the Board: entry.
4. At the top of the submenu is Boards Manager. Click on it to open the Boards Manager dialog box.
5. In the search box in the Boards Manager enter “esp32”.
6. You should see an entry for “esp32 by Espressif Systems”. Highlight this entry and click on the Install button.
7. This will install the ESP32 boards into your Arduino IDE

For ESP8266:
1. In your arduino IDE you need tto click on the Tools menu on the top menu bar
2. Scroll down to the Board: entry (i.e. Board: Arduino/Genuino Uno).
3. A submenu will open when you highlight the Board: entry.
4. At the top of the submenu is Boards Manager. Click on it to open the Boards Manager dialog box.
5. In the search box in the Boards Manager enter “ESP8266”.
6. You should see an entry for “ESP8266 by ESP8266 Community”. Highlight this entry and click on the Install button.
7. This will install the ESP8266 boards into your Arduino IDE

# Setting up the BreadBoard
<p align="center">
    <img src="/projects/enmeraz-Wifi_Lamp/wireSetup.png" alt="tictactoeENDGAME" width=400 hieght=400> 
</p>
- Resistor is 230 ohmns


## How it works