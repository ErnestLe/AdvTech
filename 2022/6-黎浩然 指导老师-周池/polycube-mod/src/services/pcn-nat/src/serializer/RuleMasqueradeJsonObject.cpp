/**
* nat API
* nat API generated from nat.yang
*
* OpenAPI spec version: 1.0.0
*
* NOTE: This class is auto generated by the swagger code generator program.
* https://github.com/polycube-network/swagger-codegen.git
* branch polycube
*/


/* Do not edit this file manually */



#include "RuleMasqueradeJsonObject.h"
#include <regex>

namespace io {
namespace swagger {
namespace server {
namespace model {

RuleMasqueradeJsonObject::RuleMasqueradeJsonObject() {
  m_enabledIsSet = false;
}

RuleMasqueradeJsonObject::RuleMasqueradeJsonObject(const nlohmann::json &val) :
  JsonObjectBase(val) {
  m_enabledIsSet = false;


  if (val.count("enabled")) {
    setEnabled(val.at("enabled").get<bool>());
  }
}

nlohmann::json RuleMasqueradeJsonObject::toJson() const {
  nlohmann::json val = nlohmann::json::object();
  if (!getBase().is_null()) {
    val.update(getBase());
  }

  if (m_enabledIsSet) {
    val["enabled"] = m_enabled;
  }

  return val;
}

bool RuleMasqueradeJsonObject::getEnabled() const {
  return m_enabled;
}

void RuleMasqueradeJsonObject::setEnabled(bool value) {
  m_enabled = value;
  m_enabledIsSet = true;
}

bool RuleMasqueradeJsonObject::enabledIsSet() const {
  return m_enabledIsSet;
}

void RuleMasqueradeJsonObject::unsetEnabled() {
  m_enabledIsSet = false;
}


}
}
}
}

