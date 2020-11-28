#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <random>

#include "Array.h"

#define ARRAY_SIZE 10

int main(int argc, char *argv[]) {
    try {
        if (argc != 2) {
            std::cerr << "Usage: client <IOR> or <ior.txt>" << std::endl;
            return 1;
        }

        CORBA::ORB_var orbVar = CORBA::ORB_init(argc, argv);

        const char *ior;
        std::string iorStr;
        std::ifstream fior(argv[1]);
        if (fior.good()) {
            std::getline(fior, iorStr);
            ior = iorStr.c_str();
        } else ior = argv[1];

        CORBA::Object_var obj = orbVar->string_to_object(ior);

        SevenTest::Sender_var senderVar = SevenTest::Sender::_narrow(obj);

        if (CORBA::is_nil(senderVar)) {
            std::cerr << "Can't narrow reference" << std::endl;
            orbVar->destroy();
            return 1;
        }

        auto toSend = new SevenTest::DoubleArray;
        toSend->length(ARRAY_SIZE);
        for (int i = 0; i < ARRAY_SIZE; ++i) (*toSend)[i] = i;

        senderVar->send(*toSend, 96);

        for (int i = 0; i < toSend->length(); ++i) {
            std::cout << (*toSend)[i] << " ";
        }
        std::cout << std::endl;

        delete toSend;
        orbVar->destroy();
    } catch (CORBA::Exception &ex) {
        std::cerr << "Caught CORBA::Exception: " << ex._name() << std::endl;
    }

    return EXIT_SUCCESS;
}