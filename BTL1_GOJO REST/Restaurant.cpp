#include "main.h"

// extern int MAXSIZE; 
class imp_res : public Restaurant
{
	public:
		imp_res() {};

	//danh sach table
		int SIZE = 0;
		customer* head = NULL;

	//danh sach chờ
		int SIZEQUEUE = 0;
		customer* queueHead = NULL;
		customer* queueTail = NULL;
	//Thu tu luu thoi gian FIFO cua ROW Wait khi purple duoc thuc hien
		int sizeFIFO = 0;
		customer* headWait = NULL;
		customer* tailWait = NULL;

	//danh sách kiểm tra thứ tự FIFO trong ban
		int sizeQueue = 0;
		customer* head_Queue = NULL;
		customer* tail_Queue = NULL;
/****************************************************************************************************/
/****************************************************************************************************/
void findDeleteTime(customer*& Head,customer*& Tail, string name, int &size){
	customer* temp = NULL;
	if(Head != NULL){
		temp = Head;
	} else {return;}

	for(int i = 0; i < size; ++i){
		if(temp == NULL){break;}
		
	if( temp->name == name){
		customer* toDelete = temp;
			if(temp->prev != NULL){
				temp->prev->next = temp->next;
			} 
			if (temp->next!= NULL) {
			temp->next->prev = temp->prev;
			}
			if (temp == Head) {
				Head = temp->next;
			}
			if(temp == Tail){
				Tail = temp->prev;
			}
			delete toDelete;
			--size;
			break;
		} else {
			if(temp->next != NULL){
			temp = temp->next;} else {break;}
		}
	}
	if(size == 0){
		Head = NULL;
		Tail = NULL;
		size = 0;
	}
		}
	//kiểm tra tên trong hàng đợi và trong bàn ăn
		bool checkName(string name){
			if(head != NULL){
			customer* tmp = head;
			for(int i = 0; i < SIZE; i++){
				if(name == tmp->name) return true;
				tmp = tmp->next;
			}
			}
			if(queueHead != NULL){
			customer* tmp = queueHead;
			while (tmp != nullptr) {
				if (tmp->name == name) {
					return true;
				}
				tmp = tmp->next;
        	}
			}
        return false;
    	}
	//danh sách thứ tự để khi xóa
		void addQueue(string name, int energy) {
			if(sizeQueue < MAXSIZE){
			customer* newCustomer = new customer(name, energy, nullptr, nullptr);
			if (head_Queue == nullptr) {
				head_Queue = newCustomer;
				tail_Queue = newCustomer;
			} else {
				tail_Queue->next = newCustomer;
				newCustomer->prev = tail_Queue;
				tail_Queue = newCustomer;
			}
			++sizeQueue;
			}
		}
	// Thêm Khách
	customer* NewCustomer(string name, int energy){
		customer* Node = new customer(name, energy, nullptr, nullptr);
		return Node;
	}

	//Thêm khách vào bàn
		void add_Customer(customer* new_customer){
			if(SIZE < MAXSIZE){
			if (head == NULL) { // Nếu danh sách rỗng
				head = new_customer;
				head->prev = head;
				head->next = head;
				++SIZE;
				return;
			} 

			if (new_customer->energy >= head->energy ) {
				// Bố trí chỗ ngồi cho khách mới tại vị trí liền kề bên phía thuận chiều kim đồng hồ
				customer* next_customer = head->next;
				if(next_customer == head){
					head->next = new_customer;
					new_customer->prev = head;
					new_customer->next = head;
					head-> prev = new_customer;
				} 
				else{
					head->next = new_customer;
					new_customer->prev = head;
					new_customer->next = next_customer;
					next_customer->prev = new_customer;
				}
				head = new_customer;
			} else {
				// Bố trí chỗ ngồi cho khách mới tại vị trí liền kề bên phía ngược chiều kim đồng hồ
				customer* prev_customer = head->prev;
				if((prev_customer == head)){
					head->next = new_customer;
					new_customer->prev = head;
					new_customer->next = head;
					head->prev = new_customer;
				} 
				else{
					head->prev = new_customer;
					new_customer->next = head;
					new_customer->prev = prev_customer;
					prev_customer->next = new_customer;
				}
				head = new_customer;
			}
			++SIZE;
			}
		}


