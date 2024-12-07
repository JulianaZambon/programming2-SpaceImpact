# **Trabalho/Avaliação #02 - Programação 02**

Neste trabalho, será desenvolvida uma versão alternativa do *Space Impact*, inspirada nas dinâmicas do *Space Impact 303*.

---

## **Requisitos Mínimos**

### **0. Extras**
- **Tela Inicial do Jogo:**  
  ![Tela Inicial](https://github.com/user-attachments/assets/0a0213de-41ca-4d72-a7df-883093452061)

---

### **1. Estrutura do Jogo**
- O jogo deve conter **no mínimo duas fases**, cada uma com um **cenário único e distinto**.  
  Exemplos de cenários:  
  ![Cenário 1](https://github.com/user-attachments/assets/893b555b-7612-486c-9002-dd81e6ae807e)  
  ![Cenário 2](https://github.com/user-attachments/assets/3990db98-d5f6-4afc-8f79-966721d99b60)  

---

### **2. Nave do Jogador**
- A nave do jogador deve possuir:
  - **Sprite** com **animações básicas** para movimentação lateral (esquerda e direita):  
    ![Nave](https://github.com/user-attachments/assets/7dc21281-f104-45fb-8ede-d0066bb08da1)  
  - **Sistema de HP (vida):** ao atingir zero, o jogo deve terminar.  
  - **Ataque básico:** sempre disponível para o jogador.  
  - **Ataques especiais:** descritos no item 6.

---

### **3. Inimigos**
- Cada fase deve conter pelo menos **dois tipos de inimigos normais** (totalizando, no mínimo, quatro tipos diferentes no jogo):  
  - **Dois inimigos** devem ser capazes de lançar **projéteis**.  
  - Apenas **um inimigo** pode ser imóvel. Os outros devem apresentar **algum padrão de movimentação**, ainda que simples.  
  - Cada tipo de inimigo deve ter uma **sprite única** (sem reutilização).  
  Exemplos de inimigos:  
  ![Inimigo 1](https://github.com/user-attachments/assets/21285467-d47f-4127-9e9e-eb23c15cf54e)  
  ![Inimigo 2](https://github.com/user-attachments/assets/f068bc94-4836-4156-91b2-1af021889e6f)  
  ![Inimigo 3](https://github.com/user-attachments/assets/376be9da-6f2b-47ed-9c07-5015929c3748)  
  ![Inimigo 4](https://github.com/user-attachments/assets/f59caee3-ce6f-4673-b5fc-3ad77151eaff)  

---

### **4. Chefes**
- Cada fase deve ter um **chefe exclusivo** ao final, totalizando **dois chefes no mínimo**.  
  Exemplos de chefes:  
  ![Chefe 1](https://github.com/user-attachments/assets/452095cc-3556-4eed-9b24-39d8aff4f2de)  
  ![Chefe 2](https://github.com/user-attachments/assets/83e72a89-9692-49a4-9f37-8095ae66ab60)  

  - Cada chefe deve possuir uma **sprite única**.  
  - Cada chefe deve ter, no mínimo, **dois ataques únicos**, sendo pelo menos **um relacionado ao lançamento de projéteis**.  
  - Os chefes devem ser **significativamente mais resistentes** do que os inimigos normais.  
  - (Subjetivo) O chefe deve apresentar algum **desafio** ao jogador.

---

### **5. Duração das Fases**
- Cada fase deve durar, no mínimo, **30 segundos**.

---

### **6. Ataques Especiais**
- A nave do jogador deve ser capaz de adquirir **dois ataques especiais diferentes**:
  - Os ataques especiais devem ser encontrados **no mapa** como itens coletáveis.
  - Esses ataques devem ser **temporários**, com duração máxima de **5 segundos** cada.  
  - **Símbolo do ataque:**  
    ![Ataque Especial](https://github.com/user-attachments/assets/c8ded351-b2eb-45c0-8fb6-e103784feb5d)
