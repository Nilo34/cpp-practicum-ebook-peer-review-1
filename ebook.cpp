#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

const int MAXIMUM_USERS = 100001;
const int MAXIMUM_PAGES = 1001;

class ReadingStimulator {
public:
    
    ReadingStimulator();
    
    void Read(int user_id, int page_number);
    double Cheer(int user_id) const;
    
private:
    std::vector<int> user_page_number_;
    std::vector<int> number_of_users_read_to_page_;
};

ReadingStimulator::ReadingStimulator() 
: user_page_number_(MAXIMUM_USERS, 0)
, number_of_users_read_to_page_(MAXIMUM_PAGES, 0)
{
}

void ReadingStimulator::Read(int user_id, int page_number) {
    
    int pages_were = user_page_number_[user_id];
    
    for (; pages_were < page_number; ++pages_were) {
        number_of_users_read_to_page_[pages_were] += 1;
    }
    
    user_page_number_[user_id] = page_number;
}

double ReadingStimulator::Cheer(int user_id) const {
    
    if (user_page_number_.at(user_id) == 0) {
        return 0;
    }
    
    int number_people_started_reading = number_of_users_read_to_page_.at(0);
    
    if (number_people_started_reading == 1) {
        return 1;
    }
    
    int  number_of_users_read_to_page_number = number_of_users_read_to_page_.at(user_page_number_.at(user_id)-1);
    
    if (number_of_users_read_to_page_number == number_people_started_reading) {
        return 0;
    }
    
    return (number_people_started_reading - number_of_users_read_to_page_number) / (number_people_started_reading - 1.0);
}


void ReadEnquiry(ReadingStimulator& reading_stimulator) {

    std::string number_of_requests_s;
    std::getline(std::cin, number_of_requests_s);
    
    int number_of_requests = stoi(number_of_requests_s);
    
    std::string request_type, user_id_s, page_number_s;
    int user_id, page_number;
    
    for (int i = 0; i < number_of_requests; ++i) {
        std::getline(std::cin, request_type, ' ');
        if (request_type == "READ") {
            
            std::getline(std::cin, user_id_s, ' ');
            std::getline(std::cin, page_number_s);
            
            user_id = std::stoi(user_id_s);
            page_number = std::stoi(page_number_s);
            
            reading_stimulator.Read(user_id, page_number);
            
        } else if (request_type == "CHEER") {
            
            std::getline(std::cin, user_id_s);
            
            user_id = std::stoi(user_id_s);
            
            std::cout << std::setprecision(6) << reading_stimulator.Cheer(user_id) << std::endl;
        }
    }
}







int main() {
    
    ReadingStimulator reading_stimulator;
    
    ReadEnquiry(reading_stimulator);
    
}