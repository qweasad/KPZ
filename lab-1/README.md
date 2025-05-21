
## Опис проєкту

Цей проєкт реалізує базову систему обліку товарів на складі. Основні класи: `Money`, `Product`, `Warehouse`, `Reporting`.

---

## Дотримання принципів програмування

У цьому проєкті реалізовано наступні принципи:

---

### 1. **DRY**

> Не повторюй себе

Використання методу `Normalize()` в `Money`, щоб уникнути повторення логіки перерахунку копійок/гривень.

Файл: `tusk1.cpp`, рядки `12–21` 
https://github.com/qweasad/KPZ/blob/390c26a20b8afdc3ea12d57e1668b88c9fb0e53c/lab-1/tusk1/tusk1.cpp#L12-L21

---

### 2. **KISS**

>  Пиши просто

Класи мають просту структуру: `Product` зберігає лише назву й ціну, без зайвого ускладнення.

Файл: `tusk1.cpp`, рядки `38–42` 
https://github.com/qweasad/KPZ/blob/390c26a20b8afdc3ea12d57e1668b88c9fb0e53c/lab-1/tusk1/tusk1.cpp#L38-L42

---

### 3. **YAGNI**

> Не реалізовуй те, чого поки не потрібно

В коді немає зайвих методів, які не використовуються. Усі класи містять лише необхідний функціонал.


---

### 4. **Fail Fast**

> Падай одразу

В `RegisterShipment` перевіряється, чи достатньо товару перед відвантаженням. Якщо ні – виводиться помилка, дія не виконується.

Файл: `tusk1.cpp`, рядки `105–107` 
https://github.com/qweasad/KPZ/blob/390c26a20b8afdc3ea12d57e1668b88c9fb0e53c/lab-1/tusk1/tusk1.cpp#L105-L107

---

### 5. **Composition Over Inheritance**

> Композиція замість наслідування

`Warehouse` має об’єкт класу `Product` замість наслідування, що спрощує розширення й використання.

Файл: `tusk1.cpp`, рядки `48,71`
https://github.com/qweasad/KPZ/blob/390c26a20b8afdc3ea12d57e1668b88c9fb0e53c/lab-1/tusk1/tusk1.cpp#L48
https://github.com/qweasad/KPZ/blob/390c26a20b8afdc3ea12d57e1668b88c9fb0e53c/lab-1/tusk1/tusk1.cpp#L71

---

## SOLID-принципи

---

### S — Single Responsibility Principle

Кожен клас виконує лише свою функцію:  
- `Money` – операції з грошима https://github.com/qweasad/KPZ/blob/390c26a20b8afdc3ea12d57e1668b88c9fb0e53c/lab-1/tusk1/tusk1.cpp#L7-L43
- `Product` – назва й ціна  https://github.com/qweasad/KPZ/blob/390c26a20b8afdc3ea12d57e1668b88c9fb0e53c/lab-1/tusk1/tusk1.cpp#L45-L67
- `Warehouse` – облік товару  https://github.com/qweasad/KPZ/blob/390c26a20b8afdc3ea12d57e1668b88c9fb0e53c/lab-1/tusk1/tusk1.cpp#L69-L89
- `Reporting` – логіка обліку надходжень/відвантажень https://github.com/qweasad/KPZ/blob/390c26a20b8afdc3ea12d57e1668b88c9fb0e53c/lab-1/tusk1/tusk1.cpp#L91-L118

`tusk1.cpp`, усі класи

---

### O — Open/Closed Principle


`tusk1.cpp`, рядки `7–43`
https://github.com/qweasad/KPZ/blob/390c26a20b8afdc3ea12d57e1668b88c9fb0e53c/lab-1/tusk1/tusk1.cpp#L7-L43
`tusk1.cpp`, рядки `45–67`
https://github.com/qweasad/KPZ/blob/390c26a20b8afdc3ea12d57e1668b88c9fb0e53c/lab-1/tusk1/tusk1.cpp#L45-L67
`tusk1.cpp`, рядки `91–118`
https://github.com/qweasad/KPZ/blob/390c26a20b8afdc3ea12d57e1668b88c9fb0e53c/lab-1/tusk1/tusk1.cpp#L91-L118

---

### L — Liskov Substitution Principle


---

### I — Interface Segregation Principle

---

### D — Dependency Inversion Principle
`tusk1.cpp`, рядки `91–118`
https://github.com/qweasad/KPZ/blob/390c26a20b8afdc3ea12d57e1668b88c9fb0e53c/lab-1/tusk1/tusk1.cpp#L91-L118


---



