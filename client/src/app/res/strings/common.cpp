/*
** EPITECH PROJECT, 2021
** R-type
** File description:
** R-type
*/

#include <string>
#include <boost/dll/runtime_symbol_info.hpp>
#include <filesystem>
#include "app/res/strings/common.hpp"

static std::string getFullPath()
{
    boost::system::error_code ec;
    auto path = boost::dll::program_location(ec);
    if (ec != boost::system::errc::errc_t::success) {
        return std::filesystem::current_path().string();
    }
    return path.parent_path().string();
}

CommonString::CommonString()
{
    auto path = getFullPath();
    list.emplace("full_path", path);    // TODO get absolute path of the exec instead of the current directory
    list.emplace("helvetica_font", path + "/assets/fonts/helvetica/helvetica.ttf");
    list.emplace("foxy_red_eye", path + "/assets/icon/foxy_red_eye_white.png");
    list.emplace("foxy_head_trans_coffe", path + "/assets/icon/foxy_head_trans_redeye_coffe.png");
    list.emplace("foxy_head_trans_gray", path + "/assets/icon/foxy_head_trans_gray3.png");
    list.emplace("Loader_Blue", path + "/assets/loader/blue.png");
    list.emplace("Loader_Green", path + "/assets/loader/green.png");
    list.emplace("extend image", path + "/assets/extend.png");
}