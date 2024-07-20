#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/sysinfo.h>
#include <unistd.h>
#include <sys/utsname.h>
#include "blockart.h"

#define COLOR1 "\033[38;5;231m"
#define COLOR2 "\033[38;5;223m"
#define COLOR3 "\033[38;5;210m"
#define COLOR4 "\033[38;5;179m"
#define COLOR5 "\033[38;5;157m"
#define COLOR6 "\033[38;5;122m"
#define COLOR7 "\033[38;5;110m"
#define COLOR8 "\033[38;5;99m"
#define COLOR9 "\033[38;5;93m"
#define COLOR10 "\033[38;5;85m"
#define COLOR11 "\033[38;5;215m"

#define RESET    "\033[0m" 

#define LABEL_WIDTH 11

void printRainbow(const char *label, const char *value, const char *color) {
    printf("%s%-*s~ %s%s\n", color, LABEL_WIDTH, label, value, RESET);
}

void printHostname() {
    char hostname[256];
    if (gethostname(hostname, sizeof(hostname)) == 0) {
        printRainbow("Hostname", hostname, COLOR1);
    } else {
        perror("gethostname");
    }
}

void printPackageCount() {
    FILE *fp = popen("dpkg -l | grep '^ii' | wc -l", "r");
    if (fp == NULL) {
        perror("popen");
        return;
    }

    char buffer[128];
    if (fgets(buffer, sizeof(buffer) - 1, fp) != NULL) {
        buffer[strcspn(buffer, "\n")] = '\0';
        printRainbow("Packages", buffer, COLOR2);
    }
    pclose(fp);
}

void printResolution() {
    FILE *fp = popen("xrandr | grep '*' | awk '{print $1}'", "r");
    if (fp == NULL) {
        perror("popen");
        return;
    }

    char buffer[128];
    if (fgets(buffer, sizeof(buffer) - 1, fp) != NULL) {
        buffer[strcspn(buffer, "\n")] = '\0'; 
        printRainbow("Resolution", buffer, COLOR3);
    }
    pclose(fp);
}

void printDE() {
    FILE *fp = popen("echo $XDG_CURRENT_DESKTOP", "r");
    if (fp == NULL) {
        perror("popen");
        return;
    }

    char buffer[128];
    if (fgets(buffer, sizeof(buffer) - 1, fp) != NULL) {
        buffer[strcspn(buffer, "\n")] = '\0';
        printRainbow("DE", buffer, COLOR4);
    }
    pclose(fp);
}

void printTerminal() {
    FILE *fp = popen("echo $TERM", "r");
    if (fp == NULL) {
        perror("popen");
        return;
    }

    char buffer[128];
    if (fgets(buffer, sizeof(buffer) - 1, fp) != NULL) {
        buffer[strcspn(buffer, "\n")] = '\0'; 
        printRainbow("Terminal", buffer, COLOR5);
    }
    pclose(fp);
}

void printShell() {
    FILE *fp = popen("echo $SHELL", "r");
    if (fp == NULL) {
        perror("popen");
        return;
    }

    char buffer[128];
    if (fgets(buffer, sizeof(buffer) - 1, fp) != NULL) {
        buffer[strcspn(buffer, "\n")] = '\0'; 
        printRainbow("Shell", buffer, COLOR6);
    }
    pclose(fp);
}

void getOSInfo() {
    FILE *fp = popen("lsb_release -d | awk -F ':' '{print $2}'", "r");
    if (fp == NULL) {
        perror("popen");
        return;
    }

    char buffer[128];
    if (fgets(buffer, sizeof(buffer) - 1, fp) != NULL) {
        buffer[strcspn(buffer, "\n")] = '\0';

        char *start = buffer;
        while (*start == ' ' || *start == '\t') start++;
        
        
        printRainbow("Distro", start, COLOR7); 
    }
    pclose(fp);
}

void getKernelVersion() {
    FILE *fp = popen("uname -r", "r");
    if (fp == NULL) {
        perror("popen");
        return;
    }

    char buffer[128];
    if (fgets(buffer, sizeof(buffer) - 1, fp) != NULL) {
        buffer[strcspn(buffer, "\n")] = '\0'; 
        printRainbow("Kernel", buffer, COLOR8);
    }
    pclose(fp);
}

void getUptime() {
    FILE *fp = popen("uptime -p", "r");
    if (fp == NULL) {
        perror("popen");
        return;
    }

    char buffer[128];
    if (fgets(buffer, sizeof(buffer) - 1, fp) != NULL) {
        buffer[strcspn(buffer, "\n")] = '\0'; 
        printRainbow("Uptime", buffer, COLOR9);
    }
    pclose(fp);
}

void getMemoryUsage() {
    FILE *fp = popen("free -h | grep Mem | awk '{print $3 \" / \" $2}'", "r");
    if (fp == NULL) {
        perror("popen");
        return;
    }

    char buffer[128];
    if (fgets(buffer, sizeof(buffer) - 1, fp) != NULL) {
        buffer[strcspn(buffer, "\n")] = '\0'; 
        printRainbow("Memory", buffer, COLOR10);
    }
    pclose(fp);
}

void getCPUInfo() {
    FILE *fp = popen("lscpu | grep 'Model name' | awk -F ':' '{print $2}'", "r");
    if (fp == NULL) {
        perror("popen");
        return;
    }

    char buffer[256];
    if (fgets(buffer, sizeof(buffer) - 1, fp) != NULL) {
        buffer[strcspn(buffer, "\n")] = '\0';
        char *trimmed = buffer;
        while (*trimmed == ' ') trimmed++;
        printRainbow("CPU", trimmed, COLOR11); 
    }
    pclose(fp);
}

int main() {

    printf("\n");
    printart();
    printf("\n");
    printHostname();
    printPackageCount();
    printResolution();
    printDE();
    printTerminal();
    printShell();
    getOSInfo();
    getKernelVersion();
    getUptime();
    getMemoryUsage();
    getCPUInfo();

    return 0;
}


