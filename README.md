# HEG ESP32 - Open Source. Home of HEGduino!
Hemoencephalography meets highly affordable IoT! Now with WiFi and bluetooth! Incoming schematics, apps, and how-to's. [New Delobotomizer repo here](https://github.com/moothyknight/HEG_ESP32_Delobotomizer) for drivers for the new hardware.

Join our little community at: [HEG Alpha](https://hegalpha.com)

Important HEGduino stuff you can find here:
- [HEG Training Quick Start Guide](https://github.com/moothyknight/HEG_ESP32/blob/master/Guides/HEG%20Training%20Quick%20Start%20Guide.pdf)
- [Progressive webapp (WIP) for desktop or Android. Same features as the chrome extension so it will likely replace it.](https://hegalomania.netlify.app)
- [Chrome Extension version of our biofeedback software with WiFi, BT Serial, & USB support](https://github.com/moothyknight/HEG_ESP32/tree/master/Software/ChromeExtension)
- [HEGduino Assembly](https://github.com/moothyknight/HEG_ESP32/blob/master/Guides/HEGduino%20Assembly%20Guide.pdf)
- [(For self-assembly only) Setting up Arduino to flash the ESP32 with our biofeedback software](https://github.com/moothyknight/HEG_ESP32/blob/master/Device_README.txt)
- [Updating the firmware via the web interface](https://github.com/moothyknight/HEG_ESP32/blob/master/Guides/How%20To%20Update.pdf)
- [Lolin32 Firmware and Updates](https://github.com/moothyknight/HEG_ESP32/tree/master/Device%20Drivers/HEG_WIFI_BLE_Lolin32)
- [Huzzah32 Feather Firmware and Updates](https://github.com/moothyknight/HEG_ESP32/tree/master/Device%20Drivers/HEG_WIFI_BLE_Feather)

## What is it?
Hemoencephalography is a method that allows you to measure and influence control over the bloodflow in regions your brain. It's just like any other FNIRS or pulse oximetry method, but allows for a type of physical brain exercise. HEG devices typically cost hundreds or thousands on the market, so this is a much better solution for people wanting to get their feet wet with biofeedback and do a cool DIY project to understand the extremely straightforward science better. [HEG biofeedback](https://en.wikipedia.org/wiki/Hemoencephalography) was originally developed as a safe and non-invasive method to treat ADD in the late 90s, later expanding to treating disorders like PTSD and Depression due to common stress symptoms like [Hypofrontality](https://en.wikipedia.org/wiki/Hypofrontality) being measurable with this tool. 

It is implicated for much more, but there's not a whole lot of data (which this 20 dollar version could solve). HEG biofeedback is informally called "brain pushups" for how it enables one to literally work out their brain to enable better bloodflow and oxygenation, therefore cognitive functioning and self-control. It only takes 5-10 minutes in the first session to gain control of bloodflow in the targeted area. I don't recommend doing more than 10 minutes at a time with this thing. Be wary of fatigue or headaches the first few times when you start gaining control of your bloodflow. View the resources section of the [About Page] on our website (https://hegalpha.com/about) to educate yourself more deeply on this subject.

![Explanation](https://raw.githubusercontent.com/moothyknight/HEG_Arduino/master/Pics/HEGExplained.png)

## Software

### Arduino Setup
See the [Device_Readme.txt](https://github.com/moothyknight/HEG_ESP32/blob/master/Device_README.txt)  for flashing instructions as well as available USB commands and the changelog, including which dependencies are required for the Arduino IDE. We packaged the more minor dependencies in the Device_Drivers folder so you don't have to chase all of them down, just get Arduino and the ESP32 addon (github version) working.

Use the HEG_WIFI_BLE sketch in the arduino IDE on your respective ESP32. Pin definitions in HEG.h for the SDA/SCL and LEDs need to be adjusted according to your setup. 

These builds are tested on the Lolin32 and Huzzah32 Feather respectively but should work on any board after modifying the pinouts in HEG.h

### All Open Source Games, Tools, & APIs.

<img src="https://github.com/moothyknight/HEG_ESP32/blob/master/Pictures/platforms.PNG" alt="platforms" width="252" height="354">

On the firmware you will find a WIP Async Web Server with cross-platform support, enabling plug-and-play and global networking features. We are creating an open source combined therapy and research toolset, using the perks of an online-enabled device and all of the diverse tools available for web front and backend. This is a living project so stay tuned!

You can demo it now via our Chrome Extension (via the Software folder) or right on board the firmware or a new webapp at [hegalomania.netlify.app](https://hegalomania.netlify.app). It's evolving fast. We will eventually be comparable to professional BCI software, free of charge. In the More folder, please find the DataCharting.html applet for analyzing and comparing your data with interactive charts.

![Screenshot](https://github.com/moothyknight/HEG_ESP32/blob/master/Pictures/HEGwebAPI.png?raw=true)

## Data Charter (To be replaced) CSV analyzer for the web app (also found on our [Data page on our website](https://hegalpha.com))
![HEGCharter](https://github.com/moothyknight/HEG_ESP32/blob/master/Pictures/datacharter.PNG?raw=true)

## More Links
Our website: [HEG Alpha](https://hegalpha.com)

Find us on [CrowdSupply](https://crowdsupply.com/alaskit/hegduino)

and [OpenBCI](https://shop.openbci.com/collections/frontpage/products/hegduino-kit?variant=32052268531784)

Special thanks to the [Biocomp/Biofeedback Institute of LA](https://www.biocompresearch.org/), [Brain Trainer](https://brain-trainer.com/), and [AlasKit](https://alaskit.net)

See also (very deprecated):
[Arduino Nano V3 HEG](https://github.com/moothyknight/HEG_Arduino)

