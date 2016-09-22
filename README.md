# bxjsontools

bxjsontools - Tools for JSON serialization (C++ library)

The     ``bxjsontools``     library     (or     ``BxJsontools``     or
``Bayeux/Jsontools``) consists in  a set of C++  classes and utilities
for JSON based serialization.  It aims to be integrated as a companion
module  of the  Bayeux  C++  library (the  foundation  library of  the
SuperNEMO physics experiment's software).

JSON  serialization  will  be  used   by  the  Vire  C++  library  for
communication between C++ implemented  service, Java based Control and
Monitoring  System  (CMS)  servers  and  external  services  (RabbitMQ
server) for the SuperNEMO experiment.


## Dependencies and inspiration

bxjsontools makes use and is based on:
* the jsoncpp C++ library (https://github.com/open-source-parsers/jsoncpp)
is amalgamated in bxjsontools source code.
* the              JsonSerializer             C++              library
  (https://github.com/SGSSGene/JsonSerializer)  : large  parts of  the
  code from  JsonSerializer has been  reused with a  few modifications
  (coding style, file splitting, minor changes in the interface, addons)

Needed tools and software (tested on Ubuntu 14.04 LTS):
* You need CMake version >= 2.8 (former version may work)
* You need gcc version >= 4.8.4 (former version may work)
* By default, some bxjsontools' parts depends on Boost 1.54 (former version may work).
  This can be inhibited at configuration (see 'CMake options' below).

## License:

See the ``LICENSE.txt`` file and the ``licensing`` directory.


## Build and install:

The  following  instructions  illustrate  how  to  build  and  install
bxjsontools on a Linux system (Ubuntu  14.04/16.04 LTS). It should be easy
to adapt for a MacOS X system.

CMake options:

* ``BXJSONTOOLS_WITH_BOOST`` (default: ``ON``) : implements some
  specific JSON serialization support for some Boost classes (implies Boost 1.54 dependency).

  Supported classes are:

  * ``boost::optional<T>`` (for optional records in message's header and/or body)
  * ``boost::posix_time::ptime`` (for message timestamping)
  * ``boost::posix_time::time_period`` (for agenda reservation/scheduling)

* ``BXJSONTOOLS_ENABLE_TESTING`` (default: ``ON``) : builds the test program(s).


### Download the source code from GitHub:
```sh
$ mkdir -p /tmp/${USER}/bxjsontools/_source.d/
$ cd /tmp/${USER}/bxjsontools/_source.d/
$ git clone https://github.com/fmauger/bxjsontools.git
```
### Build the library from a dedicated directory:

For  SuperNEMO users  only:

The SuperNEMO experiment data  processing and simulation software uses
Cadfaelbrew    (https://github.com/SuperNEMO-DBD/cadfaelbrew)    which
provides some core software tools  and libraries (C++ compiler, Boost, GSL,
ROOT libraries...).  Before to build and install BxJsontools, you must
switch to a brew shell before:
```sh
$ brew sh
```

Then:
```sh
$ mkdir -p /tmp/${USER}/bxjsontools/_build.d/
$ cd  /tmp/${USER}/bxjsontools/_build.d/
$ cmake \
  -DCMAKE_INSTALL_PREFIX=${HOME}/sw/bxjsontools/install-0.1.0 \
  /tmp/${USER}/bxjsontools/_source.d/bxjsontools/
$ make
$ make test
$ make install
```

### Enjoy bxjsontools from its installation directory:
```sh
$ LANG="C" tree ${HOME}/sw/bxjsontools/install-0.1.0
/home/mauger/sw/bxjsontools/install-0.1.0
|-- bin
|   `-- bxjsontools-query
|-- include
|   `-- bayeux
|       |-- json
|       |   |-- json-forwards.h
|       |   `-- json.h
|       `-- jsontools
|           |-- base_type_converters.h
|           |-- boost_type_converters.h
|           |-- config.h
|           |-- core.h
|           |-- exception.h
|           |-- i_jsonizable.h
|           |-- iofile-inl.h
|           |-- iofile.h
|           |-- jsontools.h
|           |-- node-inl.h
|           |-- node.h
|           |-- serdes.h
|           |-- std_type_converters.h
|           `-- version.h
|-- lib
|   |-- cmake
|   |   `-- BxJsontools-0.1.0
|   |       |-- BxJsontoolsConfig.cmake
|   |       |-- BxJsontoolsConfigVersion.cmake
|   |       |-- BxJsontoolsTargets-noconfig.cmake
|   |       `-- BxJsontoolsTargets.cmake
|   `-- libBayeux_jsontools.so
`-- share
    `-- BxJsontools-0.1.0
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

## Using bxjsontools:

* The ``bxjsontools-query`` utility allows you to fetch informations about your
BxJsontools installation. You may add the following typical line in your
``~/.bashrc`` profile:
```sh
export PATH="${HOME}/sw/bxjsontools/install-0.1.0/bin:${PATH}"
```
This will give you access to the ``bxjsontools-query`` command-line utility:
```sh
$ bxjsontools-query --help
```

* CMake  configuration  scripts (``BxJsontoolsConfig.cmake``... for ``find_package(BxJsontools ... )``)   are
provided for client software.
* There is  a simple example  ``ex01`` that illustrates a  very simple
usecase.
