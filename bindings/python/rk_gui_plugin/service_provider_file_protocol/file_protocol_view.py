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

import os, sys, traceback, yaml, gtk, gobject
import file_protocol_wrapper
import helpers

class file_protocol_view(helpers.service_provider_view, helpers.builder_base):
    def __init__(self, parent, container):
        fn = os.path.join(os.path.dirname(__file__), 'file_protocol_view.ui')
        helpers.builder_base.__init__(self, fn, 'vbox_file_protocol')
        helpers.service_provider_view.__init__(self, parent.app, parent, self.vbox_file_protocol, 'file_read')

        container.pack_start(self.vbox_file_protocol, True, True)

    def show(self, modname, devname):
        helpers.service_provider_view.show(self)

    def on_button_write_file_clicked(self, btn):
        write_filename = self.entry_write_filename.get_text()
        write_password = self.entry_write_password.get_text()
        file_name = self.filechooserbutton_write_file.get_filename()

        self.dev.write_file(write_filename, write_password, file_name)

