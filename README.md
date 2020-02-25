# Blinds

Automates window blinds (changing the angle of the slats) by pulling the pull cord.
Determines the limits by sensing a slowdown in the motor.
This is highly likely to rip the blinds off the window, so please don't use it.
Currently built for RaspberryPi (with Arduino/AVR in mind).

This is a work-in-progress. I plan on adding tests, Samsung SmartThings integration, and more documentation.

## Building

Depends on the wiringPi library.

```
mkdir cmake-build-cli
cd cmake-build-cli
cmake ..
make
```

The resulting executable is named `blinds`.

## Cross-compiling

I recommend cross-compiling with RaspberryPi's GCC distribution (see their
[instructions for cross-compiling the kernel](https://www.raspberrypi.org/documentation/linux/kernel/building.md)).
Install their toolchain:

```
git clone https://github.com/raspberrypi/tools ~/rpi/tools
```

Copy the RaspberryPi's root filesystem from the SD card to `~/rpi/rootfs` so you can
use its libraries. You'll need wiringPi to have been installed on the RaspberryPi first.

Create a CMake toolchain file at `~/rpi/Toolchain-RaspberryPi.cmake`
to use their compiler and your copied rootfs's libraries:

```
SET(CMAKE_SYSTEM_NAME Linux)
SET(CMAKE_SYSTEM_VERSION 1)
SET(CMAKE_C_COMPILER $ENV{HOME}/rpi/tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin/arm-linux-gnueabihf-gcc)
SET(CMAKE_CXX_COMPILER $ENV{HOME}/rpi/tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin/arm-linux-gnueabihf-g++)
SET(CMAKE_SYSROOT "$ENV{HOME}/rpi/rootfs")
SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
```

Finally, use the toolchain file when running CMake:

```
cmake -DCMAKE_TOOLCHAIN_FILE=~/rpi/Toolchain-RaspberryPi.cmake ..
make
```

If you're building on Debian/Ubuntu, it's also possible to get the ARM versions of the libraries on your own system
via their apt repository (rather than copying over the filesystem from the Raspberry Pi's SD card).
I intend to set up a Docker-based build which does that but for now I wanted to avoid library version mismatches.

# Hardware

I plan on adding more hardware details and photos here. Some of the key components:

* Raspberry Pi Zero W
* Motor:
  [Bringsmart 5840-555B DC 12V 27RPM with encoder](https://www.aliexpress.com/item/33016066564.html).
  Actually, that shipment has been held up because of the coronavirus
  so for now I'm using [uxcell DC 12V 7RPM with encoder](https://smile.amazon.com/gp/product/B078J521TG/).
  The rated torque and stall torque are important parameters in balancing wear on the motor vs.
  the ability to detect the end positions of the pull cord and the risk of ripping the blinds off the wall.
* Two buttons for manual control on the box.
