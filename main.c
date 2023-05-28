#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>

int main() {
    int porta;
    char buffer[255];

    // Abrir a porta COM (por exemplo, /dev/ttyUSB0)
    porta = open("/dev/ttyUSB0", O_RDONLY);
    if (porta == -1) {
        perror("Erro ao abrir a porta COM");
        return 1;
    }

    // Configurar as opções da porta
    struct termios options;
    tcgetattr(porta, &options);
    cfsetispeed(&options, B9600);  // Taxa de transmissão
    options.c_cflag |= (CLOCAL | CREAD);  // Habilitar recepção
    tcsetattr(porta, TCSANOW, &options);

    // Ler dados da porta
    ssize_t bytes_lidos;
    while ((bytes_lidos = read(porta, buffer, sizeof(buffer))) > 0) {
        // Processar e interpretar os dados recebidos
        // Aqui você pode realizar as ações desejadas com os dados lidos

        // Exemplo: Imprimir os dados no terminal
        for (int i = 0; i < bytes_lidos; i++) {
            printf("%c", buffer[i]);
        }
    }

    // Fechar a porta
    close(porta);

    return 0;
}
