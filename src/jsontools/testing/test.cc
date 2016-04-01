// Ourselves:
#include <jsontools/testing/test.h>

// Standard library:
#include <iostream>

// This project:
#include <jsontools/config.h>
#include <jsontools/core.h>
#include <jsontools/node.h>
#include <jsontools/base_type_converters.h>
#include <jsontools/std_type_converters.h>
#include <jsontools/serdes.h>
#include <jsontools/iofile.h>

#if BXJSONTOOLS_WITH_BOOST == 1
// Boost:
#include <boost/optional.hpp>
#include <boost/lexical_cast.hpp>
#include <jsontools/boost_type_converters.h>
#endif // BXJSONTOOLS_WITH_BOOST == 1

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
#if BXJSONTOOLS_WITH_BOOST == 1
        _maybe_ = boost::none;
#endif // BXJSONTOOLS_WITH_BOOST == 1
        return;
      }

#if BXJSONTOOLS_WITH_BOOST == 1
      void set_maybe(int mb_)
      {
        _maybe_ = mb_;
        return;
      }
#endif // BXJSONTOOLS_WITH_BOOST == 1

      void print(std::ostream & out_) const
      {
        out_ << "Class A : " << std::endl;
        out_ << "|-- name : '" << _name_ << "'" << std::endl;
        out_ << "|-- x : '" << _x_ << "'" << std::endl;
        out_ << "|-- values : [" << _values_.size() << "]" << std::endl;
#if BXJSONTOOLS_WITH_BOOST == 1
        out_ << "|-- maybe : ";
        if (_maybe_) {
          out_ << _maybe_.get();
        } else {
          out_ << "<none>";
        }
        out_ << std::endl;
#endif // BXJSONTOOLS_WITH_BOOST == 1
        out_ << "`-- dict : [" << _dict_.size() << "]" << std::endl;
        return;
      }

      void serialize(jsontools::node & node_, unsigned long int version_ = 0)
      {
        node_["name"]   % _name_;
        node_["x"]      % _x_;
        node_["values"] % _values_;
        node_["dict"]   % _dict_;
#if BXJSONTOOLS_WITH_BOOST == 1
        node_["maybe"]  % _maybe_;
#endif // BXJSONTOOLS_WITH_BOOST == 1
        return;
      }

    private:

      std::string _name_;
      uint32_t _x_;
      std::vector<double> _values_;
      std::map<std::string, int> _dict_;
#if BXJSONTOOLS_WITH_BOOST == 1
      boost::optional<int32_t> _maybe_;
#endif // BXJSONTOOLS_WITH_BOOST == 1

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
        node_["many"] % _many_;
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
      std::clog << "\ntest::run_test_0: \n" ;
      A a1;
#if BXJSONTOOLS_WITH_BOOST == 1
      a1.set_maybe(666);
