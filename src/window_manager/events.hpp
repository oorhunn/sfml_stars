//
// Created by Anıl Orhun Demiroğlu on 04.01.26.
//
#pragma once

#include <SFML/Graphics.hpp>

namespace window_manager {

    [[nodiscard]]
    bool process_events(sf::Window& window) {

        while (auto event = window.pollEvent()) {

            if (event->is<sf::Event::Closed>()) {

                return false;
            }

            if (auto key = event->getIf<sf::Event::KeyPressed>()) {

                if (key->code == sf::Keyboard::Key::Escape) {

                    return false;
                }
            }
        }

        return true;
    }

}  // namespace window_manager