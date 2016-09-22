// Standard library:
#include <exception>
#include <cstdlib>
#include <iostream>
#include <fstream>

// This project:
#include <foo.h>

// - Bayeux/jsontools:
#include <jsontools/iofile.h>

void ex01();

int main(void)
{
  int error_code = EXIT_SUCCESS;
  try {

    ex01();

  } catch (std::exception & x) {
    std::cerr << "ERROR: " << x.what() << std::endl;
    error_code = EXIT_FAILURE;
  } catch (...) {
    std::cerr << "ERROR: " << "Unexpected exception!" << std::endl;
    error_code = EXIT_FAILURE;
  }
  return error_code;
}

void ex01()
{

  {
    jsontools_ex01::foo f1;
    f1.set(true, 42, 1000000, 3.14159265358979, "Hello, JSON!");
    f1.append_buf('K');
    f1.append_buf('i');
    f1.append_buf('n');
    f1.append_buf('g');
    f1.append_buf(' ');
    f1.append_buf('A');
    f1.append_buf('r');
    f1.append_buf('t');
    f1.append_buf('h');
    f1.append_buf('u');
    f1.append_buf('r');
    f1.append_seq(jsontools_ex01::bar(0, "Riri"));
    f1.append_seq(jsontools_ex01::bar(10, "Fifi"));
    f1.append_seq(jsontools_ex01::bar(23, "Loulou"));
    f1.append_bar("book", jsontools_ex01::bar(42, "H2G2"));
    f1.append_bar("movie", jsontools_ex01::bar(472, "Holly Grail"));
    f1.append_bar("song", jsontools_ex01::bar(666, "Sad song"));
    std::clog << "\nf1 object to be JSON-ized: " << std::endl;
    f1.print(std::clog);
    jsontools::store("f1.json", f1);
  }

  {
    std::clog << "\nJSON file: " << std::endl;
    std::ifstream f1json("f1.json");
    while (f1json && !f1json.eof()) {
      std::string jsonline;
      std::getline(f1json, jsonline);
      std::clog << jsonline << std::endl;
      f1json >> std::ws;
    }
    std::clog << "EOF" << std::endl;
  }

  {
    jsontools_ex01::foo f1bis;
    jsontools::load("f1.json", f1bis);
    std::clog << "\nDe-JSON-ized f1 object: " << std::endl;
    f1bis.print(std::clog);
  }

  return;
}
