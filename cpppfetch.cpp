#include <iostream>
#include <string>
#include <array>
#include <unistd.h>

std::string runCommand(const std::string& cmd) {
    std::array<char, 256> buffer;
    std::string result;
    FILE* pipe = popen(cmd.c_str(), "r");
    if (!pipe) return "Command failed.";
    while (fgets(buffer.data(), buffer.size(), pipe)) {
        result += buffer.data();
    }
    pclose(pipe);
    return result;
}

int main() {
    std::cout << "\033[1;36m================== SYSTEM INFO ==================\033[0m\n";

    std::cout << "\033[1;33m> OS Information:\033[0m\n";
    std::cout << runCommand("lsb_release -a 2>/dev/null");
    std::cout << runCommand("uname -a");

    std::cout << "\033[1;33m> CPU:\033[0m\n";
    std::cout << runCommand("grep 'model name|cpu cores|vendor_id' /proc/cpuinfo | uniq");

    std::cout << "\033[1;33m> Memory:\033[0m\n";
    std::cout << runCommand("free -h");

    std::cout << "\033[1;33m> Disk:\033[0m\n";
    std::cout << runCommand("df -hT --total");

    std::cout << "\033[1;33m> Network:\033[0m\n";
    std::cout << runCommand("ip addr");

    std::cout << "\033[1;33m> GPU:\033[0m\n";
    std::cout << runCommand("lshw -C display");
    std::cout << runCommand("glxinfo | grep -E 'OpenGL|render'");

    std::cout << "\033[1;33m> Monitor:\033[0m\n";
    std::cout << runCommand("xrandr --verbose");

    std::cout << "\033[1;33m> BIOS and System (root required):\033[0m\n";
    if (geteuid() == 0) {
        std::cout << runCommand("dmidecode -t bios -t system");
        std::cout << runCommand("lshw -short");
        std::cout << runCommand("for d in /dev/sd?; do echo \"SMART for $d\"; smartctl -H $d; done");
    } else {
        std::cout << "Run as root for BIOS and SMART info\n";
    }

    std::cout << "\033[1;36m=================================================\033[0m\n";
    return 0;
}
