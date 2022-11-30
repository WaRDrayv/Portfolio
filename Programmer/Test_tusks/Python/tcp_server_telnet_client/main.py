#import working_with_table as WorkT
import TCPServer as Server
#import TelnetClient as Client

if __name__ == '__main__':

    #testData = ["0002 C1 01:13:02.877 00", "0104 C1 01:12:01.102 00", "0022 C2 01:26:02.817 01"]
    ####WorkT.Create_Test_Data()
    #Server.StartServer()
    #WorkT.WriteData(testData)
    ####WorkT.ReadData()
    #WorkT.Data_Search("0002 C1 01:13:02.877 00")

    Server.StartServer()

    input('Press eny key to continue...')



