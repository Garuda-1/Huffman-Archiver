#ifndef HUFFMAN_ARCHIVER_HUFFMAN_ENGINE_HPP
#define HUFFMAN_ARCHIVER_HUFFMAN_ENGINE_HPP

#include <vector>
#include <string>
#include <map>

namespace huffman {
    class bit_set {
        static const size_t block_size = 8;
        std::vector<unsigned char> blocks;
        size_t _size;

    public:
        bit_set();
        explicit bit_set(size_t size);
        explicit bit_set(std::vector<char> &v);

        void resize(size_t new_size);
        void set(size_t pos, bool value);
        void push_back(bool value);
        void pop_back();
        void clear();
        bool operator[](size_t pos);
        size_t size();
        void append_and_flush(huffman::bit_set &that, std::vector<char> &dest, size_t flush_size);
        void flush(std::vector<char> &dest);
    };

    struct tree {
        struct tree_node {
            std::vector<unsigned char> chars;
            uint64_t freq;
            size_t pos;
            size_t l_subtree;
            size_t r_subtree;

            tree_node(unsigned char c, uint64_t freq, size_t pos);
            tree_node(size_t l, size_t r, std::vector<tree_node> &order, size_t pos);
        };

        std::vector<tree_node> order;
        friend bool operator<(const tree::tree_node &a, const tree::tree_node &b);
        void code_table_dfs(size_t v, bit_set &cur, std::vector<bit_set> &ans);

        tree();

        void clear();
        void build(std::vector<uint64_t> frequencies);
        std::vector<bit_set> get_code_table();
    };

    bool operator<(const tree::tree_node &a, const tree::tree_node &b);

    struct huffman_archiver {
        std::vector<uint64_t> frequencies;
        bit_set bitwise_buffer;
        tree code_tree;
        std::vector<bit_set> code_table;
        std::vector<char> output_buffer;
        size_t pos;

        huffman_archiver();

        void calculate_chunk_frequencies(char *begin, const char *end);
        bool build_tree();
        void build_table();

        bool encode_chunk(char *input_begin, const char *input_end, size_t buffer_size);

        void flush(std::vector<char> &dest);
        void forced_flush(std::vector<char> &dest);

        bool decode_chunk(char *input_begin, const char *input_end, size_t buffer_size, uint64_t &total,
                          uint64_t &read);

        void reset();
    };
}

std::string to_string(huffman::bit_set &a);

#endif
