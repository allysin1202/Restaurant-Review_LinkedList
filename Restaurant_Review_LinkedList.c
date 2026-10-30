#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_STRING_LENGTH 1024

typedef struct restaurant_review
{
    char name[MAX_STRING_LENGTH];       // Restaurant's name
    char address[MAX_STRING_LENGTH];    // Restaurant's address
    int score;                          // Restaurant's score [1-5]
    float avg_cost;                     // Average cost of meal
    bool delivery;                      // Provide delivery service or not
} Review;

typedef struct Review_List_Node
{
    Review rev;
    struct Review_List_Node *next;
} Review_Node;

// Helper clean input buffer
void clear_input_buffer()
{
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF)
    {
    }
}

// Helper to remove new line when receive input
void remove_newline(char str[])
{
    str[strcspn(str, "\n")] = '\0';
}

// Helper
int read_integer()
{
    int value;
    int result;

    while(1)
    {
        result = scanf("%d", &value);
        clear_input_buffer();

        if(result == 1)
        {
            return value;
        }
        printf("Invalid input. Please enter an integer: \n");
    }
}

// Helper
void read_string(char str[], int size)
{
    if (fgets(str, size, stdin) != NULL)
    {
        remove_newline(str);
    }
}

// Helper
bool read_delivery()
{
    char ans;

    while (1)
    {
        printf("Does the restaurant provide delivery service? (Y/N)\n");

        if (scanf(" %c", &ans) != 1)
        {
            clear_input_buffer();
            continue;
        }

        clear_input_buffer();

        if (ans == 'Y' || ans == 'y')
        {
            return true;
        }

        if (ans == 'N' || ans == 'n')
        {
            return false;
        }

        printf("Invalid answer. Please enter Y or N.\n");
    }
}


// Calculate the average cost of meal
float calculate_avg_cost()
{
    float total_cost;
    int total_num;
    float cost;
    
    while (1)
    {
        total_cost = 0.0;
        total_num = 0;

        printf("Please enter the cost of meal (Enter 0 or negative number to finish): \n");

        while (1)
        {
            if (scanf("%f", &cost) != 1)
            {
                printf("Invalid input.\n");
                clear_input_buffer();
                continue;
            }

            clear_input_buffer();
            
            if (cost <= 0)
            {
                break;
            }
            
            total_cost += cost;
            total_num++;
            
            printf("Enter another cost (Enter 0 or negative number to finish): \n");

        }

        if (total_num > 0)
        {
            return total_cost / (float) total_num;
        }
        
        printf("Please enter at least one valid cost.\n");
    }
}

// Create a new list node
Review_Node *new_Review_Node()
{
    Review_Node *new_node = (Review_Node *)calloc(1, sizeof(Review_Node));

    if (new_node == NULL)
    {
        printf("new_Review_Node(): Error - There is no memory available, unable to reserve space.\n");
        return NULL;
    }

    strcpy(new_node -> rev.name, "");
    strcpy(new_node -> rev.address, "");
    new_node -> rev.score = -1;
    new_node -> rev.avg_cost = -1.0;
    new_node -> rev.delivery = false;

    new_node -> next = NULL;

    return new_node;
}

// Insert review at head
Review_Node *insert_at_head(Review_Node *head, Review_Node *new_node)
{
    if (new_node == NULL)
    {
        printf("insert_at_head(): Error - There is no new review.\n");
        return head;
    }

    new_node -> next = head;
    return new_node;
}

// Insert review at tail
Review_Node *insert_at_tail(Review_Node *head, Review_Node *new_node)
{
    if (new_node == NULL)
    {
        printf("insert_at_tail(): Error - There is no new review.\n");
        return head;
    }

    if (head == NULL)
    {
        head = new_node;
        return head;
    }

    Review_Node *p = head;

    while (p -> next != NULL)
    {
        p = p -> next;
    }

    p -> next = new_node;
    return head;
}

// Fill in new review info
Review_Node *new_review_info()
{
    Review_Node *new_review_node = new_Review_Node();
    char name[MAX_STRING_LENGTH];
    char address[MAX_STRING_LENGTH];
    int score = 0;
    
    if (new_review_node == NULL)
    {
        printf("main(): Error - There is no more memory, unable to create a new linked list node. \n");
        return NULL;
    }

    printf("Please enter the restaurant's name.\n");
    read_string(name, MAX_STRING_LENGTH);
    strcpy(new_review_node -> rev.name, name);

    printf("Please enter the restaurant's address.\n");
    read_string(address, MAX_STRING_LENGTH);
    strcpy(new_review_node -> rev.address, address);

    printf("Please enter the restaurant's score. (1-5)\n");
    while (score < 1 || score > 5)
    {
        score = read_integer();

        if (score < 1 || score > 5)
        {
            printf("Invalid score. Please input again.\n");
        }
    }
    new_review_node -> rev.score = score;

    new_review_node -> rev.avg_cost = calculate_avg_cost();

    new_review_node -> rev.delivery = read_delivery();

    return new_review_node;
}

