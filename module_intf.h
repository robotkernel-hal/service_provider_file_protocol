//! robotkernel interface file protocol requests
/*!
 * author: Robert Burger
 *
 * $Id$
 */

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

#ifndef __INTERFACE_FILE_PROTOCOL_MODULE_INTF_H__
#define __INTERFACE_FILE_PROTOCOL_MODULE_INTF_H__

#define MOD_REQUEST_FILE_PROTOCOL_MAGIC  0x24
#define MOD_REQUEST_FILE_PROTOCOL(x, s) \
    __MOD_REQUEST((MOD_REQUEST_FILE_PROTOCOL_MAGIC), (x), __MOD_REQUEST_TYPE(s))

//! file read 
typedef struct file_read_info {
    int       slave_id;             //! [in]     slave id
    char*     password;             //! [in]     file password (NULL-terminated)
    char*     file_name;            //! [in]     file name (NULL-terminated)

    uint8_t*  file_data;            //! [out]    file data, allocated by module
    ssize_t   file_data_len;        //! [out]    length of file data
} file_read_info_t;

#define MOD_REQUEST_FILE_READ  \
    MOD_REQUEST_FILE_PROTOCOL(0x0001, file_read_info_t)

#endif // __INTERFACE_FILE_PROTOCOL_MODULE_INTF_H__

