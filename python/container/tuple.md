
# 📝 元组基本操作函数（Python）

## ✅ 创建元组

### 1. 使用小括号 ()
```python
my_tuple = (1, 2, 3)
```

### 2. 单个元素的元组需要加逗号
```python
single = (1,)
```

---

## 🔍 访问元组元素

### 使用索引访问元素
```python
my_tuple = (10, 20, 30)
print(my_tuple[1])  # 输出 20
```

---

## ⚠️ 元组是不可变的

元组中的元素一旦创建，不能修改、添加或删除：
```python
my_tuple[0] = 100  # ❌ 会报错
```
特殊元祖元素如果是列表，可以对列表值修改

---

## 🔁 遍历元组

### 使用 for 循环
```python
my_tuple = ('a', 'b', 'c')
for item in my_tuple:
    print(item)
```

---

## 🧪 元组常用操作

### 1. 连接元组（+）
```python
a = (1, 2)
b = (3, 4)
c = a + b
print(c)  # (1, 2, 3, 4)
```

### 2. 复制元组（*）
```python
a = (1, 2)
b = a * 3
print(b)  # (1, 2, 1, 2, 1, 2)
```

### 3. 判断元素是否存在
```python
my_tuple = (1, 2, 3)
print(2 in my_tuple)  # True
```

### 4. 获取长度
```python
len(my_tuple)
```

### 5. 获取索引
```python
my_tuple.index(value)
```

### 6. 统计出现次数
```python
my_tuple.count(value)
```

---

## 🆚 元组 vs 列表

| 特性       | 列表 list      | 元组 tuple     |
|------------|----------------|----------------|
| 是否可变   | ✅ 可变        | ❌ 不可变      |
| 是否可哈希 | ❌ 不可哈希    | ✅ 可作为字典键 |
| 语法标识符 | 中括号 `[]`    | 小括号 `()`    |
| 使用场景   | 动态数据结构    | 静态数据或保护数据 |

---

## ✅ 元组的解包（拆包）

```python
x, y, z = (1, 2, 3)
print(x)  # 1
print(y)  # 2
print(z)  # 3
```

### 结合 enumerate 使用
```python
my_tuple = ('a', 'b', 'c')
for index, value in enumerate(my_tuple):
    print(index, value)
```
