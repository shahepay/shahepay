
Debian
====================
This directory contains files used to package shahepayd/shahepay-qt
for Debian-based Linux systems. If you compile shahepayd/shahepay-qt yourself, there are some useful files here.

## shahepay: URI support ##


shahepay-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install shahepay-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your shahepay-qt binary to `/usr/bin`
and the `../../share/pixmaps/shahepay128.png` to `/usr/share/pixmaps`

shahepay-qt.protocol (KDE)

