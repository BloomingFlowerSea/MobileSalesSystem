#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Define Constants */
#define MAX_PRODUCTS 100
#define MAX_SALES 200
#define STR_LEN 50
#define PRODUCTS_FILE "products.txt"
#define SALES_FILE "sales_records.txt"

/* Data Structures */
typedef struct {
    int warranty_months;
    char provider[STR_LEN];
} Warranty;

typedef struct {
    int product_id;
    char product_name[STR_LEN];
    char brand[STR_LEN];
    float price;
    int quantity_in_stock;
    Warranty warranty;
} Product;

typedef struct {
    int product_id;
    char customer_name[STR_LEN];
    char sale_date[11]; // DD/MM/YYYY
    int quantity_sold;
} SaleRecord;

/* Function Prototypes */
void parse_csv_line_product(char* line, Product* p);
void parse_csv_line_sale(char* line, SaleRecord* s);
int LoadProducts(Product products[], int* p_count, const char* filename);
int LoadSalesData(SaleRecord sales[], int* s_count, const char* filename);
void SaveProducts(Product products[], int p_count, const char* filename);
void AppendSaleToFile(SaleRecord* sale, const char* filename);
void PrintSingleProduct(Product* p);

/* Existing Core Logic Functions */
void Menu_ModifyLastProduct(Product products[], int p_count);
void Menu_AddNewProduct(Product products[], int* p_count);
void Menu_SellProduct(Product products[], int p_count, SaleRecord sales[], int* s_count);
void Menu_SortProducts(Product products[], int p_count);
void Menu_PrintProducts(Product products[], int p_count);
void Menu_RevenueReport(Product products[], int p_count, SaleRecord sales[], int s_count);
void Menu_MonthlyReport(Product products[], int p_count, SaleRecord sales[], int s_count);

/* New Assignment Task Wrapper Functions (Q1-Q4) */
void Q1_Task_Initialization(Product products[], int p_count, SaleRecord sales[], int* s_count);
void Q2_Task_Sorting(Product products[], int p_count);
void Q3_Task_Revenue(Product products[], int p_count, SaleRecord sales[], int s_count);
void Q4_Task_MonthlyReport(Product products[], int p_count, SaleRecord sales[], int s_count);

/*
@function: clear_buffer
@desc: Clears the standard input buffer (stdin) to prevent scanning issues.
@param: None
@return: void
*/
void clear_buffer() {
    int c;
    // Loop until newline or End Of File is reached to consume remaining characters
    while ((c = getchar()) != '\n' && c != EOF);
}

