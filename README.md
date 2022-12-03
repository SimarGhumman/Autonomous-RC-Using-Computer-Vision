# Autonomous-RC-Using-Computer-Vision
Senior Project For SJSU

How To Get Started Building This Project, I will include links underneath for more information. You Don't Need to follow this guide to the exact detail figure out an even better way, trust me, my method isn't the most optimized. There is a plently of resources and guidance online, so don't despair if my build doesn't work for you. Good Luck! P.S. Look in the Youtube Description to See The Github Code

**Step 1**

1. Buy An RC-Car, the one we used for this project is called a Traxxas Bandit XL-5
https://traxxas.com/products/models/electric/bandit-standard

2. Buy An RPLidar A1, test out the software they give you to make sure everything works
https://www.slamtec.com/en/Lidar/A1

3. Buy A PowerBank Any Works, get one with different ports if possible
https://www.amazon.com/dp/B09H4GLZXT?psc=1&ref=ppx_yo2ov_dt_b_product_details

4. Buy An perferably MKR Wifi 1010 or MKR Wifi 1000 (I used both at some point less problems with MKR Wifi 1010 finished the project though with a MKR Wifi 1000 since I accidentally wiped my bootloader I'll explain at the bottom) as well as an perferably Arduino Mega 2560 or Arduino Uno
https://store-usa.arduino.cc/products/arduino-mkr-wifi-1010
https://store-usa.arduino.cc/products/arduino-mega-2560-rev3?selectedStore=us

5. Buy An Raspberry Pi 3 And A Camera Module
https://www.amazon.com/Raspberry-Pi-Camera-Module-Megapixel/dp/B01ER2SKFS/ref=asc_df_B01ER2SKFS/?tag=hyprod-20&linkCode=df0&hvadid=309776868400&hvpos=&hvnetw=g&hvrand=3441479396816567707&hvpone=&hvptwo=&hvqmt=&hvdev=c&hvdvcmdl=&hvlocint=&hvlocphy=9032144&hvtargid=pla-406302832745&psc=1
https://www.raspberrypi.com/products/raspberry-pi-3-model-b/

**Step 2**

You Have All the Compoments Now, Let's Start Building the Raspberry Pi System first, since its the not dependently of the entire system

1. First we need to the camera connected and working follow this guide.
https://thepihut.com/blogs/raspberry-pi-tutorials/16021420-how-to-install-use-the-raspberry-pi-camera

2. Follow this guide to test the camera and get it working, as well as to test deploying a server through the camera
https://randomnerdtutorials.com/video-streaming-with-raspberry-pi-camera/

3. Follow this guide next to start incorprating the camera as well as the tensorflow model, you add custom models later but use this as a base
https://www.youtube.com/watch?v=aimSGOAUI8Y

Useful Links for **Step 2**
https://raspberrytips.com/raspberry-pi-wifi-setup/
https://raspberrypi.stackexchange.com/questions/8311/ssh-connection-timeout-when-connecting
https://www.youtube.com/watch?v=QqTLkw1IenI
https://www.youtube.com/watch?v=rgWVm_j3llo
https://www.youtube.com/watch?v=bWwZF_zVf00
https://pyimagesearch.com/2019/05/13/object-detection-and-image-classification-with-google-coral-usb-accelerator/   -> Walkthrough Among Other Amazing Projects
https://github.com/pornpasok/opencv-stream-video-to-web
https://towardsdatascience.com/deeppicar-part-3-d648b76fc0be

Other Links To Check Out
https://pyimagesearch.com/2015/12/21/increasing-webcam-fps-with-python-and-opencv/
https://pyimagesearch.com/2015/12/28/increasing-raspberry-pi-fps-with-python-and-opencv/
https://pyimagesearch.com/2019/09/02/opencv-stream-video-to-web-browser-html-page/
https://github.com/jeffbass/imagezmq
https://www.youtube.com/watch?v=bxYPJlCdDGk

Useful Command
sudo apt-get update && sudo apt-get upgrade

**Step 3**

The Raspberry Pi Camera Should be Working on it's own now, test it out by plugging it into the power bank and checking the results. The next part requires us to focus on the pin outputs and the microcontrollers of the system. Remember to download the neccessary the libaries or update them.

1. Try Following This Guide As Closely As Possible, this was mostly used in my reference but I will include tips below
https://www.youtube.com/watch?v=xSrjtJ2AZqw&t=1s

2. Use the datasheet from the RPLidar A1 to properly connect it to the MKR Wifi 1010 as well as the Arduino Mega 2560 (Click the Reddit Post to Find Data Manual)
https://www.reddit.com/r/LiDAR/comments/lzwde7/rplidar_a1m8_pinout/
https://docs.arduino.cc/hardware/mkr-wifi-1010
https://docs.arduino.cc/hardware/mega-2560

3. The next step is now to properly connect the RC motors the ESC (Electronic Speed Controller) and the Servo Motor. We are hosting an server so we don't need to worry about a transmitter/reciever anymore since our Arduino Mega 2560 is acting as the reciever and our MKR Wifi would be the transmitter sending singals to control the throttle and steering. I recommend this guide to follow.
https://www.youtube.com/watch?v=6gf5kKQ0YgQ&list=LL&index=5&t=1s

I have attached pictures for reference of my board but I recommend figuring out the wiring for yourself, it'll make life easier in the future if problems occur.

Useful Links for **Step 3**
https://www.youtube.com/watch?v=Ejh2344ZzyQ
https://www.youtube.com/watch?v=UmEPTh80KLc
https://docs.arduino.cc/tutorials/mkr-1000-wifi/mkr-1000-connect-to-wifi
https://www.slamtec.com/en/Lidar/A1Spec
https://www.partsnotincluded.com/how-to-use-an-rc-controller-with-an-arduino/
https://www.youtube.com/watch?v=VhbFbxyOI1k

**Final**

You reached the end, if everything is connected it's only a matter of plugging in the power, double check the pins beforehand just to be safe. All you need to do now is run the code, take a look at the files, I uploaded and test them out. Remember it's not the destination but the journey. Have Fun!

Problems That I Occured/Things That Could Be Better

1. I highly reccomend getting multiple parts, I destroyed a couple of my compoments by overriding the bootloader, in order to access the bootloader you double click the reset button and another should pop up that faintly dims. If this happens upload an example sketch such as a update firmware of one of your libraries should take it out of bootloader mode removing the led. If you end up getting stuck at port is busy or something else, the safest thing to do is restart your pc and the port should be cleared up.
https://forum.arduino.cc/t/com-port-disconnects-and-always-goes-into-bootloader-mode/884091

2. Always Carry a Basic Version of what your trying to implement, aiming for too much can cause undetected faults that would take forever to troubleshoot try bit by bit. And if something go wrong revert and figure out what happened.

3. There is an Arduino limit to what you can send from the ArduinoHTTPClient library. The HTTP request sends a TCP packet which can only be at limited size of 89 characters? Haven't fully tested this out.
https://stackoverflow.com/questions/59633872/arduinohttpclient-websocket-undocumented-max-message-size
https://forum.arduino.cc/t/upper-limit-for-client-print-string-length/157865

4. If your aiming to improve speed or performance, don't follow this project, This is an project that can definitely be improved on, but it is a good base for learning. I recommend if you want to improve this, try connecting the lidar pins to the raspberry pi and having it calculate the optimal direction. We won't need a server at this point as well as the MKR Wifi. If you have extra cash trying builidng an oboard computer system that can handle the cacluations on the go. Also having an upgraded Servo/Motor not an RC car would make life easier, since you would be able to have 360 degrees control instead of forward and backward. (good chasis as well would be nice)

5. There is a lot of math surprisingly, given an angle and distance we have to translate it to points on a chart as well as plotting on pygame is slightly complex. We need to calculate the best angle and direction to move in. Simple Concepts but important to be done right.

6. It's important to read as many datsheets that are pertinent because the greater your understanding, the easier it will get as well as a better project you can create. You never know for certain if the path your taking is the best, so it's important to stop for a second and research other ways at tackling the problems. Who knows you might even find it easier than you thought.

Finally this is a project that is built on continually learning, anything that seems simple can get complicated really fast. Thanks for reading till the end.
