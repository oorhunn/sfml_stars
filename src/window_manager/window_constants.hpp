//
// Created by Anıl Orhun Demiroğlu on 04.01.26.
//

#pragma once

#include <cstdint>
#include <numbers>

namespace window_manager::constants {

    static constexpr unsigned int sc_window_width{1920};
    static constexpr unsigned int sc_window_height{1080};

    static constexpr std::float_t sc_window_width_f{static_cast<std::float_t>(sc_window_width)};
    static constexpr std::float_t sc_window_height_f{static_cast<std::float_t>(sc_window_height)};

    static constexpr std::uint32_t const sc_max_frame_rate{144};
    static constexpr std::float_t sc_dt{1.0f / static_cast<float>(sc_max_frame_rate)};
}  // namespace window_manager::constants