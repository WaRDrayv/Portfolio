import telnetlib
import time


connect = telnetlib.Telnet('127.0.0.1', '2020')  # Соединяемся

while True:
    print('Menu'.ljust(20, " "))
    print('1 - Enter data'.ljust(20, " "))
    print('2 - Out of the program'.ljust(20, " "))

    option = input()
    if option == '1':
        print('Enter data for example \'0002 C1 01:13:02.877 00\'')
        set_data = input()
        connect.write(set_data.encode('utf-8'))
        #connect.read_all()

    elif option == '2':
        break
    else:
        print('ERORR! Invalid input, try again ')

input('Press eny key to continue...')
    #match option:
    #    case 1:
    #И тут я понял что юзаю 3.9 а не 3.10 питон, хнык :(



