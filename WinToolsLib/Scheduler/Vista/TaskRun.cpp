#include "TaskRun.h"

#include "..\..\Exception.h"

#include <windows.h>
#include <initguid.h>
#include <ole2.h>
#include <mstask.h>
#include <msterr.h>
#include <wchar.h>
#include <stdio.h>

#include <comutil.h>
#pragma comment(lib, "comsuppw.lib")
#pragma comment(lib, "mstask.lib")

namespace WinToolsLib { namespace Scheduler { namespace Vista
{
	TaskRun::TaskRun()
	{
		HRESULT hr = S_OK;

		///////////////////////////////////////////////////////////////////
		// Call CoInitialize to initialize the COM library and then
		// call CoCreateInstance to get the Task Scheduler object.
		///////////////////////////////////////////////////////////////////
		hr = CoInitialize(NULL);
		if (SUCCEEDED(hr))
		{
			hr = CoCreateInstance(
				CLSID_CTaskScheduler,
				NULL,
				CLSCTX_INPROC_SERVER,
				IID_ITaskScheduler,
				(PVoid*)&m_scheduler);
				if (FAILED(hr))
				{
					CoUninitialize();
					THROW_WIN32_EXCEPTION(hr);
				}
			}
			else
			{
				THROW_LAST_ERROR_EXCEPTION();
			}
		}

	TaskRun::TaskRun(TaskRun&& other)
	{
		MoveFrom(other);
	}

	TaskRun::~TaskRun()
	{
	}

	TaskRun& TaskRun::operator=(TaskRun&& other)
	{
		MoveFrom(other);
		return *this;
	}

	Void TaskRun::Run(const WChar* name)
	{
		std::wstring sched_event_fullname = std::wstring(L"C:/Windows/System32/Tasks/OVPN.SE/") + name;

		HRESULT hr = S_OK;
		hr = m_scheduler->Activate(
			sched_event_fullname .c_str(),
			IID_ITask,
			(IUnknown**) &m_task);

		(*m_scheduler).Release();
		if (FAILED(hr))
		{
			wprintf(L"Failed calling ITaskScheduler::Activate; error = 0x%x\n",hr);
			CoUninitialize();
			THROW_WIN32_EXCEPTION(hr);
		}

		hr = m_task->Run();
		(*m_task).Release();

		if (FAILED(hr))
		{
			wprintf(L"Failed calling ITask::Run, error = 0x%x\n",hr);
			CoUninitialize();
			THROW_WIN32_EXCEPTION(hr);
		}
	}

	Void TaskRun::MoveFrom(TaskRun& other)
	{
		if (this != &other)
		{
			m_scheduler = std::move(other.m_scheduler);
			m_task = std::move(other.m_task);
		}
	}

} } }
