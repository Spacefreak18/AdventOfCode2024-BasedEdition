# ADVENT OF CODE 2024 - BASED EDITION

## Dependencies
- argtable2
- orcania
- yder
- [helper](https://github.com/spacefreak18/helper)

## Building
This code depends on my based af utility functions helper library [repo](https://github.com/spacefreak18/helper).
```
git submodule sync --recursive
git submodule update --init --recursive
```

Then to compile simply navigate to a day's folder and run:
```
gcc -lyder -lorcania -largtable2 ../helper/*.c ../helper/*.h adventXX.c
```
where XX is the specific day

## Valgrind
```
valgrind ./a.out
```

## ToDo
 - add parameter to run tests
 - global compile, run, and test, maybe, with cmake or nob maybe
