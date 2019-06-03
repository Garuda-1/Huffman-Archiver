#include "huffman_engine.hpp"
#include <vector>

huffman::bit_set::bit_set() : _size(0) {}

huffman::bit_set::bit_set(size_t size) : _size(size) {
    blocks.resize((size + block_size - 1) / block_size);
}

huffman::bit_set::bit_set(std::vector<char> &v) : _size(v.size() * block_size) {
    blocks.reserve(v.size());
    for (char byte : v) {
        blocks.push_back(static_cast<unsigned char>(byte));
    }
}

void huffman::bit_set::resize(size_t new_size) {
    blocks.resize((new_size + block_size - 1) / block_size);
    if (_size < new_size) {
        for (size_t i = _size; (i < new_size) && (i % block_size != 0); ++i) {
            set(i, false);
        }
    }
    _size = new_size;
}

void huffman::bit_set::set(size_t pos, bool value) {
    if (value) {
        blocks[pos / block_size] |= 1U << (pos % block_size);
    } else {
        blocks[pos / block_size] &= ~(1U << (pos % block_size));
    }
}

void huffman::bit_set::push_back(bool value) {
    resize(size() + 1);
    set(size() - 1, value);
}

void huffman::bit_set::pop_back() {
    resize(size() - 1);
}

void huffman::bit_set::clear() {
    blocks.clear();
    _size = 0;
}

bool huffman::bit_set::operator[](size_t pos) {
    return (static_cast<size_t>(blocks[pos / block_size]) >> (pos % block_size)) & (uint8_t) 1;
}

size_t huffman::bit_set::size() {
    return _size;
}

void huffman::bit_set::append_and_flush(huffman::bit_set &that, std::vector<char> &dest, size_t flush_size) {
    for (size_t i = 0; i < that.size(); ++i) {
        if (_size == block_size * flush_size) {
            for (uint8_t block : blocks) {
                dest.push_back(static_cast<char>(block));
            }
            clear();
        }
        push_back(that[i]);
    }
}

void huffman::bit_set::flush(std::vector<char> &dest) {
    for (unsigned char block : blocks) {
        dest.push_back(static_cast<char>(block));
    }
}

std::string to_string(huffman::bit_set &a) {
    std::string ret;
    for (size_t i = 0; i < a.size(); i++) {
        ret += (a[i] ? '1' : '0');
    }
    return ret;
}