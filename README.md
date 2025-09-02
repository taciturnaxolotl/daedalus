# Daedalus

a combo repo for a vim plugin that interfaces with the [daedalus](https://github.com/geschmit/daedalus-hardware) rp2350 board and the firmware that allows that interface.

![a media offline screen from davinci resolve](https://hc-cdn.hel1.your-objectstorage.com/s/v3/8744661d883d695adc6b14a17a52ac8970d7c2dd_image.png)

# Usage

So the orginal goal was for keystrokes to make a nice pattern in your status bar as well as on the led matrix of daedalus but I couldn't get the serial to work from vim; not entirely sure why but it really doesn't like this for some reason.

What I do have instead is firmware for random led blinking when a serial character is detected and a vim plugin that displays random braille characters in the status bar.

You can read the [plugin](/lua/braille_indicator/README.md) for more information on installation and for the firmware you can use any serial interface set to a `115200` baud rate (screen for example `screen /dev/tty.usbmodem101 115200`).

<p align="center">
	<img src="https://raw.githubusercontent.com/taciturnaxolotl/carriage/main/.github/images/line-break.svg" />
</p>

<p align="center">
	<i><code>&copy 2025-present <a href="https://github.com/taciturnaxolotl">Kieran Klukas</a></code></i>
</p>

<p align="center">
	<a href="https://github.com/taciturnaxolotl/daedalus/blob/main/LICENSE.md"><img src="https://img.shields.io/static/v1.svg?style=for-the-badge&label=License&message=MIT&logoColor=d9e0ee&colorA=363a4f&colorB=b7bdf8"/></a>
</p>
