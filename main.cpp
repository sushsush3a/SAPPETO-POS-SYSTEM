#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

// ===== Data Structures =====
struct Product {
    int id;
    string name;
    double price;
};

struct CartItem {
    Product product;
    int quantity;
};

    void printBanner() {
    cout << R"(

███████╗ █████╗ ██████╗ ██████╗ ███████╗████████╗ ██████╗ 
██╔════╝██╔══██╗██╔══██╗██╔══██╗██╔════╝╚══██╔══╝██╔═══██╗
███████╗███████║██████╔╝██████╔╝█████╗     ██║   ██║   ██║
╚════██║██╔══██║██╔═══╝ ██╔═══╝ ██╔══╝     ██║   ██║   ██║
███████║██║  ██║██║     ██║     ███████╗   ██║   ╚██████╔╝
╚══════╝╚═╝  ╚═╝╚═╝     ╚═╝     ╚══════╝   ╚═╝    ╚═════╝ 
                    Welcome to SAPPETO POS
)";
    cout << endl;
}

// ===== Function Declarations =====
void displayCatalog();
Product getProductById(int id);
void checkout(const vector<CartItem>& cart);

// ===== Product Catalog =====
vector<Product> productCatalog = {
    {1, "Addidas", 253.89},
    {2, "Nikee", 453.79},
    {3, "Nwebalance", 499.99},
    {4, "Aciids", 199.99},
    {5, "Converser", 477.99}
};

int terminalWidth = 70; 

void centerLine(const string& line) {
    int padding = (terminalWidth - line.length()) / 2;
    if (padding > 0)
        cout << string(padding, ' ');
    cout << line << endl;
}

// ===== Function Definitions =====
void displayCatalog() {
    cout << "\n";
    centerLine("=== Sappeto Shoe Catalog ===");

    string header;
    ostringstream oss;

    oss << left << setw(5) << "ID" << setw(20) << "Product" << "Price ($)";
    header = oss.str();
    centerLine(header);

    centerLine("------------------------------------");

    for (const auto& product : productCatalog) {
        ostringstream lineStream;
        lineStream << left << setw(5) << product.id
                   << setw(20) << product.name
                   << fixed << setprecision(2) << product.price;
        centerLine(lineStream.str());
    }
}

Product getProductById(int id) {
    for (const auto& product : productCatalog) {
        if (product.id == id) return product;
    }
    return {-1, "Invalid", 0.0};
}

void checkout(const vector<CartItem>& cart) {
    double total = 0.0;
    cout << "\n============== Receipt ============== \n";
    cout << left << setw(20) << "Product" << setw(10) << "Qty" << "Total\n";
    cout << "--------------------------------------\n";

    for (const auto& item : cart) {
        double itemTotal = item.product.price * item.quantity;
        total += itemTotal;
        cout << left << setw(20) << item.product.name
             << setw(10) << item.quantity
             << fixed << setprecision(2) << itemTotal << "\n";
    }

    cout << "--------------------------------------\n";
    cout << "Grand Total: $" << fixed << setprecision(2) << total << "\n";
    cout << "Thank you for shopping with us!\n";
}

// ===== Main Program =====
int main() {
    printBanner();
    vector<CartItem> cart;
    char choice;

    int prodId, qty;

do {
    displayCatalog();

    Product selected;
    while (true) {
        cout << "\nEnter the Product ID to add to cart: ";
        cin >> prodId;

        selected = getProductById(prodId);

        if (selected.id == -1) {
            cout << "Invalid Product ID. Try again.\n";
        } else {
            break; // valid product found
        }
    }

    do {
        cout << "Enter quantity: ";
        cin >> qty;
        if (qty <= 0) {
            cout << "Invalid quantity. Must be greater than 0.\n";
        }
    } while (qty <= 0);

    cart.push_back({selected, qty});
    cout << "Item added to cart!\n";

    cout << "Add another item? (y/n): ";
    cin >> choice;

    } while (tolower(choice) == 'y');

    checkout(cart);

    return 0;
}