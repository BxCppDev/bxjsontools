# bxjsontools example ex01

## Build example on Linux

```sh
$ mkdir -p /tmp/${USER}/bxjsontools/ex01/_build.d
$ cd /tmp/${USER}/bxjsontools/ex01/_build.d
$ cmake \
  -DCMAKE_INSTALL_PREFIX=../_install.d \
  -DCMAKE_FIND_ROOT_PATH="$(bxjsontools-query --prefix)" \
  -DBxJsontools_DIR="$(bxjsontools-query --cmakedir)" \
  $(bxjsontools-query --prefix)/share/BxJsontools-0.1.0/examples/ex01
$ make
$ make install
```

## Run example

```sh
$ ./prgfoo
$ cat f1.json
{
   "b" : true,
   "buf" : [ 75, 105, 110, 103, 32, 65, 114, 116, 104, 117, 114 ],
   "f64" : 3.14159265358979,
   "i16" : 42,
   "seq" : [
      {
         "label" : "Riri",
         "value" : 0
      },
      {
         "label" : "Fifi",
         "value" : 10
      },
      {
         "label" : "Loulou",
         "value" : 23
      }
   ],
   "str" : "Hello, JSON!",
   "u32" : 1000000
}
```
