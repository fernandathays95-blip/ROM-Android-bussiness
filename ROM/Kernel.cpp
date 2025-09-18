#include <iostream>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

// Estrutura para representar uma tarefa
struct Tarefa {
    std::string nome;
    std::string descricao;
};

// Classe para executar tarefas e se conectar ao servidor
class Kernel {
public:
    void adicionarTarefa(Tarefa tarefa) {
        tarefas.push_back(tarefa);
    }

    void executarTarefa(std::string nomeTarefa) {
        for (auto& tarefa : tarefas) {
            if (tarefa.nome == nomeTarefa) {
                std::cout << "Executando tarefa: " << tarefa.nome << std::endl;
                // Código para executar a tarefa
                return;
            }
        }
        std::cout << "Tarefa não encontrada" << std::endl;
    }

    void conectarServidor(std::string ip, int porta) {
        // Crie um socket para se conectar ao servidor
        sock = socket(AF_INET, SOCK_STREAM, 0);
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_port = htons(porta);

        // Conecte-se ao servidor
        inet_pton(AF_INET, ip.c_str(), &serv_addr.sin_addr);
        connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    }

    void enviarMensagem(std::string mensagem) {
        send(sock, mensagem.c_str(), mensagem.length(), 0);
    }

    std::string receberMensagem() {
        char buffer[1024] = {0};
        read(sock, buffer, 1024);
        return std::string(buffer);
    }

private:
    std::vector<Tarefa> tarefas;
    int sock;
    struct sockaddr_in serv_addr;
};

int main() {
    Kernel kernel;

    // Adicionar tarefas
    Tarefa tarefa1;
    tarefa1.nome = "Tarefa 1";
    tarefa1.descricao = "Descrição da tarefa 1";
    kernel.adicionarTarefa(tarefa1);

    // Conectar ao servidor
    kernel.conectarServidor("127.0.0.1", 8080);

    // Executar tarefa e enviar mensagem ao servidor
    kernel.executarTarefa("Tarefa 1");
    kernel.enviarMensagem("Tarefa executada com sucesso!");

    // Receber resposta do servidor
    std::string resposta = kernel.receberMensagem();
    std::cout << "Resposta do servidor: " << resposta << std::endl;

    return 0;
}