/*
@function: main
@desc: The main entry point of the program. Initializes data and runs the menu loop.
@param: None
@return: int - Returns 0 upon successful execution
*/
int main() {
    Product products[MAX_PRODUCTS];
    SaleRecord sales[MAX_SALES];
    int p_count = 0;
    int s_count = 0;
    int choice;

    // --- Initialization ---
    printf("Initializing System...\n");

    // Load products from file at startup
    if (!LoadProducts(products, &p_count, PRODUCTS_FILE)) {
        printf("Warning: Failed to load products or file empty.\n");
    }
    else {
        printf("Loaded %d products.\n", p_count);
    }

    // Load sales records from file at startup
    if (!LoadSalesData(sales, &s_count, SALES_FILE)) {
        printf("Warning: Failed to load sales or file empty.\n");
    }
    else {
        printf("Loaded %d sales records.\n", s_count);
    }
    printf("System Ready.\n\n");

    // --- Main Menu Loop ---
    // Runs indefinitely until the user selects Exit (0)
    while (1) {
        printf("\n=== Product Sales Management System ===\n");
        printf("--- Operational Menu ---\n");
        printf("1. Modify Last Product Info\n");
        printf("2. Add New Product\n");
        printf("3. Sell a Product (Update Stock & Record)\n");
        printf("4. Sort Products by Price\n");
        printf("5. Print Product List\n");
        printf("6. Revenue Calculation Report\n");
        printf("7. Generate Monthly Sales Report\n");
        printf("--- Assignment Task Demos ---\n");
        printf("8. Show Q1 (Init & Validation)\n");
        printf("9. Show Q2 (Sorting Demo)\n");
        printf("10. Show Q3 (Revenue Demo)\n");
        printf("11. Show Q4 (Report Demo)\n");
        printf("0. Exit\n");
        printf("Select an option: ");

        // Validate integer input
        if (scanf("%d", &choice) != 1) {
            clear_buffer(); // Clean invalid input
            continue;
        }
        clear_buffer(); // Consume newline after number input

        // Handle user selection
        switch (choice) {
        case 1:
            Menu_ModifyLastProduct(products, p_count);
            break;
        case 2:
            Menu_AddNewProduct(products, &p_count);
            break;
        case 3:
            Menu_SellProduct(products, p_count, sales, &s_count);
            break;
        case 4:
            Menu_SortProducts(products, p_count);
            break;
        case 5:
            Menu_PrintProducts(products, p_count);
            break;
        case 6:
            Menu_RevenueReport(products, p_count, sales, s_count);
            break;
        case 7:
            Menu_MonthlyReport(products, p_count, sales, s_count);
            break;
        case 8: // Call Q1 Function
            Q1_Task_Initialization(products, p_count, sales, &s_count);
            break;
        case 9: // Call Q2 Function
            Q2_Task_Sorting(products, p_count);
            break;
        case 10: // Call Q3 Function
            Q3_Task_Revenue(products, p_count, sales, s_count);
            break;
        case 11: // Call Q4 Function
            Q4_Task_MonthlyReport(products, p_count, sales, s_count);
            break;
        case 0:
            printf("Exiting system. Goodbye!\n");
            return 0;
        default:
            printf("Invalid option. Please try again.\n");
        }
    }
    return 0;
}

/* ================== Assignment Task Wrappers (Q1-Q4) ================== */

/*
@function: Q1_Task_Initialization
@desc: Demonstrates Task 1: Modifies the last product, programmatically adds 5 sales,
       and validates data by printing the first 3 records.
@param: products[] - The array of products
@param: p_count - The current number of products
@param: sales[] - The array of sales records
@param: s_count - Pointer to the sales counter to allow updates
@return: void
*/
void Q1_Task_Initialization(Product products[], int p_count, SaleRecord sales[], int* s_count) {
    printf("\n=== [Q1 Demo] Product Database Initialization & Validation ===\n");

    // Requirement 1: Modify the last entry 
    printf("Step 1: Modifying the last entry...\n");
    Menu_ModifyLastProduct(products, p_count);

    // Requirement 2: Append 5 new sales records to sales_records.txt programmatically. 
    printf("\nStep 2: Appending 5 new sales records...\n");
    for (int i = 0; i < 5; i++) {
        printf("\nAdd record %d\n", i + 1);
        // Calls the sell function to update memory and file simultaneously
        Menu_SellProduct(products, p_count, sales, s_count);
    }

    // Requirement 3: Validate data integrity by printing the first 3 product records 
    printf("\nStep 3: Validating Data (First 3 Products)...\n");
    printf("%-5s %-30s %-15s %-10s\n", "ID", "Name", "Brand", "Price");
    printf("------------------------------------------------------------\n");
    for (int i = 0; i < 3 && i < p_count; i++) {
        printf("%-5d %-30s %-15s %-10.2f\n",
            products[i].product_id,
            products[i].product_name,
            products[i].brand,
            products[i].price);
    }
}

/*
@function: Q2_Task_Sorting
@desc: Demonstrates Task 2: Sorts the product list by price and displays the result.
@param: products[] - The array of products
@param: p_count - The number of products
@return: void
*/
void Q2_Task_Sorting(Product products[], int p_count) {
    printf("\n=== [Q2 Demo] Product Sorting by Price ===\n");

    // Requirement 1: Sort products using bubble sort 
    Menu_SortProducts(products, p_count);

    // Requirement 2: Output sorted list 
    printf("\nDisplaying Sorted List:\n");
    Menu_PrintProducts(products, p_count);
}

