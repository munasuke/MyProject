#include "EventManager.h"
#include "Typedef.h"
#include "Camera.h"

EventManager *EventManager::instance = nullptr;

void EventManager::Updata()
{
	for (auto itr = eventObj.begin(); itr != eventObj.end(); itr++) {
		(*itr)->Updata();
	}
}

void EventManager::Draw()
{
	for (auto itr = eventObj.begin(); itr != eventObj.end(); itr++) {
		(*itr)->Draw();
	}
}

void EventManager::CallEventObject(std::string name, std::weak_ptr<Player> _pl, std::weak_ptr<Camera> _cam, positin _pos)
{
	if (name == "Ladder") {
		_eventObj["Ladder"] = std::make_shared<Ladder>(_pl, _cam, _pos);
		eventObj.push_back(_eventObj["Ladder"]);
	}
}

EventManager::EventManager()
{
	eventObj.clear();
}


EventManager::~EventManager()
{
}