	//Thêm khách vào hàng đợi FIFO
		void addWaitFIFO(string name, int energy) {
			if (sizeFIFO < MAXSIZE && SIZE == MAXSIZE && sizeQueue == MAXSIZE) {
					customer* newCustomer = new customer(name, energy, nullptr, nullptr);
					if (headWait == nullptr) {
						headWait = newCustomer;
                		tailWait = newCustomer;
					} else {
						tailWait->next = newCustomer;
						newCustomer->prev = tailWait;
						tailWait = newCustomer;
					}
					++sizeFIFO;
				return;
			}
			
		}
	//Thêm khách vào hàng đợi
		void addWaitCustomer(string name, int energy) {
			if (SIZEQUEUE < MAXSIZE && SIZE == MAXSIZE && sizeQueue == MAXSIZE) {
				if (!checkName(name)) {
					customer* newCustomer = new customer(name, energy, nullptr, nullptr);
					if (queueHead == nullptr) {
						queueHead = newCustomer;
                		queueTail = newCustomer;
					} else {
						queueTail->next = newCustomer;
						newCustomer->prev = queueTail;
						queueTail = newCustomer;
					}
					++SIZEQUEUE;
				} 
				return;
			}
			
		}
	//Thêm theo chiều kim đồng hồ
		void add_clockwise(customer* new_customer){
			if(SIZE < MAXSIZE && head->next != NULL){
			customer* next_customer = head->next;
			if(next_customer == head){
				head->next = new_customer;
				new_customer->prev = head;
				new_customer->next = head;
				head-> prev = new_customer;
			} 
			else{
				head->next = new_customer;
				new_customer->prev = head;
				new_customer->next = next_customer;
				next_customer->prev = new_customer;
			}
			head = new_customer;
			++SIZE;
			}
		}
	
	//Thêm ngược chiều kim đồng hồ
		void add_counterclockwise(customer* new_customer){
			if(SIZE < MAXSIZE){
			customer* prev_customer = head->prev;
			if(prev_customer == head){
				head->next = new_customer;
				new_customer->prev = head;
				new_customer->next = head;
				head-> prev = new_customer;
			} 
			else{
				head->prev = new_customer;
				new_customer->next = head;
				new_customer->prev = prev_customer;
				prev_customer->next = new_customer;
			}
			head = new_customer;
			++SIZE;
			}
		}

	//Tìm địa chỉ res
		customer* findRES(customer* head, string name, int energy){
			customer* current = new customer(name, energy, nullptr, nullptr);
			customer* tmp = head;
			customer* index = nullptr;
			int res = 0, maxres = -2;
			for(int i = 0; i < SIZE; i++){
				res = abs(tmp->energy - current->energy);
				if (res > maxres) {
					maxres = res;
					index = tmp; 
        		}
				tmp = tmp->next;
			}
		return index;
		}

//GHI NHẬN THÔNG TIN KHÁCH HÀNG VÀ SẮP XẾP CHỖ NGỒI
	void RED(string name, int energy)
	{ 
		if(energy == 0) return;
		if(checkName(name) == true) return;
		
		if(SIZE == MAXSIZE) {
			addWaitCustomer(name, energy); /***chú ý*** ADD vô hàng chờ*/
			addWaitFIFO(name, energy);
			
		} 
		if(SIZE >= MAXSIZE/2 && SIZE < MAXSIZE) {
			customer* Customer1= NewCustomer(name, energy);
			customer* index = findRES(head, name, energy);
			int res = Customer1->energy - index->energy;
			head = index;
			if(res < 0) {
				addQueue( name, energy);
				add_counterclockwise(Customer1);
			} else {
				addQueue( name, energy);
				add_clockwise(Customer1);
				}
		} else {
			customer* Customer1 = NewCustomer(name, energy);
			addQueue(name, energy);
			add_Customer(Customer1);
		}
	}

	/****************************************************************************************************/
	/****************************************************************************************************/
	
