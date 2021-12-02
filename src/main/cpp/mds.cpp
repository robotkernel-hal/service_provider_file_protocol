//! robotkernel service provider file protocol service definitions
/*!
 * author: Robert Burger
 */

// vim: tabstop=4 softtabstop=4 shiftwidth=4 expandtab:

/*
 * This file is part of robotkernel.
 *
 * robotkernel is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * robotkernel is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with robotkernel.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "mds.h"
#include <list>

const std::string service_provider::file_protocol::service_definition_file_read =
"name: service_provider/file_protocol/file_read\n"
"request:\n"
"- uint32_t: password\n"
"- string: file_name\n"
"response:\n"
"- vector/uint8_t: file_data\n"
"- string: error_message\n";

const std::string service_provider::file_protocol::service_definition_file_write =
"name: service_provider/file_protocol/file_write\n"
"request:\n"
"- uint32_t: password\n"
"- string: file_name\n"
"- vector/uint8_t: file_data\n"
"response:\n"
"- string: error_message\n";

typedef void (*get_sd_t)(std::list<std::string>& sd_list);
extern "C" void get_sd(std::list<std::string>& sd_list) {
    sd_list.push_back(service_provider::file_protocol::service_definition_file_read);
    sd_list.push_back(service_provider::file_protocol::service_definition_file_write);
}