// Update review info
void update_review(Review_Node *new_review_node, int update_choice)
{
    if (new_review_node == NULL)
    {
        printf("No review to update.\n");
        return;
    }

    if (update_choice == 1)          // Update name
    {
        char name[MAX_STRING_LENGTH];
        printf("Please enter the restaurant's name.\n");
        read_string(name, MAX_STRING_LENGTH);
        strcpy(new_review_node -> rev.name, name);
    }

    else if (update_choice == 2)     // Update address
    {
        char address[MAX_STRING_LENGTH];
        printf("Please enter the restaurant's address.\n");
        read_string(address, MAX_STRING_LENGTH);
        strcpy(new_review_node -> rev.address, address);
    }

    else if (update_choice == 3)     // Update Score
    {
        int score = 0;
        while (score < 1 || score > 5)
        {
            printf("Please enter a new score for the restaurant. (1-5)\n");
            score = read_integer();
        }
        new_review_node -> rev.score = score;
    }

    else if (update_choice == 4)     // Update cost of meal
    {
        new_review_node -> rev.avg_cost = calculate_avg_cost();
    }
                
    else if (update_choice == 5)     // Update delivery availibility
    {
        new_review_node -> rev.delivery = read_delivery();           
    }

}

// Print a single review
void print_review(Review_Node *node)
{
    if (node == NULL)
    {
        printf("print_review(): Error - There is no review to print.\n");
        return;
    }

    printf("Restaurant's name: %s\n", node -> rev.name);
    printf("Restaurant's address: %s\n", node -> rev.address);
    printf("Restaurant's score: %d\n", node -> rev.score);
    printf("Restaurant's avg cost: %.2f\n", node -> rev.avg_cost);
    
    if (node -> rev.delivery)
    {
        printf("Provide delivery service.\n");
    }
    else
    {
        printf("Do not provide delivery service.\n");
    }
    
    printf("\n");
}

// Print all reviews
void print_list(Review_Node *head)
{
    if (head == NULL)
    {
        printf("The list is empty!\n");
        return;
    }

    Review_Node *p = head;

    while (p != NULL)
    {
        print_review(p);
        p = p -> next;
    }

    printf("All reviews are printed. \n");
    return;
}

// Delete all reviews and release memory
void delete_list(Review_Node *head)
{
    Review_Node *p = head;
    Review_Node *q = NULL;

    while (p != NULL)
    {
        q = p -> next;
        free(p);
        p = q;
    }

    printf("Memory is released.\n");
    return;
}

// Search review by restaurant's name
Review_Node *search_by_name(Review_Node *head, char name[])
{
    if (head == NULL)
    {
        return NULL;
    }

    Review_Node *p = head;

    while (p != NULL)
    {
        if (strcmp(p -> rev.name, name) == 0)
        {
            return p;
        }
        p = p -> next;
    }

    return NULL;
}

// Search review by restaurant's address
Review_Node *search_by_address(Review_Node *head, char address[])
{
    if (head == NULL)
    {
        return NULL;
    }

    Review_Node *p = head;

    while (p != NULL)
    {
        if (strcmp(p -> rev.address, address) == 0)
        {
            return p;
        }
        p = p -> next;
    }

    return NULL;
}

// Search review by restaurant's score; once find, end
Review_Node *search_by_score(Review_Node *head, int score)
{
    if (head == NULL)
    {
        return NULL;
    }

    Review_Node *p = head;

    while (p != NULL)
    {
        if (p -> rev.score == score)
        {
            return p;
        }
        else
        {
            p = p -> next;
        }
    }
    
    return NULL;
}

// Search review by restaurant's cost; find within range, once find, end
Review_Node *search_by_cost(Review_Node *head, float min_cost, float max_cost)
{
    if (head == NULL)
    {
        return NULL;
    }

    Review_Node *p = head;

    while (p != NULL)
    {
        if (p -> rev.avg_cost >= min_cost && p -> rev.avg_cost <= max_cost)
        {
            return p;
        }
        else
        {
            p = p -> next;
        }
    }
    return NULL;
}

