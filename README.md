# specppy

![Linux supported](https://img.shields.io/badge/Linux-supported-brightgreen?logo=linux)
![macOS supported](https://img.shields.io/badge/macOS-supported-brightgreen?logo=apple)
![Windows supported](https://img.shields.io/badge/Windows-supported-brightgreen?logo=windows)
![C++](https://img.shields.io/badge/C++-11-00599C?logo=cplusplus&logoColor=white)

A C++ system information viewer — like AIDA64, but for Linux, macOS and Windows. Free, clean, and no setup wizard.

Shows all your PC specs in a nice GTK window with tabs for CPU, memory, disk, network, GPU, monitors, and full OS info.  
Run with `sudo` to unlock BIOS info, SMART disk health, and the full hardware tree.

---

## How to build

```bash
g++ syspeek.cpp -o syspeek `pkg-config --cflags --libs gtk+-3.0` -std=c++11
```

Run normally:

```bash
./syspeek
```

Run with full hardware info:

```bash
sudo ./syspeek
```

---

## Dependencies

### Ubuntu / Debian / Linux Mint / Pop!_OS

```bash
sudo apt update
sudo apt install build-essential libgtk-3-dev lshw mesa-utils edid-decode smartmontools dmidecode
```

### Arch / Manjaro / EndeavourOS / Garuda

```bash
sudo pacman -S base-devel gtk3 mesa-utils edid-decode lshw smartmontools dmidecode
```

### Fedora / RHEL / AlmaLinux / Rocky Linux

```bash
sudo dnf install gcc gcc-c++ gtk3-devel mesa-demos edid-decode lshw smartmontools dmidecode
```

### openSUSE Tumbleweed / Leap

```bash
sudo zypper install gcc-c++ gtk3-devel Mesa-demo-x edid-decode lshw smartmontools dmidecode
```

### Alpine Linux

```bash
sudo apk add build-base gtk+3.0-dev lshw mesa-demos edid-decode smartmontools dmidecode
```

### Void Linux

```bash
sudo xbps-install -S gcc gtk+3-devel lshw mesa-demos smartmontools dmidecode
```

### Gentoo

```bash
sudo emerge --ask dev-libs/glib x11-libs/gtk+ sys-apps/lshw x11-apps/mesa-progs sys-apps/smartmontools sys-apps/dmidecode
```

### NixOS

Add the following to your `configuration.nix` or use `nix-shell`:

```bash
nix-shell -p gcc gtk3 pkg-config lshw mesa smartmontools dmidecode
```

### Slackware

Install GTK3 from SlackBuilds.org, then:

```bash
installpkg lshw smartmontools dmidecode
```

---

## macOS

> GTK3 on macOS is provided via Homebrew. Native macOS APIs are not used.

### Install dependencies

```bash
brew install gtk+3 pkg-config lshw smartmontools
```

> `dmidecode` and `edid-decode` are not available on macOS — BIOS/SMART features will be limited or unavailable.

### Build

```bash
g++ syspeek.cpp -o syspeek $(pkg-config --cflags --libs gtk+-3.0) -std=c++11
```

### Run

```bash
./syspeek
```

---

## Windows (MSYS2 / MinGW-w64)

> Requires [MSYS2](https://www.msys2.org/) installed. All commands run inside the **MSYS2 MINGW64** shell.

### Install MSYS2

Download and install from https://www.msys2.org/, then launch **MSYS2 MINGW64** from the Start menu.

### Install dependencies

```bash
pacman -Syu
pacman -S mingw-w64-x86_64-toolchain mingw-w64-x86_64-gtk3 mingw-w64-x86_64-pkg-config
```

### Build

```bash
g++ syspeek.cpp -o syspeek.exe $(pkg-config --cflags --libs gtk+-3.0) -std=c++11
```

### Run

```bash
./syspeek.exe
```

> Note: Hardware info commands like `lshw`, `smartctl`, and `dmidecode` are Linux tools and are not available on Windows. Tabs relying on them will show limited or no data.

---

## Works on most Linux distros, macOS, and Windows via MSYS2.  
## As long as GTK3 is installed, it should build and run.

That's it — enjoy your PC specs like a boss.
