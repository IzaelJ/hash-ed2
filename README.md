# Lista Telefônica com Tabela Hash

Este é um projeto desenvolvido como trabalho para a disciplina de **Estrutura de Dados II**, com o objetivo de implementar uma **lista telefônica** utilizando uma **tabela hash**. 

## Funcionalidades

- **Interface de Console**:
  - Adicionar contatos.
  - Buscar contatos por nome (ignora maiúsculas e minúsculas e exibe todos os resultados correspondentes).
  - Remover contatos.
  - Exibir todos os contatos cadastrados.
  - Exibir tempos médios de busca e inserção em milissegundos.

- **Estrutura de Dados**:
  - Implementação de tabela hash com tratamento de colisões usando listas encadeadas.
  - Função hash eficiente para distribuir contatos pela tabela.

- **Tratamento de Erros**:
  - Verificação de duplicidade ao adicionar contatos.
  - Mensagem de erro ao tentar buscar ou remover um contato inexistente.
  - Validação de entrada para evitar loops infinitos em caso de dados inválidos.

- **Medição de Desempenho**:
  - Cálculo e exibição do tempo médio de execução das operações de busca e inserção para análise da eficiência da tabela hash.
