# Autonome_Robotter
 Semesterprojekt i autonome robotter

OpenCV til skakbrætsgenkendelse
Bevæger sig ned indtil den kan mærke modstand

Til kalibrering af bræt i stdet for fysisk kalibrering
Målepind til fysisk kalibrering 

# UR_RTDE
For at køre dokumentet Checker kræves det at UR_RTDE library er installeret og Ubuntu er sat op til at køre Real-Time kernel.
Real-Time kernel kan opsættes ved:

```
sudo apt install ubuntu-advantage-tools
ua enable realtime-kernel --beta
```
Derefter skal der indsættes en priority
```
sudo groupadd realtime
sudo usermod -aG realtime $(whoami)
cd /etc/security
gedit limit.conf
```
Hertil tilføjes til filen:
```
@realtime soft rtprio 99
@realtime soft priority 99
@realtime soft memlock 102400
@realtime hard rtprio 99
@realtime hard priority 99
@realtime hard memlock 102400
```
Herefter kan package downloades:
```
sudo add-apt-repository ppa:sdurobotics/ur-rtde
sudo apt-get update
sudo apt install librtde librtde-dev
```
Hvis dette er gjort kan filen Checker downloades og computer kan sættes til robot og køre.

# Forbindelse til robot
For at få forbindelse til robotten skal der forbindes til den med LAN kabel. Herefter skal der sikres at IP-adresse matcher med robot og computer:

![image](https://github.com/akmun23/Autonome_Robotter/assets/159116437/ff7ad3fd-7466-4d27-a28c-f5ac45274581)

Hertil vælges tandhjulet og ud for netværket. OBS det eer LAN-kabels forbindelse, der skal vælges og IKKE Wi-Fi
Herefter vælges IPv4:
![image](https://github.com/akmun23/Autonome_Robotter/assets/159116437/e3379016-b6f6-44d7-a719-6da084d37216)

IP-adresse sættes som vist på billedet til at være 192.168.1.54 og Netmask til at være 255.255.255.0. 
De andre felter efterlades tomme!

Herefter skal IP-adresse på robot sættes op:

