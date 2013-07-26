#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <X11/Xlib.h>
#include <iwlib.h>
#include <alsa/asoundlib.h>

#include "dwmstat.h"

FILE *infile;
int skfd;
struct wireless_info *winfo;
long jif1, jif2, jif3, jif4, lnum1, lnum2, lnum3, lnum4;

char *get_wifi(char *buf) {
	char devpath[35], state[5];

	sprintf(devpath, "/sys/class/net/%s/operstate", WIRELESS_D);
	infile = fopen(devpath, "r");

	fscanf(infile, "%s", state); fclose(infile);
	if(strcmp(state, "up") == 0) {
		if(iw_get_basic_config(skfd, WIRELESS_D, &(winfo->b)) > -1) {
			if(iw_get_stats(skfd, WIRELESS_D, &(winfo->stats), &winfo->range, winfo->has_range) >= 0)
				winfo->has_stats = 1;
			if(iw_get_range_info(skfd, WIRELESS_D, &(winfo->range)) >= 0)
				winfo->has_range = 1;
			if(winfo->b.has_essid && winfo->b.essid_on)
				sprintf(buf, WIFI_S, winfo->b.essid, (winfo->stats.qual.qual * 100) / winfo->range.max_qual.qual);
		}
	}
	else
		sprintf(buf, NO_CONN_S);
	return buf;
}

char *get_vol(char *buf) {
	long max = 0, min = 0, vol = 0;
	int mute = 0;

	snd_mixer_t *handle;
	snd_mixer_elem_t *pcm_mixer, *mas_mixer;
	snd_mixer_selem_id_t *vol_info, *mute_info;

	snd_mixer_open(&handle, 0);
	snd_mixer_attach(handle, "default");
	snd_mixer_selem_register(handle, NULL, NULL);
	snd_mixer_load(handle);
	snd_mixer_selem_id_malloc(&vol_info);
	snd_mixer_selem_id_malloc(&mute_info);
	snd_mixer_selem_id_set_name(vol_info, VOL_CH);
	snd_mixer_selem_id_set_name(mute_info, VOL_CH);
	pcm_mixer = snd_mixer_find_selem(handle, vol_info);
	mas_mixer = snd_mixer_find_selem(handle, mute_info);
	snd_mixer_selem_get_playback_volume_range((snd_mixer_elem_t *)pcm_mixer, &min, &max);
	snd_mixer_selem_get_playback_volume((snd_mixer_elem_t *)pcm_mixer, SND_MIXER_SCHN_MONO, &vol);
	snd_mixer_selem_get_playback_switch(mas_mixer, SND_MIXER_SCHN_MONO, &mute);
	sprintf(buf, !(mute) ? VOL_MUTE_S : VOL_S, (int)vol * 100 / (int)max);
	if(vol_info)
		snd_mixer_selem_id_free(vol_info);
	if(mute_info)
		snd_mixer_selem_id_free(mute_info);
	if(handle)
		snd_mixer_close(handle);
	return buf;
}
	
char *get_cpu(char *buf) {
	int num;
	infile = fopen(CPU_F, "r");

	fscanf(infile, "cpu %ld %ld %ld %ld", &lnum1, &lnum2, &lnum3, &lnum4); fclose(infile);
	num = lnum4 > jif4 ? (int)((100 * ((lnum1 - jif1) + (lnum2 - jif2) + (lnum3 - jif3))) / (lnum4 - jif4)) : 0;
	jif1 = lnum1; jif2 = lnum2; jif3 = lnum3; jif4 = lnum4;
	sprintf(buf, (num > CPU_HI ? CPU_HI_S : CPU_S), num);
	return buf;
}

char *get_mem(char *buf) {
	int num;
	long buffers, cached, free, total;
	infile = fopen(MEM_F, "r");
	fscanf(infile, "MemTotal: %ld kB\nMemFree: %ld kB\nBuffers: %ld kB\nCached: %ld kB\n",
	    &total, &free, &buffers, &cached); fclose(infile);
	num = 100 * (free + buffers + cached) / total;
	sprintf(buf, num < MEM_LOW ? MEM_LOW_S : MEM_S, num);
	return buf;
}

char *get_bat(char *buf) {
	char state[8];
	long full = -1, now = -1, rate = -1, voltage = -1;
	int perc, hours, minutes, seconds = -1;

	infile = fopen(BAT_NOW, "r"); fscanf(infile, "%ld\n", &now); fclose(infile);
	infile = fopen(BAT_FULL, "r"); fscanf(infile, "%ld\n", &full); fclose(infile);
	infile = fopen(BAT_STAT, "r"); fscanf(infile, "%s\n", state); fclose(infile);
	infile = fopen(BAT_VOLT, "r"); fscanf(infile, "%ld\n", &voltage); fclose(infile);
	infile = fopen(BAT_CNOW, "r"); fscanf(infile, "%ld\n", &rate); fclose(infile);

	now = ((float)voltage * (float)now);
	full = ((float)voltage * (float)full);
	rate = ((float)voltage * (float)rate);
	perc = (now * 100) / full;

	if(strncmp(state, "Full", 8) == 0)
		sprintf(buf, BAT_FULL_S);
	else if(strncmp(state, "Unknown", 8) == 0)
		sprintf(buf, BAT_UNKN_S);
	else {
		if(strncmp(state, "Charging", 8) == 0)
			seconds = 3600 * (((float)full - (float)now) / (float)rate);
		else
			seconds = 3600 * ((float)now / (float)rate);
		hours = seconds / 3600;
		seconds -= 3600 * hours;
		minutes = seconds / 60;
		seconds -= 60 * minutes;
		if(strncmp(state, "Charging", 8) == 0)
			sprintf(buf, BAT_CHRG_S, perc, hours, minutes);
		else {
			if(perc < BAT_LOW_P || minutes < BAT_LOW_T)
				sprintf(buf, BAT_LOW_S, perc, hours, minutes);
			else
				sprintf(buf, BAT_S, perc, hours, minutes);
		}
	}
	return buf;
}

int main(void) {
	Display *dpy;
	Window root;
	char status[201], net[30], vol[14], cpu[14], mem[14], bat[48];
	int netloops = 60;

	dpy = XOpenDisplay(NULL);
	if(dpy == NULL) {
		fprintf(stderr, "ERROR: could not open display\n");
		return 1;
	}
	root = XRootWindow(dpy, DefaultScreen(dpy));
	winfo = malloc(sizeof(struct wireless_info));
	memset(winfo, 0, sizeof(struct wireless_info));

	skfd = iw_sockets_open();

	infile = fopen(CPU_F, "r");
	fscanf(infile, "cpu %ld %ld %ld %ld", &jif1, &jif2, &jif3, &jif4); fclose(infile);

	while(1) {
		if(++netloops > 60) {
			netloops = 0;
			get_wifi(net);
		}
		get_vol(vol);
		get_cpu(cpu);
		get_mem(mem);
		get_bat(bat);

		sprintf(status, "%s %s %s %s %s", net, vol, cpu, mem, bat);

		XStoreName(dpy, root, status);
		XFlush(dpy);
		sleep(INTERVAL);
	}
	/* NEXT LINES SHOULD NEVER EXECUTE! */
	XCloseDisplay(dpy);
	iw_sockets_close(skfd);
	return 0;
}
