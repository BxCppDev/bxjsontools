// Ourselves:
#include <foo.h>

// - Bayeux/jsontools:
#include <jsontools/enum_converter.h>
#include <jsontools/base_type_converters.h>
#include <jsontools/std_type_converters.h>
#include <jsontools/boost_type_converters.h>

namespace jsontools_ex01 {

  foo::foo()
  {
    _b_   = false;
    _i16_ = 0;
    _u32_ = 0;
    _f64_ = 0.0;
    _bz_  = BZ_INVALID;
    return;
  }

  foo::~foo()
  {
    return;
  }

  void foo::set(const bool b_,
                const int16_t i_,
                const uint32_t u_,
                const double d_,
                const std::string & str_)
  {
    _b_   = b_;
    _i16_ = i_;
    _u32_ = u_;
    _f64_ = d_;
    _str_ = str_;
    return;
  }

  void foo::set_timestamp(const boost::posix_time::ptime & t_)
  {
    _timestamp_ = t_;
    return;
  }

  void foo::set_bz(const baz & bz_)
  {
    _bz_ = bz_;
    return;
  }

  void foo::append_buf(const uint8_t c_)
  {
    _buf_.push_back(c_);
    return;
  }

  void foo::append_seq(const bar & b_)
  {
    _seq_.push_back(b_);
    return;
  }

  void foo::append_bar(const std::string & name_, const bar & b_)
  {
    _bars_[name_] = b_;
    return;
  }

  void foo::reset()
  {
    _b_ = false;
    _i16_ = 0;
    _u32_ = 0;
    _f64_ = 0.0;
    _str_.clear();
    _buf_.clear();
    _seq_.clear();
    _bars_.clear();
    _timestamp_ = boost::posix_time::ptime(boost::posix_time::not_a_date_time);
    _bz_ = BZ_INVALID;
    return;
  }

  void foo::print(std::ostream & out_, const std::string & indent_) const
  {
    out_.precision(15);
    out_ << indent_ << "|-- b   : " << _b_ << '\n';
    out_ << indent_ << "|-- i16 : " << _i16_ << '\n';
    out_ << indent_ << "|-- u32 : " << _u32_ << '\n';
    out_ << indent_ << "|-- f64 : " << _f64_ << '\n';
    out_ << indent_ << "|-- str : '" << _str_ << "'\n";

    out_ << indent_ << "|-- buf : [";
    std::size_t bufcount = 0;
    for (auto c : _buf_ ) {
      if (bufcount++ != 0) {
        out_ << ",";
      }
      out_ << (int) c;
    }
    out_ << "]\n";

    out_ << indent_ << "|-- seq : [";
    std::size_t seqcount = 0;
    for (const auto s : _seq_ ) {
      if (seqcount++ != 0) {
        out_ << ",";
      }
      out_ << '{' << s.value << ',' << s.label << '}';
    }
    out_ << "]\n";

    out_ << indent_ << "|-- bars : \n";
    std::size_t barcount = 0;
    for (const auto b : _bars_ ) {
      out_ << indent_ << "|   ";
      if (++barcount == _bars_.size()) {
        out_ << "`-- ";
      } else {
        out_ << "|-- ";
      }
      out_ << '"' << b.first << "\" : " << '{' << b.second.value << ',' << b.second.label << '}';
      out_ << '\n';
    }

    out_ << indent_ << "|-- timestamp : ["
         << boost::posix_time::to_iso_string(_timestamp_) << ']'
         << std::endl;

    out_ << indent_ << "`-- bz : [" << _bz_ << "]" << std::endl;

    return;
  }

  void foo::jsonize(jsontools::node & node_,
                    const unsigned long int /* version_ */)
  {
    node_["b"] % _b_;
    node_["i16"] % _i16_;
    node_["u32"] % _u32_;
    node_["f64"] % _f64_;
    node_["str"] % _str_;
    node_["buf"] % _buf_;
    node_["seq"] % _seq_;
    node_["bars"] % _bars_;
    node_["timestamp"] % _timestamp_;
    node_["bz"] % _bz_;
    return;
  }

} // end of namespace jsontools_ex01