// Print reviews that is greater than or equal to the specified score
void print_by_score(Review_Node *head, int score)
{
    if (head == NULL)
    {
        printf("The list is empty!\n");
        return;
    }

    int found = 0;
    Review_Node *p = head;

    while (p != NULL)
    {
        if (p -> rev.score >= score)
        {
            print_review(p);
            found++;
        }

        p = p -> next;
    }

    if (found == 0)
    {
        printf("No restaurants are found with score >= %d.\n", score);
    }
    else
    {
        printf("%d restaurants are found with score >= %d.\n", found, score);
    }
    
    return;
}

// Print reviews that provide delivery service
void print_by_delivery(Review_Node *head)
{
    if (head == NULL)
    {
        printf("The list is empty!\n");
        return;
    }

    int found = 0;
    Review_Node *p = head;

    while (p != NULL)
    {
        if (p -> rev.delivery)
        {
            print_review(p);
            found++;
        }

        p = p -> next;
    }

    if (found == 0)
    {
        printf("No restaurants provide delivery services.\n");
    }
    else
    {
        printf("%d restaurants provide delivery services.\n", found);
    }
    
    return;
}

// Print reviews that is smaller than or equal to the specified cost of meal
void print_by_cost(Review_Node *head, float cost)
{
    if (head == NULL)
    {
        printf("The list is empty!\n");
        return;
    }

    int found = 0;
    Review_Node *p = head;

    while (p != NULL)
    {
        if (p -> rev.avg_cost <= cost)
        {
            print_review(p);
            found++;
        }

        p = p -> next;
    }

    if (found == 0)
    {
        printf("No restaurants are found with average cost <= %.2f.\n", cost);
    }
    else
    {
        printf("%d restaurants are found with average cost <= %.2f.\n", found, cost);
    }
}

// Print reviews that is in a specified range
void print_by_cost_range(Review_Node *head, float min_cost, float max_cost)
{
    if (head == NULL)
    {
        printf("The list is empty!\n");
        return;
    }

    int found = 0;
    Review_Node *p = head;

    while (p != NULL)
    {
        if (p -> rev.avg_cost >= min_cost && p -> rev.avg_cost <= max_cost)
        {
            print_review(p);
            found++;
        }

        p = p -> next;
    }

    if (found == 0)
    {
        printf("No restaurants are found with range %.2f to %.2f.\n", min_cost, max_cost);
    }
    else
    {
        printf("%d restaurants are found with range %.2f to %.2f.\n", found, min_cost, max_cost);
    }
}

// Delete restaurant review by name
Review_Node *delete_by_name(Review_Node *head, char name[])
{
    // Use one traversal pointer only, and instead of a predecessor pointer, it uses the next item pointer in the current node to look ahead for the node we want to delete.
    if (head == NULL)
    {
        printf("The list is empty!\n");
        return NULL;
    }

    Review_Node *p = head;
    Review_Node *q = NULL;

    // Delete head
    if (strcmp(p -> rev.name, name) == 0)
    {
        q = p -> next;
        free(p);
        return q;
    }

    while (p -> next != NULL)
    {
        // Delete in middle and tail
        if(strcmp(p -> next -> rev.name, name) == 0)
        {
            q = p -> next;
            p -> next = q -> next;
            free (q);
            break;
        }

        p = p -> next;
    }

    return head;
}

// Delete restaurant review by address
Review_Node *delete_by_address(Review_Node *head, char address[])
{
    // Use 2 traversal pointer
    if (head == NULL)
    {
        printf("The list is empty!\n");
        return NULL;
    }

    Review_Node *p = head;
    Review_Node *q = p -> next;

    // Delete head
    if (strcmp(p -> rev.address, address) == 0)
    {
        free(p);
        return q;
    }

    while (q != NULL)
    {
        // Delete in middle and tail
        if(strcmp(q -> rev.address, address) == 0)
        {
            p -> next = q -> next;
            free (q);
            break;
        }

        p = p -> next;
        q = q -> next;
    }

    return head;
}

// Delete restaurant review by score; once delete, end
Review_Node *delete_by_score(Review_Node *head, int score)
{
    // Use 2 traversal pointer

    if (head == NULL)
    {
        printf("The list is empty!\n");
        return NULL;
    }

    // Delete head
    if (head -> rev.score == score)
    {
        Review_Node *temp = head -> next;
        free(head);
        return temp;
    }

    Review_Node *p = head;

    // Delete in middle and tail
    while (p -> next != NULL)
    {
        if(p -> next -> rev.score == score)
        {
            Review_Node *q = p -> next;
            p -> next = q -> next;
            free (q);
            return head;
        }
        p = p -> next;
    }

    return head;
}

