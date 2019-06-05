#include "huffman_engine.hpp"
#include <cstdint>
#include <queue>

huffman::tree::tree_node::tree_node(unsigned char c, uint64_t freq, size_t pos)
    : freq(freq), l_subtree(std::numeric_limits<size_t>::max()), r_subtree(std::numeric_limits<size_t>::max()),
    pos(pos) {
    chars.push_back(c);
}

huffman::tree::tree_node::tree_node(size_t l, size_t r, std::vector<tree_node> &order, size_t pos)
    : l_subtree(l), r_subtree(r), pos(pos) {
    for (unsigned char c : order[l].chars) {
        chars.push_back(c);
    }
    for (unsigned char c : order[r].chars) {
        chars.push_back(c);
    }
    freq = order[l].freq + order[r].freq;
}

huffman::tree::tree(std::vector<uint64_t> frequencies) {
    std::priority_queue<huffman::tree::tree_node> aux;
    bool pass = false;
    for (unsigned char i = 0; !pass || i != 0; i++, pass = true) {
        if (frequencies[i] != 0) {
            size_t pos = order.size();
            aux.emplace(i, frequencies[i], pos);
            order.emplace_back(i, frequencies[i], pos);
        }
    }

    while (aux.size() > 1) {
        tree_node a = aux.top();
        aux.pop();
        tree_node b = aux.top();
        aux.pop();
        size_t pos = order.size();
        aux.emplace(a.pos, b.pos, order, pos);
        order.emplace_back(a.pos, b.pos, order, pos);
    }
}

void huffman::tree::code_table_dfs(size_t v, bit_set &cur, std::vector<huffman::bit_set> &ans) {
    if (order[v].chars.size() == 1) {
        ans[order[v].chars[0]] = cur;
    } else {
        cur.push_back(false);
        code_table_dfs(order[v].l_subtree, cur, ans);
        cur.pop_back();
        cur.push_back(true);
        code_table_dfs(order[v].r_subtree, cur, ans);
        cur.pop_back();
    }
}

std::vector<huffman::bit_set> huffman::tree::get_code_table() {
    std::vector<huffman::bit_set> table(std::numeric_limits<unsigned char>::max() + 1);
    if (order.size() == 1) {
        table[order[0].chars[0]].resize(1);
    } else {
        bit_set initial;
        code_table_dfs(order.size() - 1, initial, table);
    }
    return table;
}

bool huffman::operator<(const huffman::tree::tree_node &a, const huffman::tree::tree_node &b) {
    if (a.freq > b.freq) {
        return true;
    }
    if (a.freq < b.freq) {
        return false;
    }
    return a.chars > b.chars;
}
