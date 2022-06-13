/**
 * @author zouxiaoliang
 * @date 2022/06/13
 */

#include "HardwareInfo.h"

#include <iostream>

void HardwareInfo::scan() {
    hd_t* hd = nullptr;

    hd_data_t* hd_data = new hd_data_t;
    hd_data->progress  = NULL;
    hd_data->debug     = ~(HD_DEB_DRIVER_INFO | HD_DEB_HDDB);

    hd_clear_probe_feature(hd_data, pr_all);
    hd_set_probe_feature(hd_data, pr_all);

    hd_scan(hd_data);
    hd = hd_data->hd;

    std::map<hd_probe_feature_t, std::string> hd_infos;

    hd_t* hd1;
    char* s;

    for (int item = 1; item < hw_all; item++) {

        s = hd_hw_item_name(static_cast<hd_hw_item_t>(item));

        if (!s) {
            continue;
        }

        if (item == hw_sys) {
            continue;
        }

        std::vector<std::tuple<std::string, std::string>>* devs = nullptr;

        int i = 0;
        for (hd1 = hd; hd1; hd1 = hd1->next) {
            if (hd1->hw_class == item) {
                if (!i++) {
                    auto r = m_details.emplace(s, std::vector<std::tuple<std::string, std::string>>{});
                    devs   = &(r.first->second);
                }

                if (nullptr != devs) {
                    devs->push_back(
                        {hd1->unix_dev_name ? hd1->unix_dev_name : "(none)", hd1->model ? hd1->model : "(none)"});
                }
            }
        }
    }

    hd_free_hd_data(hd_data);
    delete hd_data;
}
std::set<std::string> HardwareInfo::get(const std::string& dev_type) {
    auto found = m_details.find(dev_type);
    if (m_details.end() == found) {
        return {};
    }

    std::set<std::string> dev_venders;
    for (const auto& [dev, vender] : found->second) {
        dev_venders.emplace(vender);
    }

    return dev_venders;
}
void HardwareInfo::show() {
    for (const auto& item : m_details) {
        std::cout << item.first << ":" << std::endl;
        for (const auto& [devname, model] : item.second) {
            std::cout << " |- " << devname << " - " << model << std::endl;
        }
    }
}
