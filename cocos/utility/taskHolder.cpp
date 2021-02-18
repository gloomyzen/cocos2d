#include "taskHolder.h"
#include "cocos2d.h"
#include "base/CCAsyncTaskPool.h"

taskHolder::taskHolder() {}


void taskHolder::executeTasks() {
	if (allTasksLoaded) return;
	allTasksLoaded = true;

	auto allTasks = getTasks();
	if (allTasks.empty()) return;

	auto atp = cocos2d::AsyncTaskPool::getInstance();
	atp->enqueue(cocos2d::AsyncTaskPool::TaskType::TASK_OTHER, [](void*){}, nullptr,
				 [allTasks]() {
					 for (const auto &task : allTasks) {
						 if (!task) return false;
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
					 }
					 return true;
				 });
}
