CC = g++
CFLAGS = -I./include
SRCS = src/main.cpp \
       src/controllers/ControladorDeTransito.cpp \
       src/models/Cidade.cpp \
       src/models/Trajeto.cpp \
       src/models/Transporte.cpp \
       src/models/Passageiro.cpp \
       src/models/Viagem.cpp
TARGET = Sistema-de-Viagens

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS)

clean:
	rm -f $(TARGET)