	//Xóa khách khỏi danh sách thứ tự và danh sách khách trong bàn
		void removeCustomer(int index){
			if(index < MAXSIZE && head_Queue != NULL){
				for(int i = 0; i < index; ++i){
				if(head_Queue == NULL) break;
				customer* temp = head_Queue;
					string valueName= temp->name;
					int valueRemove = temp->energy;
					head_Queue = head_Queue->next;
					temp->next = NULL;
					if(head_Queue != NULL){
						head_Queue->prev = NULL;
					} else {
						tail_Queue = NULL;
					}
					delete temp;
					sizeQueue--;
			int Size = SIZE;
            customer* tmp = head;
            for (int j = 0; j < Size; ++j) {
                if (tmp->name == valueName) {
						if(valueRemove > 0)
                        {head = tmp->next;}
						if( valueRemove < 0){
							head = tmp->prev;
						}

                    if (tmp->next != NULL) {
                        tmp->next->prev = tmp->prev;
                    }

                    if (tmp->prev != NULL) {
                        tmp->prev->next = tmp->next;
                    }

                    delete tmp;
                    SIZE--;
                    break;
                	}
                	tmp = tmp->next;
            	}
					}	
			}
			if(head_Queue == NULL){
	head = NULL; SIZE = 0;
}
			return;
		}

	//Xóa hết danh sách bàn ăn
		void clear() {
		while (head != nullptr) {
			customer* tmp = head;
			head = head->next;
			if (head == tmp) {
				head = nullptr;
			} else {
				tmp->prev->next = tmp->next;
				tmp->next->prev = tmp->prev;
			}
			tmp->next = nullptr; 
			tmp->prev = nullptr;
			delete tmp;
			SIZE--;
		}
		// Thiết lập lại biến SIZE về 0 sau khi đã xóa hết
		head = NULL;
		SIZE = 0;
	}

	//Xóa trong hàng đợi FIFO
		void clearQueue() {
			if(head_Queue == NULL) return;
			while (head_Queue != nullptr && sizeQueue != 0 ) {
				customer* temp = head_Queue;
				head_Queue = head_Queue->next;
				if (head_Queue != nullptr) {
					head_Queue->prev = nullptr;
				}
				if (temp != nullptr) {
				delete temp;
				temp = nullptr;
				}
				sizeQueue--;
			}
			head_Queue = NULL;
			tail_Queue = NULL;
			sizeQueue = 0;
		}

	//KHI BLUE VA DOMAIN GOI RED
	void _RED(string name, int energy)
		{ 
			if(SIZE >= MAXSIZE/2 && SIZE < MAXSIZE) {
				customer* Customer1= NewCustomer(name, energy);
				customer* index = findRES(head, name, energy);
				int res = Customer1->energy - index->energy;
				head = index;
				if(res < 0) {
					add_counterclockwise(Customer1);
				} else {
					add_clockwise(Customer1);
					}
			} else {
				customer* Customer1 = NewCustomer(name, energy);
				add_Customer(Customer1);
			}
		}
		

//ĐUỔI KHÁCH VÀ DỌN BÀN
	void BLUE(int num){
		if(num >= SIZE || num > MAXSIZE){
			
				clear();
				clearQueue();
				if (queueHead != NULL && headWait != NULL) {
				customer* temp = queueHead;
				customer* curr = headWait;

				while (curr != NULL) {
				int i = 0;
					string name = curr->name;
					int energy = curr->energy;
					// bool found = false;

					while (temp != NULL) {
						if (temp->name == name) {
							addQueue(name, energy);
							temp = headWait;
							break;
						}
						++i;
						if(i == num){
							temp = headWait;
							break;
						}
						temp = temp->next;
					}


					if (curr->next == NULL) {
						break;
					} else {
						curr = curr->next;
					}
				}
			}

				if (queueHead != nullptr) {
				while(queueHead != NULL) {
					customer* current = queueHead;
					string name = current->name;
					int energy = current->energy;
					queueHead = queueHead->next;
					current->next = NULL;
					if (queueHead != nullptr) {
						queueHead->prev = nullptr;
					}
					delete current;
					SIZEQUEUE--;
					findDeleteTime(headWait,tailWait, name, sizeFIFO);
					_RED(name, energy);
			
				}
			
			}
		} else if(num < SIZE ){
			removeCustomer(num);
			if (queueHead != NULL && headWait != NULL) {
				customer* temp = queueHead;
				customer* curr = headWait;

				while (curr != NULL) {
				int i = 0;
					string name = curr->name;
					int energy = curr->energy;

					while (temp != NULL) {
						if (temp->name == name) {
							addQueue(name, energy);
							temp = headWait;
							break;
						}
						++i;
						if(i == num){
							temp = headWait;
							break;
						}
						temp = temp->next;
					}

					if (curr->next == NULL) {
						break;
					} else {
						curr = curr->next;
					}
				}
			}

			
			for (int i = 0; i < num; ++i) {
				if (queueHead != nullptr) {
					customer* current = queueHead;
					string name = queueHead->name;
					int energy = queueHead->energy;
					queueHead = queueHead->next;
					current->next = NULL;
					if (queueHead != nullptr) {
						queueHead->prev = nullptr;
					}
					delete current;
					SIZEQUEUE--;
					findDeleteTime(headWait, tailWait, name, sizeFIFO);
					_RED(name, energy);
				}
			}
		}
	
	}

/****************************************************************************************************/
/***************************************************************************************************/

