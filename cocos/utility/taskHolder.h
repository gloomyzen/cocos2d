#ifndef SWIPE_RPG_TASKHOLDER_H
#define SWIPE_RPG_TASKHOLDER_H

#include <functional>
#include <deque>

enum class eTasksStatus {
	STATUS_OK = 0,
	STATUS_ERROR_BREAK,
	STATUS_ERROR_RETRY
};

typedef std::function<eTasksStatus()> nodeTasks;

class taskHolder {
public:
	taskHolder();
	virtual ~taskHolder() = default;

	void executeTasks();

protected:
	/***
	 * Загрузка асинхронных тасков для ноды
	 * @return std::function<bool()>
	 */
	virtual std::deque<nodeTasks> getTasks() = 0;

private:
	void executeSingleTask(const nodeTasks&);
	bool allTasksLoaded = false;
};


#endif //SWIPE_RPG_TASKHOLDER_H
