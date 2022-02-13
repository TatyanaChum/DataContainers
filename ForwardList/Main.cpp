//ForwardList
#include<iostream>
using namespace std;
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"

#define DEBUG

class Element
{
	int Data;	//�������� ��������
	Element* pNext;//����� ���������� ��������
	static int count;
public:
	Element(int Data, Element* pNext = nullptr) :Data(Data), pNext(pNext)
	{
		count++;
#ifdef DEBUG
		cout << "EConstrcutor:\t" << this << endl;
#endif // DEBUG
	}
	~Element()
	{
		count--;
#ifdef DEBUG
		cout << "EDestrcutor:\t" << this << endl;
#endif // DEBUG
	}
	friend class ForwardList;
	friend class Iterator;
};

int Element::count = 0;

class Iterator
{
	Element* Temp;
public:
	Iterator(Element* Temp = nullptr) : Temp(Temp)
	{
		cout << "ItConstructor: \t" << this << endl;
	}
	~Iterator()
	{
		cout << "ItDestructor: \t" << this << endl;
	}
	Iterator& operator++() //Prefix increment
	{
		Temp = Temp->pNext;
		return *this;
	}
	Iterator operator++(int)//Postfix increment
	{
		Iterator old = *this;//��������� ������ �������� ���������
		Temp = Temp->pNext;//�������� ������ ��������
		return old;//���������� ������ ��������
	}
	bool operator ==(const Iterator& other)const
	{
		return this->Temp == other.Temp;
	}
	bool operator !=(const Iterator& other)const
	{
		return this->Temp != other.Temp;
	}

	int& operator*()
	{
		return Temp->Data;
	}
};

class ForwardList//����������� (����������������) ������
{
	Element* Head;	//������ ������ - ��������� �� ��������� ������� ������.
	unsigned int size;//������ ������
public:
	Element* getHead() const
	{
		return Head;
	}
	unsigned int get_size()const
	{
		return this->size;
	}
	ForwardList()
	{
		Head = nullptr;//���� ������ ��������� �� 0, �� ������ ����.
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	ForwardList(unsigned int size) :ForwardList()
	{
		//this->Head = nullptr;
		//this->size = 0;
		for (int i = 0; i < size; i++)
		{
			push_front(0);
		}
	}
	ForwardList(const initializer_list<int>& il) :ForwardList()
	{
		//il.begin() - ���������� �������� �� ������ ����������
		//il.end()  - ���������� �������� �� ����� ����������
		cout << typeid(il.begin()).name() << endl;
		//const int* - ����������� ��������� (�� ���������� �����)
		//int const* - ��������� �� ��������� (�� ���������� �������� �� ������)
		/*for (int const* it = il.begin(); it != il.end(); it++)
		{
			//it - iterator
			push_back(*it);
		}*/
		for (int const* it = il.end() - 1; it != il.begin() - 1; it--)
		{
			push_front(*it);
		}
	}
	~ForwardList()
	{
		while (Head)pop_front();
		cout << "LDestructor:\t" << this << endl;
	}

	//					Operators:
	const int& operator[](int index)const
	{
		Element* Temp = Head;
		for (int i = 0; i < index; i++)Temp = Temp->pNext;
		return Temp->Data;
	}
	int& operator[](int index)
	{
		Element* Temp = Head;
		for (int i = 0; i < index; i++)Temp = Temp->pNext;
		return Temp->Data;
	}


	//					Addigng elements:
	void push_front(int Data)
	{
		//Element* New = new Element(Data);//������� ����� ������� � �������� � ���� �������� Data
		//New->pNext = Head;	//���������� ����� ������� � ������ ������
		//Head = New;	//��������� ������ �� ����� �������

		Head = new Element(Data, Head);
		size++;
	}
	void push_back(int Data)
	{
		//0) ���������, �������� �� ������ ������:
		if (Head == nullptr)return push_front(Data);
		//1) ������� ����� �������:
		Element* New = new Element(Data);
		//2) ������� �� ����� ������:
		Element* Temp = Head;
		while (Temp->pNext)//����, pNext �������� �������� �� ����
			Temp = Temp->pNext;//��������� �� ��������� �������
		//������ �� ��������� � ��������� ��������, �.�. Temp->pNext == nullptr
		//3) ������������ ����� ������� � ����������:
		Temp->pNext = New;
		size++;
	}
	void insert(int index, int Data)
	{
		if (index == 0 || Head == nullptr)return push_front(Data);
		if (index > size)return;
		Element* New = new Element(Data);
		//1) ������� �� ������� ��������:
		Element* Temp = Head;
		for (int i = 0; i < index - 1; i++)Temp = Temp->pNext;
		//3) �������� ����� ������� � ������:
		New->pNext = Temp->pNext;
		Temp->pNext = New;
		size++;
	}

	//					Removing elements:
	void pop_front()
	{
		if (Head == nullptr)return;
		//1) ���������� ����� ����������� ��������:
		Element* Erased = Head;
		//2) ��������� ��������� ������� �� ������:
		Head = Erased->pNext;
		//3) ������� ������ �� ������:
		delete Erased;

		size--;
	}
	void pop_back()
	{
		if (Head == nullptr)return;
		if (Head->pNext == nullptr)return pop_front();
		//1) ������� �� �������������� ��������:
		Element* Temp = Head;
		while (Temp->pNext->pNext)Temp = Temp->pNext;
		//2) ������� ������� �� ������:
		delete Temp->pNext;
		//3) �������� ����� ���������� �������� �����:
		Temp->pNext = nullptr;
		size--;
	}
	void erase(int index)
	{
		if (index > size)return;
		if (index == 0)return pop_front();
		//1) ������� �� ������� ��������:
		Element* Temp = Head;	//������� ��������, � ������� � ������ ����� ������.
		//������ � ��������� ����� ��������� ��������.
		for (int i = 0; i < index - 1; i++)Temp = Temp->pNext;
		//2) ���������� ����� ���������� ��������:
		Element* Erased = Temp->pNext;
		//3) ��������� ������� �� ������:
		//Temp->pNext = Temp->pNext->pNext;
		Temp->pNext = Erased->pNext;
		//4) ������� ������� �� ������:
		delete Erased;
		size--;
	}

	//					Methods:
//#define OLD_PRINT
	void print()const
	{
#ifdef OLD_PRINT
		int a = 2;
		int* pa = &a;

		Element* Temp = Head;	//Temp - ��� ��������.
//�������� - ��� ���������, ��� ������ �������� ����� �������� ������ 
//� ��������� ��������� ������.
		while (Temp)//���� �������� �������� ��������� �����.
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
			Temp = Temp->pNext;	//������� �� ��������� �������
		}
#endif // OLD_PRINT
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
			//for (Element* Temp = Head; Temp;Temp++)
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "���������� ��������� ������: " << size << endl;
		cout << "����� ���������� ��������� : " << Head->count << endl;
	}
};

