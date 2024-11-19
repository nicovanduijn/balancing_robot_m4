After cloning to set up your environment:

```
git submodule update --init --recursive
sudo apt install gcc-arm-none-eabi clang-format
./scripts/setup_vscode
```

To build for the device:

`make stm32mp1` 

to flash the device:

`make flash`

to build the simulation:

`make posix`