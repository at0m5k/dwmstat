dwmstat
====
**Forked from Unia's dwmst:** https://github.com/Unia/dwmst

**Note: This was hardcoded for my system and may not work with yours without some modification.**

**Requirements:**
* `libX11`
* `alsa-lib`
* `wireless_tools`

Note that this makes extensive use of colors and powerline glyphs in the sprintf format strings. In order to get everything displaying properly, you will need a few more dependencies:
* dwm patched with Xft and statuscolors support.
* Either a patched font or fontconfig rule to display powerline glyphs.  
See Lokaltog's powerline [documentation](https://powerline.readthedocs.org/en/latest/installation/linux.html#font-installation).

To remove these dependencies, simply remove the colors and glyphs from the sprintf format strings.

**Installation:**

To build and install simply run:

	$ make
	# make clean install

If you wish to have dwmstat re-launch after suspending your computer, enable the systemd service file:
`systemctl enable dwmstat.service`

**Todo:**
* Minor code clean ups.
