#include <SFML/Graphics.hpp>

#include "entity/stars.hpp"
#include "window_manager/events.hpp"
#include "window_manager/window_constants.hpp"

int main() {

    sf::RenderWindow window(
        sf::VideoMode({window_manager::constants::sc_window_width, window_manager::constants::sc_window_height}),
        "sfml stars",
        sf::State::Windowed);

    window.setFramerateLimit(window_manager::constants::sc_max_frame_rate);

    sf::Texture star_texture{};
    if (!star_texture.loadFromFile("assets/star.png")) {

        return -1;
    }
    star_texture.setSmooth(true);

    auto stars = entity::stars::create_stars(window.getSize());

    sf::VertexArray va(sf::PrimitiveType::Triangles, entity::constants::sc_star_count * entity::stars::VERTS_PER_STAR);

    const sf::Vector2f screen_center{window.getSize().x * 0.5f, window.getSize().y * 0.5f};

    while (window.isOpen()) {

        bool running = window_manager::process_events(window);
        if (!running) {

            window.close();
            break;
        }

        for (auto& s : stars) {

            s.z -= entity::constants::sc_speed * (1.f / 144.f);

            if (s.z < entity::constants::sc_near_distance) {

                s.z = entity::constants::sc_far_distance;
            }
        }

        for (std::size_t i = 0; i < stars.size(); ++i) {

            entity::stars::update_geometry(i, stars[i], va, star_texture.getSize());
        }

        window.clear(sf::Color::Black);

        sf::RenderStates states;
        states.texture = &star_texture;
        states.transform.translate(screen_center);
        states.blendMode = sf::BlendAdd;

        window.draw(va, states);
        window.display();
    }

    return 0;
}