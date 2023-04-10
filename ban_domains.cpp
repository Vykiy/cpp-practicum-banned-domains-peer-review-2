#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>
#include <string_view>
#include <utility>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

class Domain {
    // разработайте класс домена
    // конструктор должен позволять конструирование из string, с сигнатурой определитесь сами
    // разработайте operator==
    // разработайте метод IsSubdomain, принимающий другой домен и возвращающий true, если this его поддомен
public:
    Domain() = default;

    explicit Domain(string domain) : domain_(std::move(domain)) {};

    //для проверки корректности заполнения
    string GetDomains() const {
        return domain_;
    }

    bool operator==(Domain const &other) const {
        return domain_ == other.domain_;
    }

    bool operator!=(Domain const &other) const {
        return domain_ != other.domain_;
    }

    bool operator<(Domain const &other) const {
        return domain_ < other.domain_;
    }

    bool operator>(Domain const &other) const {
        return domain_ > other.domain_;
    }

    bool IsSubdomain(const Domain &other) const {
        return other.GetDomains().find(domain_) != string::npos;
    }

private:
    string domain_;
};

class DomainChecker {
    // конструктор должен принимать список запрещённых доменов через пару итераторов

    // разработайте метод IsForbidden, возвращающий true, если домен запрещён
public:
    DomainChecker() = default;

    template<class Iter>
    DomainChecker(Iter begin, Iter end) : vec_(begin, end) {}

    bool IsForbidden(const Domain &dom) {
        for (auto test : vec_) {
            if (test.IsSubdomain(dom)) {
                return true;
            }
        }
        return false;
    }

private:
    vector<Domain> vec_;
};

// разработайте функцию ReadDomains, читающую заданное количество доменов из стандартного входа

void Remove_duplicates(vector<Domain> &vec) {
    sort(begin(vec), end(vec));
    auto it = unique(begin(vec), end(vec), [](Domain const &lhs, Domain const &rhs) { return lhs.IsSubdomain(rhs); });
    vec.erase(it, end(vec));
}

vector<Domain> ReadDomains(istream &input, size_t num_cin) {
    vector<Domain> block_domains;
    int convert = static_cast<int>(num_cin);
    for (int i = 0; i < convert; ++i) {
        string domain;
        input >> domain;
        //вставка '.' в начало и реверс строки для упрощенного сравнения
        domain.insert(begin(domain), '.');
        reverse(begin(domain), end(domain));
        block_domains.emplace_back(domain);
    }
    //удаление поддоменов
    Remove_duplicates(block_domains);
    return block_domains;
}

template<typename Number>
Number ReadNumberOnLine(istream &input) {
    string line;
    getline(input, line);

    Number num;
    std::istringstream(line) >> num;

    return num;
}

int main() {
//    std::istringstream in{"4\n"
//                          "gdz.ru\n"
//                          "maps.me\n"
//                          "m.gdz.ru\n"
//                          "com\n"
//                          "7\n"
//                          "gdz.ru\n"
//                          "gdz.com\n"
//                          "m.maps.me\n"
//                          "alg.m.gdz.ru\n"
//                          "maps.com\n"
//                          "maps.ru\n"
//                          "gdz.ua\n"
//    };

    const std::vector<Domain> forbidden_domains = ReadDomains(cin, ReadNumberOnLine<size_t>(cin));
//    for (const auto &forb: forbidden_domains) {
//        cout << forb.GetDomains() << endl;
//    }

    DomainChecker checker(forbidden_domains.begin(), forbidden_domains.end());

//    std::istringstream in2{"7\n"
//                          "gdz.ru\n"
//                          "gdz.com\n"
//                          "m.maps.me\n"
//                          "alg.m.gdz.ru\n"
//                          "maps.com\n"
//                          "maps.ru\n"
//                          "gdz.ua\n"
//    };

    const std::vector<Domain> test_domains = ReadDomains(cin, ReadNumberOnLine<size_t>(cin));
    for (const Domain &domain: test_domains) {
        cout << (checker.IsForbidden(domain) ? "Bad"sv : "Good"sv) << endl;
    }
}
