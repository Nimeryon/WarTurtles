#pragma once

#include <string>
#include <unordered_map>
#include <vector>

using UIEventID = std::string;

/// <summary>
/// Base Event class
/// </summary>
class UIEvent
{
public:

	UIEvent(const UIEventID& _ID) : ID(_ID) {}
	virtual ~UIEvent() {}

	UIEventID ID;

};

/// <summary>
/// Event receiver interface
/// </summary>
class IUIEventSubscriber
{
public:

	virtual void OnEvent(const UIEvent* _pEvent) = 0;
};

/// <summary>
/// Event Publisher class
/// </summary>
class UIEventPublisher
{
public:
	void SubscribeToEvent(const UIEventID& _ID, IUIEventSubscriber* pSubscriber);
	void UnSubscribeToEvent(const UIEventID& _ID, IUIEventSubscriber* pSubscriber);
	void TriggerEvent(const UIEventID& _ID);

private:

	std::unordered_map< UIEventID, std::vector<IUIEventSubscriber*> > m_hashSubscribers;

};


