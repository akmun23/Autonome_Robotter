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

Herefter skal IP-adresse på robot sættes op. På polyscope trykkes der på Setup program:

![image](https://github.com/akmun23/Autonome_Robotter/assets/159116437/d2b64b64-c21c-4018-8942-d9babb2aae0a)

Herefter vælges Network:

![image](https://github.com/akmun23/Autonome_Robotter/assets/159116437/1a05eb70-6010-4a42-b20a-05f7ed22d2eb)

Der vælges static Addres, hvortil de to felter sættes til: 

```
IP: 192.168.1.54
Netmask: 255.255.255.0
```
Herefter kan der laves et nyt program ved at vælge Program Robot, hvorefter der kan vælges Empty Program:

![image](https://github.com/akmun23/Autonome_Robotter/assets/159116437/fc6f7312-72fe-493e-9b78-279e0a8e91c1)

Når dette er valgt kan Installation vælges i toppen af skærmen, hvortil External Control vælges. Det to felter herunder sættes til at være:

![image](https://github.com/akmun23/Autonome_Robotter/assets/159116437/cd5d0058-3821-481f-8845-91d963585119)

```
Host IP: 192.168.1.53
Custom Port: 50002
```
Hvis der gåes tilbage til Program i toppen og menuen Structure vælges, hvorefter undermenuen URCaps vælges er der mulighed for at sætte en external control ind i programmet for robotten:

![image](https://github.com/akmun23/Autonome_Robotter/assets/159116437/78733ee3-a153-434e-b9bc-70f093ef73e2)

Denne skal indsættes for at c++-scriptet kan kommunikere med robotten. Herefter skal der ikke gøres mere på tabletten og programmet skulle gerne kunne køre fra computer :D

# C++-script
UR-script dokumentation:
https://s3-eu-west-1.amazonaws.com/ur-support-site/124999/scriptManual_3.15.4.pdf

# ATMega
Kommentarer til ATMega her

# Rapport
https://www.overleaf.com/8162342565fythcwbqxzsg#e25365

# Gripper
Kommentarer til Gripper her
