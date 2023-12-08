# Building

Use commands below to build minimal example:

```bash
mkdir build
cd build
cmake -DPLATFORM_NAME=x86 ..
make
```

The minimal example should be build now:
```bash
$ ./examples/minimal/minimal
$ echo $?
0
```

# Build test
To build use commands below.

```bash
mkdir build/unit-test
cd build/unit-test
cmake -DPLATFORM_NAME=x86 -DBUILD_TESTS=ON ../..
make
ctest
```