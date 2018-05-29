//
// Created by zinjkov on 05.04.18.
//

#ifndef SERI_META_HPP
#define SERI_META_HPP

#include <cstdint>

template <uint8_t packet_id_, uint8_t payload_size_>
struct meta_traits{
    const uint8_t packet_id = packet_id_;
    const uint8_t payload_size = payload_size_ + static_cast<uint8_t>(1);
    const uint16_t packet_size = payload_size_ + static_cast<uint8_t>(3);

    void operator=(const meta_traits &rv) {

    }
};


#endif //SERI_META_HPP
