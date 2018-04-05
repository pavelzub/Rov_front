//
// Created by zinjkov on 30.03.18.
//

#include "binary_stream.hpp"
#include <iostream>
namespace rov_types {

    binary_stream::binary_stream():
            m_counter(0){
        unsigned short x = 1; /* 0x0001 */
        m_system_type = (*((unsigned char *) &x) == 0) ? byte_ordering::big_endian : byte_ordering::little_endian;
        m_ordering = byte_ordering::big_endian;
    }

    binary_stream::~binary_stream() {

    }

    const std::vector<std::uint8_t> &binary_stream::data() {
        return m_data;
    }

    void binary_stream::change_byte_ordering(binary_stream::byte_ordering ordering) {
        if (m_ordering != ordering) {
            for(auto &b : m_data) {
                b = swap_endian(b);
            }
            m_ordering = ordering;
        }
    }

    binary_stream::binary_stream(const std::vector<std::uint8_t> &byte_array) :
        m_counter(0),
        m_data(byte_array)
    {
        unsigned short x = 1; /* 0x0001 */
        m_system_type = (*((unsigned char *) &x) == 0) ? byte_ordering::big_endian : byte_ordering::little_endian;
        m_ordering = byte_ordering::big_endian;
    }

}