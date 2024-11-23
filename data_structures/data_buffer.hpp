#ifndef DATA_BUFFER_HPP
#define DATA_BUFFER_HPP

#include <vector>
#include <sstream>
#include <string>

class DataBuffer {
private:
    std::vector<char> buffer;
    mutable std::stringstream stream;

public:
    template <typename T>
    DataBuffer& operator<<(const T& data) {
        stream.clear();
        stream.str("");
        stream << data;
        std::string str = stream.str();
        buffer.insert(buffer.end(), str.begin(), str.end());
        return *this;
    }

    template <typename T>
    DataBuffer& operator>>(T& data) {
        stream.clear();
        stream.str(std::string(buffer.begin(), buffer.end()));
        stream >> data;
        size_t pos = stream.tellg();
        buffer.erase(buffer.begin(), buffer.begin() + pos);
        return *this;
    }

    void clear();

    size_t size() const ;
};

#endif // DATA_BUFFER_HPP

