#!/usr/bin/env python
# -*- coding: utf-8 -*-
import cantools
from pprint import pprint
from struct import pack
path=""
db=""
def parDBC(self,path):
    path=path
    db = cantools.database.load_file(path)
    pprint(db.messages)
def parMessage(self,messCAN):
#[message('ExampleMessage', 0x1f0, False, 8, 'Example message used as template in MotoHawk models.')]
    example_message = db.get_message_by_name('FRS_Obj_38_Part02')
#pprint(example_message.signals)
#[signal('Enable', 7, 1, 'big_endian', False, 1.0, 0, 0.0, 0.0, '-', False, None, {0: 'Disabled', 1: 'Enabled'}, None),
# signal('AverageRadius', 6, 6, 'big_endian', False, 0.1, 0, 0.0, 5.0, 'm', False, None, None, ''),
# signal('Temperature', 0, 12, 'big_endian', True, 0.01, 250, 229.53, 270.47, 'degK', False, None, None, None)]

#decode message
#message = can_bus.recv()
#db.decode_message(message.arbitration_id, message.data)
#{'AverageRadius': 3.2, 'Enable': 'Enabled', 'Temperature': 250.09}
    message={"arbitration_id":"47", "data":"80 4A 0F 00 00 00 00 00"}
    e1=db.decode_message(0x45, pack('hhl',1,
    e1=db.decode_message(messCAN.id, messCAN.data)
    pprint(e1)

