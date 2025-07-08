# ♻️ Composteira Monitorada com Arduino

Este projeto utiliza um **sistema de monitoramento automatizado** com Arduino para acompanhar a **temperatura** e a **umidade do composto orgânico**, visando melhorar o processo de **compostagem doméstica**. As informações são exibidas em tempo real em um display LCD, e LEDs coloridos indicam a situação do ambiente. Um lembrete automático avisa periodicamente quando o composto deve ser revirado.

## 🎯 Objetivos

- Monitorar temperatura e umidade do composto em tempo real.
- Exibir os dados em um display LCD 16x2.
- Indicar visualmente com LEDs quando há necessidade de intervenção.
- Notificar automaticamente (via display e LEDs) a necessidade de revolver o composto após um período programado.
- Tornar o processo de compostagem mais acessível e educativo.

---

## 🔧 Funcionamento

### 📟 Leitura e exibição de dados
- **Sensor DHT11**: mede a temperatura e umidade do ar.
- **Sensor de umidade do solo**: mede diretamente a umidade do composto.
- As informações são mostradas no **LCD 16x2**:


### 🚨 Alertas por LEDs
- 🔴 **LED Vermelho**: temperatura alta (≥ 65 °C).
- 🟡 **LED Amarelo**: umidade baixa (≤ 40%).
- 🟢 **LED Verde**: condições ideais.

### 🔁 Lembrete de revolvimento do composto
- A cada **5 dias (ajustável)**, o sistema mostra no display a mensagem:
REVOLVER O COMPOSTO

- Durante o lembrete, os LEDs piscam por 20 segundos.

---

## 🧰 Componentes utilizados

### Eletrônicos
- 1x Arduino Uno
- 1x Sensor DHT11
- 1x Sensor de umidade do solo (resistivo)
- 1x Display LCD 16x2 (modo paralelo)
- 3x LEDs (vermelho, amarelo e verde)
- 3x Resistores 220 Ω
- 1x Protoboard
- Jumpers e cabos
- Fonte 5V ou cabo USB

### Estrutura física
- Caixas plásticas com tampa
- Furos para ventilação
- Matéria seca e restos orgânicos para o composto

---

## 📋 Lógica programada

- O código usa `millis()` para contar o tempo entre os lembretes sem travar o loop.
- Os LEDs piscam enquanto a mensagem de revolvimento estiver ativa.
- Após 20 segundos, o sistema volta ao modo de exibição normal.

---

## ✅ Melhorias Futuras

- Inclusão de aquecedor controlado por relé.
- Controle automatizado da umidade (aspersor ou bomba).
- Medição de pH (em desenvolvimento futuro).

---

## 📜 Licença

Este projeto está licenciado sob a **MIT License** — sinta-se livre para usar, modificar e compartilhar, mencionando os autores.

---

## 👩‍🔧 Autores

Projeto criado por [Prof. Diego] com alunos do [Colégio Dulce Maschio], como parte de um projeto para a feira de ciências.  
Contato: [diiegow10@gmail.com]
