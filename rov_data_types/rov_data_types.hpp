//
// Created by zinjkov on 30.03.18.
//

#ifndef RC_ROV_SERVER_ROV_DATA_TYPES_HPP
#define RC_ROV_SERVER_ROV_DATA_TYPES_HPP

#include <cstdint>
#include "base_packet_t.hpp"


namespace rov_types {
    struct rov_telimetry : public base_packet_t<0x1E, 27, 29> {

        float yaw = 0; //-180, 180
        float pitch = 0; //-180, 180
        float roll = 0; //-180, 180
        float depth = 0; //+inf
        std::uint8_t mega_communication = 0; //0 not connected, 1 connected
        std::uint8_t mini_communication = 0; //0 not connected, 1 connected
        std::uint8_t esp_communication = 0;  //0 not connected, 1 connected
        std::uint8_t esp_state = 0; //0 searching wifi, 1 connecting wifi, 2 connecting tcp, 3 http request
        std::int8_t manipulator_rotated = 0; //-1, 1 feedback
        std::int8_t manipulator_opened_closed = 0; //-1, 1 feedback
        std::int8_t camera_rotate[2] = {0}; //-1, 1 x2 feedback
        std::int8_t magnet = 0; //0 - close, 1 open
        std::int8_t acoustic = 0; // -1 close, 0 no noise, 1 open
    private:
        void data_serialize(binary_stream &bs) override final;

        void data_deserialize(binary_stream &bs) override final;
    };

    struct rov_control : public base_packet_t<0x2E, 16, 18> {

        std::int8_t axis_x = 0; //-100, 100
        std::int8_t axis_y = 0; //-100, 100
        std::int8_t axis_z = 0; //-100, 100
        std::int8_t axis_w = 0; //-100, 100
        std::int8_t manipulator_rotate = 0; //-1, 1
        std::int8_t manipulator_open_close = 0; //-1, 1
        std::int8_t camera_rotate[2] = {0}; //-1, 1
        std::int8_t magnet = 0; //0 - close, 1 open
        std::int8_t acoustic = 0; // -1 close, 0 no noise, 1 open
        std::int8_t twisting_motors[4] = {0}; // крутилки -1 1 х4
        int8_t secondary_maninpulator = 0;
    private:
        void data_serialize(binary_stream &bs) override final;

        void data_deserialize(binary_stream &bs) override final;
    };





    struct rov_hardware_firmware : public base_packet_t<0x3E, 9, 11> {
        std::size_t size;
        std::string firmware;

        virtual error_code deserialize(const std::vector<std::uint8_t> &input) override final;
    private:
        void data_serialize(binary_stream &bs) override final;

        void data_deserialize(binary_stream &bs) override final;
    };

    struct rov_debug : public base_packet_t<0x4E, 9, 11> {
        int8_t thruster_power[8] = {0};

    private:
        void data_serialize(binary_stream &bs) override final;

        void data_deserialize(binary_stream &bs) override final;
    };

    struct rov_enable_pd : public base_packet_t<0x4E, 5, 7> {
        int8_t yaw_pd = -1;   // -1 - default, 0 - disable, 1 - enable
        int8_t depth_pd = -1; // -1 - default, 0 - disable, 1 - enable
        int8_t roll_pd = -1;  // -1 - default, 0 - disable, 1 - enable
        int8_t pitch_pd = -1; // -1 - default, 0 - disable, 1 - enable

    private:
        void data_serialize(binary_stream &bs) override final;

        void data_deserialize(binary_stream &bs) override final;
    };


    struct rov_pd : public base_packet_t<0x4E, 41, 43> {
        float yaw_p = -1;
        float yaw_d = 1;

        float depth_p = -1;
        float depth_d = -1;

        float roll_p = -1;
        float roll_d = -1;
        float roll_to_set = -200;

        float pitch_p = -1;
        float pitch_d = -1;
        float pitch_to_set = -200;

    private:
        void data_serialize(binary_stream &bs) override final;

        void data_deserialize(binary_stream &bs) override final;
    };

    struct rov_hardware_control : public base_packet_t<0x1A, 19, 21> {
        int8_t horizontal_power[4] = { 0 }; //-100, 100 x 4
        int8_t vertical_power[4] = { 0 }; //-100, 100 x 4
        int8_t manipulator_rotate = 0; //-1 left, 1 right, 0 stop
        int8_t manipulator_open_close = 0; //-1 close, 1 open, 0 stop
        int8_t camera_rotate[2] = { 0 }; //-1 bottom, 1 top, 0 stop
        int8_t magnet = 0; //0 - close, 1 open
        int8_t acoustic = 0; // -1 close, 0 no noise, 1 open
        int8_t twisting_motors[4] = { 0 }; // �������� -1 1 �4
    private:
        void data_serialize(binary_stream &bs) override final;

        void data_deserialize(binary_stream &bs) override final;
    };


    struct rov_hardware_telimetry : public base_packet_t<0x2A, 19, 21> {
        float depth = 0; //+inf
        uint8_t mega_communication = 0; //0 not connected, 1 connected
        uint8_t mini_communication = 0; //0 not connected, 1 connected
        uint8_t esp_communication = 0;  //0 not connected, 1 connected
        uint8_t esp_state = 0; //0 searching wifi, 1 connecting wifi, 2 connecting tcp, 3 http request
        int8_t manipulator_rotated = 0; //-1, 1 feedback
        int8_t manipulator_opened_closed = 0; //-1, 1 feedback
        int8_t camera_rotate[2] = { 0 }; //-1, 1 x2 feedback
        int8_t magnet = 0; //0 - close, 1 open
        int8_t acoustic = 0; // -1 close, 0 no noise, 1 open
        int8_t twisting_motors[4] = { 0 };
    private:
        void data_serialize(binary_stream &bs) override final;

        void data_deserialize(binary_stream &bs) override final;
    };

    struct rov_mini_telimetry : public base_packet_t<0x1B, 9, 11> {
        int8_t twisting_motors_feedback[4] = { 0 };
        int8_t magnet = 0;
        int8_t acoustics = 0;
        int8_t mini_communicator_feedback = 0;
        uint8_t manipulator_feedback = 0;
    private:
        void data_serialize(binary_stream &bs) override final;

        void data_deserialize(binary_stream &bs) override final;
    };

    struct rov_mini_control : public base_packet_t<0x2B, 8, 10> {
        int8_t twisting_motors[4] = { 0 };
        int8_t acoustics = 0;
        int8_t manipulator = 0;
        int8_t magnet = 0;
    private:
        void data_serialize(binary_stream &bs) override final;

        void data_deserialize(binary_stream &bs) override final;
    };
};


#endif //RC_ROV_SERVER_ROV_DATA_TYPES_HPP
