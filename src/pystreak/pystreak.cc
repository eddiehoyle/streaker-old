#include <boost/python.hpp>

char const* greet()
{
    return "hello, world";
}

BOOST_PYTHON_MODULE(libpystreak)
{
    using namespace boost::python;
    def("greet", greet);
}