# cmake-a-tutorial
Following the tutorial at https://whereisalan.dev/blog/cmake-tutorial/chapter-02-cmake-a-quick-primer

## Debug

### folder

```bash
cd build-debug
```

## configure

```bash
cmake .. -DCMAKE_BUILD_TYPE=Debug
```

## build

```bash
cmake --build .
```

## run

```bash
./HelloWorld
```

## test

```bash
ctest --verbose
```

## Release

### folder

```bash
cd build-release
```

## configure

```bash
cmake .. -DCMAKE_BUILD_TYPE=Release
```

## build

```bash
cmake --build .
```

## run

```bash
./HelloWorld
```

## test

```bash
ctest --verbose
```

## package

```bash
cpack
```
