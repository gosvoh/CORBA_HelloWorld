#include <iostream>
#include <fstream>
#include "Hello.h"

class Server : public POA_Hello {
    const char *helloString = "Hello World";
public:
    inline Server() {}

    virtual ~Server() {}

    virtual char *say_hello();
};

char *Server::say_hello() {
    std::cout << "Saying Hello" << std::endl;
    return CORBA::string_dup(helloString);
}

int main(int argc, char **argv) {
    try {
        CORBA::ORB_var orbVar = CORBA::ORB_init(argc, argv);
        CORBA::Object_var objectVar = orbVar->resolve_initial_references("RootPOA");
        PortableServer::POA_var poaVar = PortableServer::POA::_narrow(objectVar);

        PortableServer::Servant_var<Server> server = new Server();

        poaVar->activate_object(server);

        CORBA::String_var sior(orbVar->object_to_string(server->_this()));
        std::cout << sior << std::endl;
        std::ofstream fior("ior.txt");
        fior << sior;
        fior.close();

        PortableServer::POAManager_var poaManagerVar = poaVar->the_POAManager();

        poaManagerVar->activate();

        orbVar->run();
        orbVar->destroy();
    } catch (CORBA::Exception &ex) {
        std::cerr << "Caught CORBA::Exception: " << ex._name() << std::endl;
    }

    return EXIT_SUCCESS;
}