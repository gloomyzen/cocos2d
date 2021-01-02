#include "taskHolder.h"
#include "cocos2d.h"
#if (CC_TARGET_PLATFORM != CC_PLATFORM_ANDROID)
	#include "base/CCAsyncTaskPool.h"
#endif

using namespace cocos2d;

taskHolder::taskHolder() {}


void taskHolder::executeTasks() {
	if (allTasksLoaded) return;
	allTasksLoaded = true;

	auto allTasks = getTasks();
	if (allTasks.empty()) return;

	for (const auto &item : allTasks) {
		if (item == nullptr) continue;
		executeSingleTask(item);
	}
}

void taskHolder::executeSingleTask(const nodeTasks& task) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
	auto atp = AsyncTaskPool::getInstance();
	atp->enqueue(AsyncTaskPool::TaskType::TASK_OTHER, [](void*){}, nullptr,
				 [task]() {
					 auto res = task();
					 switch (res) {
						 case eTasksStatus::STATUS_OK:
							 break;
						 case eTasksStatus::STATUS_ERROR_BREAK:
							 //todo log error
							 break;
						 case eTasksStatus::STATUS_ERROR_RETRY:
							 //todo log error
							 break;
					 }
				 });
#else
	task();
#endif
}
