#include "../../header/UI/UIElement/ButtonView.h"
#include "../../header/Global/ServiceLocator.h"
#include "../../header/Event/EventService.h"
#include "../../header/Sound/SoundService.h"

namespace UI
{
    namespace UIElement
    {
        using namespace Event;
        using namespace Global;

        ButtonView::ButtonView() = default;

        ButtonView::~ButtonView() = default;

        void ButtonView::initialize(sf::String title, sf::String texture_path, float button_width, float button_height, sf::Vector2f position)
        {
            ImageView::initialize(texture_path, button_width, button_height, position);
            button_title = title;
        }

        void ButtonView::registerCallbackFuntion(CallbackFunction button_callback)
        {
            callback_function = button_callback;
        }

        void ButtonView::update()
        {
            ImageView::update();

            if (ui_state == UIState::VISIBLE)
            {
                handleButtonInteraction();
            }
        }

        void ButtonView::render()
        {
            ImageView::render();
        }

        void ButtonView::handleButtonInteraction()
        {
            sf::Vector2f mouse_position = sf::Vector2f(sf::Mouse::getPosition(*game_window));

            if (clickedLeftMouseButton(&image_sprite, mouse_position))
            {
                if (callback_function) callback_function(ButtonType::LEFT_MOUSE_BUTTON);
            }

            if (clickedRightMouseButton(&image_sprite, mouse_position))
            {
                if (callback_function) callback_function(ButtonType::RIGHT_MOUSE_BUTTON);
            }
        }

        bool ButtonView::clickedLeftMouseButton(sf::Sprite* button_sprite, sf::Vector2f mouse_position)
        {
            return ServiceLocator::getInstance()->getEventService()->pressedLeftMouseButton() &&
                button_sprite->getGlobalBounds().contains(mouse_position);
        }

        bool ButtonView::clickedRightMouseButton(sf::Sprite* button_sprite, sf::Vector2f mouse_position)
        {
            return ServiceLocator::getInstance()->getEventService()->pressedRightMouseButton() &&
                button_sprite->getGlobalBounds().contains(mouse_position);
        }

        void ButtonView::printButtonClicked()
        {
            printf("Clicked %s\n", button_title.toAnsiString().c_str());
        }
    }
}