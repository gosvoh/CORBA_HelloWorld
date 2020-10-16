#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>

#include "Hello.h"

int main(int argc, char *argv[]) {
    try {
        if (argc != 2) {
            std::cerr << "Usage: client <IOR> or <ior.txt>" << std::endl;
            return 1;
        }
        CORBA::ORB_var orbVar = CORBA::ORB_init(argc, argv);

        const char *ior;
        std::string test;
        std::ifstream fior(argv[1]);
        if (fior.good()) {
            std::getline(fior, test);
            ior = test.c_str();
        } else ior = argv[1];
        CORBA::Object_var obj = orbVar->string_to_object(ior);

        Hello_var helloVar = Hello::_narrow(obj);

        if (CORBA::is_nil(helloVar)) {
            std::cerr << "Can't narrow reference" << std::endl;
            orbVar->destroy();
            return 1;
        }

        std::cout << helloVar->say_hello() << std::endl;
        orbVar->destroy();
    } catch (CORBA::Exception &ex) {
        std::cerr << "Caught CORBA::Exception: " << ex._name() << std::endl;
    }

    return EXIT_SUCCESS;
}
