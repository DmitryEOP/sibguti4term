Компиляция клиента: g++ -std=c++11 -I"F:\tools\asio\include" -DASIO_STANDALONE client.cpp -o client.exe -lws2_32
Компиляция сервера: g++ -std=c++11 -I"F:\tools\asio\include" -DASIO_STANDALONE server.cpp -o server.exe -lws2_32 -lwsock32 -lmswsock

Запуск клиента: .\client.exe 127.0.0.1 57686 3 50
Запуск сервера: .\server.exe