// Dequeue (Delete head of list)
Review_Node *dequeue(Review_Node *head)
{
    if (head == NULL)
    {
        printf("The list is empty!\n");
        return NULL;
    }

    Review_Node *p = head -> next;
    free (head);
    return p;
}

// Total number of reviews in list
int total_review(Review_Node *head)
{
    int total = 0;

    if (head == NULL)
    {
        return total;
    }
    
    Review_Node *p = NULL;
    p = head;
    
    while (p != NULL)
    {
        total++;
        p = p -> next;
    }

    return total;
}

// Total avg cost across all restaurants
float total_average_cost(Review_Node *head)
{
    if (head == NULL)
    {
        printf("The list is empty!\n");
        return -1.0;
    }

    int total_review = 0;
    float total_cost = 0.0;

    Review_Node *p = head;

    while (p != NULL)
    {
        if (p -> rev.avg_cost > 0)
        {
            total_cost += p -> rev.avg_cost;
            total_review++;
        }
        p = p -> next;
    }

    if (total_review == 0)
    {
        return -1.0;
    }

    return total_cost / (float) total_review;
}



void display_main_menu()
{
    printf("Please choose one of the following: \n");
    printf("1 - Add a new restaurant review\n");
    printf("2 - Print the existing reviews\n");
    printf("3 - Update an existing review\n");
    printf("4 - Delete an existing review\n");
    printf("5 - Exit this program\n");
    printf("\n");
}

Review_Node *display_add_menu(Review_Node *head)
{
    int new_choice = 0;

    printf("Where do you want to insert the review?\n");
    printf("1 - Insert at head\n");
    printf("2 - Insert at tail\n");
    printf("3 - Back to menu\n");
    
    while (new_choice < 1 || new_choice > 3)
    {
        new_choice = read_integer();
                
        if (new_choice < 1 || new_choice > 3)
        {
            printf("Invalid choice. Please input again.\n");
        }
    }

    if (new_choice == 3) // Back to menu
    {
        return head;
    }

    Review_Node *new_review_node = new_review_info();

    if (new_choice == 1)        // Insert at head
    {
        head = insert_at_head(head, new_review_node);
    }
    else if (new_choice == 2)   // Insert at tail
    {
        head = insert_at_tail(head, new_review_node);
    }
    return head;
}

void display_print_menu(Review_Node *head)
{
    int print_choice = 0;

    printf("Which restaurant do you want to print?\n");
    printf("1 - Print all existing reviews\n");
    printf("2 - Print reviews of specific score or higher\n");
    printf("3 - Print reviews of specific cost or lower\n");
    printf("4 - Print reviews of restaurant that provide delivery service\n");
    printf("5 - Back to menu\n");

    while (print_choice < 1 || print_choice > 5)
    {
        print_choice = read_integer();
            
        if (print_choice < 1 || print_choice > 5)
        {
            printf("Invalid choice. Please input again.\n");
        }
    }

    if (print_choice == 1)      // Print all reviews
    {
        print_list(head);
        printf("Total reviews: %d\n", total_review(head));
        printf("Total average cost: %.2f\n", total_average_cost(head));
    }

    else if (print_choice == 2) // Print review by score
    {
        int print_score = 0;
        printf("Please enter the score.\n");

        while (print_score < 1 || print_score > 5)
        {
            print_score = read_integer();

            if (print_score < 1 || print_score > 5)
            {
                printf("Invalid score. Please input again.\n");
            }
        }

        print_by_score(head, print_score);
    }

    else if (print_choice == 3) // Print review by cost
    {
        float print_cost = 0.0;
        while (1)
        {   
            printf("Please enter the cost.\n");
            if (scanf("%f", &print_cost) != 1)
            {
                printf("Invalid input. Please input again.\n");
                clear_input_buffer();
                continue;
            }

            clear_input_buffer();

            if (print_cost <= 0.0)
            {
                printf("Invalid cost. Please input again.\n");
                continue;
            }
            break;
        }
        
        print_by_cost(head, print_cost);
    }

    else if (print_choice == 4) // Print review by delivery
    {
        print_by_delivery(head);
    }

    else if (print_choice == 5) // Back to menu
    {
        return;
    }

}

