[README.md](https://github.com/user-attachments/files/27463924/README.md)
# AgendaPlus

Sistema de agenda pessoal desenvolvido em C, com gerenciamento (CRUD) de contatos e atividades, manutenção de dados em CSV e organização automatizada.

> "O Agenda Plus é uma ferramenta para cadastro de informações gerais de contatos, reuniões, atividades, dentre outros. A ideia básica é realizar o cadastro de toda uma rotina do usuário e deixar disponível a possibilidade de alertas e consultas."

Trabalho da 3ª Nota — Linguagem de Programação I

---

## Sobre o Projeto

O **AgendaPlus** é um sistema de agenda via terminal que permite ao usuário cadastrar contatos e agendar atividades, associando ou não a uma pessoa da sua lista de contatos. Os dados são salvos em arquivos `.csv` para que não sejam perdidos entre execuções.

---

## Funcionalidades

### Contatos
- Cadastrar novo contato (nome e sobrenome, telefone, e-mail, local de trabalho)
- Listar todos os contatos
- Atualizar dados de um contato
- Remover contato

### Atividades
- Agendar nova atividade com data, horário e tipo
- Associar um contato (opcionalmente)
- Atualizar atividade existente
- Consultar atividade prevista
- Remover atividade
- Verificar disponibilidade de horário antes de agendar

---

## Estrutura de Arquivos

```
AgendaPlus/
├── main.c          # Ponto de entrada e menu principal
├── deff.c          # Implementação das funções
├── deff.h          # Definições de structs e protótipos
└── arquivos/
    ├── agenda.csv      # Dados das atividades (gerado automaticamente)
    └── contatos.csv    # Dados dos contatos (gerado automaticamente)
```

---

## Tech Stack

- **Linguagem:** C (padrão C99)
- **Bibliotecas:** `stdio.h`, `stdlib.h`, `string.h`, `time.h`
- **Persistência:** Arquivos CSV com delimitador customizável
- **Compilador recomendado:** GCC

---

## ▶Como Compilar e Executar

### Pré-requisitos
- GCC instalado
- Sistema operacional Linux, macOS ou Windows (com MinGW)

### Compilação

```bash
gcc main.c deff.c -o agendaplus
```

### Execução

```bash
./agendaplus
```

---