/*
@function: Q3_Task_Revenue
@desc: Demonstrates Task 3: Calculates revenue for the year 2025.
@param: products[] - Array of products
@param: p_count - Number of products
@param: sales[] - Array of sales
@param: s_count - Number of sales
@return: void
*/
void Q3_Task_Revenue(Product products[], int p_count, SaleRecord sales[], int s_count) {
    printf("\n=== [Q3 Demo] Sales Record Integration & Revenue ===\n");
    // Reuse existing revenue report logic
    Menu_RevenueReport(products, p_count, sales, s_count);
}

/*
@function: Q4_Task_MonthlyReport
@desc: Demonstrates Task 4: Generates a text file report for October 2025 sales.
@param: products[] - Array of products
@param: p_count - Number of products
@param: sales[] - Array of sales
@param: s_count - Number of sales
@return: void
*/
void Q4_Task_MonthlyReport(Product products[], int p_count, SaleRecord sales[], int s_count) {
    printf("\n=== [Q4 Demo] Monthly Sales Report Generation ===\n");
    // Reuse existing monthly report logic
    Menu_MonthlyReport(products, p_count, sales, s_count);
}


/* ================== Operational Logic Implementations ================== */

/*
@function: Menu_ModifyLastProduct
@desc: Allows the user to select and modify attributes of the last product in the database.
       It saves changes to the file immediately.
@param: products[] - Array of products
@param: p_count - Current number of products
@return: void
*/
void Menu_ModifyLastProduct(Product products[], int p_count) {
    if (p_count == 0) {
        printf("Error: No products in database to modify.\n");
        return;
    }

    int idx = p_count - 1; // Target the last index
    Product* p = &products[idx]; // Use pointer for direct memory modification

    // Print Original Info
    printf("\n[Current Information (Before Modification)]");
    PrintSingleProduct(p);

    // Sub-menu for attribute selection
    int choice;
    printf("\n--- Modify Attribute ---\n");
    printf("1. Product Name\n");
    printf("2. Brand\n");
    printf("3. Price\n");
    printf("4. Stock Quantity\n");
    printf("5. Warranty Months\n");
    printf("6. Warranty Provider\n");
    printf("0. Cancel\n");
    printf("Select attribute to modify: ");

    if (scanf("%d", &choice) != 1) {
        clear_buffer();
        return;
    }
    clear_buffer();

    if (choice == 0) {
        printf("Modification cancelled.\n");
        return;
    }

    // Process modification based on user choice
    printf("\nEnter new value: ");
    switch (choice) {
    case 1: scanf("%[^\n]", p->product_name); clear_buffer(); break;
    case 2: scanf("%[^\n]", p->brand); clear_buffer(); break;
    case 3: scanf("%f", &p->price); clear_buffer(); break;
    case 4: scanf("%d", &p->quantity_in_stock); clear_buffer(); break;
    case 5: scanf("%d", &p->warranty.warranty_months); clear_buffer(); break;
    case 6: scanf("%[^\n]", p->warranty.provider); clear_buffer(); break;
    default: printf("Invalid selection.\n"); return;
    }

    // Print New Info
    printf("\n[Updated Information (After Modification)]");
    PrintSingleProduct(p);

    // Sync changes to disk
    SaveProducts(products, p_count, PRODUCTS_FILE);
    printf("\nDatabase updated successfully!\n");
}

/*
@function: Menu_AddNewProduct
@desc: Prompts user for all product details and adds a new product to the list and file.
@param: products[] - Array of products
@param: p_count - Pointer to product count (to increment it)
@return: void
*/
void Menu_AddNewProduct(Product products[], int* p_count) {
    if (*p_count >= MAX_PRODUCTS) {
        printf("Error: Product database full.\n");
        return;
    }
    Product* p = &products[*p_count];

    // Collect Input
    printf("Enter Product ID: "); scanf("%d", &p->product_id); clear_buffer();
    printf("Enter Name: "); scanf("%[^\n]", p->product_name); clear_buffer();
    printf("Enter Brand: "); scanf("%[^\n]", p->brand); clear_buffer();
    printf("Enter Price: "); scanf("%f", &p->price);
    printf("Enter Stock Quantity: "); scanf("%d", &p->quantity_in_stock);
    printf("Enter Warranty Months: "); scanf("%d", &p->warranty.warranty_months); clear_buffer();
    printf("Enter Warranty Provider: "); scanf("%[^\n]", p->warranty.provider); clear_buffer();

    // Increment count and save
    (*p_count)++;
    SaveProducts(products, *p_count, PRODUCTS_FILE);
    printf("Product added and saved successfully.\n");
}

