//
// Created by zinjkov on 30.03.18.
//

#include "rov_data_types.hpp"


void rovTypes::rov_telimetry::data_serialize(rovTypes::binary_stream &bs) {
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

void rovTypes::rov_telimetry::data_deserialize(rovTypes::binary_stream &bs) {
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


void rovTypes::rov_control::data_serialize(rovTypes::binary_stream &bs) {
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
    bs << secondary_maninpulator;
}

void rovTypes::rov_control::data_deserialize(rovTypes::binary_stream &bs) {
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
    bs >> secondary_maninpulator;
}

void rovTypes::rov_hardware_control::data_serialize(rovTypes::binary_stream &bs) {
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

void rovTypes::rov_hardware_control::data_deserialize(rovTypes::binary_stream &bs) {
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


void rovTypes::rov_hardware_telimetry::data_serialize(rovTypes::binary_stream &bs) {
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
    for (auto & b : twisting_motors) {
        bs << b;
    }
}

void rovTypes::rov_hardware_telimetry::data_deserialize(rovTypes::binary_stream &bs) {
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
    for (auto & b : twisting_motors) {
        bs >> b;
    }
}

void rovTypes::rov_hardware_firmware::data_serialize(rovTypes::binary_stream &bs) {
    bs << size;
    for (const auto & byte : firmware) {
        bs << byte;
    }
}

void rovTypes::rov_hardware_firmware::data_deserialize(rovTypes::binary_stream &bs) {
    bs >> size;
    if (size != 0) {
        firmware.resize(size);
        for (std::size_t i = 0; i < size; i++) {
            bs >> firmware[i];
        }
    }
}

rovTypes::serializable::error_code rovTypes::rov_hardware_firmware::deserialize(const std::vector<uint8_t> &input) {
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

void rovTypes::rov_mini_telimetry::data_serialize(rovTypes::binary_stream &bs) {
    for(auto & b : twisting_motors_feedback) {
        bs << b;
    }
    bs << magnet;
    bs << acoustics;
    bs << mini_communicator_feedback;
    bs << manipulator_feedback;
}

void rovTypes::rov_mini_telimetry::data_deserialize(rovTypes::binary_stream &bs) {
    for(auto & b : twisting_motors_feedback) {
        bs >> b;
    }
    bs >> magnet;
    bs >> acoustics;
    bs >> mini_communicator_feedback;
    bs >> manipulator_feedback;
}

void rovTypes::rov_mini_control::data_serialize(rovTypes::binary_stream &bs) {
    for(auto & b : twisting_motors) {
        bs << b;
    }
    bs << magnet;
    bs << acoustics;
    bs << manipulator;
}

void rovTypes::rov_mini_control::data_deserialize(rovTypes::binary_stream &bs) {
    for(auto & b : twisting_motors) {
        bs >> b;
    }
    bs >> magnet;
    bs >> acoustics;
    bs >> manipulator;
}

void rovTypes::rov_debug::data_serialize(rovTypes::binary_stream &bs) {
    for (auto &b : thruster_power) {
        bs << b;
    }
}

void rovTypes::rov_debug::data_deserialize(rovTypes::binary_stream &bs) {
    for (auto &b : thruster_power) {
        bs >> b;
    }
}

void rovTypes::rov_pd::data_serialize(rovTypes::binary_stream &bs) {
    bs << yaw_p;
    bs << yaw_d;

    bs << depth_p;
    bs << depth_d;

    bs << roll_p;
    bs << roll_d;
    bs << roll_to_set;

    bs << pitch_p;
    bs << pitch_d;
    bs << pitch_to_set;

}

void rovTypes::rov_pd::data_deserialize(rovTypes::binary_stream &bs) {
    bs >> yaw_p;
    bs >> yaw_d;

    bs >> depth_p;
    bs >> depth_d;

    bs >> roll_p;
    bs >> roll_d;
    bs >> roll_to_set;

    bs >> pitch_p;
    bs >> pitch_d;
    bs >> pitch_to_set;
}

void rovTypes::rov_enable_pd::data_serialize(rovTypes::binary_stream &bs) {
    bs << yaw_pd;
    bs << depth_pd;
    bs << pitch_pd;
    bs << roll_pd;
}

void rovTypes::rov_enable_pd::data_deserialize(rovTypes::binary_stream &bs) {
    bs >> yaw_pd;
    bs >> depth_pd;
    bs >> pitch_pd;
    bs >> roll_pd;
}
