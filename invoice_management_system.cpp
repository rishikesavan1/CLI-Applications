#include<iostream>
#include<vector>
#include<string>
using namespace std;

class InvoiceItem{
private:
	string itemName;
	int itemQuantity;
	int itemPrice;
	
public:
	InvoiceItem(string name,int quantity,int price) : itemName(name), itemQuantity(quantity), itemPrice(price) {}
		
	string getItemName() const{
		return itemName;
	}
	int getItemQuantity() const{
		return itemQuantity;
	}
	int getItemPrice() const{
		return itemPrice;
	}
	int getItemTotalPrice() const{
		return itemQuantity*itemPrice;
	}
};

class Invoice{
private:
	int invoiceId;
	vector<InvoiceItem> items;
	int customerId;

public:
	Invoice(int invId, int cusId) : invoiceId(invId), customerId(cusId){}
	
	void addItem(const InvoiceItem& item){
		items.push_back(item);
	}
	
	const vector<InvoiceItem> getItem() const{
		return items;
	}
	
	int getInvoiceId() const{
		return invoiceId;
	}
	
	int getTotalPrice() const{
		int totalPrice = 0;
		for(const auto& item : items){
			totalPrice += item.getItemTotalPrice();
		}
		return totalPrice;
	}
	
	int getCustomerId() const{
		return customerId;
	}
};

class Customer{
private:
	int customerId;
	string name;
	
public:
	Customer(int cusId, string s) : customerId(cusId) , name(s) {}
	
	int getCustomerId() const{
		return customerId;
	}
	
	string getCustomerName() const{
		return name;
	}
	
};

class InvoiceManagementSystem {
private:
	vector<Invoice> invoices;
	vector<Customer> customers;
	int nextCustomer = 1;
	int nextInvoice = 101;
public:
	void addCustomer(string customerName){
		Customer customer(nextCustomer,customerName);
		customers.push_back(customer);
		cout << "Customer Name  " << customerName << "  was added with Customer Id  " << nextCustomer << endl;
		nextCustomer++;
	}
	
	void addInvoice(string customerName){
		int customerId = -1;
		for(const auto& customer:customers){
			if(customer.getCustomerName() == customerName){
				customerId = customer.getCustomerId();
				break;
			}
		}
		if(customerId == -1){
			cout << "Customer not found...";
			return;
		}
		Invoice invoice(nextInvoice,customerId);
		invoices.push_back(invoice);
		cout << "Customer Name  " << customerName << "  was added with Invoice Id  " << nextInvoice << endl;
		nextInvoice++;
	}
	
	void addItemToInvoice(int invoiceId, InvoiceItem item){
		int itemFound = -1;
		for(auto& invoice : invoices){
			if(invoice.getInvoiceId() == invoiceId){
				itemFound = 1;
				invoice.addItem(item);
			}
		}
		if(itemFound == -1){
			cout << "Invoice Not found...";
			return;
		}
		cout <<"Invoice Id  " << invoiceId << " got a new item  " << item.getItemName() << " with price of  " << item.getItemPrice() << " and quantity of  " << item.getItemQuantity() << endl;
	}
	
	bool invoiceCheck(int invoiceId){
		int itemFound = -1;
		for(auto& invoice : invoices){
			if(invoice.getInvoiceId() == invoiceId){
				itemFound = 1;
			}
		}
		if(itemFound == -1){
			cout << "Invoice Not found...";
			return true;
		}
		return false;
	}
	
	void displayCustomers(){
		cout << endl;
		cout << "Customer Id\t" << "Customer Name" << endl; 
		cout << "----------------------------------" << endl;
		for(const auto& customer:customers){
			cout << customer.getCustomerId() << "\t\t" << customer.getCustomerName() << endl;
		}
		cout << "----------------------------------" << endl;
	}
	
	void displayInvoices(){
		cout << endl;
		cout << "Invoice Id\tCustomer Id\tCustomer Name\tTotal Price" << endl; 
		string customerName;
		cout << "-------------------------------------------------------" << endl;
		for(const auto& invoice:invoices){
			for(const auto& customer:customers){
				if(customer.getCustomerId() == invoice.getCustomerId()){
					customerName = customer.getCustomerName();
				}
			}
			cout << invoice.getInvoiceId() << "\t\t" << invoice.getCustomerId() << "\t\t" << customerName << "\t\t" << invoice.getTotalPrice() <<endl;
		}
		cout << "-------------------------------------------------------" << endl;
	}
	
