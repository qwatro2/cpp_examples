#include "readers_util.h"

LimitReader::LimitReader(std::unique_ptr<Reader> reader, size_t limit) : reader_(std::move(reader)), limit_(limit) {
}

size_t LimitReader::Read(char *buf, size_t len) {
    auto read_size = std::min(len, limit_);
    auto success_size = reader_->Read(buf, read_size);
    limit_ -= success_size;
    return success_size;
}

TeeReader::TeeReader(std::vector<std::unique_ptr<Reader>> readers) : readers_(std::move(readers)) {
}

size_t TeeReader::Read(char *buf, size_t len) {
    while (true) {
        if (current_ == readers_.size()) {
            return 0;
        }

        auto size = readers_[current_]->Read(buf, len);
        if (size == 0) {
            ++current_;
            continue;
        }

        return size;
    }
}

HexDecodingReader::HexDecodingReader(std::unique_ptr<Reader> reader) : reader_(std::move(reader)) {
}

size_t HexDecodingReader::Read(char *buf, size_t len) {
    std::string str(len * 2, '0');
    auto read_len = reader_->Read(&(str[0]), str.size());
    auto hex_to_dec = [](char digit) { return '0' <= digit && digit <= '9' ? digit - '0' : digit - '7'; };

    for (auto i = 0; i < read_len; i += 2) {
        buf[i / 2] = static_cast<char>(hex_to_dec(str[i]) << 4 | hex_to_dec(str[i + 1]));
    }

    return read_len / 2;
}