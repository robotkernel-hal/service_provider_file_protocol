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

#ifndef __INTERFACE_FILE_PROTOCOL_H__
#define __INTERFACE_FILE_PROTOCOL_H__

#include "module_intf.h"
#include "robotkernel/interface_base.h"

namespace interface_file_protocol {
    
class file_protocol : public robotkernel::interface_base {
    public:
        //! default construction
        /*!
         * \param node configuration node
         */
        file_protocol(const YAML::Node& node);
        
        //! service callback request file read
        /*!
         * \param message service message
         * \return success
         */
        int service_file_read(YAML::Node& message);
        static const std::string service_definition_file_read;	

        //! service callback request file write
        /*!
         * \param message service message
         * \return success
         */
        int service_file_write(YAML::Node& message);
        static const std::string service_definition_file_write;	
};

} // namespace interface

#endif // __INTERFACE_FILE_PROTOCOL_H__

