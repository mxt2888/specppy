# ALL ISSUES A ACCEPTED

# specppy
A C++ aida64 tryna be

# system info viewer gtk edition

this app shows all the specs of your pc using a nice gtk window  
like aida64 but for linux and free and clean

includes tabs for cpu memory disk network gpu monitor and full os info  
if you run it with sudo you get bios smart disk health and full hardware tree too

no setup wizard no config just build and run

## how to build it

```bash
g++ syspeek.cpp -o syspeek `pkg-config --cflags --libs gtk+-3.0` -std=c++11
```

run it like this

```bash
./syspeek
```

or if you want all the juicy info

```bash
sudo ./syspeek
```

## dependencies to install before building

### ubuntu and debian

```bash
sudo apt update
sudo apt install build-essential gtk+-3.0 libgtk-3-dev lshw mesa-utils edid-decode smartmontools dmidecode
```

### arch based like manjaro or endeavouros

```bash
sudo pacman -S base-devel gtk3 mesa-utils edid-decode lshw smartmontools dmidecode
```

### fedora

```bash
sudo dnf install gcc gcc-c++ gtk3-devel mesa-demos edid-decode lshw smartmontools dmidecode
```

### opensuse

```bash
sudo zypper install gcc-c++ gtk3-devel Mesa-demo-x edid-decode lshw smartmontools dmidecode
```

### alpine linux

```bash
sudo apk add build-base gtk+3.0 gtk+3-dev lshw mesa-demos edid-decode smartmontools dmidecode
```

## works on most linux distros tested on ubuntu arch fedora and suse  
## if gtk3 is installed it should work

thats it enjoy your pc specs like a boss
