
Debian
====================
This directory contains files used to package sctcd/sctc-qt
for Debian-based Linux systems. If you compile sctcd/sctc-qt yourself, there are some useful files here.

## sctc: URI support ##


sctc-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install sctc-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your sctc-qt binary to `/usr/bin`
and the `../../share/pixmaps/bitcoin128.png` to `/usr/share/pixmaps`

sctc-qt.protocol (KDE)

