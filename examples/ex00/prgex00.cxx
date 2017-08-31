// Standard library:
#include <iostream>
#include <string>
#include <vector>
#include <map>

// Bayeux/jsontools:
#include <jsontools/jsontools.h>

// A class made serializable through the jsontools::i_jsonizable interface:
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

  // Main (de-)serialization interface method
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
  // (De-)Serialize a STD container of base type:
  std::vector<double> vec{1, 2, 3, 4};
  jsontools::store("file.json", vec);
  vec.clear();
  jsontools::load("file.json", vec); // It's back!

  // (De-)Serialize a simple user class made JSON-izable:
  A a1, a2;
  a1.set();
  std::cout << "a1=" << a1 << std::endl;
  std::cout << "a2=" << a2 << std::endl;
  std::cout << "serializing a1..." << std::endl;
  jsontools::store("file2.json", a1);
  std::cout << "deserializing a2..." << std::endl;
  jsontools::load("file2.json", a2);
  std::cout << "a2=" << a2 << std::endl;
  // a1 and a2 are now the same

  // (De-)Serialize a dictionary of JSON-izable user class:
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
