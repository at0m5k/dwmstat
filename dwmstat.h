/* settings */
#define BAT_LOW_P   10
#define CPU_HI	    100
#define MEM_LOW	    50
#define INTERVAL    1

/* devices */
#define WIRELESS_D  "wlo1"
#define VOL_CH	    "Master"

/* files */
#define BAT_NOW	    "/sys/class/power_supply/BAT0/energy_now"
#define BAT_FULL    "/sys/class/power_supply/BAT0/energy_full"
#define BAT_STAT    "/sys/class/power_supply/BAT0/status"
#define BAT_VOLT    "/sys/class/power_supply/BAT0/voltage_now"
#define BAT_CNOW    "/sys/class/power_supply/BAT0/power_now"
#define CPU_F	    "/proc/stat"
#define MEM_F	    "/proc/meminfo"

/* sprintf strings */
#define WIFI_S	    "\x05\x08 %s\x09 %d%%"
#define NO_CONN_S   "\x05\x08 net\x0a x"
#define VOL_S	    "\x05\x08 vol\x09 %d%%"
#define VOL_MUTE_S  "\x05\x08 vol\x0a M"
#define CPU_S	    "\x05\x08 cpu\x09 %02d%%"
#define CPU_HI_S    "\x05\x08 cpu\x0a %02d%%"
#define MEM_S	    "\x05\x08 mem\x09 %d%%"
#define MEM_LOW_S   "\x05\x08 mem\x0a %d%%"
#define BAT_FULL_S  "\x0e\x0b bat F "
#define BAT_S	    "\x0e\x0b bat D\x0c %d%%\x0b, %02d:%02d "
#define BAT_LOW_S   "\x0e\x0b bat D\x0d %d%%\x0b, %02d:%02d "
#define BAT_CHRG_S  "\x0e\x0b bat C\x0c %d%%\x0b, %02d:%02d "