	//Lấy địa chỉ khách ở vị trí index 
		customer* getIndex(customer* tempHead, int index){

			customer* tmp = tempHead; 
			if(index != 0){
			for(int i = 0; i < index; i++){
				tmp = tmp->next;
			}
			}
			return tmp;
		
		}

	// Hàm hoán đổi giá trị ENERGY của hai nút                         
		void swapNodes(customer* &node1, customer* &node2) {
			int tempEnergy = node1->energy;
			string tempName = node1->name;
			node1->energy = node2->energy;
			node1->name = node2->name;
			node2->energy = tempEnergy;
			node2->name = tempName;
		}
	
	// Hàm Insertion Sort tùy chỉnh cho danh sách liên kết đôi
		int inssort2(customer* head, int n, int incr) {
			int swaps = 0;
			for (int i = incr; i < n; i += incr) {
				// cout<<"incea = "<<incr<<endl;
				for (int j = i; (j >= incr); j-= incr ) {
					// cout<<"j= "<<j<<endl;
					customer* node1 = getIndex(head, j);
					customer* node2 = getIndex(head, j - incr);
						// cout<<node1->energy<<"  "<<node2->energy<<endl;
					if(abs(node1->energy) > abs(node2->energy)){
					swapNodes(node1, node2);
					swaps++;
				
					}
		
				}
			}
			return swaps;
		}

	// Hàm sắp xếp danh sách liên kết đôi bằng giải thuật Shell Sort
		int shellsort(customer* head, int n) {
			int swaps = 0;
			int position = 0;
					customer* maxEnergyCustomer = queueTail;
					customer* currentCustomer = queueTail->prev;
					
					while(currentCustomer != NULL){
						if (abs(currentCustomer->energy) > abs(maxEnergyCustomer->energy)){
							maxEnergyCustomer = currentCustomer;
						} else{
						if(abs(currentCustomer->energy) == abs(maxEnergyCustomer->energy)){
							maxEnergyCustomer = maxEnergyCustomer;
							// position++;
						}
					currentCustomer = currentCustomer->prev;
			}	}
			customer* temp = queueHead;
			while (temp !=  NULL)
			{ 	if(temp == maxEnergyCustomer){
				position++;
				break;
			}
			position++;
				temp = temp ->next;
			}
			
			if (head == nullptr || n <= 1) {
				return swaps;
			}

			for (int i = (position) / 2; i > 2; i /= 2) {
				for (int j = 0; j < i; j++) {
					customer* temp = getIndex(queueHead, j);
					swaps += inssort2(temp, position - j, i);
					} 
				}
			
			swaps += inssort2(queueHead, position, 1);
		return swaps;
		}


//SẮP XẾP LẠI HÀNG CHỜ DỰA VÀO GIÁ TRỊ TUYỆT ĐỐI CỦA ENERGY
	void PURPLE(){	
		if(queueHead != NULL){
			int N = shellsort(queueHead, SIZEQUEUE);
			BLUE(N % MAXSIZE);
			}
	}

/****************************************************************************************************/
/****************************************************************************************************/
	
