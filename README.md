## Measuring Fine Dust Particle Concentration implemented in C

`dustmeter` is an application to read out data from a SDS011 fine dust paticle
sensor. It formats the results for showing them in a web site and transfers these
information via ftp push to a web server.

## Why Doing Another Program For This?

1. I like to write hardware realted programs by myself.
2. This application shall run on a [Raspberry Pis](https://www.raspberrypi.org/),
it is not provided for anything else (but porting may be possible).
3. The sensor is attached to the RaspPi directly. For the first tests via USB
adapter, in the final version using a serial port. No intelligence or WLAN e.g.
is needed.
4. This application must fit into my own personal hardware environment and to
the necessities of my web page.
5. I have my own idea on how code should be implemented.

## Keep In Mind

`dustmeter` is a command line based application that is able to run as a systemd
service too - and should do so.

## Requirements

- C language developtment tools
- `curl` library (runtime and development)

### More to Come . . .
