#pragma once
#include "../../header/UI/Interface/IUIController.h"
#include "../../header/UI/UIElement/TextView.h"
#include "../../header/UI/UIElement/ButtonView.h"

namespace UI
{
	namespace GameplayUI
	{
		class GameplayUIController : public Interface::IUIController
		{
		private:
			const int font_size = 110;

			const float mine_text_top_offset = 65.f;
			const float mine_text_left_offset = 660.f;

			const float time_text_top_offset = 65.f;
			const float time_text_left_offset = 1090.f;

			const float restart_button_top_offset = 100.f;
			const float restart_button_left_offset = 920.f;

			const float button_height = 80.f;
			const float button_width = 80.f;

			const int tile_height = 32;

			const sf::Color text_color = sf::Color::Red;

			UIElement::TextView* mine_text;
			UIElement::TextView* time_text;
			UIElement::ButtonView* restart_button;

			void createButton();
			void createTexts();
			void initializeButton();
			void initializeTexts();
			void initializeMineText();
			void initializeTimeText();

			void updateMineText();
			void updateTimeText();
			void restartButtonCallback();
			void registerButtonCallback();

			void destroy();

		public:
			GameplayUIController();
			~GameplayUIController();

			void initialize() override;
			void update() override;
			void render() override;
			void show() override;
		};
	}
}