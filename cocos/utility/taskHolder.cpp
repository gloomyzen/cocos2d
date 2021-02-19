#include "taskHolder.h"
#include "cocos2d.h"
#include "base/CCAsyncTaskPool.h"
#include <2d/CCNode.h>

taskHolder::taskHolder() = default;


void taskHolder::executeTasks() {
	if (allTasksLoaded) return;
	allTasksLoaded = true;

	auto allTasks = getTasks();
	if (allTasks.empty()) return;

	if (auto currentNode = dynamic_cast<cocos2d::Node*>(this)) {
		currentNode->scheduleOnce([allTasks](float){
			for (const auto &task : allTasks) {
				if (!task) return false;
				auto res = task();
				switch (res) {
					case eTasksStatus::STATUS_OK:
						break;
					case eTasksStatus::STATUS_ERROR_BREAK:
						return false;
						break;
				}
			}
			return true;
		}, 0.f, "runTasks");
	}
}
