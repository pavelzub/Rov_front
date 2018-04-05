//
// Created by zinjkov on 30.03.18.
//

#ifndef RC_ROV_SERVER_ROV_DATA_TYPES_HPP
#define RC_ROV_SERVER_ROV_DATA_TYPES_HPP

#include <cstdint>
#include "serializable.hpp"

namespace rov_types {
    struct rov_telimetry : serializable {
        enum meta : uint8_t {
            packet_id = 0x1E,
            payload_size = 13,
            packet_size = 15
        };

        float yaw = 0;
        float pitch = 0;
        float roll = 0;

        std::vector<std::uint8_t> serialize() override final;

        error_code deserialize(const std::vector<std::uint8_t> &input) override final;
    };

    struct rov_control : serializable {
        enum meta: uint8_t{
            packet_id = 0x2E,
            payload_size = 5,
            packet_size = 7
        };

        std::int8_t axis_x = 0;
        std::int8_t axis_y = 0;
        std::int8_t axis_z = 0;
        std::int8_t axis_w = 0;

        virtual std::vector<std::uint8_t> serialize() override final;

        virtual error_code deserialize(const std::vector<std::uint8_t> &input) override final;
    };
};


#endif //RC_ROV_SERVER_ROV_DATA_TYPES_HPP
