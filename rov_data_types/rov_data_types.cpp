//
// Created by zinjkov on 30.03.18.
//

#include "rov_data_types.hpp"


void rov_types::rov_telimetry::data_serialize(rov_types::binary_stream &bs) {
    bs << roll;
    bs << pitch;
    bs << yaw;
    bs << depth;

    bs << mega_communication;
    bs << mini_communication;
    bs << esp_communication;
    bs << esp_state;
    bs << manipulator_rotated;
    bs << manipulator_opened_closed;
    for (auto &c : camera_rotate) {
        bs << c;
    }
    bs << magnet;
    bs << acoustic;

}

void rov_types::rov_telimetry::data_deserialize(rov_types::binary_stream &bs) {
    bs >> roll;
    bs >> pitch;
    bs >> yaw;
    bs >> depth;

    bs >> mega_communication;
    bs >> mini_communication;
    bs >> esp_communication;
    bs >> esp_state;
    bs >> manipulator_rotated;
    bs >> manipulator_opened_closed;
    for (auto &c : camera_rotate) {
        bs >> c;
    }
    bs >> magnet;
    bs >> acoustic;
}


void rov_types::rov_control::data_serialize(rov_types::binary_stream &bs) {
    bs << axis_x;
    bs << axis_y;
    bs << axis_z;
    bs << axis_w;
    bs << manipulator_rotate;
    bs << manipulator_open_close;
    for(const auto & b : camera_rotate) {
        bs << b;
    }
    bs << magnet;
    bs << acoustic;
    for(const auto & b : twisting_motors) {
        bs << b;
    }
}

void rov_types::rov_control::data_deserialize(rov_types::binary_stream &bs) {
    bs >> axis_x;
    bs >> axis_y;
    bs >> axis_z;
    bs >> axis_w;
    bs >> manipulator_rotate;
    bs >> manipulator_open_close;
    for(auto & b : camera_rotate) {
        bs >> b;
    }
    bs >> magnet;
    bs >> acoustic;
    for(auto & b : twisting_motors) {
        bs >> b;
    }
}

void rov_types::rov_hardware_control::data_serialize(rov_types::binary_stream &bs) {
    for(auto & p : horizontal_power) {
        bs << p;
    }
    for(auto & p : vertical_power) {
        bs << p;
    }
    bs << manipulator_rotate;
    bs << manipulator_open_close;
    for(auto & b : camera_rotate) {
        bs << b;
    }
    bs << magnet;
    bs << acoustic;
    for(const auto & b : twisting_motors) {
        bs << b;
    }
}

void rov_types::rov_hardware_control::data_deserialize(rov_types::binary_stream &bs) {
    for(auto & p : horizontal_power) {
        bs >> p;
    }
    for(auto & p : vertical_power) {
        bs >> p;
    }

    bs >> manipulator_rotate;
    bs >> manipulator_open_close;
    for(auto & b : camera_rotate) {
        bs >> b;
    }
    bs >> magnet;
    bs >> acoustic;
    for(auto & b : twisting_motors) {
        bs >> b;
    }
}

void rov_types::rov_hardware_firmware::data_serialize(rov_types::binary_stream &bs) {
    bs << size;
    for (const auto & byte : firmware) {
        bs << byte;
    }
}

void rov_types::rov_hardware_firmware::data_deserialize(rov_types::binary_stream &bs) {
    bs >> size;
    if (size != 0) {
        firmware.resize(size);
        for (std::size_t i = 0; i < size; i++) {
            bs >> firmware[i];
        }
    }
}

rov_types::serializable::error_code rov_types::rov_hardware_firmware::deserialize(const std::vector<uint8_t> &input) {
    binary_stream bs(input);
    std::uint8_t packet_id;

    if (input.size() < meta().packet_size){
        return error_code::size_less;
    }

    bs >> packet_id;
    if (packet_id != meta().packet_id) {
        return error_code::wrong_id;
    }

    data_deserialize(bs);

    std::int16_t current_crc = 0;
    bs >> current_crc;

    if (current_crc != crc::calculateCRC(input.data(), size + 1 + sizeof(std::size_t))) {
        return error_code::crc_mismatch;
    }

    if (input.size() > size + meta().packet_size){
        return error_code::success_size_greater;
    }

    return success;
}

void rov_types::rov_hardware_telimetry::data_serialize(rov_types::binary_stream &bs) {
    bs << depth;
    bs << mega_communication;
    bs << mini_communication;
    bs << esp_communication;
    bs << esp_state;
    bs << manipulator_rotated;
    bs << manipulator_opened_closed;
    for(auto & b : camera_rotate) {
        bs << b;
    }
    bs << magnet;
    bs << acoustic;
}

void rov_types::rov_hardware_telimetry::data_deserialize(rov_types::binary_stream &bs) {
    bs >> depth;
    bs >> mega_communication;
    bs >> mini_communication;
    bs >> esp_communication;
    bs >> esp_state;
    bs >> manipulator_rotated;
    bs >> manipulator_opened_closed;
    for(auto & b : camera_rotate) {
        bs >> b;
    }
    bs >> magnet;
    bs >> acoustic;
}

void rov_types::rov_mini_telimetry::data_serialize(rov_types::binary_stream &bs) {
    for(auto & b : pins) {
        bs << b;
    }
    for(auto & b : value) {
        bs << b;
    }
    bs << acoustics;
    bs << mini_communicator_feedback;
}

void rov_types::rov_mini_telimetry::data_deserialize(rov_types::binary_stream &bs) {
    for(auto & b : pins) {
        bs >> b;
    }
    for(auto & b : value) {
        bs >> b;
    }
    bs >> acoustics;
    bs >> mini_communicator_feedback;
}

void rov_types::rov_mini_control::data_serialize(rov_types::binary_stream &bs) {
    for(auto & b : pins) {
        bs << b;
    }
    for(auto & b : value) {
        bs << b;
    }
    bs << acoustics;
}

void rov_types::rov_mini_control::data_deserialize(rov_types::binary_stream &bs) {
    for(auto & b : pins) {
        bs >> b;
    }
    for(auto & b : value) {
        bs >> b;
    }
    bs >> acoustics;
}
