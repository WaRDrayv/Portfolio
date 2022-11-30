import socket
import working_with_table as WorkT


def StartServer():
#Создаём сокет 1. socket.AF_INET - сокет протокола IPv4, 2. socket.SOCK_STREAM - на основе TCP
    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
#"делаем" сокет серверным, указывая адрес (127.0.0.1 - то же самое что localhost) и порт (лучше выше 1024)
    server.bind(('127.0.0.1', 2020))

#можно было указать что это сервер в 1 строку server = socket.create_server(('127.0.0.1', 2020)). Стандартно ставит AF_INET и SOCK_STREAM

#5 - это кол-во входящих запросов, принятые ОС. 1 работаем 4 ожидают. Если будет выше 5 - идут лесом (сбросим)
    server.listen(5)
    print(">>Server is ON!<<\n")
#Тут будем ждать подключения, пака его нет - работа стоит
    while True:
        client_socket, addres = server.accept()
        #print(client_socket)
        print(f'Connected {addres}')
#Получаем содержимое запроса (данные), 1024 - размер пакета вы байтах. Декадируем в utf-8
        data = client_socket.recv(1024).decode('utf-8')
        WorkT.Log_Write(f'Receiving data \"{data}\" from \"{addres}\"')
        #Условие выключение сервера
        if data == 'exit':
            break

        data = data.split()
        if len(data) == 4:
            if data[3] == "00":
                WorkT.Log_Write(f'Getting data for group \'{data[3]}\'. Output to the terminal (+)')
                WorkT.Log_Write(f'Спортсмен, нагрудный номер {data[0]} прошёл отсечку {data[1]} в {data[2]}')
                #print(f'Спортсмен, нагрудный номер {data[0]} прошёл отсечку {data[1]} в {data[2]}:{data[3]}:{data[4]}.{data[5][:0]}')
                print(f'Спортсмен, нагрудный номер {data[0]} прошёл отсечку {data[1]} в {data[2][0:10]}')
            elif int(data[3]) == 1 or int(data[3]) == 2 or int(data[3]) == 3:
                WorkT.Log_Write(f'Getting data for group \'{data[3]}\'. Do not output to the terminal (-)')
                WorkT.Log_Write(f'Спортсмен, нагрудный номер {data[0]} прошёл отсечку {data[1]} в {data[2]}')
            else:
                WorkT.Log_Write(f'ERORR!!! Received data does not match the format')
                print(f'ERORR!!! Received data does not match the format \"BBBBxNNxHH:MM:SS.zhqxGGCR (For example \'0002 C1 01:13:02.877 00\')\"')
        else:
            WorkT.Log_Write(f'ERORR!!! The list is to short or long. Its length should be equal to 4(four). But the length is {len(data)}')
            print(f'ERORR!!! The list is to short or long. Its length should be equal to 4(four). But the length is {len(data)}')

    #print(data)
    #HDRS = 'HTTP/1.1 200 OK\r\nContent-Type: text/html; charset=utf-8\r\n\r\n'
    #testOUT = "I's all is working properly. Maybe......".encode('utf-8')
    #client_socket.send(HDRS.encode('utf-8') + testOUT)
    print("\n>>Server is OFF<<")
