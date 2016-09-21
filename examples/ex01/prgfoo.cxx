// Standard library:
#include <exception>
#include <cstdlib>
#include <iostream>

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
    f1.set(42, 1000000, 3.14159265358979, "Hello, JSON!");
    std::clog << "f1: " << std::endl;
    f1.print(std::clog);
    jsontools::store("f1.json", f1);
  }

  {
    jsontools_ex01::foo f1bis;
    jsontools::load("f1.json", f1bis);
    std::clog << "f1bis: " << std::endl;
    f1bis.print(std::clog);
  }

  return;
}
