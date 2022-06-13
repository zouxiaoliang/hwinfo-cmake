/**
 * @author zouxiaoliang
 * @date 2022/06/13
 */

#ifndef HARDWAREINFO_H
#define HARDWAREINFO_H

#include <hwinfo/src/hd/hd.h>
#include <map>
#include <string>
#include <set>
#include <vector>

typedef std::map<std::string, std::vector<std::tuple<std::string, std::string>>>
    HardwareDetails;

/**
 * @brief 简单的硬件信息扫描，基于hwinfo工具实现的硬件信息扫描
 */
class HardwareInfo {
private:
  typedef std::map<std::string,
                   std::vector<std::tuple<std::string, std::string>>>
      HardwareDetails;

public:
  /**
   * @brief scan the hardware info
   */
  void scan();

  /**
   * @brief get hardware vendor info
   *
   * @param dev_type
   * @return std::set<std::string>
   */
  std::set<std::string> get(const std::string &dev_type);

  void show();

private:
  HardwareDetails m_details;
};

#endif // HARDWAREINFO_H
