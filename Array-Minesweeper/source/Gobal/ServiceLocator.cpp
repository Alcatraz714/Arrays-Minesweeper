#include "../../header/Global/ServiceLocator.h"
#include "../../header/Main/GameService.h"

namespace Global
{
	using namespace Graphics;
	using namespace Event;
	using namespace Sound;
	using namespace UI;
	using namespace Gameplay;
	using namespace Board;
	using namespace Main;
	using namespace Time;

	ServiceLocator::ServiceLocator()
	{
		graphic_service = nullptr;
		event_service = nullptr;
		sound_service = nullptr;
		ui_service = nullptr;
		gameplay_service = nullptr;
		time_service = nullptr;
		board_service = nullptr;

		createServices();
	}

	ServiceLocator::~ServiceLocator() { clearAllServices(); }

	void ServiceLocator::createServices()
	{
		event_service = new EventService();
		graphic_service = new GraphicService();
		sound_service = new SoundService();
		ui_service = new UIService();
		gameplay_service = new GameplayService();
		time_service = new TimeService();
		board_service = new BoardService();
	}

	void ServiceLocator::initialize()
	{
		graphic_service->initialize();
		time_service->initialize();
		sound_service->initialize();
		event_service->initialize();
		ui_service->initialize();
		gameplay_service->initialize();
		board_service->initialize();
	}

	void ServiceLocator::update()
	{
		time_service->update();
		event_service->update();
		graphic_service->update();

		if (GameService::getGameState() == GameState::GAMEPLAY)
		{
			gameplay_service->update();
			board_service->update();

		}

		ui_service->update();
	}

	void ServiceLocator::render()
	{
		graphic_service->render();

		if (GameService::getGameState() == GameState::GAMEPLAY)
		{
			gameplay_service->render();
			board_service->render();
		}

		ui_service->render();
	}

	void ServiceLocator::clearAllServices()
	{
		delete(ui_service);
		delete(graphic_service);
		delete(sound_service);
		delete(event_service);
		delete(gameplay_service);
		delete(time_service);
		delete(board_service);
	}

	ServiceLocator* ServiceLocator::getInstance()
	{
		static ServiceLocator instance;
		return &instance;
	}

	EventService* ServiceLocator::getEventService() { return event_service; }

	GraphicService* ServiceLocator::getGraphicService() { return graphic_service; }

	SoundService* ServiceLocator::getSoundService() { return sound_service; }

	UIService* ServiceLocator::getUIService() { return ui_service; }

	GameplayService* ServiceLocator::getGameplayService() { return gameplay_service; }

	Time::TimeService* ServiceLocator::getTimeService() { return time_service; }

	Board::BoardService* ServiceLocator::getBoardService() { return board_service; }


	void ServiceLocator::deleteServiceLocator() { delete(this); }
}