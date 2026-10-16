// 2. 两数相加 (Add Two Numbers) — 2026-10-16
// 思路：哑结点 + 一次遍历模拟竖式加法；循环条件含 carry 以处理最高位进位
// 时间 O(max(m,n)) / 空间 O(max(m,n))
// 提交结果：通过 1569/1569 用例，0 ms 击败 100.00%
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