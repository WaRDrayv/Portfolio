#. Формат данных BBBBxNNxHH:MM:SS.zhqxGGCR Где BBBB - номер участника x - пробельный символ NN - id канала HH - Часы MM - минуты
# SS - секунды zhq - десятые сотые тысячные GG - номер группы CR - «возврат каретки» (закрывающий символ) Пример данных: 0002 C1 01:13:02.877 00[CR]
import os
from random import randrange
import datetime as dt

from RaceData import RaceData


#Пишем в файл
def WriteData(stringResult):
    with open("base.txt", "w") as file:
        for line in stringResult:
            file.write(line + '\n')
    if (os.path.exists("base.txt")): #Касяк, исправим
        print("write is done")

#Читаем из файла
def ReadData():
    file = open("base.txt", "r")
    print(*file)


#Метод для создания тестовых записей
def Create_Test_Data():


    #1-2 записи делаем ручками, т.к. 2 запись у нас из примера, вот так захотелось
    testData = [RaceData('0001', 'C3', 1, 26, 54, 432, '02'), RaceData('0002', 'C1', 1, 13, 2, 877, 00)]

    #Кол-во создоваемых записей, от 3 до n участника ( в данном примере 50)
    rNumberRacer = range(3, 50)
    #Список, для рандомности установки канала для БЕГЛЕЦА) далеко не уйдёт)
    channel = ['C1', 'C2', 'C3', 'C4']


    #Генерируем данные
    for num in rNumberRacer:
        randChannel = channel[randrange(0,3)]
        randHour = randrange(0, 1)
        randMinets = randrange(0, 59) if randHour == 1 else randrange(40, 59) #Попытка добавить правдоподобности по результатам, чтоб никто не пришёл за 1 минуту
        randSecond = randrange(0, 59)
        randZHQ = randrange(0, 999)
        randGroup = randrange(0, 4)
        #Заносим данные в экземпляры класа ДанныеЗабега
        testData.append(RaceData(str(num), randChannel, str(randHour), str(randMinets), str(randSecond), str(randZHQ), str(randGroup)))

    #Пишем данные, но сначало приводим их к определённому виду, списку строк, т.к. делаем возможность потом добавлять данные в таблицы exel и бд
    WriteData(String_Type_Data(testData))

#Великолепная функция приведения данных из полей класа в список строк
def String_Type_Data(class_list):
    string_data = []
    #record = []
    for unit in class_list:
        #record = str(unit.RunnerNumber) + " " + str(unit.Channel) + " " + str(unit.Hours) + " " + str(unit.Minets) + " " + str(unit.Seconds) + " " + str(unit.ZHQ) + " " + str(unit.Group)
        string_data.append(str(unit.RunnerNumber.zfill(4)) + " " + str(unit.Channel) + " " + str(unit.Hours).zfill(2) + " " + str(unit.Minets).zfill(2) + " " + str(unit.Seconds).zfill(2) + " " + str(unit.ZHQ).zfill(3) + " " + str(unit.Group).zfill(2))
        #string_data.append(copy.deepcopy(record))
        #string_data.append(record)

    return string_data

def Data_Search(target):
    Log_Write(f'Search entry \"{target}\" in \'base.txt\'')
    file = ReadData()
    result = []
    if target[len(target-2):len(target)] == '00':

        for strData in file:
            if strData == target:
                result.append(strData) #Можно хранить в строке, но я буду хронить в листе из 1 элемента)
    result = str(result).split()
    result = f"«спортсмен, нагрудный номер {result[0]} прошёл отсечку NN в «время»"


def Log_Write(target):
    if os.path.exists('logs.txt'):
        now = dt.datetime.now()
        result = str(now.day).zfill(2) + '.' + str(now.month).zfill(2) + '.' + str(now.year) + ' ' + str(now.hour).zfill(2) + ':' + str(now.minute).zfill(2) + ':' + str(now.second).zfill(2) + " - " + str(target)
        with open('logs.txt', 'a') as file:
            file.write(str(result) + '\n')
    else:
        file = open('logs.txt', 'w')
        file.close()
        Log_Write(target)
