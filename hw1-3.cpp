#include<iostream>

using namespace std;

template <class ItemType> 
struct NodeType
{
   ItemType info;
   NodeType<ItemType>* next;
}; 
   
template <class ItemType> 
class LinkedList
{						
public:
	LinkedList(){
		first = NULL;
		length = 0;
	}

	~LinkedList(){
		NodeType<ItemType>* temptr;

		while(first != NULL)
		{
			temptr = first;
			first = first->next;
			delete temptr;
		}
	}

	bool isEmpty() const{  // List가 비었는지 확인함
		return (length == 0);
	}

	int Length() const{  // List의 길이를 return함
		return length;
	}

	bool Get(int k, ItemType& x) const{  // x에 k위치의 값을 저장함

		if( !(k>=1 && k<=length) )  // k 값 검증
			return false;

		NodeType<ItemType>* temptr = first;

		for(int i=1; i<k; i++)  // k 위치의 값을 찾는 과정
			temptr = temptr->next;

		x = temptr->info;  // k 위치의 값을 x에 저장
		return true;
	}

	int Search(ItemType& x) const{  // x가 저장된 위치를 return함
		NodeType<ItemType>* temptr = first;
		int index = 1;  // index:  x가 저장된 위치를 저장하는 변수

		while(temptr != NULL){
			if(temptr->info == x) break;  // 위치를 찾은 순간 break

			temptr = temptr->next;
			index++;
		}

		if(temptr == NULL)  // x가 저장되지 않았을 경우
			return 0;
		else				// x의 위치를 찾았을 경우
			return index;
	}

	bool Delete(int k){  // k위치 값을 지움

		if( !(k>=1 && k<=length) )  // k 값 검증
			return false;

		NodeType<ItemType>* temptr = first;
		
		if(k == 1){  // 지우고자 하는 값이 first일 경우
			first = temptr->next;
			delete temptr;
		}
		else{  // 중간 값을 지우고자 할 경우
			NodeType<ItemType>* remove;  // remove: 지우고자 하는 값을 가리키는 포인터

			for(int i=1; i<k-1; i++)
				temptr = temptr->next;  // temptr: 지우고자 하는 값의 이전을 가리키는 포인터

			remove = temptr->next;

			temptr->next = temptr->next->next;
			delete remove;
		}

		length--;
		return true;
	}

	void Insert(ItemType& x){  // x를 List에 삽입함
		NodeType<ItemType>* newnode;
		newnode = new NodeType<ItemType>;  // 'newnode'라는 메모리를 할당하여 List에 사용

		newnode->info = x;
		newnode->next = first;

		NodeType<ItemType>* temptr = NULL;  // temptr: newnode의 이전 값을 포인팅

		if(first != NULL){  // List에 값이 몇 개 있는 상태에서 삽입할 경우
			while(newnode->next != NULL){
				if(newnode->info <= newnode->next->info) break;  // List에서 보다 큰 값을 발견하면 break

				temptr = newnode->next;
				newnode->next = newnode->next->next;
			}

			if(temptr == NULL)  // 제일 앞 쪽에 값을 삽입할 경우
				first = newnode;
			else  // 중간에 삽입할 경우
				temptr->next = newnode;
		}
		else{  // 최초로 값을 삽입할 경우
			first = newnode;
		}

		length++;
	}

	void Output(ostream& out) const{  // List 전체를 출력함
		NodeType<ItemType>* temptr = first;

		while(temptr != NULL){
			out << temptr->info << " ";
			temptr = temptr->next;
		}

		out << endl;
	}


private:
	NodeType<ItemType>* first;
	int length;
};


int main(){

	LinkedList<int> S;  // S: list class
	int n;  // n: list에 넣을 숫자
	int cnt;  // cnt: list에 넣을 숫자의 갯수

	cout << "Input the the number of things: ";
	cin >> cnt;  // 갯수를 입력받음

	int i = 1;
	cout << "Input the things: ";
	while(i <= cnt)  // 입력받은 값들을 모두 list에 저장
	{
		cin >> n;

		S.Insert(n);
		i++;
	}

	S.Output(cout);  // list 내의 값들을 모두 출력함

	return 0;
}