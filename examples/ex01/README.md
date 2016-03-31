# bxjsontools example ex01

## Build example on Linux

```sh
$ mkdir -p /tmp/${USER}/bxjsontools/ex01/_build.d
$ cd  /tmp/${USER}/bxjsontools/ex01/_build.d
$ cmake \
  -DCMAKE_INSTALL_PREFIX=../_install.d \
  -Djsontools_INCLUDE_DIRS="<jsontools-install-dir>/include" \
  -Djsontools_LIBRARIES="<jsontools-install-dir>/lib/libjsontools.so" \
   <jsontools-install-dir>/share/jsontools-0.1.0/examples/ex01
$ make
```

## Run example

```sh
$ ./prgfoo
$ cat f1.json
{
   "f64" : 3.14159265358979,
   "i16" : 42,
   "u32" : 1000000
}

```