#ifndef BLOOMFILTER_H
#define BLOOMFILTER_H

#include <vector>
#include <cstdint>

#define ROUND_UP(a, b) ((a)+(b)-1)/(b)*(b) /* 把a按照b取上整 */
#define SET_BIT(bitset, i) bitset[(i) / CHAR_BIT] |= (1 << ((i) % CHAR_BIT)) /* 将bitset的位i置1 */
#define GET_BIT(bitset, i) (bitset[(i) / CHAR_BIT] & (1 << ((i) % CHAR_BIT))) /* 取bitset的位i */

namespace leveldb {

typedef unsigned int(*HashFunc)(const char *);

/* RS */
unsigned int rs_hash(const char *str);

/* JS */
unsigned int js_hash(const char *str);

/* ELF */
unsigned int elf_hash(const char *str);

/* BKDP */
unsigned int bkdr_hash(const char *str);

/* SDBM */
unsigned int sdbm_hash(const char *str);

/* DBJ */
unsigned int dbj_hash(const char *str);

/* DEK */
unsigned int dek_hash(const char *str);

/* AP */
unsigned int ap_hash(const char *str);

/* Murmur */
unsigned int murmur_hash(const char *str);


class BloomFilter
{
public:
    BloomFilter(const int max_bits, const std::vector<HashFunc> &hash_funcs);

    ~BloomFilter();

    void Add(const char *key);

    bool Lookup(const char *key);

    int Size();

private:
    uint8_t *bitset_;
    int bitset_size_;
    int size_;
    std::vector<HashFunc> hash_funcs_;
};

} // namespace leveldb

#endif /* BLOOMFILTER_H */
