#pragma once
#include "CharactorObject.h"
#include "Player.h"
#include "Ladder.h"
#include <memory>
#include <list>
#include <map>
#include <string>

class Camera;

//ƒCƒxƒ“ƒg‚Ì¶¬‚Æ”jŠü
class EventManager
{
public:
	~EventManager();
	static EventManager* GetInstance() {
		return instance;
	}
	static void Create() {
		if (instance == nullptr) {
			instance = new EventManager();
		}
	}
	static void Destroy() {
		if (instance != nullptr) {
			delete instance;
		}
		instance = nullptr;
	}

	void Updata();
	void Draw();
	void CallEventObject(std::string name, std::weak_ptr<Player> _pl, std::weak_ptr<Camera> _cam, positin _pos);
private:
	EventManager();
	static EventManager* instance;

	std::list<std::shared_ptr<CharactorObject>> eventObj;
	std::map<std::string, std::shared_ptr<CharactorObject>> _eventObj;
};

