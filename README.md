# Lightdm related ports for FreeBSD

I have created lightdm related ports, e.g. web-greeter, lightdm-gtk-greeter and themes.
You can download these files and overwrite ports tree, or use ports overlays method.
I recommend using ports overlays method.

## ports overlay method

Add in your `/etc/make.conf` as follows:

`OVERLAYS+=/your/download/directory/lightdm-related-ports`