/*
@function: Menu_SellProduct
@desc: Handles a sales transaction. Checks stock, updates product quantity,
       records the sale, and updates both product and sales files.
@param: products[] - Array of products
@param: p_count - Number of products
@param: sales[] - Array of sales records
@param: s_count - Pointer to sales count (to increment it)
@return: void
*/
void Menu_SellProduct(Product products[], int p_count, SaleRecord sales[], int* s_count) {
    if (*s_count >= MAX_SALES) {
        printf("Error: Sales database full.\n");
        return;
    }
    int target_id, qty;
    char customer[STR_LEN], date[15];

    // 1. Get Product ID
    printf("Enter Product ID to sell: ");
    scanf("%d", &target_id);

    // 2. Find Product in Array
    int p_idx = -1;
    for (int i = 0; i < p_count; i++) {
        if (products[i].product_id == target_id) {
            p_idx = i;
            break;
        }
    }

    if (p_idx == -1) {
        printf("Error: Product ID not found.\n");
        return;
    }

    printf("Product Found: %s. Current Stock: %d\n", products[p_idx].product_name, products[p_idx].quantity_in_stock);

    // 3. Get Quantity and validate stock
    printf("Enter Quantity to Sell: ");
    scanf("%d", &qty);
    clear_buffer();

    if (qty > products[p_idx].quantity_in_stock) {
        printf("Error: Insufficient stock!\n");
        return;
    }

    // 4. Get Customer info
    printf("Enter Customer Name: "); scanf("%[^\n]", customer); clear_buffer();
    printf("Enter Date (DD/MM/YYYY): "); scanf("%s", date); clear_buffer();

    // 5. Execute Logic: Decrease stock
    products[p_idx].quantity_in_stock -= qty;

    // 6. Execute Logic: Record Sale in Memory
    SaleRecord* s = &sales[*s_count];
    s->product_id = target_id;
    s->quantity_sold = qty;
    strcpy(s->customer_name, customer);
    strcpy(s->sale_date, date);
    (*s_count)++;

    // 7. Execute Logic: Save to Files
    AppendSaleToFile(s, SALES_FILE);
    SaveProducts(products, p_count, PRODUCTS_FILE);
    printf("Transaction completed successfully! Stock updated.\n");
}

/*
@function: Menu_SortProducts
@desc: Sorts the product array in ascending order of price using Bubble Sort.
@param: products[] - Array of products
@param: p_count - Number of products
@return: void
*/
void Menu_SortProducts(Product products[], int p_count) {
    // Standard Bubble Sort implementation
    for (int i = 0; i < p_count - 1; i++) {
        for (int j = 0; j < p_count - i - 1; j++) {
            if (products[j].price > products[j + 1].price) {
                // Swap entire product structure
                Product temp = products[j];
                products[j] = products[j + 1];
                products[j + 1] = temp;
            }
        }
    }
    printf("Products sorted by price.\n");
}

/*
@function: PrintSingleProduct
@desc: Helper function to print a single product row formatted in a table.
@param: p - Pointer to the product to print
@return: void
*/
void PrintSingleProduct(Product* p) {
    printf("\n%-5s %-30s %-15s %-10s %-8s %-10s %-15s\n", "ID", "Name", "Brand", "Price", "Stock", "Warranty", "Provider");
    printf("----------------------------------------------------------------------------------------------------------\n");
    printf("%-5d %-30s %-15s %-10.2f %-8d %-10d %-15s\n",
        p->product_id, p->product_name, p->brand, p->price, p->quantity_in_stock,
        p->warranty.warranty_months, p->warranty.provider);
    printf("----------------------------------------------------------------------------------------------------------\n");
}

