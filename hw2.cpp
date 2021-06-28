#include<iostream>
#include<string>

using namespace std;

struct ACCOUNT
{
	string name;
	int number;
	int money;
};

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

	int Search(ACCOUNT& x) const{  // x가 저장된 위치를 return함 (계좌번호로 찾기)
		NodeType<ItemType>* temptr = first;
		int index = 1;  // index:  x가 저장된 위치를 저장하는 변수

		while(temptr != NULL){
			if(temptr->info.number == x.number) break;  // 위치를 찾은 순간 break

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

		int location = Search(x);

		if(location != 0){
			cout << "Error: 기존에 있는 계좌번호를 신규계좌로 입력" << endl;
			cout << endl;
			return;
		}

		NodeType<ItemType>* newnode;
		newnode = new NodeType<ItemType>;  // 'newnode'라는 메모리를 할당하여 List에 사용

		newnode->info= x;
		newnode->next = first;
		first = newnode;

		length++;
	}

	void Output(ostream& out) const{  // List 전체를 출력함
		NodeType<ItemType>* temptr = first;

		out << "Total )" << endl;
		while(temptr != NULL){
			out << temptr->info.number << " "<< temptr->info.name << " "<< temptr->info.money << endl;
			temptr = temptr->next;
		}

		out << endl;
	}


	void SearchbyName(string name) const{  // <NEW> 해당 이름이 저장된 계정을 모두 return함
		NodeType<ItemType>* temptr = first;
		int index = 1;  // index:  x가 저장된 위치를 저장하는 변수
		bool isExist = false;

		while(temptr != NULL){
			if(temptr->info.name == name){
				isExist = true;
				cout << temptr->info.number << " " << temptr->info.money << endl;
			}

			temptr = temptr->next;
			index++;
		}

		if(isExist == false){
			cout << "Error: 존재하지 않는 이름" << endl;
			cout << endl;
		}
	}

	void OutputSum() const{  // <NEW> List에 저장된 money의 합계를 출력함
		NodeType<ItemType>* temptr = first;
		int sum = 0;

		while(temptr != NULL){
			sum += temptr->info.money;
			temptr = temptr->next;
		}

		cout << "Total money: " << sum << endl;

		cout << endl;
	}


private:
	NodeType<ItemType>* first;
	int length;
};


