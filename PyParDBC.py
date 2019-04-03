import cantools
#from struct import pack
def Hello(str):

    path="files\dbc1.dbc"
    db=""
    db = cantools.database.load_file(path)
    #pprint(db.messages)

    #[message('ExampleMessage', 0x1f0, False, 8, 'Example message used as template in MotoHawk models.')]
    #example_message = db.get_message_by_name('FRS_Obj_38_Part02')

    #message1={'id':0x47, 'data':0x000000000000000B}
    #e1=db.decode_message(str['id'], pack('ci',b'*', str['data']))
    #pprint(e1)
    return str