	void displayCustomerInvoices(string customerName){
		int customerId;
		for(const auto& customer:customers){
			if(customer.getCustomerName() == customerName){
				customerId = customer.getCustomerId();
			}
		}
		cout << endl;
		cout << "Customer Id : " << customerId << "\tCustomer Name : " << customerName << endl;
		cout << "-------------------------------------" << endl;
		cout << "Invoice Id\t" << "Price" << endl;
		cout << "-------------------------------------" << endl;
		for(const auto& invoice : invoices){
			if(invoice.getCustomerId() == customerId){
				cout << invoice.getInvoiceId() << "\t\t" << invoice.getTotalPrice() << endl;
			}
		}
		cout << "-------------------------------------" << endl;
	}
	
	void displayInvoiceDetails(int invoiceId){
		Invoice* targetInvoice = nullptr;
		int customerId;
		string customerName;
		for(auto& invoice : invoices){
			if(invoice.getInvoiceId() == invoiceId){
				targetInvoice = &invoice;
				customerId = invoice.getCustomerId();
			}
		}
		for(const auto& customer : customers){
			if(customer.getCustomerId() == customerId){
				customerName = customer.getCustomerName();
				
			}
		}
		cout << endl;
		cout << "Invoice Id : " << invoiceId << "\tCustomer Id : " << customerId << "\tCustomer Name : " << customerName << endl;
		cout << "-------------------------------------------------------" << endl;
		cout << "Item Name\tPrice per Unit\tItem Quantity\tItem Price" << endl;
		for(const auto&item : targetInvoice -> getItem()){
				cout << item.getItemName() << "\t\t" << item.getItemPrice() <<"\t\t" << item.getItemQuantity() << "\t\t" << item.getItemTotalPrice() << endl;
		}
		cout << "-------------------------------------------------------" << endl;
		cout << "\t\t\t\t\tTotal : " << targetInvoice->getTotalPrice() << endl;
		cout << "-------------------------------------------------------" << endl;
	}
};


int main(){
	InvoiceManagementSystem inv;
	
	
//	inv.addCustomer("Rishi");
//	inv.addCustomer("Kesavan");
//	inv.displayCustomers();
//	inv.addInvoice("Rishi");
//	inv.addInvoice("Rishi");
//	inv.addInvoice("Kesavan");
//	inv.displayInvoices();
//	inv.displayCustomerInvoices("Rishi");
//	inv.addItemToInvoice(101, InvoiceItem("Laptop", 1, 50000));
//    inv.addItemToInvoice(101, InvoiceItem("Mouse", 1, 800));
//    inv.addItemToInvoice(102, InvoiceItem("Monitor", 2, 15000));
//    inv.addItemToInvoice(103, InvoiceItem("Keyboard", 1, 1200));
//
//    inv.displayInvoices();
//    inv.displayCustomerInvoices("Rishi");
//    inv.displayInvoiceDetails(101);
    
    int choice = 0;
    int invoiceId,itemQuantity,itemPrice;
    string customerName, itemName;
    while(true){
    	cout << "\n\n----- Select From the choice -----";
    	cout <<"\n1. Add a customer \n2. Add an invoice \n3. Add items to an invoice \n4. List all customers \n5. List all invoices \n6. List all invoices of a customer \n7. Display the full details of an invoice \n8. Exit" << endl;
		cout << "Enter Your Choice : ";
		cin >> choice;
		if(choice == 8){
			cout << "Exiting... \nDone...";
			break;
		}
		switch(choice){
			
			//add a customer
			case 1: 
				cout << "Enter the Customer Name : ";
				cin >> customerName;
				inv.addCustomer(customerName);
				break;
			
			//Add an invoice
			case 2: 
				cout << "Enter the Customer Name to create a Invoice: ";
				cin >> customerName;
				inv.addInvoice(customerName);
				break;
			
			//Add items to an invoice
			case 3: 
				cout << "Enter the Invoice Id to add an item : ";
				cin >> invoiceId;
				if(inv.invoiceCheck(invoiceId)){
					break;	
				}
				cout << "Enter the item Name : ";
				cin >> itemName;
				cout << "Enter the item Price : ";
				cin >> itemPrice;
				cout << "Enter number of items bought : ";
				cin >> itemQuantity;
				inv.addItemToInvoice(invoiceId, InvoiceItem(itemName, itemQuantity, itemPrice));
				break;
			
			//List all customers
			case 4:
				inv.displayCustomers();
				break;
				
			//List all invoices
			case 5: 
				inv.displayInvoices();
				break;
			
			//List all invoices of a customer
			case 6: 
				cout << "Enter the Customer Name to view all Invoices: ";
				cin >> customerName;
				inv.displayCustomerInvoices(customerName);
				break;
				
			//Display the full details of an invoice
			case 7: 
				cout << "Enter the Invoice Id to Check details : ";
				cin >> invoiceId;
				inv.displayInvoiceDetails(invoiceId);
				break;
				
			default:
				cout << "Invalid Choice !" << endl;
				break;
			
		}
	}
	return 0;
}