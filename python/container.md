# 容器
## 列表基本操作函数

### 创建列表
```python
my_list = [1, 2, 3, 4]
```

---

### 一、 插入元素

#### 1. 指定位置插入（`insert()`）
```python
my_list.insert(index, value)
```
🔹 在指定索引处插入元素，原位置及其后的元素向后移动。

```python
my_list = [1, 2, 3]
my_list.insert(1, 99)  # 插入到索引1的位置
print(my_list)  # [1, 99, 2, 3]
```

#### 2. 末尾追加（`append()`）
```python
my_list.append(value)
```
🔹 在列表末尾追加一个元素。

```python
my_list = [1, 2]
my_list.append(3)
print(my_list)  # [1, 2, 3]
```

#### 3. 批量追加（`extend()`）
```python
my_list.extend(another_list)
```
🔹 将另一个可迭代对象的所有元素追加到列表末尾。

```python
my_list = [1, 2]
my_list.extend([3, 4])
print(my_list)  # [1, 2, 3, 4]
```

---

#### 二、 删除元素

#### 1. 删除指定值（`remove()`）
```python
my_list.remove(value)
```
🔹 删除列表中**第一个**匹配的值（只能删除一个！重复项删除需要重复调用）。

```python
my_list = [1, 2, 3, 2]
my_list.remove(2)
print(my_list)  # [1, 3, 2]
```

#### 2. 删除指定位置元素（`pop()`）
```python
my_list.pop(index)
```
🔹 删除指定索引处的元素并返回它；若不指定 index，则默认删除并返回**最后一个元素**。

```python
my_list = [1, 2, 3]
value = my_list.pop(1)
print(value)     # 2
print(my_list)   # [1, 3]
```

#### 3. 使用 `del` 删除
```python
del my_list[index]
```
🔹 删除指定索引处的元素（与pop的区别：仅做删除操作，无返回值。）

```python
my_list = [1, 2, 3]
del my_list[0]
print(my_list)  # [2, 3]
```

---

### 三、 清空列表

#### 使用 `clear()` 方法
```python
my_list.clear()
```

```python
my_list = [1, 2, 3]
my_list.clear()
print(my_list)  # []
```

---

### 四 额外：常用其他操作

#### 查找元素索引（`index()`）
```python
my_list.index(value)
```
🔹 返回第一次出现该值的索引。

#### 统计元素个数（`count()`）
```python
my_list.count(value)
```

#### 反转列表（`reverse()`）
```python
my_list.reverse()
```

#### 排序（`sort()`）
```python
my_list.sort()
```

#### 列表长度（`len()`）
```python
length = len(my_list)
```

#### 遍历
```python
my_list = [1,2,3]
for element in my_list
    print(f"{element}")

index = 0
while index < len(my_list)
    print(f"{element}")