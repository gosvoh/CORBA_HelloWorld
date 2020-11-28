//
// Created by gosvoh on 28.11.2020.
//

// & - адрес в памяти

#include "Array.h"
#include <iostream>

class SenderImpl : public POA_SevenTest::Sender {
public:
    SenderImpl() {};
    void send(::SevenTest::DoubleArray& Array, ::CORBA::Double constanta) override {
        Array.length(Array.length() + 1);
        Array[Array.length() - 1] = constanta;
    };
};