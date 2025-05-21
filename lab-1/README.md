# Ћабораторна робота: ќбл≥к товар≥в на склад≥

## ќпис проЇкту

÷ей проЇкт реал≥зуЇ базову систему обл≥ку товар≥в на склад≥. ќсновн≥ класи: `Money`, `Product`, `Warehouse`, `Reporting`.

---

## ƒотриманн€ принцип≥в програмуванн€

” цьому проЇкт≥ реал≥зовано наступн≥ принципи:

---

### 1. **DRY**

> Ќе повторюй себе

¬икористанн€ методу `Normalize()` в `Money`, щоб уникнути повторенн€ лог≥ки перерахунку коп≥йок/гривень.

‘айл: `tusk1.cpp`, р€дки `12Ц21` 
https://github.com/qweasad/KPZ/blob/390c26a20b8afdc3ea12d57e1668b88c9fb0e53c/lab-1/tusk1/tusk1.cpp#L12-L21

---

### 2. **KISS**

>  ѕиши просто

 ласи мають просту структуру: `Product` збер≥гаЇ лише назву й ц≥ну, без зайвого ускладненн€.

‘айл: `tusk1.cpp`, р€дки `38Ц42` 
https://github.com/qweasad/KPZ/blob/390c26a20b8afdc3ea12d57e1668b88c9fb0e53c/lab-1/tusk1/tusk1.cpp#L38-L42

---

### 3. **YAGNI**

> Ќе реал≥зовуй те, чого поки не потр≥бно

¬ код≥ немаЇ зайвих метод≥в, €к≥ не використовуютьс€. ”с≥ класи м≥ст€ть лише необх≥дний функц≥онал.


---

### 4. **Fail Fast**

> ѕадай одразу

¬ `RegisterShipment` перев≥р€Їтьс€, чи достатньо товару перед в≥двантаженн€м. якщо н≥ Ц виводитьс€ помилка, д≥€ не виконуЇтьс€.

‘айл: `tusk1.cpp`, р€дки `105Ц107` 
https://github.com/qweasad/KPZ/blob/390c26a20b8afdc3ea12d57e1668b88c9fb0e53c/lab-1/tusk1/tusk1.cpp#L105-L107

---

### 5. **Composition Over Inheritance**

>  омпозиц≥€ зам≥сть насл≥дуванн€

`Warehouse` маЇ обТЇкт класу `Product` зам≥сть насл≥дуванн€, що спрощуЇ розширенн€ й використанн€.

‘айл: `tusk1.cpp`, р€дки `48,71`
https://github.com/qweasad/KPZ/blob/390c26a20b8afdc3ea12d57e1668b88c9fb0e53c/lab-1/tusk1/tusk1.cpp#L48
https://github.com/qweasad/KPZ/blob/390c26a20b8afdc3ea12d57e1668b88c9fb0e53c/lab-1/tusk1/tusk1.cpp#L71

---

## SOLID-принципи

---

### S Ч Single Responsibility Principle

 ожен клас виконуЇ лише свою функц≥ю:  
- `Money` Ц операц≥њ з грошима https://github.com/qweasad/KPZ/blob/390c26a20b8afdc3ea12d57e1668b88c9fb0e53c/lab-1/tusk1/tusk1.cpp#L7-L43
- `Product` Ц назва й ц≥на  https://github.com/qweasad/KPZ/blob/390c26a20b8afdc3ea12d57e1668b88c9fb0e53c/lab-1/tusk1/tusk1.cpp#L45-L67
- `Warehouse` Ц обл≥к товару  https://github.com/qweasad/KPZ/blob/390c26a20b8afdc3ea12d57e1668b88c9fb0e53c/lab-1/tusk1/tusk1.cpp#L69-L89
- `Reporting` Ц лог≥ка обл≥ку надходжень/в≥двантажень https://github.com/qweasad/KPZ/blob/390c26a20b8afdc3ea12d57e1668b88c9fb0e53c/lab-1/tusk1/tusk1.cpp#L91-L118

`tusk1.cpp`, ус≥ класи

---

### O Ч Open/Closed Principle


`tusk1.cpp`, р€дки `7Ц43`
https://github.com/qweasad/KPZ/blob/390c26a20b8afdc3ea12d57e1668b88c9fb0e53c/lab-1/tusk1/tusk1.cpp#L7-L43
`tusk1.cpp`, р€дки `45Ц67`
https://github.com/qweasad/KPZ/blob/390c26a20b8afdc3ea12d57e1668b88c9fb0e53c/lab-1/tusk1/tusk1.cpp#L45-L67
`tusk1.cpp`, р€дки `91Ц118`
https://github.com/qweasad/KPZ/blob/390c26a20b8afdc3ea12d57e1668b88c9fb0e53c/lab-1/tusk1/tusk1.cpp#L91-L118

---

### L Ч Liskov Substitution Principle


---

### I Ч Interface Segregation Principle

---

### D Ч Dependency Inversion Principle
`tusk1.cpp`, р€дки `91Ц118`
https://github.com/qweasad/KPZ/blob/390c26a20b8afdc3ea12d57e1668b88c9fb0e53c/lab-1/tusk1/tusk1.cpp#L91-L118


---



