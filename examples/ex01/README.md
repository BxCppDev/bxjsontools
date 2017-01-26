# bxjsontools example ex01

## Build example on Linux

```sh
$ mkdir -p /tmp/${USER}/bxjsontools/ex01/_build.d
$ cd /tmp/${USER}/bxjsontools/ex01/_build.d
$ cmake \
  -DCMAKE_INSTALL_PREFIX=../_install.d \
  -DCMAKE_FIND_ROOT_PATH="$(bxjsontools-query --prefix)" \
  -DBxJsontools_DIR="$(bxjsontools-query --cmakedir)" \
  $(bxjsontools-query --exampledir)/ex01
$ make
$ make install
```

## Run example

```sh
$ ./prgfoo
$ cat f1.json
...
```
