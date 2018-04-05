//
// Created by zinjkov on 30.03.18.
//

#include "rov_data_types.hpp"
#include "crc.hpp"


std::vector<std::uint8_t> rov_types::rov_telimetry::serialize() {
    binary_stream bs;
    bs << meta::packet_id;
    bs << roll;
    bs << pitch;
    bs << yaw;
    bs << crc::calculateCRC(bs.data().data(), meta::payload_size);
    return bs.data();
}

rov_types::serializable::error_code rov_types::rov_telimetry::deserialize(const std::vector<std::uint8_t> &input) {
    binary_stream bs(input);
    std::uint8_t packet_id;

    if (input.size() < meta::packet_size){
        return error_code::size_less;
    }

    bs >> packet_id;
    if (packet_id != meta::packet_id) {
        return error_code::wrong_id;
    }

    bs >> roll;
    bs >> pitch;
    bs >> yaw;
    std::int16_t current_crc = 0;
    bs >> current_crc;

    if (current_crc != crc::calculateCRC(input.data(), meta::payload_size)) {
        return error_code::crc_mismatch;
    }

    if (input.size() > meta::packet_size){
        return error_code::success_size_greater;
    }

    return success;
}

std::vector<std::uint8_t> rov_types::rov_control::serialize() {
    binary_stream bs;
    bs << meta::packet_id;
    bs << axis_x;
    bs << axis_y;
    bs << axis_z;
    bs << axis_w;
    bs << crc::calculateCRC(bs.data().data(), meta::payload_size);
    return bs.data();
}

rov_types::serializable::error_code rov_types::rov_control::deserialize(const std::vector<std::uint8_t> &input) {
    binary_stream bs(input);
    std::uint8_t packet_id;

    if (input.size() < meta::packet_size){
        return error_code::size_less;
    }

    bs >> packet_id;
    if (packet_id != meta::packet_id) {
        return error_code::wrong_id;
    }

    bs >> axis_x;
    bs >> axis_y;
    bs >> axis_z;
    bs >> axis_w;

    std::int16_t current_crc = 0;
    bs >> current_crc;

    if (current_crc != crc::calculateCRC(input.data(), meta::payload_size)) {
        return error_code::crc_mismatch;
    }

    if (input.size() > meta::packet_size){
        return error_code::success_size_greater;
    }

    return success;
}
