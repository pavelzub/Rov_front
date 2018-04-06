//
// Created by zinjkov on 30.03.18.
//

#ifndef RC_ROV_SERVER_CRC_HPP
#define RC_ROV_SERVER_CRC_HPP

#include <cstdint>
namespace rov_types {
    namespace crc {
        std::int16_t calculateCRC(const uint8_t *data, std::size_t len);
    };
};


#endif //RC_ROV_SERVER_CRC_HPP