//#define BASE_CHECK
//#define DESTRUCTOR_CHECK
//#define HOME_WORK_1
//#define HOME_WORK_2

void print_list(const ForwardList& list)
{
	for (int i = 0; i < list.get_size(); i++)
	{
		cout << list[i] << tab;
	}
	cout << endl;
}

void main()
{
	setlocale(LC_ALL, "");
#ifdef BASE_CHECK
	int n;
	cout << "������� ������ ������: "; cin >> n;
	ForwardList list;
	list.pop_front();
	for (int i = 0; i < n; i++)
	{
		//list.push_front(rand() % 100);
		list.push_back(rand() % 100);
	}
	list.print();
	//list.push_back(123);
	//list.pop_front();
	//list.pop_back();

	int index;
	int value;
	cout << "������� ������ ������������ ��������: "; cin >> index;
	cout << "������� �������� ������������ ��������: "; cin >> value;

	list.insert(index, value);
	list.print();

	cout << "������� ������ ���������� ��������: "; cin >> index;
	list.erase(index);
	list.print();

#endif // BASE_CHECK

	/*ForwardList list1;
	list1.push_back(3);
	list1.push_back(5);
	list1.push_back(8);
	list1.push_back(13);
	list1.push_back(21);
	list1.print();

	ForwardList list2;
	list2.push_back(34);
	list2.push_back(55);
	list2.push_back(89);
	list2.print();*/

#ifdef DESTRUCTOR_CHECK
	int n;
	cout << "������� ������ ������: "; cin >> n;
	ForwardList list;
	for (int i = 0; i < n; i++)
	{
		list.push_front(rand() % 100);
	}
	//cout << "������ ��������" << endl;
	list.print();
#endif // DESTRUCTOR_CHECK

	/*const int a = 250;
	a = 270;*/
#ifdef HOME_WORK_1
	int n;
	cout << "������� ������ ������: "; cin >> n;
	ForwardList list(n);
	for (int i = 0; i < n; i++)
	{
		//l-value = r-value;
		list[i] = rand() % 100;
		//			(int)
	}
	print_list(list);
#endif // HOME_WORK_1

#ifdef HOME_WORK_2
	//		 l-value = r-value
	ForwardList list = { 3,5,8,13,21 };
	//(ForwardList)  = (initializer_list)
	//list.print();
	/*for (Iterator it = list.getHead(); it != nullptr; it++)
	{
		cout << *it << tab;
	}
	cout << endl;*/
	Iterator it = list.getHead();
	Iterator it2 = it++;
	cout << it << endl;
	cout << it2 << endl;
#endif // HOME_WORK_2

	int arr[] = { 3,5,8,13,21 };
	/*for (size_t i = 0; i < sizeof(arr)/sizeof(int); i++)
	{
		cout << arr[i] << tab;
	}
	cout << endl;*/
	for (int i : arr)//range-based for(for ��� ���������)
	{
		cout << i << tab;
	}

	cout << endl;
	//��� ���������� ���������� ��������� (������, ������, � ��)
	//� ������ ������ ��������������� ��� �������� foreach
}