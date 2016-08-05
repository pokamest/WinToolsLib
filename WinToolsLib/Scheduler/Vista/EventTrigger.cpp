#include "EventTrigger.h"

#include "..\..\Exception.h"

#include <comutil.h>
#pragma comment(lib, "comsuppw.lib")

namespace WinToolsLib { namespace Scheduler { namespace Vista
{
	EventTrigger::EventTrigger()
	{
	}

	EventTrigger::EventTrigger(Com::Ptr<IEventTrigger>&& trigger)
	{
		m_eventTrigger = std::move(trigger);
	}

	EventTrigger::EventTrigger(EventTrigger&& other)
	{
                this->MoveFrom(other);
	}

	EventTrigger::~EventTrigger()
	{
	}

	EventTrigger& EventTrigger::operator=(EventTrigger&& other)
	{
		MoveFrom(other);
		return *this;
	}

	TriggerType EventTrigger::GetType() const
	{
		TASK_TRIGGER_TYPE2 type2;

		auto hr = m_eventTrigger->get_Type(&type2);
		if (FAILED(hr))
		{
			THROW_WIN32_EXCEPTION(hr);
		}

                return static_cast<TriggerType>(type2);
        }

        StringW EventTrigger::GetSubscription() const
        {
                _bstr_t subscription;

                auto hr = m_eventTrigger->get_Subscription(subscription.GetAddress());
                if (FAILED(hr))
                {
                        THROW_WIN32_EXCEPTION(hr);
                }

                return (subscription.length() > 0) ? StringW(subscription) : StringW();
        }

        Void EventTrigger::SetSubscription(const WChar* queryString)
        {
                StringW queryStringW(queryString);
                if (!queryStringW.IsEmpty())
                {
                        auto hr = m_eventTrigger->put_Subscription(queryStringW.GetBuffer());
                        if (FAILED(hr))
                        {
                                THROW_WIN32_EXCEPTION(hr);
                        }
                }
        }

        Void EventTrigger::MoveFrom(EventTrigger& other)
        {
                if (this != &other)
                {
                        m_eventTrigger = std::move(other.m_eventTrigger);
                }
        }
} } }
