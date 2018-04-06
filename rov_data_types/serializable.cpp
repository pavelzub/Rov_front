//
// Created by zinjkov on 30.03.18.
//

#include "serializable.hpp"


std::string rov_types::serializable::error_to_string(rov_types::serializable::error_code err) {
    std::string str_to_ret;
    switch (err) {
        case error_code::success: str_to_ret = "success";
            break;
        case error_code::success_size_greater: str_to_ret = "success_size_greater";
            break;
        case error_code::size_less: str_to_ret = "size_less";
            break;
        case error_code::crc_mismatch: str_to_ret = "crc_mismatch";
            break;
        case error_code::wrong_size: str_to_ret = "wrong_size";
            break;
        case error_code::wrong_id: str_to_ret = "wrong_id";
            break;
        default:str_to_ret = "unknown_error";
    }
    return str_to_ret;
}

bool rov_types::serializable::check_for_success(rov_types::serializable::error_code err) {
    return (err == success) || (err == success_size_greater);

}
