#include <iostream>
#include <cassert>
#include <string>
#include "data_buffer.hpp"

void testIntSerialization() {
    std::cout << "Testing int serialization..." << std::endl;
    DataBuffer buffer;
    int original = 42;
    buffer << original;

    int deserialized = 0;
    buffer >> deserialized;

    assert(original == deserialized);
    assert(buffer.size() == 0);
    std::cout << "Int serialization test passed!" << std::endl;
}

void testFloatSerialization() {
    std::cout << "Testing float serialization..." << std::endl;
    DataBuffer buffer;
    float original = 3.14159f;
    buffer << original;

    float deserialized = 0.0f;
    buffer >> deserialized;

    assert(original == deserialized);
    assert(buffer.size() == 0);
    std::cout << "Float serialization test passed!" << std::endl;
}

void testStringSerialization() {
    std::cout << "Testing string serialization..." << std::endl;
    DataBuffer buffer;
    std::string original = "Hello, World!";
    buffer << original;

    std::string deserialized;
    buffer >> deserialized;

    assert(original == deserialized);
    assert(buffer.size() == 0);
    std::cout << "String serialization test passed!" << std::endl;
}

void testMultipleDataTypes() {
    std::cout << "Testing multiple data types..." << std::endl;
    DataBuffer buffer;
    int intVal = 42;
    float floatVal = 3.14159f;
    std::string strVal = "Hello, World!";

    buffer << intVal << floatVal << strVal;

    int deserializedInt;
    float deserializedFloat;
    std::string deserializedStr;

    buffer >> deserializedInt >> deserializedFloat >> deserializedStr;

    assert(intVal == deserializedInt);
    assert(floatVal == deserializedFloat);
    assert(strVal == deserializedStr);
    assert(buffer.size() == 0);
    std::cout << "Multiple data types test passed!" << std::endl;
}

void testPartialDeserialization() {
    std::cout << "Testing partial deserialization..." << std::endl;
    DataBuffer buffer;
    int intVal = 42;
    float floatVal = 3.14159f;

    buffer << intVal << floatVal;

    int deserializedInt;
    buffer >> deserializedInt;

    assert(intVal == deserializedInt);
    assert(buffer.size() > 0);
    std::cout << "Partial deserialization test passed!" << std::endl;
}

void testClear() {
    std::cout << "Testing clear method..." << std::endl;
    DataBuffer buffer;
    int intVal = 42;
    buffer << intVal;

    assert(buffer.size() > 0);
    buffer.clear();
    assert(buffer.size() == 0);
    std::cout << "Clear method test passed!" << std::endl;
}

int main() {
    testIntSerialization();
    testFloatSerialization();
    testStringSerialization();
    testMultipleDataTypes();
    testPartialDeserialization();
    testClear();

    std::cout << "All DataBuffer tests passed successfully!" << std::endl;
    return 0;
}
