//! robotkernel interface file protocol
/*!
 * author: Robert Burger
 *
 * $Id$
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

#include <string.h>
#include <string_util/string_util.h>

#include "interface_file_protocol.h"
#include "robotkernel/kernel.h"
#include "robotkernel/exceptions.h"

INTERFACE_DEF(file_protocol, interface_file_protocol::file_protocol)

using namespace std;
using namespace robotkernel;
using namespace interface_file_protocol;

//! default construction
/*!
 * \param node configuration node
 */
file_protocol::file_protocol(const YAML::Node& node) 
    : interface_base("file_protocol", node) {
    kernel& k = *kernel::get_instance();
    if (!k.clnt)
        throw robotkernel::str_exception("[interface_sercos_protocol|%s] "
                "no ln_connection!\n", mod_name.c_str());

    stringstream base;
    base << k.clnt->name << "." << mod_name << "." << dev_name << ".";

}

