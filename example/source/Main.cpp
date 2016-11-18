#include <cstdio>
#include <iostream>

#include "ExampleApplication.hpp"

int main(int argc, char* argv[])
{
    example::ExampleApplication app;
    app.create();
    app.run();
    app.destroy();
    return EXIT_SUCCESS;
}
