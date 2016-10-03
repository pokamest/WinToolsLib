#pragma once
#include "..\..\Types.h"
#include "..\..\String.h"
#include "..\..\Com\Ptr.h"

#include <taskschd.h>
#include <MSTask.h>

#pragma comment(lib, "taskschd.lib")
#pragma comment(lib, "mstask.lib")

namespace WinToolsLib { namespace Scheduler { namespace Vista
{
	class TaskRun
	{
		TaskRun(const TaskRun& other);            // Non-copyable
		TaskRun& operator=(const TaskRun& other); // Non-copyable

	public:
		TaskRun();
		TaskRun(TaskRun&& other);
		~TaskRun();

		TaskRun& operator=(TaskRun&& other);

		Void Run(const WChar* name);

	protected:
		Void MoveFrom(TaskRun& other);

	private:
		Com::Ptr<ITaskScheduler> m_scheduler;
		Com::Ptr<ITask> m_task;
	};
} } }
