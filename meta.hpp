//
// Created by zinjkov on 05.04.18.
//

#ifndef SERI_META_HPP
#define SERI_META_HPP

#include <cstdint>

template <uint8_t packet_id_, uint8_t payload_size_, uint16_t packet_size_>
struct meta_traits{
    const uint8_t packet_id = packet_id_;
    const uint8_t payload_size = payload_size_;
    const uint16_t packet_size = packet_size_;

    void operator=(const meta_traits &rv) {

    }
};


#endif //SERI_META_HPP
