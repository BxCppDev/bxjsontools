# bxjsontools

bxjsontools - Tools for JSON serialization (C++ library)

The     ``bxjsontools``     library     (also   ``BxJsontools``     or
``Bayeux/Jsontools``) consists in  a set of C++  classes and utilities
for JSON based serialization.  It aims to be integrated as a companion
module  of the  Bayeux  C++  library (the  foundation  library of  the
SuperNEMO physics experiment's software).

This is a very preliminary work that needs more development and tests.

bxjsontools  has been  initiated  in the  framework  of the  SuperNEMO
physics experiment software.

**Note for SuperNEMO users**:

JSON serialization is  used by the Vire C++  library for communication
between C++  implemented services,  Java based Control  and Monitoring
System (CMS) servers  and external services (RabbitMQ  server) for the
SuperNEMO experiment.


## Dependencies and inspiration

bxjsontools makes use and is based on:

* the jsoncpp C++ library (https://github.com/open-source-parsers/jsoncpp)
  is amalgamated in bxjsontools source code.

* the              JsonSerializer             C++              library
  (https://github.com/SGSSGene/JsonSerializer)  : large  parts of  the
  original code from  JsonSerializer has been  reused with some modifications
  (coding style, file splitting, minor changes in the interface, addons)

Needed tools and software (tested on Ubuntu 16.04 LTS):
* You need CMake version >= 3.6.1 (former version may work)
* You need gcc version >= 5.4.0 (former version may work)
* bxjsontools depends on Boost >= 1.58 (former version may work).

## License:

See the ``LICENSE.txt`` file and the ``licensing`` directory.


## Build and install:

The  following  instructions  illustrate  how  to  build  and  install
bxjsontools on a  Linux system (tested: 16.04 LTS).  It should be
easy to adapt for a MacOS X system.

CMake option(s):

* ``BXJSONTOOLS_ENABLE_TESTING`` (default: ``ON``) : builds the test program(s).

### Note on Boost:

bxjsontools implements some specific  JSON serialization support for a
few Boost classes of interest (implies Boost 1.58 dependency):

* ``boost::optional<T>`` (for optional records in Vire message's header and/or body)
* ``boost::posix_time::ptime`` (for Vire message timestamping)
* ``boost::posix_time::time_period`` (for Vire agenda reservation/scheduling)

In  principle  bxjsontools   can  build  both  with   a  system  Boost
installation (version  1.58 on Ubuntu  16.04 resolved by  the standard
``FindBoost.cmake`` script  using the ``find_package``  *MODULE* mode)
or with  a Boost  installation provided  by Cadfaelbrew  (version 1.60
resolved  from  a  dedicated ``BoostConfig.cmake``  script  using  the
``find_package`` *CONFIG* mode).

### Download the source code from GitHub:
```sh
$ mkdir -p /tmp/${USER}/bxjsontools/_source.d/
$ cd /tmp/${USER}/bxjsontools/_source.d/
$ git clone https://github.com/BxCppDev/bxjsontools.git
```
### Build the library from a dedicated directory:


Make sure you have a proper installation of the Boost library (>=1.58)
on your system.


**Note for SuperNEMO users:**

The SuperNEMO experiment data  processing and simulation software uses
Cadfaelbrew    (https://github.com/SuperNEMO-DBD/cadfaelbrew)    which
provides some core software tools  and libraries (C++ compiler, Boost,
GSL,  ROOT,  XercesC  libraries...).   Before  to  build  and  install
BxJsontools, you must switch to a ``brew`` shell before:

```sh
$ brew sh
```

Then:

```sh
$ mkdir -p /tmp/${USER}/bxjsontools/_build.d/
$ cd  /tmp/${USER}/bxjsontools/_build.d/
$ cmake \
    -DCMAKE_INSTALL_PREFIX=/tmp/${USER}/bxjsontools/_install.d \
    /tmp/${USER}/bxjsontools/_source.d/bxjsontools
$ make
$ make test
$ make install
```

## Using bxjsontools:

* The ``bxjsontools-query``  utility allows you to  fetch informations
  about  your  BxJsontools installation.  You  may  add the  following
  typical line in your ``~/.bashrc`` profile:

```sh
export PATH="/tmp/${USER}/bxjsontools/_install.d/bin:${PATH}"
```

This will  give you  access to the  ``bxjsontools-query`` command-line
utility:

```sh
$ bxjsontools-query --help
```

* CMake  configuration scripts  (i.e. ``BxJsontoolsConfig.cmake``  and
  ``BxJsontoolsConfigVersion.cmake``)   are    provided   for   client
  software.  The CMake  ``find_package(BxJsontools REQUIRED  CONFIG)``
  command can be given the  following variable to find the BxJsontools
  installation on your system:

```sh
$ cmake ... -DBxJsontools_DIR="$(bxjsontools-query --cmakedir)" ...
```

* There is  a simple example  ``ex01`` that illustrates a  very simple
  usecase.
