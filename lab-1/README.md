# ����������� ������: ���� ������ �� �����

## ���� ������

��� ����� ������ ������ ������� ����� ������ �� �����. ������ �����: `Money`, `Product`, `Warehouse`, `Reporting`.

---

## ���������� �������� �������������

� ����� ����� ���������� ������� ��������:

---

### 1. **DRY**

> �� �������� ����

������������ ������ `Normalize()` � `Money`, ��� �������� ���������� ����� ����������� ������/�������.

����: `tusk1.cpp`, ����� `12�21` 
https://github.com/qweasad/KPZ/blob/390c26a20b8afdc3ea12d57e1668b88c9fb0e53c/lab-1/tusk1/tusk1.cpp#L12-L21

---

### 2. **KISS**

>  ���� ������

����� ����� ������ ���������: `Product` ������ ���� ����� � ����, ��� ������� �����������.

����: `tusk1.cpp`, ����� `38�42` 
https://github.com/qweasad/KPZ/blob/390c26a20b8afdc3ea12d57e1668b88c9fb0e53c/lab-1/tusk1/tusk1.cpp#L38-L42

---

### 3. **YAGNI**

> �� ��������� ��, ���� ���� �� �������

� ��� ���� ������ ������, �� �� ����������������. �� ����� ������ ���� ���������� ����������.


---

### 4. **Fail Fast**

> ����� ������

� `RegisterShipment` ������������, �� ��������� ������ ����� �������������. ���� � � ���������� �������, �� �� ����������.

����: `tusk1.cpp`, ����� `105�107` 
https://github.com/qweasad/KPZ/blob/390c26a20b8afdc3ea12d57e1668b88c9fb0e53c/lab-1/tusk1/tusk1.cpp#L105-L107

---

### 5. **Composition Over Inheritance**

> ���������� ������ �����������

`Warehouse` �� �ᒺ�� ����� `Product` ������ �����������, �� ������ ���������� � ������������.

����: `tusk1.cpp`, ����� `48,71`
https://github.com/qweasad/KPZ/blob/390c26a20b8afdc3ea12d57e1668b88c9fb0e53c/lab-1/tusk1/tusk1.cpp#L48
https://github.com/qweasad/KPZ/blob/390c26a20b8afdc3ea12d57e1668b88c9fb0e53c/lab-1/tusk1/tusk1.cpp#L71

---

## SOLID-��������

---

### S � Single Responsibility Principle

����� ���� ������ ���� ���� �������:  
- `Money` � �������� � ������� https://github.com/qweasad/KPZ/blob/390c26a20b8afdc3ea12d57e1668b88c9fb0e53c/lab-1/tusk1/tusk1.cpp#L7-L43
- `Product` � ����� � ����  https://github.com/qweasad/KPZ/blob/390c26a20b8afdc3ea12d57e1668b88c9fb0e53c/lab-1/tusk1/tusk1.cpp#L45-L67
- `Warehouse` � ���� ������  https://github.com/qweasad/KPZ/blob/390c26a20b8afdc3ea12d57e1668b88c9fb0e53c/lab-1/tusk1/tusk1.cpp#L69-L89
- `Reporting` � ����� ����� ����������/����������� https://github.com/qweasad/KPZ/blob/390c26a20b8afdc3ea12d57e1668b88c9fb0e53c/lab-1/tusk1/tusk1.cpp#L91-L118

`tusk1.cpp`, �� �����

---

### O � Open/Closed Principle


`tusk1.cpp`, ����� `7�43`
https://github.com/qweasad/KPZ/blob/390c26a20b8afdc3ea12d57e1668b88c9fb0e53c/lab-1/tusk1/tusk1.cpp#L7-L43
`tusk1.cpp`, ����� `45�67`
https://github.com/qweasad/KPZ/blob/390c26a20b8afdc3ea12d57e1668b88c9fb0e53c/lab-1/tusk1/tusk1.cpp#L45-L67
`tusk1.cpp`, ����� `91�118`
https://github.com/qweasad/KPZ/blob/390c26a20b8afdc3ea12d57e1668b88c9fb0e53c/lab-1/tusk1/tusk1.cpp#L91-L118

---

### L � Liskov Substitution Principle


---

### I � Interface Segregation Principle

---

### D � Dependency Inversion Principle
`tusk1.cpp`, ����� `91�118`
https://github.com/qweasad/KPZ/blob/390c26a20b8afdc3ea12d57e1668b88c9fb0e53c/lab-1/tusk1/tusk1.cpp#L91-L118


---



