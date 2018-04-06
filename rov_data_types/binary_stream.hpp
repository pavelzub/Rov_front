//
// Created by zinjkov on 30.03.18.
//

#ifndef RC_ROV_SERVER_BINARY_STREAM_HPP
#define RC_ROV_SERVER_BINARY_STREAM_HPP

#include <vector>
#include <cstdint>
#include <stddef.h>
#include <cstring>
//#include <stdfloat.h>
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

        binary_stream &operator>>(uint8_t &val);
        binary_stream &operator>>(int8_t &val);
        binary_stream &operator>>(uint16_t &val);
        binary_stream &operator>>(int16_t &val);
        binary_stream &operator>>(uint32_t &val);
        binary_stream &operator>>(int32_t &val);
        binary_stream &operator>>(uint64_t &val);
        binary_stream &operator>>(int64_t &val);
        binary_stream &operator>>(float &val);
        binary_stream &operator>>(double &val);
        binary_stream &operator>>(long double &val);

        binary_stream &operator<<(const uint8_t &val);
        binary_stream &operator<<(const int8_t &val);
        binary_stream &operator<<(const uint16_t &val);
        binary_stream &operator<<(const int16_t &val);
        binary_stream &operator<<(const uint32_t &val);
        binary_stream &operator<<(const int32_t &val);
        binary_stream &operator<<(const uint64_t &val);
        binary_stream &operator<<(const int64_t &val);
        binary_stream &operator<<(const float &val);
        binary_stream &operator<<(const double &val);
        binary_stream &operator<<(const long double &val);

        binary_stream &operator<<(uint8_t &val);
        binary_stream &operator<<(int8_t &val);
        binary_stream &operator<<(uint16_t &val);
        binary_stream &operator<<(int16_t &val);
        binary_stream &operator<<(uint32_t &val);
        binary_stream &operator<<(int32_t &val);
        binary_stream &operator<<(uint64_t &val);
        binary_stream &operator<<(int64_t &val);
        binary_stream &operator<<(float &val);
        binary_stream &operator<<(double &val);
        binary_stream &operator<<(long double &val);


        template<typename T>
        static inline T swap_endian(T u) {
            union {
                T u;
                unsigned char u8[sizeof(T)];
            } source, dest;

            source.u = u;

            for (std::size_t k = 0; k < sizeof(T); k++)
                dest.u8[k] = source.u8[sizeof(T) - k - 1];

            return dest.u;
        }

    private:
        byte_ordering m_system_type;
        byte_ordering m_ordering;
        std::size_t m_counter;
        std::vector<std::uint8_t> m_data;

        template<typename T>
        inline void read(T &data) {
            std::memcpy((void *) (&data), (void *) (m_data.data() + m_counter), sizeof(T));
            if (m_ordering != m_system_type) {
                data = swap_endian<T>(data);
            }
            m_counter += sizeof(T);
        }

        template<typename T>
        inline void write(const T &data) {
            T loc = data;

            if (m_ordering != m_system_type) {
                loc = swap_endian<T>(loc);
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
