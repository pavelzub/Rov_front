//
// Created by zinjkov on 05.04.18.
//

#ifndef SERI_BASE_PACKET_T_HPP
#define SERI_BASE_PACKET_T_HPP

#include "serializable.hpp"
#include "meta.hpp"
#include "binary_stream.hpp"
#include "crc.hpp"
namespace rov_types {
    template <uint8_t packet_id_, uint8_t payload_size_>
    class base_packet_t : public serializable {
    public:
        typedef meta_traits<packet_id_, payload_size_> meta;

        virtual std::vector<std::uint8_t> serialize() override  {
            binary_stream bs;
            bs << meta().packet_id;

            data_serialize(bs);

            bs << crc::calculateCRC(bs.data().data(), bs.data().size());
            return bs.data();
        }

        virtual error_code deserialize(const std::vector<std::uint8_t> &input) override {
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

            if (current_crc != crc::calculateCRC(input.data(), meta().payload_size)) {
                return error_code::crc_mismatch;
            }

            if (input.size() > meta().packet_size){
                return error_code::success_size_greater;
            }

            return success;
        }

    protected:

        virtual void data_serialize(binary_stream &bs) = 0;
        virtual void data_deserialize(binary_stream &bs) = 0;
    };
}


#endif //SERI_BASE_PACKET_T_HPP
