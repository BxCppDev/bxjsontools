# bxjsontools

bxjsontools - Tools for JSON serialization (C++ library)

The     ``bxjsontools``    library     (also    ``BxJsontools``     or
``Bayeux/Jsontools``) consists in  a set of C++  classes and utilities
for JSON based serialization of simple classes.

bxjsontools   allows  you   to   add   JSON  based   (de)serialization
functionalities  to your  classes, as  long as  they are  defined from
supported types  (typically scalar attributes): C++  base types (bool,
integer and  real numbers),  enumerations, commonly used  C++ template
containers   (std::string,  std::vector<>,   std::list<>,  std::map<>,
std::array<>...).  Support for a few classes from the Boost library is
also implemented.  It is possible to extend the JSON (de)serialization
functionalities    to   more    (complex)   types,    using   template
specialization.

bxjsontools serialization is available for standard I/O streams.

This is a very preliminary work that needs more development and tests.

bxjsontools  aims  to be  integrated  as  a  companion module  of  the
https://github.com/BxCppDev/Bayeux                                 and
https://github.com/BxCppDev/Vire C++ libraries.

bxjsontools  has been  initiated  in the  framework  of the  SuperNEMO
physics experiment software.


## Dependencies and inspiration

bxjsontools makes use and is based on:

* the   [jsoncpp](https://github.com/open-source-parsers/jsoncpp)  C++
  library is amalgamated in bxjsontools source code.
* the [JsonSerializer](https://github.com/SGSSGene/JsonSerializer) C++
    library : large parts of the original code from JsonSerializer has
    been reused with some modifications (coding style, file splitting,
    minor changes in the interface, addons)

Needed tools and software (tested on Ubuntu 16.04/18.04/20.04 LTS):
* You  need  [CMake](https://cmake.org/)   version  >=  3.5.1  (former
  version may work)
* You need gcc version >= 5.4.0 (former version may work)
* bxjsontools  depends   on  [Boost](http://www.boost.org/)   >=  1.58
  (former version may work).

## License:

See the ``LICENSE.txt`` file and the ``licensing`` directory.


## Build and install:

The  following  instructions  illustrate  how  to  build  and  install
bxjsontools on a Linux  system (tested: Ubuntu 16.04/18.04/20.04 LTS).
It should be easy to adapt for a MacOS X system.

CMake option(s):

* ``BXJSONTOOLS_ENABLE_TESTING`` (default: ``ON``) : builds the test program(s).

### Note on Boost:

bxjsontools implements some specific  JSON serialization support for a
few Boost classes of interest (implies Boost >=1.58 dependency):

* ``boost::optional<T>``
* ``boost::posix_time::ptime``
* ``boost::posix_time::time_period``

In  principle  bxjsontools  can  build  both  with  a  *system*  Boost
installation (version  1.58 on Ubuntu  16.04 resolved by  the standard
``FindBoost.cmake`` script  using the ``find_package``  *MODULE* mode)
or  with  a   Boost  installation  provided  by   the  user  (example:
[Linuxbrew](http://linuxbrew.sh/)).

### Download the source code from GitHub:

In the following  we use ``/tmp`` as the base  working directory. Feel
free to change it to somewhere else (your ``${HOME}`` dir, ``/opt``...).

```sh
$ mkdir -p /tmp/${USER}/bxjsontools/_source.d/
$ cd /tmp/${USER}/bxjsontools/_source.d/
$ git clone https://github.com/BxCppDev/bxjsontools.git
```

### Install dependencies:

Make sure you have a proper installation of the Boost library (>=1.58)
on your system.

Suggestion for Ubuntu 16.04:
```sh
$ sudo apt-get install cmake
$ sudo apt-get install g++
$ sudo apt-get install libboost-all-dev
```

Boost may also be installed from linuxbrew/homebrew or Spack.

### Build the library from a dedicated directory:

Instructions to build bxjsontools from a working build directory:
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

On Ubuntu 20.04, system Boost  1.71 is available from ``/usr/include``
and ``/usr/lib`` and  should be found automatically by  CMake.  If you
want to use  a specific version of Boost (for  example one provided by
Linuxbrew), you must  specify the proper path to help  CMake to locate
Boost files:

```sh
$ mkdir -p /tmp/${USER}/bxjsontools/_build.d/
$ cd  /tmp/${USER}/bxjsontools/_build.d/
$ cmake \
    -DCMAKE_INSTALL_PREFIX=/tmp/${USER}/bxjsontools/_install.d \
    -DBOOST_ROOT=/path/to/linuxbrew/installation/base/dir \
    /tmp/${USER}/bxjsontools/_source.d/bxjsontools
$ make
$ make test
$ make install
```

You can also use:

```sh
$ mkdir -p /tmp/${USER}/bxjsontools/_build.d/
$ cd  /tmp/${USER}/bxjsontools/_build.d/
$ cmake \
    -DCMAKE_INSTALL_PREFIX=/tmp/${USER}/bxjsontools/_install.d \
    -DBOOST_ROOT=$(brew --prefix) \
    /tmp/${USER}/bxjsontools/_source.d/bxjsontools
$ make
$ make test
$ make install
```

## Using bxjsontools:

* The ``bxjsontools-query``  utility allows you to  fetch informations
  about  your BxJsontools  installation.   You may  add the  following
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
  software.  The  CMake ``find_package(BxJsontools  REQUIRED CONFIG)``
  command can  be given  the following  variable to  successfully find
  BxJsontools on your system:

```sh
$ cmake ... -DBxJsontools_DIR="$(bxjsontools-query --cmakedir)" ...
```

* There are simple  examples in the source  repository that illustrate
  very simple usecases with a set of dummy classes.

## Example:

Extracted from example ``ex00``:

```c++
// Standard library:
#include <iostream>
#include <string>
#include <vector>
#include <map>

// Bayeux/jsontools:
#include <jsontools/jsontools.h>

// A class made serializable through the jsontools interface:
class A : public jsontools::i_jsonizable {
public:
  A() {
    _x_ = 0;
  }

  void set() {
    _name_ = "foo";
    _x_ = 42;
    _values_.push_back(1);
    _values_.push_back(2);
  }

  void reset() {
    _name_.clear();
    _x_ = 0;
    _values_.clear();
  }

  friend std::ostream & operator<<(std::ostream & out_, const A & a_) {
    out_ << '{' << "name='" << a_._name_ << "';x=" << a_._x_ << ";values=[";
    std::size_t count = 0;
    for (auto v : a_._values_) {
      out_ << v;
      if (++count < a_._values_.size()) out_ << ",";
    }
    out_ << "]}";
    return out_;
  }

  // The `magic' (de-)serialization interface method
  virtual void jsonize(jsontools::node & node_,
                       const unsigned long int /* version_ */ = 0) {
    node_["name"]   % _name_;
    node_["x"]      % _x_;
    node_["values"] % _values_;
  }

private:
  std::string         _name_;
  uint32_t            _x_;
  std::vector<double> _values_;
};

int main() {

  // Serialize/deserialize a STD container of a base type:
  std::vector<double> vec{1.0, 2.0, 3.0, 4.0};
  jsontools::store("file.json", vec);
  vec.clear();
  jsontools::load("file.json", vec); // It's back!

  // Serialize/deserialize a simple user class made JSON-izable:
  A a1;
  a1.set();
  std::cout << "a1=" << a1 << std::endl;
  std::cout << "a2=" << a2 << std::endl;
  std::cout << "serializing a1..." << std::endl;
  jsontools::store("file2.json", a1);
  std::cout << "deserializing a2..." << std::endl;
  A  a2;
  jsontools::load("file2.json", a2);
  std::cout << "a2=" << a2 << std::endl;
  // a1 and a2 are now the same

  // Serialize/deserialize a dictionary of JSON-izable user class:
  std::map<std::string, A> dict;
  dict["a1"] = a1;
  a1.reset();
  dict["a2"] = a2;
  dict["a3"] = a1;
  for (auto p : dict) {
    std::cout << p.first << " : " << p.second << std::endl;
  }
  std::cout << "serializing dict..." << std::endl;
  jsontools::store("file3.json", dict);
  std::cout << "reset dict..." << std::endl;
  dict.clear();
  std::cout << "deserializing dict..." << std::endl;
  jsontools::load("file3.json", dict);
  for (auto p : dict) {
    std::cout << p.first << " : " << p.second << std::endl;
  }
  return 0;
}
```
