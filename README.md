# Flowtime Watch 🌀

The Flowtime Watch is an implementation of the [Flowtime](https://github.com/Ucodia/flowtime) on a classic Casio watch.

This project depends on the `movement` framework from the [Sensor Watch](https://github.com/joeycastillo/Sensor-Watch) project.

## Dependencies

To build this project, you need to install the `arm-none-eabi` variant of the Arm GNU Toolchain installed on your machine: [Arm GNU Toolchain Downloads](https://developer.arm.com/downloads/-/arm-gnu-toolchain-downloads)

## Building

After cloning this repository, make sure you have pulled the submodules for `sensor-watch` and its submodules.

```
git submodule update --init
cd sensor-watch
git submodule update --init
```

Hack: These files need to be removed as make does not seem to respect priority of header directory as defined in the Makefile

```
rm sensor-watch/movement/movement_config.h
rm sensor-watch/movement/movement_faces.h
```

Find which Sensor Watch board you are building for (RED, GREEN or BLUE), then run the following command by specifying the proper color

```
cd make
make COLOR=RED
```

## Testing

To test in the emulator, run the following command

```
cd make
emmake make COLOR=RED
python3 -m http.server -d build-sim
```

The emulator should be available at http://localhost:8000/watch.html

## Flashing

To flash your Sensor Watch with the Flowtime watch firmware, copy the `movement/make/build/watch.uf2` firmware file to your board. Read more in the official [Sensor Watch documentation](https://www.sensorwatch.net/docs/firmware/flashing/).