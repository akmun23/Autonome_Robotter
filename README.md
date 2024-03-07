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
Herefter kan packagen downloades:
```
sudo add-apt-repository ppa:sdurobotics/ur-rtde
sudo apt-get update
sudo apt install librtde librtde-dev
```