	//In danh sách trong bàn ăn
		void printCusTable(int NUM){
		if(head != nullptr){
		customer* cur = head;
			if(NUM > 0){
				do{
					cur->print();
					cur = cur->next;
				} while(cur!= head);
			} else if(NUM < 0){
				do{
					cur->print();
					cur = cur->prev;
				} while(cur!= head);
			} }

			if(NUM == 0 && queueHead != NULL) {
				customer* cusWait = queueHead;
				while(cusWait != NULL){
					cusWait->print();
					cusWait = cusWait->next;
				}
			}
		
		}


//TỪ X, ĐẢO NGƯỢC VỊ TRÍ TRONG BÀN ĂN THEO CHIỀU NGƯỢC CHIỀU KIM ĐỒNG HỒ
	void REVERSAL(){
		if(head == NULL) return ;
		customer* temp = head->next;
		customer* X = head;
		customer* tmp = head;
		customer* tempHead = NULL;
		int i = 1, j = SIZE;
		do{ if(temp == head){break;}
			if( j <= i){break;}
			if( X->energy  < 0 && temp->energy > 0){
				temp = temp->next;
				--j;
			} else if(X->energy > 0 && temp->energy < 0){
				X = X->prev;
				++i;
			} else if(X->energy < 0 && temp->energy < 0){
				if( X == head){ tempHead = temp;}
				swapNodes(X, temp);
				temp = temp->next;
				X = X->prev;
				++i;
				--j;
			} else if(X->energy > 0 && temp->energy > 0){
				temp = temp->next;
				X = X->prev;
				++i;
				--j;
			}
		}
		while( X != NULL);
		
		if(tempHead != NULL){
		head = tempHead;	}
		i = 1;
		j = SIZE;
		temp = tmp->next;
		X = tmp;
		tempHead = NULL;
		do{ if(temp == tmp){break;}
			if(j <= i){break;}
			if( X->energy  > 0 && temp->energy < 0){
				temp = temp->next;
				--j;
			} else if(X->energy < 0 && temp->energy > 0){
				X = X->prev;
				++i;
			} else if(X->energy > 0 && temp->energy > 0){
				if( X == tmp){ tempHead = temp;}
				swapNodes(X, temp);
				temp = temp->next;
				X = X->prev;
				++i;
				--j;
			} else if(X->energy < 0 && temp->energy < 0){
				temp = temp->next;
				X = X->prev;
				++i;
				--j;
			}
			
		}
		while( X != NULL);
		if(tempHead != NULL){
		head = tempHead;	}
	
		
	}

/****************************************************************************************************/
/****************************************************************************************************/


/*từ vị trí X, xét theo chiều thuận chiều kim đồng hồ, tìm dãy con dài nhất (số phần
từ liên tiếp nhau >= 4) có tổng giá trị ENERGY nhỏ nhất ứng với các vị khách trong bàn ăn.*/
	void UNLIMITED_VOID()
		{
			if (SIZE < 4) return;
			int minsum = 1e7;
			int len = 0;
			customer* cus = head;
			customer* head = nullptr;
			customer* tail = nullptr;
			for (int i = 0; i < SIZE; ++i) {
				int tmpsum = 0;
				customer* lcus = cus;
				for (int j = 0; j < SIZE; ++j) {
					tmpsum += lcus->energy;
					if (j >= 3) {
						if (minsum > tmpsum) {
							minsum = tmpsum;
							len = j + 1;
							//update head tail
							head = cus;
							tail = lcus;
						}
						else if (minsum == tmpsum && j + 1 >= len) {
							minsum = tmpsum;
							len = j + 1;
							//update head tail
							head = cus;
							tail = lcus;
						}
					}
					lcus = lcus->next;
				}
				cus = cus->next;
			}
			if (!head) return;
			cus = head;
			customer* tmp = head;
			minsum = tmp->energy;
			for (int i = 0; i < len; ++i) {
				if (tmp->energy < minsum) {
					minsum = tmp->energy;
					cus = tmp;
				}
				tmp = tmp->next;
			}
			tmp = cus;
			while (tmp) {
				tmp->print();
				if (tmp == tail) break;
				tmp = tmp->next;
			}
			tmp = head;
			while (tmp && cus != head) {
				tmp->print();
				tmp = tmp->next;
				if (tmp == cus) break;
			}
		}
		
/****************************************************************************************************/
/****************************************************************************************************/
	// delete o danh sach thu tu FIFO ban an
		void deleteFIFO(int num){
			if(num == 0){
				int size = sizeQueue;
				customer* temp = head_Queue;
				for(int i = 0; i < size; ++i){
					if(temp == NULL){break;}
					if( temp->energy > 0){
						customer* toDelete = temp;
						if(temp->prev != NULL){
							temp->prev->next = temp->next;
						} 
						if (temp->next!=NULL) {
							temp->next->prev = temp->prev;
						}
						if (temp == head_Queue) {
							head_Queue = temp->next;
						}
						temp = temp->next;
						toDelete->next = NULL;
						if(toDelete != head_Queue){
							toDelete->prev = NULL;
						}
						delete toDelete;
						sizeQueue--;
						} else {
						temp = temp->next;
						}
				}
			} else {
				int size = sizeQueue;
				customer* temp = head_Queue;
				for(int i = 0; i < size; ++i){
					if(temp == NULL){break;}
					if( temp->energy < 0){
						customer* toDelete = temp;
						if(temp->prev != NULL){
							temp->prev->next = temp->next;
						} 
						if (temp->next!=NULL) {
							temp->next->prev = temp->prev;
						}
						if (temp == head_Queue) {
							head_Queue = temp->next;
						}
						temp = temp->next;
						toDelete->next = NULL;
						if(toDelete != head_Queue){
							toDelete->prev = NULL;
						}
						delete toDelete;
						sizeQueue--;
						} else {
						temp = temp->next;
						}
				}
			}
		}
	//Print thuat su or oan linh bi duoi ve
		void print_Customer_Out(customer* tail, int num){
			if(tail != NULL) {
			customer* cus = tail;
			if( num == 0){
				while(cus != NULL){
					if(cus->energy > 0){
					cus->print();
					}
					if(cus->prev != NULL){
					cus = cus->prev;} else {break;}
				}
			} else { 
				while(cus != NULL){
					if(cus->energy < 0){
					cus->print();
					}
					if(cus->prev != NULL){
					cus = cus->prev;} else {break;}
				}
			}
			}
			
		}
	
