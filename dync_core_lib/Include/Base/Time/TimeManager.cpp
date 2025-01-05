#include "TimeManager.h"
#include <chrono>
TimeManager& TimeManager::GetInstance(){
	if(instance == NULL){
		std::lock_guard<std::mutex> lock(mtx);
		if(instance == NULL){
			instance.reset(new TimeManager());
		}

	}
	return *instance;
}

std::unique_ptr<TimeManager> TimeManager::instance = nullptr;
std::mutex TimeManager::mtx;


extern "C" {

time_t TimeManager::GetNowTime(){
	time_t  nowTime;
	time(&nowTime);
	return nowTime;
}

std::uint64_t TimeManager::GetMicroSeconds(){
	 // 获取当前时间点
    auto now = std::chrono::high_resolution_clock::now();	
	// 转换为自epoch以来的时间长度，以微秒为单位
	auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(now.time_since_epoch()).count();
	
	return microseconds;
}

}