/*
@function: Menu_PrintProducts
@desc: Iterates through the product array and prints all products in a table format.
@param: products[] - Array of products
@param: p_count - Number of products
@return: void
*/
void Menu_PrintProducts(Product products[], int p_count) {
    printf("\n%-5s %-30s %-15s %-10s %-8s %-10s %-15s\n", "ID", "Name", "Brand", "Price", "Stock", "Warranty", "Provider");
    printf("--------------------------------------------------------------------------\n");
    for (int i = 0; i < p_count; i++) {
        printf("%-5d %-30s %-15s %-10.2f %-8d %-10d %-15s\n",
            products[i].product_id, products[i].product_name, products[i].brand, products[i].price,
            products[i].quantity_in_stock, products[i].warranty.warranty_months, products[i].warranty.provider);
    }
    printf("\n");
}

/*
@function: Menu_RevenueReport
@desc: Calculates and prints total revenue for a specific year by merging sales with product data.
@param: products[] - Array of products
@param: p_count - Number of products
@param: sales[] - Array of sales
@param: s_count - Number of sales
@return: void
*/
void Menu_RevenueReport(Product products[], int p_count, SaleRecord sales[], int s_count) {
    float total_revenue = 0.0;
    int target_year = 2025; // Hardcoded target year as per assignment

    printf("\n--- Revenue Report (Year: %d) ---\n", target_year);
    printf("%-15s %-30s %-20s %-10s %-10s\n", "Date", "Product", "Customer", "Qty", "Revenue");

    // Loop through all sales records
    for (int i = 0; i < s_count; i++) {
        // Extract year from date string "DD/MM/YYYY" (offset +6)
        int sale_year = atoi(&sales[i].sale_date[6]);

        if (sale_year == target_year) {
            // Find corresponding product to get the price
            for (int j = 0; j < p_count; j++) {
                if (products[j].product_id == sales[i].product_id) {
                    float revenue = sales[i].quantity_sold * products[j].price;
                    total_revenue += revenue;
                    // Print individual record details
                    printf("%-15s %-30s %-20s %-10d $%-10.2f\n",
                        sales[i].sale_date, products[j].product_name, sales[i].customer_name,
                        sales[i].quantity_sold, revenue);
                    break;
                }
            }
        }
    }
    printf("------------------------------------------------------------\n");
    printf("Total Revenue: $%.2f\n", total_revenue);
}

/*
@function: Menu_MonthlyReport
@desc: Filters sales records for a user-specified month/year and exports them to a text file.
@param: products[] - Array of products
@param: p_count - Number of products
@param: sales[] - Array of sales
@param: s_count - Number of sales
@return: void
*/
void Menu_MonthlyReport(Product products[], int p_count, SaleRecord sales[], int s_count) {
    char target_month[10];
    char filename[50];
    char month_full[12][20] = {
        "January",   
        "February",  
        "March",    
        "April",    
        "May",     
        "June",    
        "July",      
        "August",   
        "September", 
        "October",   
        "November",  
        "December"   
    };

    printf("Enter Month/Year (MM/YYYY): ");
    scanf("%s", target_month);
    // int target_month = 10;

    int mo = (target_month[0] - '0') * 10 + target_month[1] - '0';
    int ye = atoi(&target_month[3]);
    // Create filename
    sprintf(filename, "%s_Sales_Report_2559321.txt", month_full[mo - 1]);
    for (int i = 0; filename[i]; i++) if (filename[i] == '/') filename[i] = '_';

    FILE* fp = fopen(filename, "w");
    if (!fp) {
        printf("Error creating file.\n");
        return;
    }

    fprintf(fp, "--- Monthly Sales Report: %s ---\n", target_month);
    fprintf(fp, "%-10s %-20s %-10s %-10s\n", "Date", "Product Name", "Qty Sold", "Price");

    int found = 0;
    for (int i = 0; i < s_count; i++) {
        // Use strstr to find the month substring in the date string
        if (strstr(sales[i].sale_date, target_month) != NULL) {
            char p_name[STR_LEN] = "Unknown";
            float p_price = 0.0;
            // Lookup product details
            for (int j = 0; j < p_count; j++) {
                if (products[j].product_id == sales[i].product_id) {
                    strcpy(p_name, products[j].product_name);
                    p_price = products[j].price;
                    break;
                }
            }
            // Write to file
            fprintf(fp, "%-10s %-20s %-10d $%-10.2f\n",
                sales[i].sale_date, p_name, sales[i].quantity_sold, p_price);
            found++;
        }
    }
    fclose(fp);
    printf("Report generated: %s (%d records found)\n", filename, found);
}

