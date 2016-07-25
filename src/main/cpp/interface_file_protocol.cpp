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

#ifndef __linux__
char *strndup(const char *s, size_t n) {
    char *result;
    size_t len = strlen (s);

    if (n < len)
        len = n;

    result = (char *) malloc (len + 1);
    if (!result)
        return 0;

    result[len] = '\0';
    return (char *) memcpy (result, s, len);
}
#endif

//! default construction
/*!
 * \param node configuration node
 */
file_protocol::file_protocol(const YAML::Node& node) 
    : interface_base("file_protocol", node) {
    kernel& k = *kernel::get_instance();
    if (!k.clnt)
        throw robotkernel::str_exception("[interface_file_protocol|%s] "
                "no ln_connection!\n", mod_name.c_str());

    stringstream base;
    base << k.clnt->name << "." << mod_name << "." << dev_name << ".";

    register_file_read(k.clnt, base.str() + "file_protocol.file_read");
    register_file_write(k.clnt, base.str() + "file_protocol.file_write");
}
        
int file_protocol::on_file_read(ln::service_request& req, 
        ln_service_robotkernel_file_protocol_file_read& svc) {
    file_readwrite_info_t frwi;
    memset(&frwi, 0, sizeof(frwi));
    frwi.slave_id  = slave_id;
    frwi.password  = strndup(svc.req.password, svc.req.password_len);
    frwi.file_name = strndup(svc.req.file_name, svc.req.file_name_len);

    // execute module request file read
    int ret = kernel::request_cb(mod_name.c_str(), 
            MOD_REQUEST_FILE_READ, (void *)&frwi);
    if (ret == -1) {
        printf("got error\n");
        if (frwi.error_message) 
            svc.resp.error_message = frwi.error_message;
        else
            svc.resp.error_message = strdup("reading file failed!");

        svc.resp.error_message_len = strlen(svc.resp.error_message);

        goto exit;
    }

    if (frwi.file_data && (frwi.file_data_len > 0)) {
        // copy file data
        svc.resp.file_data_len = frwi.file_data_len;
        svc.resp.file_data = (uint8_t *)malloc(frwi.file_data_len);
        memcpy(svc.resp.file_data, frwi.file_data, frwi.file_data_len);
    }

exit:
    req.respond();

    if (frwi.password)
        free(frwi.password);
    if (frwi.file_name)
        free(frwi.file_name);
    if (svc.resp.error_message)
        free(svc.resp.error_message);
    if (svc.resp.file_data)
        free(svc.resp.file_data);

    return 0;
}

int file_protocol::on_file_write(ln::service_request& req, 
        ln_service_robotkernel_file_protocol_file_write& svc) {
    file_readwrite_info_t frwi;
    memset(&frwi, 0, sizeof(frwi));
    frwi.slave_id       = slave_id;
    frwi.password       = strndup(svc.req.password, svc.req.password_len);
    frwi.file_name      = strndup(svc.req.file_name, svc.req.file_name_len);
    frwi.file_data      = svc.req.file_data;
    frwi.file_data_len  = svc.req.file_data_len;

    // execute module request file read
    int ret = kernel::request_cb(mod_name.c_str(), 
            MOD_REQUEST_FILE_WRITE, (void *)&frwi);
    if (ret == -1) {
        if (frwi.error_message) 
            svc.resp.error_message = frwi.error_message;
        else
            svc.resp.error_message = strdup("writing file failed!");

        goto exit;
    }

exit:
    req.respond();

    if (frwi.password)
        free(frwi.password);
    if (frwi.file_name)
        free(frwi.file_name);
    if (svc.resp.error_message)
        free(svc.resp.error_message);

    return 0;
}

