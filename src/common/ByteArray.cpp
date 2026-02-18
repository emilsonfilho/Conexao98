#include "ByteArray.h"

ByteArray::ByteArray() {
    internalBuffer = std::vector<uint8_t>();
}

ByteArray::ByteArray(const std::string &str): ByteArray() {
    write(str.c_str(), str.size());
}

ByteArray::~ByteArray() {
    clear();
}

const char* ByteArray::data() const {
    return reinterpret_cast<const char *>(internalBuffer.data());
}

char *ByteArray::data() {
    return reinterpret_cast<char *>(internalBuffer.data());
}

size_t ByteArray::size() const {
    return internalBuffer.size();
}

void ByteArray::write(const void *data, const size_t len) {
    const auto* start = static_cast<const uint8_t*>(data);

    internalBuffer.insert(internalBuffer.end(), start, start + len);
}

void ByteArray::clear() {
    internalBuffer.clear();
}
