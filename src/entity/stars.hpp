#pragma once

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/System/Vector2.hpp>

#include <array>
#include <random>

#include "entity_constants.hpp"

namespace entity::stars {

    struct Star {

        sf::Vector2f position{};
        float z{};
    };

    inline std::mt19937& rng() {

        static std::mt19937 gen{std::random_device{}()};
        return gen;
    }

    inline float frand(float a, float b) {

        std::uniform_real_distribution<float> d(a, b);
        return d(rng());
    }

    inline auto create_stars(sf::Vector2u window_size) -> std::array<Star, entity::constants::sc_star_count> {

        std::array<Star, entity::constants::sc_star_count> stars{};

        for (auto& s : stars) {

            s.position = {frand(-0.5f, 0.5f) * window_size.x, frand(-0.5f, 0.5f) * window_size.y};

            s.z = frand(entity::constants::sc_near_distance, entity::constants::sc_far_distance);
        }

        return stars;
    }

    constexpr std::size_t VERTS_PER_STAR{6};

    inline void update_geometry(std::size_t id, const Star& star, sf::VertexArray& va, sf::Vector2u texture_size) {

        const float scale{1.f / star.z};

        const float depth_ratio = (star.z - entity::constants::sc_near_distance) /
                                  (entity::constants::sc_far_distance - entity::constants::sc_near_distance);

        const std::uint8_t brightness = static_cast<std::uint8_t>((1.f - depth_ratio) * 255.f);

        const sf::Color color{brightness, brightness, brightness, brightness};

        const sf::Vector2f p = star.position * scale;
        const float half = (entity::constants::sc_star_size * scale) * 0.5f;

        const sf::Vector2f tl{p.x - half, p.y - half};
        const sf::Vector2f tr{p.x + half, p.y - half};
        const sf::Vector2f br{p.x + half, p.y + half};
        const sf::Vector2f bl{p.x - half, p.y + half};

        const sf::Vector2f ts{static_cast<float>(texture_size.x), static_cast<float>(texture_size.y)};

        const std::size_t base = id * VERTS_PER_STAR;

        va[base + 0].position = tl;
        va[base + 1].position = tr;
        va[base + 2].position = br;

        va[base + 3].position = br;
        va[base + 4].position = bl;
        va[base + 5].position = tl;

        va[base + 0].texCoords = {0.f, 0.f};
        va[base + 1].texCoords = {ts.x, 0.f};
        va[base + 2].texCoords = {ts.x, ts.y};

        va[base + 3].texCoords = {ts.x, ts.y};
        va[base + 4].texCoords = {0.f, ts.y};
        va[base + 5].texCoords = {0.f, 0.f};

        for (std::size_t i = 0; i < 6; ++i) {

            va[base + i].color = color;
        }
    }

}  // namespace entity::stars