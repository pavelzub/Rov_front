//
// Created by zinjkov on 30.03.18.
//

#ifndef RC_ROV_SERVER_BINARY_STREAM_HPP
#define RC_ROV_SERVER_BINARY_STREAM_HPP

#include <vector>
#include <cstdint>
#include <cstring>
#include <iostream>
namespace rov_types {
    class binary_stream {
    public:
        enum class byte_ordering {
            big_endian,
            little_endian
        };

        binary_stream();

        binary_stream(const std::vector<std::uint8_t> &byte_array);

        ~binary_stream();

        const std::vector<std::uint8_t> &data();

        void change_byte_ordering(byte_ordering t);

        template<typename T>
        binary_stream &operator>>(T &val) {
            if ((m_data.size() - m_counter) >= sizeof(T))
                read(val);
            return *this;
        }

        template<typename T>
        binary_stream &operator<<(const T &val) {
            write(val);
            return *this;
        }

    private:
        byte_ordering m_system_type;
        byte_ordering m_ordering;
        std::size_t m_counter;
        std::vector<std::uint8_t> m_data;


        template<typename T>
        inline T swap_endian(T u) {
            union {
                T u;
                unsigned char u8[sizeof(T)];
            } source, dest;

            source.u = u;

            for (std::size_t k = 0; k < sizeof(T); k++)
                dest.u8[k] = source.u8[sizeof(T) - k - 1];

            return dest.u;
        }

        template<typename T>
        inline void read(T &data) {
            std::memcpy((void *) (&data), (void *) (m_data.data() + m_counter), sizeof(T));
            if (m_ordering != m_system_type) {
                data = swap_endian(data);
            }
            m_counter += sizeof(T);
        }

        template<typename T>
        inline void write(const T &data) {
            T loc = data;

            if (m_ordering != m_system_type) {
                loc = swap_endian(loc);
            }

            union {
                T u;
                unsigned char u8[sizeof(T)];
            } source;

            source.u = loc;
            for (auto &b : source.u8) {
                m_data.emplace_back(b);
            }

        }
    };

}
#endif //RC_ROV_SERVER_BINARY_STREAM_HPP