void display_update_menu(Review_Node *head)
{
    int search_choice = 0;
    int update_choice = 0;

    printf("Which restaurant do you want to update?\n");
    printf("1 - Search by name\n");
    printf("2 - Search by address\n");
    printf("3 - Back to menu\n");

    while (search_choice < 1 || search_choice > 3)
    {
        search_choice = read_integer();

        if (search_choice < 1 || search_choice > 3)
        {
            printf("Invalid choice. Please input again.\n");
        }

    }

    if (search_choice == 3)         // Back to menu
    {
        return;
    }

    Review_Node *node = NULL;

    if (search_choice == 1)    // Search by name
    {
        char name[MAX_STRING_LENGTH];
        printf("Please enter the restaurant's name.\n");
        read_string(name, MAX_STRING_LENGTH);
        node = search_by_name(head, name);
    }

    else if (search_choice == 2)    // Search by address
    {
        char address[MAX_STRING_LENGTH];
        printf("Please enter the restaurant's address.\n");
        read_string(address, MAX_STRING_LENGTH);
        node = search_by_address(head, address);
    }

    if (node == NULL)
    {
        printf("Sorry, the restaurant is not in the list. Please check if there were any typo or use option 1 to create a new review.\n");
        return;
    }

    printf("Review Info: \n");
    print_review(node);

    printf("What content do you want to update?\n");
    printf("1 - Name\n");
    printf("2 - Address\n");
    printf("3 - Score\n");
    printf("4 - Average cost of meal\n");
    printf("5 - Delivery availibility\n");
    printf("6 - Back to menu\n");
        
    while (update_choice < 1 || update_choice > 6)
    {
        update_choice = read_integer();
                    
        if (update_choice < 1 || update_choice > 6)
        {
            printf("Invalid choice. Please input again.\n");
        }
    }

    if (update_choice == 6)     // Back to menu
    {
        return;
    }

    update_review(node, update_choice);
    return;
}

Review_Node *display_delete_menu(Review_Node *head)
{
    int delete_choice = 0;

    printf("Which restaurant do you want to delete?\n");
    printf("1 - Delete by name\n");
    printf("2 - Delete by address\n");
    printf("3 - Delete reviews with specific score\n");
    printf("4 - Back to menu\n");
            
    while (delete_choice < 1 || delete_choice > 4)
    {
        delete_choice = read_integer();

        if (delete_choice < 1 || delete_choice > 4)
        {
            printf("Invalid choice. Please input again.\n");
        }
    }

    if (delete_choice == 4)         // Back to menu
    {
        return head;
    }

    Review_Node *node = NULL;
    
    if (delete_choice == 1)    // Delete by name
    {
        char name[MAX_STRING_LENGTH];
        printf("Please enter the restaurant's name.\n");
        read_string(name, MAX_STRING_LENGTH);
        node = search_by_name(head, name);
        
        if (node == NULL)
        {
            printf("Sorry, the restaurant is not in the list. Please check if there were any typo or use option 1 to create a new review.\n");
            return head;
        }
        
        head = delete_by_name(head, name);
        printf("Review deleted successfully.\n");
        
    }

    else if (delete_choice == 2)    // Delete by address
    {
        char address[MAX_STRING_LENGTH];
        printf("Please enter the restaurant's address.\n");
        read_string(address, MAX_STRING_LENGTH);
        node = search_by_address(head, address);

        if (node == NULL)
        {
            printf("Sorry, the restaurant is not in the list. Please check if there were any typo or use option 1 to create a new review.\n");
            return head;
        }

        head = delete_by_address(head, address);
        printf("Review deleted successfully.\n");
            
    }

    else if (delete_choice == 3)    // Delete by score
    {
        int delete_score = 0;
        while (delete_score < 1 || delete_score > 5)
        {
            printf("Which specific score do you want to delete?\n");
            delete_score = read_integer();
        }
                
        while (search_by_score(head, delete_score)!= NULL)
        {
            head = delete_by_score(head, delete_score);
        }

        printf("Reviews with score %d are deleted!\n", delete_score);
    }
    return head;
}



int main()
{
    Review_Node *head = NULL;

    int choice = 0;

    while (choice != 5)
    {
        display_main_menu();
        choice = read_integer();

        if (choice == 1)        // Add new review
        {
            head = display_add_menu(head);
        }
        
        else if (choice == 2)   // Print reviews
        {
            display_print_menu(head);
        }
        
        else if (choice == 3)   // Update review
        {
            display_update_menu(head);
        }

        else if (choice == 4)   // Delete review
        {
            head = display_delete_menu(head);
        }

        else if (choice == 5)   // Release memory and exit program
        {
            delete_list(head);
            head = NULL;
        }

        else
        {
            printf("Invalid choice. Please input again.\n");
        }
        printf("\n");
    }

    return 0;
}
