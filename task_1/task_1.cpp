#include <iostream>
#include <vector>
#include <map>
#include <iomanip>
#include <algorithm>

class BookManager{
public: 
    BookManager() :
        user_to_page_(MAX_USER_COUNT_ + 1, 0){
        }
    
    void Read(int user, int page) {
         int prev_page_count = user_to_page_[user];
        if (!prev_page_count) {
            ++total_users_;
        } else {
            auto it = page_to_num_users_.find(prev_page_count);
            if (it->second == 1)
                page_to_num_users_.erase(it);
            else
                it->second--;
        }
        
        user_to_page_[user] = page;
        ++page_to_num_users_[page];
    }
    double Cheer(int user) {
        int page_count = user_to_page_[user];
        if (!page_count)
            return 0;
        if (total_users_ == 1)
            return 1;
        int less_pages = 0;
        for (auto& p : page_to_num_users_) {
            if (p.first >= page_count)
                break;
            less_pages += p.second;
        }
        
        return (less_pages) * 1.0 / (total_users_ - 1);
    }
private:
    static const int MAX_USER_COUNT_ = 100000;
    
    std::vector<int> user_to_page_;
    std::map<int, int> page_to_num_users_;
    unsigned int total_users_ = 0;
};

int main(){
    
    BookManager bk;
    
    int count;
    std::cin >> count;
    
    for (int i = 0; i < count; ++i){
        std::string quest;
        int num;
        std::cin >> quest; std::cin >> num;
        if (quest == "READ"){
            int page;
            std::cin >> page;
            bk.Read(num, page);
        }else if (quest == "CHEER"){
            std::cout << std::setprecision(6) << bk.Cheer(num) << std::endl;
        }
    }
}
