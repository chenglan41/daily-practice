# 2. 两数相加 (Add Two Numbers)

- 难度：中等
- 日期：2026-10-16
- 链接：https://leetcode.cn/problems/add-two-numbers/
- 结果：**通过 1569/1569 用例，0 ms 击败 100.00%**，内存 75.49 MB

## 题意

两个**非空**链表表示两个非负整数，每个节点存**一位数字**，且按**逆序**存储
（例：`2 -> 4 -> 3` 表示 342）。把两数相加，以相同的逆序链表形式返回结果。

## 思路

模拟小学竖式加法，一次遍历：

1. 建一个**哑结点 `dummy`** 作为结果链表头，`cur` 指向它；
2. `carry` 记录进位，循环条件写成 `while (l1 || l2 || carry)` ——
   这样能自动处理**两个链表长度不同**和**最高位还有进位**（如 9999999 + 1）两种情况；
3. 每轮把两个当前位的值和进位相加，`carry = s / 10`，新节点存 `s % 10`；
4. 最后返回 `dummy.next`（哑结点的下一个才是真正的头）。

**易错点**：循环条件若只写 `while (l1 || l2)`，会丢掉最后产生的进位。

## 复杂度

- 时间：**O(max(m, n))**，m、n 为两链表长度
- 空间：**O(max(m, n))**，结果链表本身

## 代码（C++）

```cpp
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode dummy(0);
        ListNode* cur = &dummy;
        int carry = 0;
        while (l1 || l2 || carry) {
            int s = carry;
            if (l1) { s += l1->val; l1 = l1->next; }
            if (l2) { s += l2->val; l2 = l2->next; }
            carry = s / 10;
            cur->next = new ListNode(s % 10);
            cur = cur->next;
        }
        return dummy.next;
    }
};
```

## 本地自测（g++ 16.2.0，4/4 通过）

| 用例 | 输入 | 期望输出 | 结果 |
|---|---|---|---|
| 342 + 465 | `[2,4,3]` + `[5,6,4]` | `[7,0,8]` | PASS |
| 0 + 0 | `[0]` + `[0]` | `[0]` | PASS |
| 9999999 + 1 | `[9,9,9,9,9,9,9]` + `[1]` | `[0,0,0,0,0,0,0,1]` | PASS |
| 5 + 5 | `[5]` + `[5]` | `[0,1]` | PASS |