	//Tính tổng energy của thuật sư hoặc oán linh
		int sum_Energy( int num){
			int sumEnergy = 0;
			if( num == 0){//THUAT SU
			// ban an
				if(head != NULL){
				customer* current = head;
				do{
					if(current->energy > 0){
						sumEnergy += current->energy;
					}
					if(current->next != NULL){
						current = current->next;}
						else {
							break;
						}
				} while(current != head);
				}

			// Hang doi
				if(headWait != NULL){
				customer* current = headWait;
				while(current != NULL){
					if(current->energy > 0){
						sumEnergy += current->energy;
					}
						if(current->next != NULL){
						current = current->next;}
						else {
							break;
						}
				}
				}
			} else {//OAN LINH
				// ban an
				sumEnergy = 0;
				if(head != NULL){
				customer* current = head;
				do{
					if(current->energy < 0){
						sumEnergy += abs(current->energy);
					}
						if(current->next != NULL){
						current = current->next;}
						else {
							break;
						}
				} while(current != head);
				}

			// Hang doi
			if(headWait != NULL){
				customer* current = headWait;
				while(current != NULL){
					if(current->energy < 0){
						sumEnergy += abs(current->energy);
					}
						if(current->next != NULL){
						current = current->next;}
						else {
							break;
						}
				}
			}
			}
	
		return sumEnergy;
	}