#endif // BXJSONTOOLS_WITH_BOOST == 1
      std::clog << "a1 = \n";
      a1.print(std::clog);
      jsontools::store("test-jsontools-file_0.json", a1);

      A a2;
      a2.reset();
      std::clog << "a2 = \n";
      a2.print(std::clog);
      jsontools::load("test-jsontools-file_0.json", a2);
      std::clog << "a2 = \n";
      a2.print(std::clog);

      return;
    }

    // static
    void test::run_test_1()
    {
      std::clog << "\ntest::run_test_1: \n" ;
      B b1;
      for (int i = 0; i < 4; i++) {
        A a1;
#if BXJSONTOOLS_WITH_BOOST == 1
        if (i % 2) {
          a1.set_maybe(333 - i);
        }
#endif // BXJSONTOOLS_WITH_BOOST == 1
        b1.add(a1);
      }
      std::clog << "b1 = \n";
      b1.print(std::clog);
      jsontools::store("test-jsontools-file_1.json", b1);

      B b2;
      jsontools::load("test-jsontools-file_1.json", b2);
      std::clog << "b2 = \n";
      b2.print(std::clog);

      return;
    }

    // static
    void test::run_test_2()
    {
      std::clog << "\ntest::run_test_2: \n" ;
      std::map<std::string, B> bees;

      B b1;
      for (int i = 0; i < 4; i++) {
        A a1;
#if BXJSONTOOLS_WITH_BOOST == 1
        if (i % 2) {
          a1.set_maybe(666 - i);
        }
#endif // BXJSONTOOLS_WITH_BOOST == 1
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
      std::clog << "\ntest::run_test_3: \n" ;
      std::map<std::string, bar::Foreign> fees;
      fees["f0"] = bar::Foreign(+1.0, -2.0);
      fees["f1"] = bar::Foreign(-3.0, +0.5);
      fees["f2"] = bar::Foreign(+2.0, -1.0);
      std::clog << "fees = \n";
      for (auto f : fees) {
        std::clog << f.first << " : " << f.second << std::endl;
      }
      jsontools::store("test-jsontools-file_3.json", fees);

      fees.clear();
      jsontools::load("test-jsontools-file_3.json", fees);
      std::clog << "fees = \n";
      for (auto f : fees) {
        std::clog << f.first << " : " << f.second << std::endl;
      }

      return;
    }

    // static
    void test::run_test_4()
    {
      std::clog << "\ntest::run_test_4: \n" ;
#if BXJSONTOOLS_WITH_BOOST == 1
      std::map<std::string, boost::posix_time::ptime> times;
      for (int i = 0; i < (int) 7; i++) {
        boost::posix_time::ptime t(boost::posix_time::microsec_clock::local_time());
        if (i == 3) {
          t = boost::posix_time::ptime(boost::posix_time::neg_infin);
        } else if (i == 4) {
          t = boost::posix_time::ptime(boost::posix_time::pos_infin);
        } else if (i == 5) {
          t = boost::posix_time::ptime(boost::posix_time::not_a_date_time);
        }
        times["t" + boost::lexical_cast<std::string>(i)] = t;
      }
      std::clog << "times = \n";
      for (auto t : times) {
        std::clog << t.first << " : " << boost::posix_time::to_simple_string(t.second) << std::endl;
      }
      jsontools::store("test-jsontools-file_4.json", times);

      times.clear();
      jsontools::load("test-jsontools-file_4.json", times);
      std::clog << "times = \n";
      for (auto t : times) {
        std::clog << t.first << " : " << boost::posix_time::to_simple_string(t.second) << std::endl;
      }

      {
        boost::posix_time::time_period tp(boost::posix_time::microsec_clock::local_time(),
                                          boost::posix_time::microsec_clock::local_time() +
                                          boost::posix_time::seconds(10));
        std::clog << "tp : " << boost::posix_time::to_simple_string(tp) << std::endl;
        jsontools::store("test-jsontools-file_4bis.json", tp);
      }

      {
        boost::posix_time::time_period tp(boost::posix_time::microsec_clock::local_time(),
                                          boost::posix_time::microsec_clock::local_time() -
                                          boost::posix_time::seconds(1));
        jsontools::load("test-jsontools-file_4bis.json", tp);
        std::clog << "tp : " << boost::posix_time::to_simple_string(tp) << std::endl;
      }

      {
        boost::posix_time::time_period tp(boost::posix_time::microsec_clock::local_time(),
                                          boost::posix_time::microsec_clock::local_time() -
                                          boost::posix_time::seconds(1));
        std::clog << "tp : " << boost::posix_time::to_simple_string(tp) << std::endl;
        jsontools::store("test-jsontools-file_4ter.json", tp);
      }

      {
        boost::posix_time::time_period tp(boost::posix_time::microsec_clock::local_time(),
                                          boost::posix_time::microsec_clock::local_time() +
                                          boost::posix_time::seconds(1));
        jsontools::load("test-jsontools-file_4ter.json", tp);
        std::clog << "tp : " << boost::posix_time::to_simple_string(tp) << std::endl;
      }

#endif // BXJSONTOOLS_WITH_BOOST == 1

      return;
    }

  } // end of namespace testing

} // end of namespace jsontools