/* ================== File I/O Helpers ================== */

/*
@function: parse_csv_line_product
@desc: Parses a CSV formatted line into a Product structure.
@param: line - The CSV string
@param: p - Pointer to the Product structure to fill
@return: void
*/
void parse_csv_line_product(char* line, Product* p) {
    // Scanset used to handle quoted strings containing commas/spaces
    sscanf(line, "%d,\"%[^\"]\",\"%[^\"]\",%f,%d,%d,\"%[^\"]\"",
        &p->product_id, p->product_name, p->brand, &p->price,
        &p->quantity_in_stock, &p->warranty.warranty_months, p->warranty.provider);
}

/*
@function: parse_csv_line_sale
@desc: Parses a CSV formatted line into a SaleRecord structure.
@param: line - The CSV string
@param: s - Pointer to the SaleRecord structure to fill
@return: void
*/
void parse_csv_line_sale(char* line, SaleRecord* s) {
    char name_buf[STR_LEN], date_buf[15];
    sscanf(line, "%d,\"%[^\"]\",\"%[^\"]\",%d",
        &s->product_id, name_buf, date_buf, &s->quantity_sold);
    strcpy(s->customer_name, name_buf);
    strcpy(s->sale_date, date_buf);
}

/*
@function: LoadProducts
@desc: Reads product data from a file into the product array.
@param: products[] - Array to store products
@param: p_count - Pointer to update the count of loaded products
@param: filename - Name of the file to read
@return: int - 1 on success, 0 on failure
*/
int LoadProducts(Product products[], int* p_count, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) return 0;
    char line[256];
    *p_count = 0;
    while (fgets(line, sizeof(line), file) && *p_count < MAX_PRODUCTS) {
        if (strlen(line) < 5) continue; // Skip empty lines
        parse_csv_line_product(line, &products[*p_count]);
        (*p_count)++;
    }
    fclose(file);
    return 1;
}

/*
@function: LoadSalesData
@desc: Reads sales data from a file into the sales array.
@param: sales[] - Array to store sales records
@param: s_count - Pointer to update the count of loaded sales
@param: filename - Name of the file to read
@return: int - 1 on success, 0 on failure
*/
int LoadSalesData(SaleRecord sales[], int* s_count, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) return 0;
    char line[256];
    *s_count = 0;
    while (fgets(line, sizeof(line), file) && *s_count < MAX_SALES) {
        if (strlen(line) < 5) continue;
        parse_csv_line_sale(line, &sales[*s_count]);
        (*s_count)++;
    }
    fclose(file);
    return 1;
}

/*
@function: SaveProducts
@desc: Writes the entire product array back to the file to save changes (e.g., stock updates).
@param: products[] - Array of products
@param: p_count - Number of products
@param: filename - Name of the file to write to
@return: void
*/
void SaveProducts(Product products[], int p_count, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        printf("Error writing to product file.\n");
        return;
    }
    for (int i = 0; i < p_count; i++) {
        fprintf(file, "%d,\"%s\",\"%s\",%.2f,%d,%d,\"%s\"\n",
            products[i].product_id,
            products[i].product_name,
            products[i].brand,
            products[i].price,
            products[i].quantity_in_stock,
            products[i].warranty.warranty_months,
            products[i].warranty.provider);
    }
    fclose(file);
}

/*
@function: AppendSaleToFile
@desc: Appends a single new sale record to the end of the sales file.
@param: sale - Pointer to the sale record
@param: filename - Name of the file to append to
@return: void
*/
void AppendSaleToFile(SaleRecord* sale, const char* filename) {
    FILE* file = fopen(filename, "a"); // Open in append mode
    if (!file) {
        printf("Error appending to sales file.\n");
        return;
    }
    fprintf(file, "%d,\"%s\",\"%s\",%d\n",
        sale->product_id,
        sale->customer_name,
        sale->sale_date,
        sale->quantity_sold);
    fclose(file);
}