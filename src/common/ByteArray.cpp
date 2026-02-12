#include "ByteArray.h"

ByteArray::ByteArray() {
    internalBuffer = std::vector<uint8_t>();
}

// Esse metodo não pode ser const pois quando eu for receber mensagens o recv vai
// precisar que o ponteiro não seja constante
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
