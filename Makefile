LIBS = -lomnithread -lomniORB4

#STUBS = HelloSK.cpp
#STUB_HEADERS = Hello.h

STUBS = ArraySK.cpp
STUB_HEADERS = Array.h
IMPLS = SenderImpl.cpp

all: client server

#$(STUBS): Hello.idl
#	omniidl -bcxx -Wbh='.h' -Wbs='SK.cpp' Hello.idl

$(STUBS): Array.idl
	omniidl -bcxx -Wbh='.h' -Wbs='SK.cpp' Array.idl

server: server.cpp $(STUBS)
	g++ -o server $(LIBS) server.cpp $(STUBS) $(IMPLS)

client: client.cpp $(STUBS)
	g++ -o client $(LIBS) client.cpp $(STUBS) $(IMPLS)

clean:
	rm -f client server main $(STUBS) $(STUB_HEADERS)

main:
	g++ -o main main.cpp