/*
 * Copyright 2018 The Polycube Authors
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

// Modify these methods with your own implementation

#include "Helloworld.h"

// files generated by cmake from "Helloworld_dp_{ingress, egress}.c
#include "Helloworld_dp_egress.h"
#include "Helloworld_dp_ingress.h"

using namespace polycube::service;

Helloworld::Helloworld(const std::string name, const HelloworldJsonObject &conf)
    : Cube(conf.getBase(), {helloworld_code_ingress}, {helloworld_code_egress}),
      HelloworldBase(name) {
  logger()->info("Creating Helloworld instance");
  setAction(conf.getAction());

  // initialize ports map (at this point there are not ports)
  update_ports_map();

  addPortsList(conf.getPorts());
}

Helloworld::~Helloworld() {
  logger()->info("Destroying Helloworld instance");
}

void Helloworld::packet_in(Ports &port, polycube::service::PacketInMetadata &md,
                           const std::vector<uint8_t> &packet) {
  logger()->info("packet arrived to the slowpath from port {0}", port.name());
}

HelloworldActionEnum Helloworld::getAction() {
  uint8_t value = get_array_table<uint8_t>("action_map").get(0x0);
  return static_cast<HelloworldActionEnum>(value);
}

void Helloworld::setAction(const HelloworldActionEnum &value) {
  uint8_t action = static_cast<uint8_t>(value);
  get_array_table<uint8_t>("action_map").set(0x0, action);
}

void Helloworld::addPorts(const std::string &name,
                          const PortsJsonObject &conf) {
  if (get_ports().size() == 2) {
    throw std::runtime_error("maximum number of ports reached");
  }

  add_port<PortsJsonObject>(name, conf);
  logger()->info("port {0} was connected", name);
  update_ports_map();
}

void Helloworld::delPorts(const std::string &name) {
  remove_port(name);
  logger()->info("port {0} was removed", name);
  update_ports_map();
}

void Helloworld::update_ports_map() {
  auto ports_table = get_array_table<uint16_t>("ports_map");
  auto ports = get_ports();
  uint32_t i = 0;

  for (auto &port: ports) {
    ports_table.set(i, port->index());
    i++;
  }

  // mark other ports as empty (UINT16_MAX means empty)
  while (i < 2) {
    ports_table.set(i, UINT16_MAX);
    i++;
  }
}
