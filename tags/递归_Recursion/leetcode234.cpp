/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
 class Solution {
    public:
        bool isPalindrome(ListNode* head) {
            int n=0;
            ListNode *p=head;
            while(p!=nullptr){
                p=p->next;
                n++;
            }
            stack<int> s;
            p=head;
            for(int i=0;i<n/2;i++){
                s.push(p->val);
                p=p->next;
            }
            if(n%2==1){
                p=p->next;
            }
            while(p!=nullptr){
                if(p->val!=s.top()){
                    return false;
                }
                s.pop();
                p=p->next;
            }
            return true;
        }
    };