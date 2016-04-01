# bxjsontools example ex01

## Build example on Linux

```sh
$ mkdir -p /tmp/${USER}/bxjsontools/ex01/_build.d
$ cd  /tmp/${USER}/bxjsontools/ex01/_build.d
$ cmake \
  -DCMAKE_INSTALL_PREFIX=../_install.d \
  -DCMAKE_FIND_ROOT_PATH="<bxjsontools-install-dir>" \
   <bxjsontools-install-dir>/share/BxJsontools-0.1.0/examples/ex01
$ make
```

[//]: # -DBxJsontools_DIR="<bxjsontools-install-dir>/lib/x86_64-linux-gnu/cmake/BxJsontools-0.1.0/" \

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