int main(){

	string order;  // order: 명령어를 입력받기 위한 변수
	LinkedList<ACCOUNT> List;  // List: class list

	ACCOUNT the_A;  // ths_A: struct account
	string the_name;  // the_name: 이름 값을 저장하기 위한 변수
	int the_number;  // the_number: 계좌번호 값을 저장하기 위한 변수
	int the_money;  // the_money: 금액 값을 저장하기 위한 변수

	while(true){
		
		cout << "Input the order. (N, W, T, C, Q, R, S, P, L, F) : ";
		cin >> order;  // 명령어를 입력받음

		if(order == "F") break;

		if(order == "N"){
			cout << "N: 신규 계좌" << endl;
			cout << "Input the number, name, and money : ";
			cin >> the_A.number >> the_A.name >> the_A.money;  // 계좌번호, 이름, 금액을 입력받음

			List.Insert(the_A);  // 입력받은 계정을 list에 삽입함
		}
		else if(order == "W"){
			cout << "W: 인출" << endl;
			cout << "Input the number and money : ";
			cin >> the_A.number >> the_money;  // 계좌번호, 금액을 입력받음

			int location = List.Search(the_A);

			if(location == 0)  // 존재하지 않는 계좌번호일 경우 error
			{
				cout << "Error: 존재하지 않는 계좌번호" << endl;
				cout << endl;
			}
			else
			{
				List.Get(location, the_A);

				if(the_A.money < the_money)  // 잔액이 부족할 경우 error
				{
					cout << "Error: 인출금액이 잔액을 넘음" << endl;
					cout << endl;
				}
				else
				{
					List.Delete(location);

					the_A.money = the_A.money - the_money;
					List.Insert(the_A);  // list에서 계정을 지운 다음 수정 후 다시 삽입
				}
			}
		}
		else if(order == "T"){
			ACCOUNT A2;
			cout << "T: 이체" << endl;
			cout << "Input the number1, number2 and money : ";
			cin >> the_A.number >> A2.number >> the_money;  // 계좌번호 2개, 금액을 입력받음

			int location1, location2;

			if( List.Search(the_A) == 0 || List.Search(A2) == 0 )  // 계좌번호 2개 중 하나라도 존재하지 않을 경우 error
			{
				cout << "Error: 존재하지 않는 계좌번호" << endl;
				cout << endl;
			}
			else
			{
				location1 = List.Search(the_A);
				List.Get(location1, the_A);

				if(the_A.money < the_money)  // 잔액이 부족할 경우 error
				{
					cout << "Error: 이체금액이 잔액을 넘음" << endl;
					cout << endl;
				}
				else
				{
					List.Delete(location1);

					location2 = List.Search(A2);
					List.Get(location2, A2);

					List.Delete(location2);

					the_A.money = the_A.money - the_money;
					List.Insert(the_A);  // list에서 계정을 지운 다음 수정 후 다시 삽입(보내는 계좌)

					A2.money = A2.money + the_money;
					List.Insert(A2);  // list에서 계정을 지운 다음 수정 후 다시 삽입(받는 계좌)
				}
			}
		}
		else if(order == "C"){
			cout << "C: 계좌 해지" << endl;
			cout << "Input the number : ";
			cin >> the_A.number;  // 계좌번호를 입력받음

			int location = List.Search(the_A);

			if(location == 0)  // 존재하지 않는 계좌번호일 경우 error
			{
				cout << "Error: 존재하지 않는 계좌번호" << endl;
				cout << endl;
			}
			else
			{
				List.Get(location, the_A);
				List.Delete(location);  // 해당 계정를 삭제함
			}
		}
		else if(order == "Q"){
			cout << "Q: 조회" << endl;
			cout << "Input the number : ";
			cin >> the_A.number;  // 계좌번호를 입력받음

			int location = List.Search(the_A);

			if(location == 0)  // 존재하지 않는 계좌번호일 경우 error
			{
				cout << "Error: 존재하지 않는 계좌번호" << endl;
				cout << endl;
			}
			else
			{
				List.Get(location, the_A);

				cout << the_A.number << " " << the_A.name << " "<< the_A.money << endl;  // 해당 계정를 가져온 후 출력
			}
		}
		else if(order == "R"){
			cout << "R: 예금주이름의 모든 계좌번호와 잔액을 출력" << endl;
			cout << "Input the name : ";
			cin >> the_name;  // 이름을 입력받음

			List.SearchbyName(the_name);  // 해당 이름의 계정들을 모두 출력
		}
		else if(order == "S"){
			cout << "S: 입금" << endl;
			cout << "Input the number and money : ";
			cin >> the_A.number >> the_money;  // 계좌번호, 금액을 입력받음

			int location = List.Search(the_A);

			if(location == 0)  // 존재하지 않는 계좌번호일 경우 error
			{
				cout << "Error: 존재하지 않는 계좌번호" << endl;
				cout << endl;
			}
			else
			{
				List.Get(location, the_A);
				List.Delete(location);

				the_A.money = the_A.money + the_money;
				List.Insert(the_A);  // list에서 계정을 지운 다음 수정 후 다시 삽입
			}
		}
		else if(order == "P"){
			List.OutputSum();  // money의 합계를 출력함
		}
		else if(order == "L"){
			List.Output(cout);  // list 전체를 출력함
		}
		else  // 유효하지 않은 명령어 일 경우 error
		{
			cout << "Error: 존재하지 않는 명령어" << endl;
			cout << endl;
		}

		cout << endl;

	}

	cout << endl;
	cout << "Thanks for using this program!" << endl;
	cout << "Please refer to file 'text.txt'" << endl;
	cout << endl;

	ofstream fout;  // fout: ofstream
	fout.open("bank.txt");
	List.Output(fout);  // bank.text에 정보를 저장함

	return 0;
 }