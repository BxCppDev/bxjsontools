# bxjsontools example ex01

## Build example on Linux

```sh
mkdir _build.d/
cd  _build.d/
cmake \
  -DCMAKE_INSTALL_PREFIX=../_install.d \
  -Djsontools_INCLUDE_DIRS="<jsontools-install-include-dir>" \
  -Djsontools_LIBRARIES="<jsontools-install-lib-dir>/libjsontools.so" \
  ..
make
```
