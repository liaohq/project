#include <memory>
#include <mutex>
#include <ctime>



class TimeManager {

public:
	static TimeManager& GetInstance();
	
	TimeManager(){};
	
	time_t GetNowTime();
	std::uint64_t GetMicroSeconds();
	int test(){return 111;}
private:
	static std::unique_ptr<TimeManager> instance;
	static std::mutex mtx;

	TimeManager(const TimeManager&) = delete;
	TimeManager& operator=(const TimeManager&) = delete;
};

