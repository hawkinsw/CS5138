## Climatology 101 -- A Forecast for VTables

### Compiling

You will need a compiler (`gcc`, `clang`), and `cmake`. On an Ubuntu-like system, you can get those with
the `build-essential` meta package:

```console
$ sudo apt-get install build-essential
$ sudo apt-get install clang
```

On a Fedora-like system, you can get those with a few group packages:
```console
$ sudo dnf groupinstall "Development Tools" "Development Libraries"
$ sudo dnf install cmake
```

You can build the software with
```console
$ cmake -B build
$ cmake --build build
```

### Running

If everything above worked correctly, you can run the Forecasting software with

```console
$ ./build/VtablesClimate
```

