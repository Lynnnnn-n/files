a = int(input("请输入头的数量"))
b = int(input("请输入腿的数量"))
for i in range(a+1):
    j = a - i
    if 2*i + 4*j == b:
        print("鸡有", i, "只，兔有", j, "只")
        result = True
if not result:
    print("没有符合条件的解")
    