for client get inside client folder 
and run this command --> g++ client.cpp ..\Server_Code\Car.cpp ..\Server_Code\SUV.cpp ..\Server_Code\Sedan.cpp ..\Server_Code\Hatchback.cpp ..\Server_Code\Person.cpp ..\Server_Code\Employee.cpp ..\Server_Code\Customer.cpp ..\Server_Code\Showroom.cpp ..\Server_Code\Transaction.cpp ..\Server_Code\Insurance.cpp ..\Server_Code\Service.cpp -o client.exe -lws2_32      
and then run --> ./client.exe


for server get inside server folder 
and run this command -->  g++ server.cpp Car.cpp SUV.cpp Sedan.cpp Hatchback.cpp Person.cpp Employee.cpp Customer.cpp Showroom.cpp Transaction.cpp Insurance.cpp Service.cpp -o server.exe -lws2_32      
and then run --> ./server.exe

