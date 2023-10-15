#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>
#include <string_view>
#include <vector>

using namespace std;

class Domain {
    // разработайте класс домена

    // конструктор должен позволять конструирование из string, с сигнатурой определитесь сами

    // разработайте operator==

    // разработайте метод IsSubdomain, принимающий другой домен и возвращающий true, если this его поддомен
public:
    Domain(std::string str) : domain_(str){ 
    }
    
    bool operator==(const Domain& rhs) const {
        return domain_ == rhs.domain_;
    }
    
    std::string GetValue() const {
        return domain_;
    }
    
    bool IsSubdomain(const Domain& other) const {
        if (other.domain_.size() <= domain_.size()){
            return std::equal(other.domain_.begin(), other.domain_.end(), domain_.begin());
        } else {
            return false;
        }
    }
private:
    std::string domain_;
};

class DomainChecker {
public:
    // конструктор должен принимать список запрещённых доменов через пару итераторов
    template<typename Iter>
    DomainChecker(Iter begin, Iter end) : forbidden_(begin, end) {
        Sort();
    }
    // разработайте метод IsForbidden, возвращающий true, если домен запрещён
    bool IsForbidden(const Domain& domain) {
        if (forbidden_.empty()){
            return false;
        }
        
        auto it = std::upper_bound(forbidden_.begin(), forbidden_.end(), domain, [](const Domain& lhs, const Domain& rhs){
            return lhs.GetValue() < rhs.GetValue();
        });
        /*if (it == forbidden_.end()) {
            return false;
        }*/
        if (it != forbidden_.begin()){
            return domain.IsSubdomain(forbidden_[it - forbidden_.begin() - 1]);
        } else {
            return domain.IsSubdomain(forbidden_[it - forbidden_.begin()]);
        }
        
        return false;
    }
    
private:
    
    std::vector<Domain> forbidden_;
    
    void Sort() {
        std::sort(forbidden_.begin(), forbidden_.end(), [](const Domain& lhs, const Domain& rhs){
            return lhs.GetValue() < rhs.GetValue();
        });
        auto last = std::unique(forbidden_.begin(), forbidden_.end(), [](const Domain& lhs, const Domain& rhs){
            return rhs.IsSubdomain(lhs);
        });
        forbidden_.erase(last, forbidden_.end());
    }
};

// разработайте функцию ReadDomains, читающую заданное количество доменов из стандартного входа
template<typename Number>
vector<Domain> ReadDomains(std::istream& input, Number num) {
    vector<Domain> result;
    for (Number i = 0; i < num; ++i){
        string line;
        std::getline(input, line);
        line.insert(0, 1, '.');
        std::reverse(line.begin(), line.end());
        result.push_back(std::move(line));
    }
    
    return result;
}

template <typename Number>
Number ReadNumberOnLine(istream& input) {
    string line;
    getline(input, line);

    Number num;
    std::istringstream(line) >> num;

    return num;
}

int main() {
    const std::vector<Domain> forbidden_domains = ReadDomains(cin, ReadNumberOnLine<size_t>(cin));
    DomainChecker checker(forbidden_domains.begin(), forbidden_domains.end());

    const std::vector<Domain> test_domains = ReadDomains(cin, ReadNumberOnLine<size_t>(cin));
    for (const Domain& domain : test_domains) {
        cout << (checker.IsForbidden(domain) ? "Bad"sv : "Good"sv) << endl;
    }
}
