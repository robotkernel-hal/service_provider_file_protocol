'''
(C) Robert Burger <robert.burger@dlr.de>

This file is part of Robotkernel-GUI.

Robotkernel-GUI is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Robotkernel-GUI is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Robotkernel-GUI.  If not, see <http://www.gnu.org/licenses/>.
'''
from __future__ import print_function

import time, traceback
import numpy as np
import helpers


class file_protocol_device(helpers.svc_wrapper):
    def __init__(self, service_prefix, app, widget, modname, devname):
        helpers.svc_wrapper.__init__(self, app.clnt,
                "%s.%s.%s.file_protocol" % (service_prefix, modname, devname))
        self.modname = modname
        self.devname = devname
        self.widget = widget

    def write_file(self, remote_filename, password, local_filename):
        self.file_write.req.file_name = remote_filename
        self.file_write.req.password  = password
        self.file_write.req.file_data = np.fromfile(local_filename, dtype=np.uint8)
        self.file_write.call()

        if self.file_write.resp.error_message_len:
            raise Exception(self.file_write.resp.error_message)

    def read_block(self, start_adr, end_adr, bs=16, view=None):
        def cb_read_memory(starttime):
            #callback after canopen_protocol returned with data
            try:
                self.buf += self.async_read_memory.resp.data.tolist()

                if view:
                    view.update()

                if (start_adr + bs) < end_adr:
                    self.read_block(start_adr + bs, end_adr, bs, view)
            except:
                print(traceback.format_exc())
            return False

        #non-blocking read on data, with callback (see get_data)
        self.async_read_memory.req.data_adr = start_adr
        self.async_read_memory.req.data_len = min(bs, end_adr - start_adr)
        self.async_read_memory.call_async()
        
        #self.async_read_memory.gobject_on_async_finish(cb_read_memory, time.time())
        self.async_read_memory.mainloop_on_async_finish(self.async_loop, cb_read, time.time())

    def update(self, start_adr, end_adr, view):
        self.buf = []
        self.read_block(start_adr, end_adr, view=view)

