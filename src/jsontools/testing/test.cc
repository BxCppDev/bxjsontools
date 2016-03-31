// Ourselves:
#include <jsontools/testing/test.h>

// Standard library:
#include <iostream>

// This project:
#include <jsontools/jsontools.h>

namespace bar {

  /// A foreign class with no embedded JSON-serialization method
  class Foreign
  {
  public:
    Foreign() : _x_(0.0), _y_(0.0) {}
    Foreign(double x_, double y_) : _x_(x_), _y_(y_) {}
    double get_x() const { return _x_; }
    double get_y() const { return _y_; }
    double & grab_x() { return _x_; }
    double & grab_y() { return _y_; }
    void zero() {
      _x_ = 0.0;
      _y_ = 0.0;
      return;
    }
    friend std::ostream & operator<<(std::ostream & out_, const Foreign & f_)
    {
      out_ << "{x=" << f_._x_<< ";y=" << f_._y_ << "}";
      return out_;
    }
  private:
    double _x_;
    double _y_;
  };

} // namespace bar

namespace jsontools {

  /// A JSON converter dedicated to the foreign class
  template<>
  class converter<bar::Foreign>
  {
  public:

    static void serialize(node & node_, bar::Foreign & f_)
    {
      node_.grab_value() = Json::objectValue;
      {
        Json::Value & xValue = node_.grab_value()["x"];
        node_value newNode(xValue, node_.is_serializing(), false);
        newNode % f_.grab_x();
      }
      {
        Json::Value & yValue = node_.grab_value()["y"];
        node_value newNode(yValue, node_.is_serializing(), false);
        newNode % f_.grab_y();
      }
      return;
    }

    static void deserialize(node & node_, bar::Foreign & f_)
    {
      if (not node_.get_value().isObject()) {
        throw wrong_type(node_.get_value(), "expected object!");
      }
      {
        Json::Value & xValue = node_.grab_value()["x"];
        node_value newNode(xValue, node_.is_serializing(), false);
        newNode % f_.grab_x();
      }
      {
        Json::Value & yValue = node_.grab_value()["y"];
        node_value newNode(yValue, node_.is_serializing(), false);
        newNode % f_.grab_y();
      }
      return;
    }

  };

} // namespace jsontools

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

      void serialize(jsontools::node & node_, unsigned long int version_ = 0)
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

      void serialize(jsontools::node & node_, unsigned long int version_ = 0)
      {
        node_["many"]   % _many_;
        return;
      }

      void print(std::ostream & out_) const
      {
        out_ << "Class B : " << std::endl;
        out_ << "`-- many : [" << _many_.size() << "]" << std::endl;
        for (auto a : _many_) {
          out_ << "   item : ";
          a.print(out_);
        }
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
      jsontools::store("test-jsontools-file_0.json", a1);

      A a2;
      a2.reset();
      a2.print(std::clog);
      jsontools::load("test-jsontools-file_0.json", a2);
      a2.print(std::clog);
      // a1 and a2 are now the same

      return;
    }

    // static
    void test::run_test_1()
    {
      B b1;
      for (int i = 0; i < 4; i++) {
        A a1;
        b1.add(a1);
      }
      b1.print(std::clog);
      jsontools::store("test-jsontools-file_1.json", b1);

      B b2;
      jsontools::load("test-jsontools-file_1.json", b2);
      b2.print(std::clog);

      return;
    }

    // static
    void test::run_test_2()
    {
      std::map<std::string, B> bees;

      B b1;
      for (int i = 0; i < 4; i++) {
        A a1;
        b1.add(a1);
      }
      bees["riri"] = b1;
      bees["fifi"] = b1;
      bees["loulou"] = b1;
      jsontools::store("test-jsontools-file_2.json", bees);

      bees.clear();
      jsontools::load("test-jsontools-file_2.json", bees);

      return;
    }

    // static
    void test::run_test_3()
    {
      std::map<std::string, bar::Foreign> fees;
      fees["f0"] = bar::Foreign(+1.0, -2.0);
      fees["f1"] = bar::Foreign(-3.0, +0.5);
      fees["f2"] = bar::Foreign(+2.0, -1.0);
      for (auto f : fees) {
        std::clog << f.first << " : " << f.second << std::endl;
      }

      jsontools::store("test-jsontools-file_3.json", fees);

      fees.clear();
      jsontools::load("test-jsontools-file_3.json", fees);
      for (auto f : fees) {
        std::clog << f.first << " : " << f.second << std::endl;
      }

      return;
    }

  } // end of namespace testing

} // end of namespace jsontools
