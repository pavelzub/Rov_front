//
// Created by zinjkov on 30.03.18.
//

#include "crc.hpp"
namespace rov_types {
    namespace crc {
        namespace prvt {

            //! CRC values
            static const int16_t poly_val = 0x1021;
            static const int16_t seed_val = 0xFFFF;

            int16_t updateCRC(int16_t acc, const int8_t input) {
                acc ^= (input << 8);
                for (int8_t i = 0; i < 8; i++) {
                    if ((acc & 0x8000) == 0x8000) {
                        acc <<= 1;
                        acc ^= poly_val;
                    } else {
                        acc <<= 1;
                    }
                }
                return acc;
            }

        }

        std::int16_t calculateCRC(const uint8_t *data, std::size_t len) {
            int16_t crcout = prvt::seed_val;
            unsigned long i;
            for (i = 0; i < len; ++i) {
                crcout = prvt::updateCRC(crcout, data[i]);
            }

            return crcout;
        }
    }
}