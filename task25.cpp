#include <array>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <functional>
#include <iostream>
#include <limits>
#include <random>
#include <vector>

using Gen = std::mt19937;
using IP = std::array<uint8_t, 4>;

using hash_func = std::function<size_t(IP&)>;
hash_func gen_hash_func(size_t m, Gen& gen) {
  static std::uniform_int_distribution<> distrib(0, m);

  int a1, a2, a3, a4;
  a1 = distrib(gen), a2 = distrib(gen), a3 = distrib(gen), a4 = distrib(gen);

  return [a1, a2, a3, a4](IP& addr) {
    return a1 * addr[0] + a2 * addr[1] + a3 * addr[2] + a4 * addr[3];
  };
}

class IPSet {
  std::vector<bool> bitset;
  std::vector<hash_func> hashes;

public:
  IPSet(size_t predicted_num, double fp_rate, Gen& gen) {
    double k = log(fp_rate) / log(0.5);
    double b = k / log(2);

    size_t hashes_num = static_cast<size_t>(floor(k));
    size_t bit_per_obj = static_cast<size_t>(floor(b));

    hashes.resize(hashes_num);
    bitset.resize(bit_per_obj * predicted_num);

    for (size_t i = 1; i <= hashes_num; i++) {
      hashes[i - 1] = gen_hash_func(i, gen);
    }
  }

  void insert(IP& addr) {
    for (auto hash : hashes) {
      bitset[hash(addr) % hashes.size()] = true;
    }
  };

  bool lookup(IP& addr) {
    for (auto hash : hashes) {
      if (!bitset[hash(addr) % hashes.size()]) {
        return false;
      };
    }
    return true;
  };
};

int main() {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<uint8_t> distrib(0, 255);

  IPSet set(1000, 0.01, gen);
  std::array<IP, 1000> addresses;
  addresses[0] = {distrib(gen), distrib(gen), distrib(gen), distrib(gen)};
  for (size_t i = 1; i < 1000; i++) {
    do {
    IP addr = {distrib(gen), distrib(gen), distrib(gen), distrib(gen)};
    addresses[i] = addr;
    } while (addresses[i] == addresses[0]);
  }

  set.insert(addresses[0]);

  int cnt;
  for (auto addr : addresses) {
    cnt += set.lookup(addr);
  }

  std::cout << ((double) (cnt - 1) / 1000) << '\n';
}
