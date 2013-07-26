/* settings */
#define BAT_LOW_P   10
#define BAT_LOW_T   10
#define CPU_HI	    100
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
#define WIFI_S	    "\x08\x0d %s\x0e %d%%"
#define NO_CONN_S   "\x08\x0d net\x0f x"
#define VOL_S	    "\x08\x0d vol\x0e %d%%"
#define VOL_MUTE_S  "\x08\x0d vol\x0f M"
#define CPU_S	    "\x08\x0d cpu\x0e %02d%%"
#define CPU_HI_S    "\x08\x0d cpu\x0f %02d%%"
#define MEM_S	    "\x08\x0d mem\x0e %ld%%"
#define BAT_FULL_S  "\x13\x10 bat F "
#define BAT_S	    "\x13\x10 bat D\x11 %d%%\x10, %02d:%02d "
#define BAT_LOW_S   "\x13\x10 bat D\x12 %d%%\x10, %02d:%02d "
#define BAT_CHRG_S  "\x13\x10 bat C\x11 %d%%\x10, %02d:%02d "
#define BAT_UNKN_S  "\x13\x10 bat U "
