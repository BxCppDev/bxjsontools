# bxjsontools

bxjsontools - Tools for JSON serialization (C++ library)

(bx)jsontools consists in a set of C++ classes and utilities
for JSON based serialization.  It aims to be integrated in
the Bayeux C++ library.

## Dependencies and inspiration

(bx)jsontools  is makes  use  or  is based  on:
* the jsoncpp library (https://github.com/open-source-parsers/jsoncpp)
is amalgamated in bxjsontools source code.
* the                      JsonSerializer                      library
  (https://github.com/SGSSGene/JsonSerializer)  : large  parts of  the
  code from  JsonSerializer has been  reused with a  few modifications
  (coding style, file splitting and minor changes in the interface).


## License:

See the LICENSE.txt file and the 'licensing' directory.


## Build and install:

The following instructions illustrate how to build and
install (bx)jsontools on a Linux system. It should be easy to adapt
for a MacOS X system.

1. Download the source code from GitHub:
```sh
$ mkdir -p /tmp/${USER}/bxjsontools/_source.d/
$ cd /tmp/${USER}/bxjsontools/_source.d/
$ git clone https://github.com/fmauger/bxjsontools.git
```
2. Build the library from a dedicated directory:
```sh
$ mkdir -p /tmp/${USER}/bxjsontools/_build.d/
$ cd  /tmp/${USER}/bxjsontools/_build.d/
$ cmake \
  -DCMAKE_INSTALL_PREFIX=${HOME}/sw/bxjsontool/install-0.1.0 \
  /tmp/${USER}/bxjsontools/_source.d/bxjsontools/
$ make
$ make test
$ make install
```
3. Enjoy (bx)jsontools from its installation directory:
```
$ LANG="C" tree ~/sw/bxjsontool/install-0.1.0
/home/{login}/sw/bxjsontool/install-0.1.0
|-- include
|   |-- json
|   |   |-- json-forwards.h
|   |   `-- json.h
|   `-- jsontools
|       |-- base_type_converters.h
|       |-- core.h
|       |-- exception.h
|       |-- i_jsonizable.h
|       |-- iofile-inl.h
|       |-- iofile.h
|       |-- jsontools.h
|       |-- node-inl.h
|       |-- node.h
|       |-- serdes.h
|       |-- std_type_converters.h
|       `-- test.h
|-- lib
|   `-- libjsontools.so
`-- share
    `-- jsontools-0.1.0
        |-- LICENSE.txt
        |-- examples
        |   `-- ex01
        |       |-- CMakeLists.txt
        |       |-- README.md
        |       |-- foo.cc
        |       |-- foo.h
        |       `-- prgfoo.cxx
        `-- licensing
            |-- JsonSerializer
            |   `-- LICENSE.txt
            |-- bxjsontools
            |   `-- LICENSE.txt
            `-- jsoncpp
                `-- LICENSE.txt
```
