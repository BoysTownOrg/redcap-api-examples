#include <curl/curl.h>
#include <string>

namespace {
auto write(void *source, size_t, size_t nmemb, void *destination_) -> size_t {
    auto *destination{static_cast<std::string *>(destination_)};
    destination->append(static_cast<char *>(source), nmemb);
    return nmemb;
}

class GlobalCurl {
  public:
    GlobalCurl() { curl_global_init(CURL_GLOBAL_ALL); }

    ~GlobalCurl() { curl_global_cleanup(); }
};

class Curl {
  public:
    Curl() : curl{curl_easy_init()} {
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1);
        // https://curl.haxx.se/libcurl/c/CURLOPT_SSL_VERIFYHOST.html
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 2);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
    }

    void setUrl(const std::string &s) {
        curl_easy_setopt(curl, CURLOPT_URL, s.c_str());
    }

    void setPostFields(const std::string &s) {
        curl_easy_setopt(curl, CURLOPT_COPYPOSTFIELDS, s.c_str());
    }

    auto post() -> std::string {
        curl_easy_perform(curl);
        auto copy{response};
        response.clear();
        return copy;
    }

    ~Curl() { curl_easy_cleanup(curl); }

  private:
    std::string response;
    GlobalCurl _;
    CURL *curl;
};
}

int main() {}
