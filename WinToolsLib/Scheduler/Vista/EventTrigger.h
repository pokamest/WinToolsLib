#pragma once
#include "..\..\Types.h"
#include "..\..\String.h"
#include "..\..\Com\Ptr.h"

#include <taskschd.h>
#pragma comment(lib, "taskschd.lib")

#include "Trigger.h"
#include "DailyTrigger.h"
#include "WeeklyTrigger.h"

namespace WinToolsLib { namespace Scheduler { namespace Vista
{
	class EventTrigger
	{
		EventTrigger(const EventTrigger& other);            // Non-copyable
		EventTrigger& operator=(const EventTrigger& other); // Non-copyable

	public:
		EventTrigger();
		EventTrigger(Com::Ptr<IEventTrigger>&& trigger);
		EventTrigger(EventTrigger&& other);
		~EventTrigger();

		EventTrigger& operator=(EventTrigger&& other);

                TriggerType GetType() const;

                StringW GetSubscription() const;
                Void SetSubscription(const WChar* queryString);

	protected:
		Void MoveFrom(EventTrigger& other);

	private:
		Com::Ptr<IEventTrigger> m_eventTrigger;
	};

} } }
