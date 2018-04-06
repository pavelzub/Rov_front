//
// Created by zinjkov on 05.04.18.
//

#include "base_packet_t.hpp"

namespace rov_types {


//    std::vector<std::uint8_t> base_packet_t::serialize() {
//        binary_stream bs;
//        bs << meta::packet_id;
//        data_serialize(bs);
//        bs << crc::calculateCRC(bs.data().data(), meta::payload_size);
//        return bs.data();
//    }

//    serializable::error_code base_packet_t::deserialize(const std::vector<std::uint8_t> &input) {
//        binary_stream bs(input);
//        std::uint8_t packet_id;
//
//        if (input.size() < meta::packet_size){
//            return error_code::size_less;
//        }
//
//        bs >> packet_id;
//        if (packet_id != meta::packet_id) {
//            return error_code::wrong_id;
//        }
//
//        data_deserialize(bs);
//
//        std::int16_t current_crc = 0;
//        bs >> current_crc;
//
//        if (current_crc != crc::calculateCRC(input.data(), meta::payload_size)) {
//            return error_code::crc_mismatch;
//        }
//
//        if (input.size() > meta::packet_size){
//            return error_code::success_size_greater;
//        }
//
//        return success;
//    }
}
