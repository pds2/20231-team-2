# 🍔 SistemaUfmgfood

SistemaUfmgfood é uma aplicação em terminal que permite aos usuários realizar pedidos de comida de forma prática e rápida.

## 🚀 Desenvolvedores:
- [Gabriella de Lima](https://github.com/hellolima)
- [Vitor Costa](https://github.com/vitorcosuta)
- [Gabriel Prudente](https://github.com/Gabrielzzz7)
- [Erik Neves](https://github.com/erikneves04)

## 📚 Histórias de Usuário:
1) Eu como restaurante quero conseguir cadastrar novos produtos e editá-los quando necessário, incluindo descontos esporádicos para que os clientes possam comprar.

2) Eu como usuário quero ter uma espécie de carteira virtual para realizar transações.

3) Eu como usuário quero adicionar saldo na minha carteira para efetuar compras.

4) Eu como usuário quero comprar mais de uma refeição por vez.

5) Eu como usuário quero adicionar várias comidas a um carrinho que exibirá todas as refeições a serem pedidas e o valor total da compra.

6) Eu como usuário quero ter um catálogo de comidas para selecionar e adicionar ao carrinho de compras.

## 📝 Instruções de Uso

### Pré-requisitos
- Compilador C++ (recomenda-se o g++)
- SQLite3

### Configuração do Ambiente
1. Clone este repositório em sua máquina local.

### Instalação do SQLite
1. Para utilizar o SQLite, é necessário baixá-lo e instalá-lo em seu sistema operacional.
   - **Windows:** 
     - Acesse o site oficial do SQLite em https://www.sqlite.org/index.html.
     - Na seção de downloads, encontre a versão adequada para o seu sistema operacional Windows.
     - Baixe o arquivo de instalação (por exemplo, sqlite-tools-win32-x86-3360000.zip).
     - Extraia o conteúdo do arquivo ZIP para um diretório de sua escolha.
     - Adicione o diretório onde o SQLite foi instalado ao seu PATH do sistema.
   - **Linux:**
     - Abra o terminal.
     - Execute o seguinte comando para instalar o SQLite:
     ```
     sudo apt-get install sqlite3
     ```
     - Aguarde o processo de instalação ser concluído.
     
### Compilação
1. Abra um terminal.
2. Navegue até o diretório raiz do projeto (SistemaUfmgfood).
3. Execute o comando `make` para compilar o código.
4. Execute o comando `make tests` para compilar os testes.

### Execução
1. Após a compilação, ainda no terminal, execute um dos seguintes comandos:
   - Para executar o programa principal:
     ```
     ./bin/main
     ```
   - Para executar os testes:
     ```
     ./bin/tester
     ```

### Limpeza
- Para limpar os arquivos objeto e binários gerados durante a compilação, execute o seguinte comando: `make clean`

## 👥 Usuários e Senhas de Teste
Aqui estão as informações de login para os clientes e restaurantes já cadastrados no banco de dados:

💁‍♀️ Clientes:
- Login: maria_silva
   - Senha: cliente1_senha
- Login: joao_santos
   - Senha: cliente2_senha
- Login: ana_oliveira
   - Senha: cliente3_senha

🏢 Restaurantes:
- Login: restaurante1_login
   - Senha: restaurante1_senha
- Login: restaurante2_login
   - Senha: restaurante2_senha
- Login: restaurante3_login
   - Senha: restaurante3_senha

#### Utilize essas informações para realizar testes no sistema. 🚀
