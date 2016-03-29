// Ourselves:
#include <jsontools/testing/test.h>

// Standard library:
#include <iostream>

// This project:
#include <jsontools/jsontools.h>

namespace jsontools {

  namespace testing {

    class A
    {
    public:

      A()
      {
        _name_ = "foo";
        _x_ = 1234567;
        _values_ = {1.2, 3.4, 4.5};
        _dict_["a"] = 4;
        _dict_["b"] = 3;
        _dict_["c"] = 2;
        _dict_["d"] = 1;
        return;
      }

      void reset()
      {
        _name_.clear();
        _x_ = 0;
        _values_.clear();
        _dict_.clear();
        return;
      }

      void print(std::ostream & out_) const
      {
        out_ << "Class A : " << std::endl;
        out_ << "|-- name : '" << _name_ << "'" << std::endl;
        out_ << "|-- x : '" << _x_ << "'" << std::endl;
        out_ << "|-- values : [" << _values_.size() << "]" << std::endl;
        out_ << "`-- dict : [" << _dict_.size() << "]" << std::endl;
        return;
      }

      void serialize(jsontools::node & node_)
      {
        node_["name"]   % _name_ or "unknown"; //(de-)serialize name, if name is not set, set it to "unknown"
        node_["x"]      % _x_;
        node_["values"] % _values_;
        node_["dict"]   % _dict_;
        return;
      }

    private:

      std::string _name_;
      uint32_t _x_;
      std::vector<double> _values_;
      std::map<std::string, int> _dict_;

    };

    class B
    {
    public:

      B()
      {
        return;
      }

      void add(const A & a_)
      {
        _many_.push_back(a_);
        return;
      }

      void serialize(jsontools::node & node_)
      {
        node_["many"]   % _many_;
        return;
      }

    private:
      std::vector<A> _many_;
    };

    // static
    void test::run_test_0()
    {
      A a1;
      a1.print(std::clog);
      jsontools::store("test-jsontools-file.json", a1);

      A a2;
      a2.reset();
      a2.print(std::clog);
      jsontools::load("test-jsontools-file.json", a2);
      a2.print(std::clog);
      // a1 and a2 are now the same

      return;
    }

    // static
    void test::run_test_1()
    {
      B b1;
      for (int i = 0; i < 5; i++) {
        A a1;
        b1.add(a1);
      }
      jsontools::store("test-jsontools-file2.json", b1);

      B b2;
      jsontools::load("test-jsontools-file2.json", b2);

      return;
    }

  } // end of namespace testing

} // end of namespace jsontools
