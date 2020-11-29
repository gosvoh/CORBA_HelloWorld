//
// Created by gosvoh on 22.11.2020.
//

#include <iostream>
#include <fstream>
#include "Array.h"
#include "SenderImpl.cpp"

int main(int argc, char **argv) {
    try {
        CORBA::ORB_var orb = CORBA::ORB_init(argc, argv);
        CORBA::Object_var rpObj = orb->resolve_initial_references("RootPOA");
        PortableServer::POA_var rootPoa = PortableServer::POA::_narrow(rpObj);

        PortableServer::Servant_var<SenderImpl> server = new SenderImpl();
        rootPoa->activate_object(server);
        std::cout << "Root activated" << std::endl;

        CORBA::String_var sior(orb->object_to_string(server->_this()));
        std::cout << sior << std::endl;
        std::ofstream fior("ior.txt");
        fior << sior;
        fior.close();

        PortableServer::POAManager_var poaManagerVar = rootPoa->the_POAManager();

        poaManagerVar->activate();
        std::cout << "POA Mgr activated" << std::endl;

        orb->run();
        std::cout << "Run" << std::endl;
        orb->destroy();
        std::cout << "Destroy" << std::endl;
    } catch (CORBA::Exception &ex) {
        std::cerr << "Caught CORBA::Exception: " << ex._name() << std::endl;
    }

    return EXIT_SUCCESS;
}