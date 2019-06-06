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
    public:
        explicit tree(std::vector<uint64_t> frequencies);
        std::vector<bit_set> get_code_table();
    };

    bool operator<(const tree::tree_node &a, const tree::tree_node &b);

    struct huffman_archiver {
        static const size_t charcode_range = 256;
        static const size_t buffer_max_size = 16;
        const uint64_t version;

        std::string source_file_path;
        std::vector<uint64_t> frequencies;

        static uint64_t read_uint64_t(std::ifstream &input_file_stream);

        void calculate_chunk_frequencies(char *begin, const char *end);
        void calculate_file_frequecies(const std::string &input_file_path);

        void cross_encode_file(const std::string &input_file_path, const std::string &output_file_path,
                const std::vector<huffman::bit_set> &table);
        static void read_chunk_from_file(std::ifstream &input_file_stream, std::vector<char> &input_buffer);

        void cross_decode_file(std::ifstream &input_file_stream, const std::string &target_path);

        void write_version_to_file(std::ofstream &output_file_stream);
        void write_frequencies_to_file(std::ofstream &output_file_stream);

    public:
        explicit huffman_archiver(std::string source_file_path);
        void change_source(const std::string &new_source_file_path);
        void encode(const std::string &target_path);
        void decode(const std::string &target_path);
    };
}

std::string to_string(huffman::bit_set &a);

#endif
