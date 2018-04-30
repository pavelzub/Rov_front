//
// Created by zinjkov on 30.03.18.
//

#ifndef RC_ROV_SERVER_SERIALAZER_HPP
#define RC_ROV_SERVER_SERIALAZER_HPP


#include <iostream>
#include <vector>
#include "binary_stream.hpp"
namespace rovTypes {

    struct serializable {
        enum error_code : uint8_t {
            success,
            success_size_greater,
            size_less,
            crc_mismatch,
            wrong_size,
            wrong_id
        };

        static bool check_for_success(error_code err);

        virtual std::vector<std::uint8_t> serialize() = 0;

        virtual error_code deserialize(const std::vector<std::uint8_t> &input) = 0;

        static std::string error_to_string(error_code err);
    };

};

#endif //RC_ROV_SERVER_SERIALAZER_HPP
