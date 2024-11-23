#include "data_buffer.hpp"

void DataBuffer::clear()
{
    buffer.clear();
    stream.clear();
    stream.str("");
}

size_t DataBuffer::size() const
{
    return buffer.size();
}