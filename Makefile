LIBS = -lomnithread -lomniORB4
STUBS = HelloSK.cpp
STUB_HEADERS = Hello.h

all: client server

$(STUBS): Hello.idl
	omniidl -bcxx -Wbh='.h' -Wbs='SK.cpp' Hello.idl

server: server.cpp $(STUBS)
	g++ -o server $(LIBS) server.cpp $(STUBS)

client: client.cpp $(STUBS)
	g++ -o client $(LIBS) client.cpp $(STUBS)

clean:
	rm -f client server $(STUBS) $(STUB_HEADERS)