	//Xoa customer
		int deleteCustomer(int num){
			int N = 0;
			//XOA THUAT SU
			if(num == 0 ){
				//duyet danh sach khach hang
			
				if(tailWait != NULL){
				print_Customer_Out(tailWait, 0);}
				
				if(tail_Queue != NULL){
				print_Customer_Out(tail_Queue, 0);}

	
	if (head_Queue!= NULL) {
    customer* temp = head_Queue;
    while (temp != NULL) {
        customer* nextTemp = temp->next; // Store the next node

        if (temp->energy > 0) {
            // Save necessary information before deletion
            string valueName = temp->name;
            int valueRemove = temp->energy;

            // Remove the current node
            if (temp == tail_Queue) {
                tail_Queue = temp->prev; // Update tail_Queue if necessary
            }
			if(temp == head_Queue){
				head_Queue = temp->next;
			}

            if (temp->next != NULL) {
                temp->next->prev = temp->prev;
            }

            if (temp->prev != NULL) {
                temp->prev->next = temp->next;
            }
			++N;
            delete temp;
            sizeQueue--;

            // Search and delete the corresponding node in head_Queue
            int Size = SIZE;
            customer* tmp = head;
            for (int j = 0; j < Size; ++j) {
                if (tmp->name == valueName) {
						if(valueRemove > 0)
                        {head = tmp->next;}
						if( valueRemove < 0){
							head = tmp->prev;
						}

                    if (tmp->next != NULL) {
                        tmp->next->prev = tmp->prev;
                    }

                    if (tmp->prev != NULL) {
                        tmp->prev->next = tmp->next;
                    }

                    delete tmp;
                    SIZE--;
                    break;
                }
                tmp = tmp->next;
            }
        }

        temp = nextTemp; // Move to the next node
    }
}
if(head_Queue == NULL){
	head = NULL; SIZE = 0;
}

				
				//duyet danh sach hang choo
					if(queueHead != NULL){
					customer* temp = queueHead;
					while (temp != NULL) {
						if (temp->energy > 0) {
							// Lưu thông tin cần thiết trước khi xóa
							string name = temp->name;
					
							
							// Xóa node khỏi danh sách
							if (temp->prev != NULL) {
								temp->prev->next = temp->next;
							}
							if (temp->next != NULL) {
								temp->next->prev = temp->prev;
							}
							if (temp == queueHead) {
								queueHead = temp->next;
							}
							if(temp == queueTail){
								queueTail = temp->prev;
							 }
							customer* toDelete = temp;
							temp = temp->next;
							toDelete->next = NULL;
							if (toDelete != queueHead) {
								toDelete->prev = NULL;
							}
							delete toDelete;
							--SIZEQUEUE;

							// Gọi hàm findDeleteTime sau khi xóa node
							findDeleteTime(headWait,tailWait, name, sizeFIFO);
				
						} else {
							if(temp->next != NULL){
							temp = temp->next;}
							else {
								break;
							}
						}
						}
				
			} 
			} else 
			{///OAN LINH
				
					if(tailWait != NULL){
					print_Customer_Out(tailWait, 1);}
					if(tail_Queue != NULL){
					print_Customer_Out(tail_Queue, 1);}
		
	if (head_Queue!= NULL) {
    customer* temp = head_Queue;
    while (temp != NULL) {
        customer* nextTemp = temp->next; // Store the next node

        if (temp->energy < 0) {
            // Save necessary information before deletion
            string valueName = temp->name;
            int valueRemove = temp->energy;

            // Remove the current node
            if (temp == tail_Queue) {
                tail_Queue = temp->prev; // Update tail_Queue if necessary
            }
			if(temp == head_Queue){
				head_Queue = temp->next;
			}

            if (temp->next != NULL) {
                temp->next->prev = temp->prev;
            }

            if (temp->prev != NULL) {
                temp->prev->next = temp->next;
            }
			++N;
            delete temp;
            sizeQueue--;

            // Search and delete the corresponding node in head_Queue
            int Size = SIZE;
            customer* tmp = head;
            for (int j = 0; j < Size; ++j) {
                if (tmp->name == valueName) {
						if(valueRemove > 0)
                        {head = tmp->next;}
						if( valueRemove < 0){
							head = tmp->prev;
						}

                    if (tmp->next != NULL) {
                        tmp->next->prev = tmp->prev;
                    }

                    if (tmp->prev != NULL) {
                        tmp->prev->next = tmp->next;
                    }

                    delete tmp;
                    SIZE--;
                    break;
                }
                tmp = tmp->next;
            }
        }

        temp = nextTemp; // Move to the next node
    }
}
if(head_Queue == NULL){
	head = NULL; SIZE = 0;
}

			
				//duyet danh sach hang cho
			
					if(queueHead != NULL){
					customer* temp = queueHead;
					while (temp != NULL) {
						if (temp->energy < 0) {
							// Lưu thông tin cần thiết trước khi xóa
							string name = temp->name;
				
							
							// Xóa node khỏi danh sách
							if (temp->prev != NULL) {
								temp->prev->next = temp->next;
							}
							if (temp->next != NULL) {
								temp->next->prev = temp->prev;
							}
							if (temp == queueHead) {
								queueHead = temp->next;
							}
							 if(temp == queueTail){
								queueTail = temp->prev;
							 }
							customer* toDelete = temp;
							temp = temp->next;
							toDelete->next = NULL;
							if (toDelete != queueHead) {
								toDelete->prev = NULL;
							}
							delete toDelete;
							// Gọi hàm findDeleteTime sau khi xóa node
							--SIZEQUEUE;
							findDeleteTime(headWait,tailWait, name, sizeFIFO);
							
						} else {
							if(temp->next != NULL){
							temp = temp->next;}
							else {
								break;
							}
						}
						}
				
			} 
				}
		return N;
		}
		/*****************************************/
		
	
/*Vì các chú thuật sư và oán linh trong quá trình dùng bữa có lời qua tiếng lại dẫn đến mất
không khí dùng bữa tại nhà hàng. Cho nên chủ nhà hàng quyết định sẽ đuổi tất cả chú thuật
sư hoặc oán linh */
	void DOMAIN_EXPANSION()
		{
			// cout << "\ndomain_expansion" << endl;
			if( head != NULL || headWait != NULL){
				int size = 0;
				int a = sum_Energy(0);//thuat su
					// cout<<"SUM OF MAGIC ENERGY: "<< a <<endl;
				int b = sum_Energy(1);//oan linh
					// cout<<"SUM OF SPIRIT ENERGY : "<< b <<endl;
				if(a >= b && b!= 0 && a!=0){
					//xoa tat ca oan linh co mat nha hang
					size += deleteCustomer(1);//xoa oan linh
					
				} else if(a < b && b!= 0 && a!=0)
				{
					size += deleteCustomer(0);//xoa thuat su
				
				}
			
				if (queueHead != NULL && headWait != NULL && sizeQueue < MAXSIZE) {
				customer* temp = queueHead;
				customer* curr = headWait;

				while (curr != NULL) {
				int i = 0;
					string name = curr->name;
					int energy = curr->energy;
			

					while (temp != NULL) {
						if (temp->name == name) {
							addQueue(name, energy);
						
							temp = headWait;
							break;
						}
						++i;
						if(i == size){
							temp = headWait;
							break;
						}
						temp = temp->next;
					}

		
					if (curr->next == NULL) {
						break;
					} else {
						curr = curr->next;
					}
				}
			}
			for (int i = 0; i < size; ++i) {
					if (queueHead != nullptr && SIZE < MAXSIZE) {
				
						string name = queueHead->name;
						int energy = queueHead->energy;
				
						findDeleteTime(headWait, tailWait, name, sizeFIFO);
						findDeleteTime(queueHead, queueTail, name, SIZEQUEUE);
						
						_RED(name, energy);
					}
				}

						
			}
			
		}
		
/****************************************************************************************************/
/****************************************************************************************************/

/*In thông tin của tất cả vị khách ngồi vào bàn ăn tính từ vị trí gần nhất vừa có sự thay đổi*/
	void LIGHT(int num)
	{
		// cout << "\nlight START " << num << endl;
		printCusTable(num);
		// cout << "light END " << num << endl;
	}
	~imp_res(){
		if(head != NULL){
			clear();
		}
		if(head_Queue != NULL){
			clearQueue();
		}
		if(headWait != NULL){
			while (headWait != nullptr && sizeFIFO != 0 ) {
				customer* temp = headWait;
				headWait = headWait->next;
				if (headWait!= nullptr) {
					headWait->prev = nullptr;
				}
				if (temp != nullptr) {
				delete temp;
				temp = nullptr;
				}
				sizeFIFO--;
			}
			headWait = NULL;
			tailWait = NULL;
			sizeFIFO = 0;
		}
		if(queueHead != NULL){
			while (queueHead != nullptr && SIZEQUEUE != 0 ) {
				customer* temp = queueHead;
				queueHead = queueHead->next;
				if (queueHead!= nullptr) {
					queueHead->prev = nullptr;
				}
				if (temp != nullptr) {
				delete temp;
				temp = nullptr;
				}
				SIZEQUEUE--;
			}
			queueHead = NULL;
			queueTail= NULL;
			SIZEQUEUE= 0;
		}

		
	}
};
