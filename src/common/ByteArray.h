#ifndef CONEXAO98_BYTEARRAY_H
#define CONEXAO98_BYTEARRAY_H

#include <cstdint>
#include <vector>

class ByteArray {
private:
    std::vector<uint8_t> internalBuffer;
public:
    ByteArray();

    [[nodiscard]] char* data();
    [[nodiscard]] size_t size() const;

    void write(const void* data, size_t len);
    void clear();
};

#endif //CONEXAO98_BYTEARRAY_H